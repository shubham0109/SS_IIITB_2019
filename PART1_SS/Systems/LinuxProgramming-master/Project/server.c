#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ERR_EXIT(msg) do{perror(msg);/*pthread_exit(NULL);*/}while(0)
#define _ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

#define INDIVIDUAL "./db/individual_acct_det.db"
#define JOINT "./db/joint_acct_det.db"

#define PASS_LENGTH 20

struct individual_account
{
	int account_number;
	char name[100];
	char password[PASS_LENGTH];
	unsigned int amount;
};

struct joint_account
{
	int account_number;
	char name1[100];
	char name2[100];
	char password[PASS_LENGTH];
	unsigned int amount;
};

// authenticate the account number and password 
// return 0 for success full
// for joint else return -1 for invalid
short authenticate(int account_number, char *password, int account_type)
{
	int fd;
	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR; // 0600
	if (account_type == 1)
	{
		struct individual_account iad;
		if((fd = open(INDIVIDUAL, flags, mode)) == -1) ERR_EXIT("open()");
		if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
			ERR_EXIT("authenticate() -> lseek()");
		if(read(fd, &iad, sizeof(iad)) == -1)
			ERR_EXIT("authenticate() -> read()");
		if(iad.account_number == account_number)
			if(strcmp(iad.password, password) == 0) 
			{
				close(fd);
				return 0;
			}
	}
	else if(account_type = 2)
	{
		struct joint_account jad;
		if((fd = open(JOINT, flags, mode)) == -1) ERR_EXIT("open()");
			struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = (account_number - 1) * sizeof(jad);
		lock.l_len = sizeof(jad);
		lock.l_pid = getpid();
		if(fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("authenticate() -> fcntl(SETLKW)");

		if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
			ERR_EXIT("authenticate() -> lseek()");
		if(read(fd, &jad, sizeof(jad)) == -1)
			ERR_EXIT("authenticate() -> read()");
			// Unlock
		lock.l_type = F_UNLCK;
		if(fcntl(fd, F_SETLKW, &lock) == -1)
			ERR_EXIT("authenticate() -> fcntl()");
		if(jad.account_number == account_number)
		{
			if(strcmp(jad.password, password) == 0)
			{
				close(fd);
				return 0;
			}
		}
	}
	else if(account_type == 3) //admin
	{
	}
	return -1;
}

int create_individual_account(int conn_fd)
{
	char password[PASS_LENGTH];
	char user[100];
	ssize_t count_user, count_pass;
	int errorcode = -1;
	if((count_user = read(conn_fd, user, sizeof(user))) == -1)
		ERR_EXIT("create_individual_account() -> read()");
	user[count_user] = '\0';
	if((count_pass = read(conn_fd, password, sizeof(password))) == -1)
		ERR_EXIT("create_individual_account() -> read()");
	if(count_pass < 5)
		if(write(conn_fd, &errorcode, sizeof(int)) == -1)
			ERR_EXIT("create_individual_account() -> write()");
	password[count_pass] = '\0';
	struct individual_account iad;
	for (int i = 0; i <= count_user; ++i)
		iad.name[i] = user[i];
	for (int i = 0; i <= count_pass; ++i)
		iad.password[i] = password[i];
	iad.amount = 0;
	iad.account_number = 1;
	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR; // 0600
	int fd = open(INDIVIDUAL, flags, mode);
	if(fd == -1) ERR_EXIT("create_individual_account() -> open()");
	else
	{
		off_t offset = 0;
		if((offset = lseek(fd, (off_t)0, SEEK_END)) == (off_t)-1 ) ERR_EXIT("lseek()");
		if (offset == 0) // file was empty
		{
			iad.account_number = 1; // initial account
			if(write(fd, &iad, sizeof(iad)) == -1) ERR_EXIT("write()");
		}
		else
		{
			struct individual_account temp;
			offset = -sizeof(iad);
			if(lseek(fd, offset, SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
			if(read(fd, &temp, sizeof(temp)) == -1) ERR_EXIT("read()");
			iad.account_number = temp.account_number + 1;
	    	if(lseek(fd, (off_t)0, SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
	    	if(write(fd, &iad, sizeof(iad)) == -1) ERR_EXIT("write()");
	    }
	}
	if(close(fd) == -1) ERR_EXIT("close()");
	return iad.account_number;
}

int create_joint_account(int conn_fd)
{
	char user1[100];
	char user2[100];
	char password[PASS_LENGTH];
	int errorcode = -1;
	ssize_t count_user1, count_user2, count_pass;
	if((count_user1 = read(conn_fd, user1, sizeof(user1))) == -1)
		ERR_EXIT("read()");
	user1[count_user1] = '\0';
	if((count_user2 = read(conn_fd, user2, sizeof(user2))) == -1)
		ERR_EXIT("read()");
	user2[count_user2] = '\0';
	if((count_pass = read(conn_fd, password, sizeof(password))) == -1)
		ERR_EXIT("read()");
	if(count_pass < 5)
		if(write(conn_fd, &errorcode, sizeof(int)) == -1)
			ERR_EXIT("write()");
	password[count_pass] = '\0';
	struct joint_account jad;
	for (int i = 0; i <= count_user1; ++i)
		jad.name1[i] = user1[i];
	for (int i = 0; i <= count_user2; ++i)
		jad.name2[i] = user2[i];
	for (int i = 0; i <= count_pass; ++i)
		jad.password[i] = password[i];
	jad.amount = 0;
	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR; // 0600
	// write locking
	int fd = open(JOINT, flags, mode);
	if(fd == -1) ERR_EXIT("read()");
	else
	{
		off_t offset = 0;
		if((offset = lseek(fd, (off_t)0, SEEK_END)) == (off_t)-1 ) ERR_EXIT("lseek()");
		if (offset == 0) // file was empty
		{
			jad.account_number = 1; // initial account
			if(write(fd, &jad, sizeof(jad)) == -1) ERR_EXIT("write()");
		}
		else
		{
			struct individual_account temp;
			offset = -sizeof(jad);
			if(lseek(fd, offset, SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
			if(read(fd, &temp, sizeof(temp)) == -1) ERR_EXIT("read()");
			jad.account_number = temp.account_number + 1;
	    	if(lseek(fd, (off_t)0, SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
	    	if(write(fd, &jad, sizeof(jad)) == -1) ERR_EXIT("write()");
	    }
	}
	if(close(fd) == -1) ERR_EXIT("close()");
	return jad.account_number;
}

void deposit_individual(int amount, int account_number, int conn_fd)
{
	// do amount checking on client
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret_val = 0;
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, flags, mode)) == -1)
		ERR_EXIT("deposit_individual() -> open()");
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("deposit_individual() -> lseek()");
	if(read(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("deposit_individual() -> read()");
	iad.amount += amount; //adding amount to account
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("deposit_individual() -> lseek()");
	if(write(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("deposit_individual() -> write()");
	close(fd);
	if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
		ERR_EXIT("deposit_individual() -> write()");
}

void deposit_joint(int amount, int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret_val = 0;
	struct joint_account jad;	
	if((fd = open(JOINT, flags, mode)) == -1)
		ERR_EXIT("deposit_joint() -> open()");
	// locking advisory file locking on record of the account
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (account_number - 1) * sizeof(jad);
	lock.l_len = sizeof(jad);
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("deposit_joint() -> fcntl(SETLKW)");
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("deposit_joint() -> lseek()");
	if(read(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("deposit_joint() -> read()");
	jad.amount += amount; //adding amount to account
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("deposit_joint() -> lseek()");
	if(write(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("deposit_joint() -> write()");
	if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
		ERR_EXIT("deposit_joint() -> write()");
	// Unlock
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("deposit_joint() -> fcntl()");
	close(fd);
}

void withdrawl_individual(int amount, int account_number, int conn_fd)
{
	// do amount checking on client
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret_val = -1; //0 success -1 insufficient funds
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, flags, mode)) == -1)
		ERR_EXIT("withdrawl_individual() -> open()");
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("withdrawl_individual() -> lseek()");
	if(read(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("withdrawl_individual() -> read()");
	if (amount > iad.amount)
	{
		// insufficient funds
		ret_val = -2;
		ret_val = htonl(ret_val);
		if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
			ERR_EXIT("withdrawl_individual() -> write()");
		return;
		// pthread_exit(NULL);
	}
	iad.amount -= amount; //adding amount to account
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("withdrawl_individual() -> lseek()");
	if(write(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("withdrawl_individual() -> write()");
	ret_val = 0; // success
	ret_val = htonl(ret_val);
	if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
		ERR_EXIT("withdrawl_individual() -> write()");
	close(fd);
}

void withdrawl_joint(int amount, int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret_val = -2;
	struct joint_account jad;	
	if((fd = open(JOINT, flags, mode)) == -1)
		ERR_EXIT("withdrawl_joint() -> open()");
	// locking advisory file locking on record of the account
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (account_number - 1) * sizeof(jad);
	lock.l_len = sizeof(jad);
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("withdrawl_joint() -> fcntl(SETLKW)");
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("withdrawl_joint() -> lseek()");
	if(read(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("withdrawl_joint() -> read()");
	if (amount > jad.amount)
	{
		// insufficient funds
		ret_val = htonl(ret_val);
		if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
			ERR_EXIT("withdrawl_joint() -> write()");
		return;
		// pthread_exit(NULL);
	}
	jad.amount -= amount; //adding amount to account
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("withdrawl_joint() -> lseek()");
	if(write(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("withdrawl_joint() -> write()");
	ret_val = 0;
	ret_val = htonl(ret_val);
	if(write(conn_fd, &ret_val, sizeof(ret_val)) == -1)
		ERR_EXIT("withdrawl_joint() -> write()");
	// Unlock
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("withdrawl_joint() -> fcntl()");
	close(fd);
}

void send_details_individual(int account_number, int conn_fd)
{
	// search for detail
	// send details after searching to connection fd in buffer
	int fd;
	int flags = O_RDONLY;
	int mode = 0; //ignore mode
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, flags, mode)) == -1)
		ERR_EXIT("send_details_individual() -> open()");
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("send_details_individual() -> lseek()");
	if(read(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("send_details_individual() -> read()");
	close(fd);
	char details[1024];
	memset(details, 0, 1024);
	sprintf(details, "Account Number: %d\nName: %s\nPassword: %s\nBalance: %d\n", iad.account_number, iad.name, iad.password, iad.amount);
	if(write(conn_fd, details, sizeof(details)) == -1)
		ERR_EXIT("send_details_individual() -> write()");
}

void send_details_joint(int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDONLY;
	int mode = 0;
	struct joint_account jad;	
	if((fd = open(JOINT, flags, mode)) == -1)
		ERR_EXIT("send_details_joint() -> open()");
	// locking advisory file locking on record of the account
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (account_number - 1) * sizeof(jad);
	lock.l_len = sizeof(jad);
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("send_details_joint() -> fcntl(SETLKW)");
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("send_details_joint() -> lseek()");
	if(read(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("send_details_joint() -> read()");
	char details[1024];
	memset(details, 0, 1024);
	sprintf(details, "Account Number: %d\nName 1: %s\nName 2: %s\nPassword: %s\nBalance: %d\n", jad.account_number, jad.name1, jad.name2, jad.password, jad.amount);
	if(write(conn_fd, details, sizeof(details)) == -1)
		ERR_EXIT("send_details_joint() -> write()");
	// Unlock
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("send_details_joint() -> fcntl()");
	close(fd);
}

void send_account_balance_individual(int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDONLY;
	int mode = 0; //ignore mode
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, flags, mode)) == -1)
		ERR_EXIT("send_account_balance_individual() -> open()");
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("send_account_balance_individual() -> lseek()");
	if(read(fd, &iad, sizeof(iad)) == -1)
		ERR_EXIT("send_account_balance_individual() -> read()");
	close(fd);
	iad.amount = htonl(iad.amount);
	if(write(conn_fd, &(iad.amount), sizeof(int)) == -1)
		ERR_EXIT("send_account_balance_individual() -> write()");	
}

void send_account_balance_joint(int account_number, int conn_fd)
{

	int fd;
	int flags = O_RDONLY;
	int mode = 0;
	struct joint_account jad;	
	if((fd = open(JOINT, flags, mode)) == -1)
		ERR_EXIT("send_account_balance_joint() -> open()");
	// locking advisory file locking on record of the account
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (account_number - 1) * sizeof(jad);
	lock.l_len = sizeof(jad);
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("send_account_balance_joint() -> fcntl(SETLKW)");
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
		ERR_EXIT("send_account_balance_joint() -> lseek()");
	if(read(fd, &jad, sizeof(jad)) == -1)
		ERR_EXIT("send_account_balance_joint() -> read()");
	jad.amount = htonl(jad.amount);
	if(write(conn_fd, &(jad.amount), sizeof(int)) == -1)
		ERR_EXIT("send_account_balance_joint() -> write()");
	// Unlock
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("send_account_balance_joint() -> fcntl()");
	close(fd);
}

void change_password_individual(int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret = 0;
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, flags, mode)) == -1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> open()");
	}
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> lseek()");
	}
	if(read(fd, &iad, sizeof(iad)) == -1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> read()");
	}
	//get password string
	char password[PASS_LENGTH];
	memset(password, 0, sizeof(password));
	if(read(conn_fd, password, sizeof(password)) == -1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> read() 1");
	}
	strcpy(iad.password, password);
	if((lseek(fd, (account_number - 1) * sizeof(iad), SEEK_SET)) == (off_t)-1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> lseek() 1");
	}
	if(write(fd, &iad, sizeof(iad)) == -1)
	{
		ret = -1;
		ERR_EXIT("change_password_individual() -> write()");
	}
	ret = htonl(ret);
	if (write(conn_fd, &ret, sizeof(int)) == -1)
	{
		ERR_EXIT("change_password_individual() -> write() 1");
	}
	close(fd);
}

void change_password_joint(int account_number, int conn_fd)
{
	int fd;
	int flags = O_RDWR;
	int mode = 0; //ignore mode
	int ret = 0;
	struct joint_account jad;	
	if((fd = open(JOINT, flags, mode)) == -1)
		ERR_EXIT("withdrawl_joint() -> open()");
	// locking advisory file locking on record of the account
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (account_number - 1) * sizeof(jad);
	lock.l_len = sizeof(jad);
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
	{
		ret = -1;
		ERR_EXIT("withdrawl_joint() -> fcntl(SETLKW)");
	}
	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
	{
		ret = -1;
		ERR_EXIT("withdrawl_joint() -> lseek()");
	}
	if(read(fd, &jad, sizeof(jad)) == -1)
	{
		ret = -1;
		ERR_EXIT("withdrawl_joint() -> read()");
	}
	
	//get password string
	char password[PASS_LENGTH];
	memset(password, 0, sizeof(password));
	if(read(conn_fd, password, sizeof(password)) == -1)
	{
		ret = -1;
		ERR_EXIT("read()");
	}
	strcpy(jad.password, password);

	if((lseek(fd, (account_number - 1) * sizeof(jad), SEEK_SET)) == (off_t)-1)
	{
		ret = -1;
		ERR_EXIT("withdrawl_joint() -> lseek()");
	}
	if(write(fd, &jad, sizeof(jad)) == -1)
	{
		ret = -1;
		ERR_EXIT("withdrawl_joint() -> write()");
	}
	if(write(conn_fd, &ret, sizeof(int)) == -1)
		ERR_EXIT("withdrawl_joint() -> write()");
	// Unlock
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("withdrawl_joint() -> fcntl()");
	close(fd);
}

void print_all_details()
{
	int fd;
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, O_RDONLY | O_CREAT, 0600)) == -1) ERR_EXIT("open()");
	ssize_t count = 1;
	printf("=================================\n");
	while(1) 
	{
		if((count = read(fd, &iad, sizeof(iad))) == -1)
			ERR_EXIT("read()");
		if(count == 0) break;
		printf("account_number: %d\n", iad.account_number);
		printf("Name: %s == >", iad.name); printf("%ld\n", strlen(iad.name));
		printf("Password: %s == >", iad.password); printf("%ld\n", strlen(iad.password));
		printf("amount: %d\n", iad.amount);
	}
	printf("================================\n");
	close(fd);
	struct joint_account jad;
	if((fd = open(JOINT, O_RDONLY | O_CREAT, 0600)) == -1) ERR_EXIT("open()");
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("authenticate() -> fcntl(SETLKW)");
	printf("=================================\n");
	while(1) 
	{
		if((count = read(fd, &jad, sizeof(jad))) == -1)
			ERR_EXIT("read()");
		if(count == 0) break;
		printf("account_number: %d\n", jad.account_number);
		printf("Name 1: %s == >", jad.name1); printf("%ld\n", strlen(jad.name1));
		printf("Name 2: %s == >", jad.name2); printf("%ld\n", strlen(jad.name2));
		printf("Password: %s == >", jad.password); printf("%ld\n", strlen(jad.password));
		printf("amount: %d\n", jad.amount);
	}
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock) == -1)
		ERR_EXIT("authenticate() -> fcntl()");
	printf("================================\n");
	close(fd);
}

void menu(int conn_fd, int account_type, int account_number)
{
	int option;
	while(1)
	{
		if(read(conn_fd, &option, sizeof(int)) == -1) ERR_EXIT("read()");
		option = ntohl(option);
		int amount;
		switch(option)
		{
			case 1:
				if(read(conn_fd, &amount, sizeof(int)) == -1) ERR_EXIT("read()");
				amount = ntohl(amount);
				account_type == 1 ? deposit_individual(amount, account_number, conn_fd) :
					deposit_joint(amount, account_number, conn_fd);
				break;
			case 2:
				if(read(conn_fd, &amount, sizeof(int)) == -1) ERR_EXIT("read()");
				amount = ntohl(amount);
				account_type == 1 ? withdrawl_individual(amount, account_number, conn_fd) :
					withdrawl_joint(amount, account_number, conn_fd);
				break;
			case 3:
				account_type == 1 ? send_details_individual(account_number, conn_fd) :
					send_details_joint(account_number, conn_fd);
				break;
			case 4:
				account_type == 1 ? send_account_balance_individual(account_number, conn_fd) :
					send_account_balance_joint(account_number, conn_fd);
				break;
			case 5:
				account_type == 1 ? change_password_individual(account_number, conn_fd) :
					change_password_joint(account_number, conn_fd);
				break;
			default:
				// menu(conn_fd, account_type, account_number);
				pthread_exit(NULL);
		}
	}
}

void service_request(int *connection)
{
// print_all_details();
	int conn_fd = *connection;
	while(1)
	{
		int option;
		if(read(conn_fd, &option, sizeof(option)) == -1) ERR_EXIT("read()");
		option = ntohl(option);
		if(option == 1)
		{//sign in
			int account_number;
			char password[PASS_LENGTH];
			int account_type=0;
			ssize_t count;
			if(read(conn_fd, &account_type, sizeof(account_type)) == -1)
				ERR_EXIT("read()");
			account_type = ntohl(account_type);
			if(read(conn_fd, &account_number, sizeof(account_number)) == -1)
				ERR_EXIT("read()");
			account_number = ntohl(account_number);
			if((count = read(conn_fd, password, sizeof(password))) == -1)
				ERR_EXIT("read()");
			int ret = authenticate(account_number, password, account_type);
			ret = htonl(ret);
			if(write(conn_fd, &ret, sizeof(ret)) == -1) ERR_EXIT("write()");

			if(ret == 0) menu(conn_fd, account_type, account_number);
		}
		else if(option == 2)
		{
			int account_type;
			if(read(conn_fd, &account_type, sizeof(account_type)) == -1)
				ERR_EXIT("read()");
			account_type = ntohl(account_type);
			int account_number;
			if (account_type == 1) 
			{
				account_number = create_individual_account(conn_fd);
				account_number = htonl(account_number);
				if(write(conn_fd, &account_number, sizeof(int)) == -1)
					ERR_EXIT("write()");
			}
			else
			{
				account_number = create_joint_account(conn_fd);
				account_number = htonl(account_number);
				if(write(conn_fd, &account_number, sizeof(int)) == -1)
					ERR_EXIT("write()");
			}
		}
		else
		{
			if(close(conn_fd) == -1) ERR_EXIT("close()");
			pthread_exit(NULL);
		}
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <port_number>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int socket_fd, conn_fd;
	struct sockaddr_in serv_addr;
	
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		_ERR_EXIT("socket()");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		_ERR_EXIT("bind()");
	
	if(listen(socket_fd, 10) == -1)
		_ERR_EXIT("listen()");

	while(1)
	{
		if((conn_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1)
			_ERR_EXIT("accept()");
		pthread_t th;
		if(pthread_create(&th, NULL, (void*)service_request, (void*)&conn_fd) != 0)
			_ERR_EXIT("pthread_create()");
	}
	close(socket_fd);
}
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

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

#define INDIVIDUAL "individual_acct_det.db"
#define JOINT "joint_acct_det.db"

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
	printf("account_type: ==> %d\n", account_type);
	if (account_type == 1)
	{
		struct individual_account iad;
		if((fd = open(INDIVIDUAL, flags, mode)) == -1) ERR_EXIT("open()");
		int ret_val;
		ssize_t count = 1;
		while(1) 
		{
			if((count = read(fd, &iad, sizeof(iad))) == -1)
				ERR_EXIT("read()");
			else if(count == 0) //EOF
				return -1;
			printf("Matching with: %s", iad.name);
			if(iad.account_number == account_number)
			{
				printf("and password: %s", iad.password);
				if(strcmp(iad.password, password) == 0) return 0;
			}
			printf("\n");
		}
	}
	else
	{
		struct joint_account jad;
		if((fd = open(JOINT, flags, mode)) == -1) ERR_EXIT("open()");
		ssize_t count;
		while(1) 
		{
			if((count = read(fd, &jad, sizeof(jad))) == -1)
				ERR_EXIT("read()");
			else if(count == 0) //EOF
				return -1;
			if(jad.account_number == account_number)
			{
				if(strcmp(jad.password, password) == 0) return 0;
			}
		}	
	}
}


void print_all_details()
{
	int fd;
	struct individual_account iad;
	if((fd = open(INDIVIDUAL, O_RDONLY, 0)) == -1) ERR_EXIT("open()");
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
		printf("_____________________________\n");
	}
	printf("================================\n");
	close(fd);
}

int create_individual_account()
{
	char password[PASS_LENGTH];
	char user[100];
	ssize_t count_user, count_pass;
printf("Enter details.Name: \n");
	if((count_user = read(0, user, sizeof(user))) == -1)
		ERR_EXIT("read()");
	user[count_user-1] = '\0';
printf("Name: %s\n", user);
	if((count_pass = read(0, password, sizeof(password))) == -1)
		ERR_EXIT("read()");
	password[count_pass-1] = '\0';
printf("Password: %s\n", password);
	if(count_pass < 5)
	{
		printf("Please enter more thans 5 char for password\n");
		return 1;
	}
	struct individual_account iad;
	for (int i = 0; i < count_user; ++i)
		iad.name[i] = user[i];
	for (int i = 0; i < count_pass; ++i)
		iad.password[i] = password[i];
	iad.amount = 0;
	iad.account_number = -1;

	int flags = O_RDWR | O_CREAT;
	int mode = S_IRUSR | S_IWUSR; // 0600
	
	int fd = open(INDIVIDUAL, flags, mode);
	if(fd == -1) ERR_EXIT("read()");
	else
	{
		off_t offset = 0;
		if((offset = lseek(fd, (off_t)0, SEEK_END)) == (off_t)-1 ) ERR_EXIT("lseek()");
		if (offset == 0)
		{
			iad.account_number = 1;
			if(write(fd, &iad, sizeof(iad)) == -1) ERR_EXIT("write()");
		}
		else
		{
			struct individual_account temp;
		printf("Offset before: %ld\n", offset);
			offset -= sizeof(iad);
			if(lseek(fd, (off_t)-(sizeof(iad)), SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
			if(read(fd, &temp, sizeof(temp)) == -1) ERR_EXIT("read()");
		printf("Temp account_number: %d\n", temp.account_number);
		printf("temp name: %s\n", temp.name);
			iad.account_number = temp.account_number + 1;
	    	if(lseek(fd, (off_t)0, SEEK_END) == (off_t)-1 ) ERR_EXIT("lseek()");
	    	if(write(fd, &iad, sizeof(iad)) == -1) ERR_EXIT("write()");
	    }
	}
	if(close(fd) == -1) ERR_EXIT("close()");
	return iad.account_number;
}



int main(int argc, char const *argv[])
{
	int account_number;
	char* password;
	int account_type;
	int choice = 0;
	while(choice == 0)
	{
		printf("New account_number: %d\n", create_individual_account());
		printf("continue? \n");
		scanf("%d", &choice);
	}
	print_all_details();
	printf("Enter account_number: ");
	scanf("%d", &account_number);
	printf("Enter account_type: ");
	scanf("%d", &account_type);
	printf("Enter password: ");
	scanf("%s", password);
	printf("Entered details-- account_number: %d, account_type: %d, password: %s\n", account_number, account_number, password);
	printf("Return: %d\n", authenticate(account_number, password, account_type));
	return 0;
}
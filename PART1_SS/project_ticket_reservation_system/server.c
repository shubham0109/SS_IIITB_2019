
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define PORT 8100
#define PASS_LENGTH 30
#define TRAIN "train"
#define BOOKING "booking"



struct account{
	int id;                       // unique id for each account
	char name[10];
	char pass[PASS_LENGTH];
};

struct train{
	int tid;                  // unique id for each train
	char train_name[20];
	int train_no;
	int av_seats;
	int last_seatno_used;
};

struct bookings{
	int bid;                // unique id for each booking
	int type;
	int acc_no;
	int tr_id;
	char trainname[20];
	int seat_start;
	int seat_end;
	int cancelled;
};

// the database files
char *Account[3] = {"customer", "agent", "admin"};

void service_client(int sock_fd);
int login(int sock_fd);
int signup(int sock_fd);
int admin_menu(int sock_fd, int id);
int user_menu(int sock_fd, int id, int type);
void view_booking(int sock_fd, int id, int type);
void server_handler(int sig);


int main(int argc, char** argv){
	
    
    /*if (argc >= 2){
        PORT = atoi(argv[1]);
    }*/
    
    // interrupt handlers
    
	//signal(SIGTSTP, server_handler);
	//signal(SIGINT, server_handler);
	signal(SIGQUIT, server_handler);
	
    
    // create the socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd==-1) {
		printf("socket creation failed\n");
		exit(0);
	}
    
    // set the option values
	int optval = 1;
	int optlen = sizeof(optval);
	if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, optlen)==-1){
		printf("set socket options failed\n");
		exit(0);
	}
    
    // socket address
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(PORT);

    // bind the address to the socket
	if(bind(sock_fd, (struct sockaddr *)&sa, sizeof(sa))==-1){
		printf("binding port failed\n");
		exit(0);
	}
    
    // listen for clints, backlog = 100
	if(listen(sock_fd, 100)==-1){
		printf("listen failed\n");
		exit(0);
	}
    
	while(1){
        
		int connectedfd;
		
        if((connectedfd = accept(sock_fd, (struct sockaddr *)NULL, NULL))==-1){
			printf("connection error\n");
			exit(0);
		}
		
        if(fork()==0){
            // child process
            service_client(connectedfd);
        }
            
			
	}

	close(sock_fd);
	return 0;
}

void service_client(int sock_fd){
	int func_id;
    
    // get the option
	read(sock_fd, &func_id, sizeof(int));
	printf("Client connected\n");
	
    while(1){
		if(func_id==1){
            // login
            login(sock_fd);
            read(sock_fd, &func_id, sizeof(int));
        }
		
        if(func_id==2) {
            // signup
            signup(sock_fd);
            read(sock_fd, &func_id, sizeof(int));
        }
        
        // quit
		if(func_id==3) break;
	}
    
	close(sock_fd);
	printf("Client disconnected\n", sock_fd);
}

int login(int sock_fd){
    
	int type, acc_no, fd, valid=1, invalid=0, login_success=0;
	char password[PASS_LENGTH];
	
    struct account temp;
	
    // get info from client
    read(sock_fd, &type, sizeof(type));
	read(sock_fd, &acc_no, sizeof(acc_no));
	read(sock_fd, &password, sizeof(password));

	if((fd = open(Account[type-1], O_RDWR))==-1)printf("File Error\n");
	
    struct flock lock;
	
    // record locking
	lock.l_start = (acc_no-1)*sizeof(struct account);
	lock.l_len = sizeof(struct account);
	lock.l_whence = SEEK_SET;
	lock.l_pid = getpid();

	if(type == 1){
        
		// customer
		
        lock.l_type = F_WRLCK;
        
        // wait for lock
		fcntl(fd,F_SETLKW, &lock);
        
		lseek(fd, (acc_no - 1)*sizeof(struct account), SEEK_SET);
		read(fd, &temp, sizeof(struct account));
		
        if(temp.id == acc_no){
			if(!strcmp(temp.pass, password)){
                // valid case
				write(sock_fd, &valid, sizeof(valid));
                
                // send the user to dashboard
				while(user_menu(sock_fd, temp.id, type)!=-1);
                
				login_success = 1;
			}
		}
        
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		
        close(fd);
		
        if(login_success)
		return 3;
	}
	else if(type == 2){
		//agent
        
        // read lock, multiple readings allowed
		lock.l_type = F_RDLCK;
		
        // wait for lock
        fcntl(fd,F_SETLKW, &lock);
        
		lseek(fd, (acc_no - 1)*sizeof(struct account), SEEK_SET);
		read(fd, &temp, sizeof(struct account));
		
        if(temp.id == acc_no){
			if(!strcmp(temp.pass, password)){
				write(sock_fd, &valid, sizeof(valid));
                
                // send the agent to dashboard
				while(user_menu(sock_fd, temp.id, type)!=-1);
				login_success = 1;
			}
		}
        
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		
        close(fd);
		
        if(login_success) return 3;
		
	}
	else if(type == 3){
		// Admin
        
        // if admin logged then no one can log in
		lock.l_type = F_WRLCK;
		int ret = fcntl(fd,F_SETLK, &lock);
		if(ret != -1){
			lseek(fd, (acc_no - 1)*sizeof(struct account), SEEK_SET);
			read(fd, &temp, sizeof(struct account));
			if(temp.id == acc_no){
				if(!strcmp(temp.pass, password)){
					write(sock_fd, &valid, sizeof(valid));
					while(admin_menu(sock_fd, temp.id)!=-1);
					login_success = 1;
				}
			}
			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);
		}
		
        close(fd);
		
        if(login_success)
		return 3;
	}
	
    write(sock_fd, &invalid, sizeof(invalid));
	return 3;
}


int signup(int sock_fd){
	int type, fd, acc_no=0;
	char password[PASS_LENGTH], name[10];
	struct account temp;

	read(sock_fd, &type, sizeof(type));
	read(sock_fd, &name, sizeof(name));
	read(sock_fd, &password, sizeof(password));

	if((fd = open(Account[type-1], O_RDWR))==-1)printf("File Error\n");
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_start = 0;
	lock.l_len = 0; //lock whole file
	lock.l_whence = SEEK_SET;
	lock.l_pid = getpid();

	fcntl(fd,F_SETLKW, &lock);

	int fp = lseek(fd, 0, SEEK_END);

	if(fp==0){
		temp.id = 1;
		strcpy(temp.name, name);
		strcpy(temp.pass, password);
		write(fd, &temp, sizeof(temp));
		write(sock_fd, &temp.id, sizeof(temp.id));
	}
	else{
		fp = lseek(fd, -1 * sizeof(struct account), SEEK_END);
		read(fd, &temp, sizeof(temp));
		temp.id++;
		strcpy(temp.name, name);
		strcpy(temp.pass, password);
		write(fd, &temp, sizeof(temp));
		write(sock_fd, &temp.id, sizeof(temp.id));
	}

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);
	return 3;
}


int admin_menu(int sock_fd, int id){
    
	int op_id;
	read(sock_fd, &op_id, sizeof(op_id));
	
    if(op_id == 1){
		//add a train
		int tid = 0;
		int tno; 
		char tname[20];
		read(sock_fd, &tname, sizeof(tname));
		read(sock_fd, &tno, sizeof(tno));
		struct train temp, temp2;

        // get all info from socket
		temp.tid = tid;
		temp.train_no = tno;
		strcpy(temp.train_name, tname);
		temp.av_seats = 20;
		temp.last_seatno_used = 0;

		int fd = open(TRAIN, O_RDWR);
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;       //lock whole train database file
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();

		fcntl(fd, F_SETLKW, &lock);

		int fp = lseek(fd, 0, SEEK_END);
        
		if(fp == 0){
            // first train
			write(fd, &temp, sizeof(temp));
			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);
			close(fd);
			write(sock_fd, &op_id, sizeof(op_id));
		}
		else{
            //get the correct id
			lseek(fd, -1 * sizeof(struct train), SEEK_CUR);
			read(fd, &temp2, sizeof(temp2));
			temp.tid = temp2.tid + 1;
			write(fd, &temp, sizeof(temp));
			write(sock_fd, &op_id, sizeof(op_id));	
			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);
			close(fd);
		}
		return op_id;
	}
    
	if(op_id == 2){
		//delete train
		int fd = open(TRAIN, O_RDWR);

		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();
		
		fcntl(fd, F_SETLKW, &lock);

		int fp = lseek(fd, 0, SEEK_END);
        
		int no_of_trains = fp / sizeof(struct train);
		printf("no of train:%d\n",no_of_trains);
		
        write(sock_fd, &no_of_trains, sizeof(int));
		lseek(fd, 0, SEEK_SET);
		
        struct train temp;
		
        // display all the trains
        while(fp != lseek(fd, 0, SEEK_CUR)){
			read(fd, &temp, sizeof(struct train));
			write(sock_fd, &temp.tid, sizeof(int));
			write(sock_fd, &temp.train_name, sizeof(temp.train_name));
			write(sock_fd, &temp.train_no, sizeof(int));			
		}
        
        // get the train id to be deleted
		read(sock_fd, &no_of_trains, sizeof(int));
		
        if(no_of_trains != -2)
		{
			struct train temp;
			
			lseek(fd, (no_of_trains)*sizeof(struct train), SEEK_SET);
			read(fd, &temp, sizeof(struct train));			
			printf("%s is deleted\n", temp.train_name);
			strcpy(temp.train_name,"deleted");
            
            // comeback one element
			lseek(fd, -1*sizeof(struct train), SEEK_CUR);
			write(fd, &temp, sizeof(struct train));
		}
        
		write(sock_fd, &no_of_trains, sizeof(int));
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		close(fd);
	}
    
	if(op_id == 3){
		//modify
		int fd = open(TRAIN, O_RDWR);

		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();
		
		fcntl(fd, F_SETLKW, &lock);

		int fp = lseek(fd, 0, SEEK_END);
        
		int no_of_trains = fp / sizeof(struct train);
        
		write(sock_fd, &no_of_trains, sizeof(int));
		lseek(fd, 0, SEEK_SET);
		
        // display all the trains
        while(fp != lseek(fd, 0, SEEK_CUR)){
			struct train temp;
			read(fd, &temp, sizeof(struct train));
			write(sock_fd, &temp.tid, sizeof(int));
			write(sock_fd, &temp.train_name, sizeof(temp.train_name));
			write(sock_fd, &temp.train_no, sizeof(int));			
		}
        
        // get the train id
		read(sock_fd, &no_of_trains, sizeof(int));

		struct train temp;
		lseek(fd, 0, SEEK_SET);
		lseek(fd, (no_of_trains-1)*sizeof(struct train), SEEK_CUR);
		read(fd, &temp, sizeof(struct train));			

        // get the option to modify
		read(sock_fd, &no_of_trains,sizeof(int));
        
		if(no_of_trains == 1){
            // name change
			char name[20];
			write(sock_fd, &temp.train_name, sizeof(temp.train_name));
			read(sock_fd, &name, sizeof(name));
			strcpy(temp.train_name, name);
		}
		else if(no_of_trains == 2){
            // train no. changed
			write(sock_fd, &temp.train_no, sizeof(temp.train_no));
			read(sock_fd, &temp.train_no, sizeof(temp.train_no));
		}
		else{
            // seat changed
			write(sock_fd, &temp.av_seats, sizeof(temp.av_seats));
			read(sock_fd, &temp.av_seats, sizeof(temp.av_seats));
		}

		no_of_trains = 3;
        
		printf("%s\t%d\t%d\n", temp.train_name, temp.train_no, temp.av_seats);
		
        lseek(fd, -1*sizeof(struct train), SEEK_CUR);
		
        write(fd, &temp, sizeof(struct train));
		write(sock_fd, &no_of_trains, sizeof(int));

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		
        close(fd);
		return op_id;
	}
	if(op_id == 4){
		//add admin
        
		int type=3, fd, acc_no=0;
		char password[PASS_LENGTH], name[10];
		struct account temp;
		read(sock_fd, &name, sizeof(name));
		read(sock_fd, &password, sizeof(password));

		if((fd = open(Account[type-1], O_RDWR))==-1)printf("File Error\n");
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();

		fcntl(fd,F_SETLKW, &lock);
		int fp = lseek(fd, 0, SEEK_END);
        
		fp = lseek(fd, -1 * sizeof(struct account), SEEK_CUR);
		
        read(fd, &temp, sizeof(temp));
		// get the correct id
        temp.id++;
		strcpy(temp.name, name);
		strcpy(temp.pass, password);
        
		write(fd, &temp, sizeof(temp));
		
        write(sock_fd, &temp.id, sizeof(temp.id));
		
        lock.l_type = F_UNLCK;
		
        fcntl(fd, F_SETLK, &lock);

		close(fd);
		op_id=4;
		write(sock_fd, &op_id, sizeof(op_id));
		return op_id;
	}
    
	if(op_id == 5){
        
		//delete user
		int type, id;
		struct account var;
		read(sock_fd, &type, sizeof(type));

		int fd = open(Account[type - 1], O_RDWR);
        
		struct flock lock;
		
        lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
		lock.l_pid = getpid();

		fcntl(fd, F_SETLKW, &lock);

		int fp = lseek(fd, 0 , SEEK_END);
		
        
        int users = fp/ sizeof(struct account);
		write(sock_fd, &users, sizeof(int));

		lseek(fd, 0, SEEK_SET);
		
        while(fp != lseek(fd, 0, SEEK_CUR)){
			read(fd, &var, sizeof(struct account));
			write(sock_fd, &var.id, sizeof(var.id));
			write(sock_fd, &var.name, sizeof(var.name));
		}

        // id to be deleted
		read(sock_fd, &id, sizeof(id));
		if(id == 0){write(sock_fd, &op_id, sizeof(op_id));}
		else{
			lseek(fd, 0, SEEK_SET);
			lseek(fd, (id-1)*sizeof(struct account), SEEK_CUR);
			read(fd, &var, sizeof(struct account));
			lseek(fd, -1*sizeof(struct account), SEEK_CUR);
			strcpy(var.name,"deleted");
			strcpy(var.pass, "");
			write(fd, &var, sizeof(struct account));
			write(sock_fd, &op_id, sizeof(op_id));
		}

		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);

		return op_id;
	}
	if(op_id == 6) {
		write(sock_fd,&op_id, sizeof(op_id));
		return -1;
	}
}

int user_menu(int sock_fd, int id, int type){
	
    // get the option
    int op_id;
	read(sock_fd, &op_id, sizeof(op_id));
    
	if(op_id == 1){
		//book a ticket
		int fd = open(TRAIN, O_RDWR);

		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();
		
		fcntl(fd, F_SETLKW, &lock);

		struct train temp;
		int fp = lseek(fd, 0, SEEK_END);
		int no_of_trains = fp / sizeof(struct train);
        
		write(sock_fd, &no_of_trains, sizeof(int));
		lseek(fd, 0, SEEK_SET);
		
        // display all the trains
        while(fp != lseek(fd, 0, SEEK_CUR)){
			read(fd, &temp, sizeof(struct train));
			write(sock_fd, &temp.tid, sizeof(int));
			write(sock_fd, &temp.train_no, sizeof(int));	
			write(sock_fd, &temp.av_seats, sizeof(int));	
			write(sock_fd, &temp.train_name, sizeof(temp.train_name));		
		}
        
		memset(&temp,0,sizeof(struct train));
		int trainid, seats;
		
        // get the train id
        read(sock_fd, &trainid, sizeof(trainid));
        
        // goto that train
		lseek(fd, trainid*sizeof(struct train), SEEK_SET);
		read(fd, &temp, sizeof(struct train));
        
        // get available seats
		write(sock_fd, &temp.av_seats, sizeof(int));
		read(sock_fd, &seats, sizeof(seats));
        
		if(seats>0){
            
			temp.av_seats -= seats;
			
            int fd2 = open(BOOKING, O_RDWR);
			
            // set lock on booking
            fcntl(fd2, F_SETLKW, &lock);
			struct bookings bk;
			int fp2 = lseek(fd2, 0, SEEK_END);
            
            // get the bid
			if(fp2 > 0)
			{
				lseek(fd2, -1*sizeof(struct bookings), SEEK_CUR);
				read(fd2, &bk, sizeof(struct bookings));
				bk.bid++;
			}
			else 
				bk.bid = 0;
            
			bk.type = type;
			bk.acc_no = id;
			bk.tr_id = trainid;
			bk.cancelled = 0;
			strcpy(bk.trainname, temp.train_name);
			
            bk.seat_start = temp.last_seatno_used + 1;
			bk.seat_end = temp.last_seatno_used + seats;
			
            temp.last_seatno_used = bk.seat_end-bk.seat_start-1;
			write(fd2, &bk, sizeof(bk));
			lock.l_type = F_UNLCK;
			fcntl(fd2, F_SETLK, &lock);
		 	close(fd2);
			lseek(fd, -1*sizeof(struct train), SEEK_CUR);
			write(fd, &temp, sizeof(temp));
		}
		fcntl(fd, F_SETLK, &lock);
	 	close(fd);

		if(seats<=0)
			op_id = -1;
		write(sock_fd, &op_id, sizeof(op_id));
		return 1;
	}
    
	if(op_id == 2){
		// view bookings
        
        view_booking(sock_fd, id, type);
		write(sock_fd, &op_id, sizeof(op_id));
		return 2;
	}
	if(op_id == 3){
        
		//update booking
		view_booking(sock_fd, id, type);

		int fd1 = open(TRAIN, O_RDWR);
		int fd2 = open(BOOKING, O_RDWR);
        
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();

		fcntl(fd1, F_SETLKW, &lock);
		fcntl(fd2, F_SETLKW, &lock);

		int val;
		struct train temp1;
		struct bookings temp2;
        
        //Read the Booking ID to updated
		read(sock_fd, &val, sizeof(int));
		
        // read the booking to be updated
		lseek(fd2, 0, SEEK_SET);
		lseek(fd2, val*sizeof(struct bookings), SEEK_CUR);
		read(fd2, &temp2, sizeof(temp2));
		lseek(fd2, -1*sizeof(struct bookings), SEEK_CUR);
		printf("%d %s %d\n", temp2.tr_id, temp2.trainname, temp2.seat_end);
		
        // read the train details of the booking
		lseek(fd1, 0, SEEK_SET);
		lseek(fd1, (temp2.tr_id-1)*sizeof(struct train), SEEK_CUR);
		read(fd1, &temp1, sizeof(temp1));
		lseek(fd1, -1*sizeof(struct train), SEEK_CUR);
		printf("%d %s %d\n", temp1.tid, temp1.train_name, temp1.av_seats);


        // option
        read(sock_fd, &val, sizeof(int));


        
		if(val==1){
            
            // increase
            
            // no. of seats
			read(sock_fd, &val, sizeof(int));
            
			if(temp1.av_seats>= val){
                
                // previous booking is cancelled
				temp2.cancelled = 1;
				temp1.av_seats += val;
				write(fd2, &temp2, sizeof(temp2));

                // total seats to be added to the booking
				int tot_seats = temp2.seat_end - temp2.seat_start + 1 + val;
				
                struct bookings bk;

				int fp2 = lseek(fd2, 0, SEEK_END);
				
                lseek(fd2, -1*sizeof(struct bookings), SEEK_CUR);
				read(fd2, &bk, sizeof(struct bookings));

				bk.bid++;
				bk.type = temp2.type;
				bk.acc_no = temp2.acc_no;
				bk.tr_id = temp2.tr_id;
				bk.cancelled = 0;
				strcpy(bk.trainname, temp2.trainname);
				bk.seat_start = temp1.last_seatno_used + 1;
				bk.seat_end = temp1.last_seatno_used + tot_seats;

				temp1.av_seats -= tot_seats;
				temp1.last_seatno_used = bk.seat_end - temp2.seat_end;

				write(fd2, &bk, sizeof(bk));
				write(fd1, &temp1, sizeof(temp1));
			}
			else{
				op_id = -2;
				write(sock_fd, &op_id, sizeof(op_id));
			}
		}
		else{
            //decrease
			read(sock_fd, &val, sizeof(int)); //No of Seats
			if(temp2.seat_end - val < temp2.seat_start){
                // invalid case
				temp2.cancelled = 1;
				temp1.av_seats += val;
			}
			else{
				temp2.seat_end -= val;
				temp1.av_seats += val;
			}
			write(fd2, &temp2, sizeof(temp2));
			write(fd1, &temp1, sizeof(temp1));
		}
		lock.l_type = F_UNLCK;
		fcntl(fd1, F_SETLK, &lock);
		fcntl(fd2, F_SETLK, &lock);
		close(fd1);
		close(fd2);
		if(op_id>0)
		write(sock_fd, &op_id, sizeof(op_id));
		return 3;

	}
	if(op_id == 4) {
		//cancel booking
        
        
        // get all the bookings
		view_booking(sock_fd, id, type);


		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();

		int fd1 = open(TRAIN, O_RDWR);
		int fd2 = open(BOOKING, O_RDWR);
		fcntl(fd1, F_SETLKW, &lock);


		int val;
		struct train temp1;
		struct bookings temp2;
        
        //Read the Booking ID to deleted
		read(sock_fd, &val, sizeof(int));
		lseek(fd2, val*sizeof(struct bookings), SEEK_SET);
		

		lock.l_start = val*sizeof(struct bookings);
		lock.l_len = sizeof(struct bookings);
		fcntl(fd2, F_SETLKW, &lock);

		
		read(fd2, &temp2, sizeof(temp2));
		lseek(fd2, -1*sizeof(struct bookings), SEEK_CUR);
		printf("%d %s %d\n", temp2.tr_id, temp2.trainname, temp2.seat_end);
		// read the train details of the booking
		

		lseek(fd1, (temp2.tr_id)*sizeof(struct train), SEEK_SET);
		lock.l_start = (temp2.tr_id)*sizeof(struct train);
		lock.l_len = sizeof(struct train);
		fcntl(fd1, F_SETLKW, &lock);
        
		read(fd1, &temp1, sizeof(temp1));
        
		lseek(fd1, -1*sizeof(struct train), SEEK_CUR);
        
		printf("%d %s %d\n", temp1.tid, temp1.train_name, temp1.av_seats);
        
		temp1.av_seats += temp2.seat_end - temp2.seat_start + 1;
		
        // cancel
        temp2.cancelled=1;
        
		write(fd2, &temp2, sizeof(temp2));
		write(fd1, &temp1, sizeof(temp1));
		
		lock.l_type = F_UNLCK;
		fcntl(fd1, F_SETLK, &lock);
		fcntl(fd2, F_SETLK, &lock);
		close(fd1);
		close(fd2);
		write(sock_fd, &op_id, sizeof(op_id));
		return 4;
	}
	if(op_id == 5) {
		write(sock_fd, &op_id, sizeof(op_id));
		return -1;
	}
	
	return 0;
}

void view_booking(int sock_fd, int id, int type){
	int fd = open(BOOKING, O_RDONLY);
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_whence = SEEK_SET;
	lock.l_pid = getpid();
	
	fcntl(fd, F_SETLKW, &lock);

	int fp = lseek(fd, 0, SEEK_END);
	int entries = 0;
	if(fp == 0)
		write(sock_fd, &entries, sizeof(entries));
	else{
        
        // there could be 10 bookings at a time
		struct bookings bk[10];
		while(fp>0 && entries<10){
			struct bookings temp;
			fp = lseek(fd, -1*sizeof(struct bookings), SEEK_CUR);
			read(fd, &temp, sizeof(struct bookings));
			if(temp.acc_no == id && temp.type == type)
				bk[entries++] = temp;
			fp = lseek(fd, -1*sizeof(struct bookings), SEEK_CUR);
		}
		write(sock_fd, &entries, sizeof(entries));
		for(fp=0;fp<entries;fp++){
			write(sock_fd, &bk[fp].bid, sizeof(bk[fp].bid));
			write(sock_fd, &bk[fp].trainname, sizeof(bk[fp].trainname));
			write(sock_fd, &bk[fp].seat_start, sizeof(int));
			write(sock_fd, &bk[fp].seat_end, sizeof(int));
			write(sock_fd, &bk[fp].cancelled, sizeof(int));
		}
	}
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	close(fd);
}

void server_handler(int sig) {
	char str[5];
	printf("Do you want to stop the server(y/n)?\n");
	scanf("%s", str);
	if(strcmp("y", str) == 0) {
		exit(0);
	}
	return;
}

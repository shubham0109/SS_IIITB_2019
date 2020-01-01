#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h> 
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

struct  individual{
  char name[100];
  char password[20];
};
struct  joint_user{
  char name1[100];
  char name2[100];
  char password[20];
};
struct login_details {
     int account_no;
     char password[20];
     int type;
};

void display(int, int, int);

void signin(int sockfd)
{

	struct login_details det;
    int verify;
    int type;

	printf("Enter account type:\n1. Normal user.\n2. Joint account\n");
	scanf("%d", &type);	
	type = htonl(type);
	if(write(sockfd, &type, sizeof(int)) == -1)
		ERR_EXIT("write()");
	
	printf("Enter account number: ");
	scanf("%d", &det.account_no);
	det.account_no = htonl(det.account_no);
	if(write(sockfd,&det.account_no,sizeof(int)) == -1)
		ERR_EXIT("write()");			 	
	
	// printf("Enter password: ");
	// scanf("%s", det.password);
	// if(write(sockfd, det.password, sizeof(det.password)) == -1)
	// 	ERR_EXIT("write()");
	char* password;
	password = getpass("Enter password: ");
	if(write(sockfd, password, sizeof(det.password)) == -1) ERR_EXIT("write()");
	if(read(sockfd, &verify, sizeof(int)) == -1)
		ERR_EXIT("read()");
	verify = ntohl(verify);
	while ((getchar()) != '\n');
	// clear input buffer
	if(verify == 0)
	{
		printf("Login successful.\n");
		printf("Press enter to show the menu.\n");
		getchar();
		display(det.account_no, type, sockfd);
	}
	else if(verify == -1)
	{
		printf("Invalid login details.\n");
		printf("Press any key to retry...\n");
		getchar();
	}
}

void signup(int sockfd)
{
	struct individual normal;
	struct joint_user joint; 
	int type;
	int account_no;
	int login;
	printf("Enter account type.\n1. Individual\n2. Joint\n");
	scanf("%d",&type);
	type = htonl(type);
	if(write(sockfd, &type, sizeof(int)) == -1)
		ERR_EXIT("write()");
	type = ntohl(type);
	if(type == 1)  
	{
		printf("Enter name: ");
		scanf("%s",normal.name);
		if(write(sockfd, normal.name, sizeof(normal.name)) == -1)
			ERR_EXIT("write()");

		char* password;
		password = getpass("Enter password: ");
		if(write(sockfd, password, sizeof(normal.password)) == -1) ERR_EXIT("write()");
		
		// printf("Enter password: ");
		// // fflush(stdin);
		// scanf("%s",normal.password);
		// if(write(sockfd, normal.password, sizeof(normal.password)) == -1)
		// 	ERR_EXIT("write()");	
		if(read(sockfd, &account_no, sizeof(int)) == -1)
			ERR_EXIT("read()");
		printf("Sign up successful.\n");
		printf("Your account number for further login: %d\n", ntohl(account_no));
		printf("Press any key to continue...\n");
		while ((getchar()) != '\n');getchar();
	}
	else if(type == 2)
	{   
		printf("Enter first name: ");
		scanf("%s", joint.name1);
		if( write(sockfd, joint.name1, sizeof(joint.name1)) == -1)
			ERR_EXIT("write()");
		printf("Enter second name: ");
		scanf("%s", joint.name2);
		if( write(sockfd, joint.name2, sizeof(joint.name2)) == -1)
			ERR_EXIT("write()");

		char* password;
		password = getpass("Enter password: ");
		if(write(sockfd, password, sizeof(joint.password)) == -1) ERR_EXIT("write()");
		

		// printf("Enter password: ");
		// scanf("%s", joint.password);
		// if( write(sockfd,joint. password, sizeof(joint.password)) == -1)
		// 	ERR_EXIT("write()");
		//call for server to store password get account number and display to user	
		printf("Sign up successful.\n");
		if(read(sockfd,&account_no,sizeof(int)) == -1)
			ERR_EXIT("read()");
		printf("Your account number for further login: %d\n", ntohl(account_no));
		printf("Press any key to continue...\n");
		// clear the buffer
		while ((getchar()) != '\n');getchar();
	}
}

void display(int account_no,int type,int sockfd)
{
	int choice=0;
	int balance=0;
	int ack=0;
	int deposit_money=0;
	int withdraw_money=0;

	while(1)
	{
		// clear screen
		printf("\e[1;1H\e[2J");
		printf("Enter you choice\n1. Deposit\n2. Withdrawl\n");
		printf("3. View Account Details\n4. View Balance\n");
		printf("5. Change Passowrd\n6. Exit\n");
		scanf("%d", &choice);
		choice = htonl(choice);
		if(write(sockfd, &choice, sizeof(choice)) == -1) ERR_EXIT("write()");
		choice = ntohl(choice);
		switch(choice)
		{
			case 1:
			{
				// call server for deposit money server(1)
				printf("Enter the amount to deposit: ");
				scanf("%d", &deposit_money);
				if(deposit_money > 0) {
					deposit_money = htonl(deposit_money);
					if(write(sockfd, &deposit_money, sizeof(int)) == -1) ERR_EXIT("write()");
					if(read(sockfd,&ack,sizeof(ack)) == -1) ERR_EXIT("read()");
					if(ntohl(ack) == 0) printf("Successful.\n");
					else if(ntohl(ack) == -1) printf("Deposit failed please try again.\n");
				}
				else
					printf("Enter amount greater than zero.\n");
				break;  
			}

			case 2:
			{  
				// call server to withdraw money
				printf("Enter the amount to withdraw: ");
				scanf("%d", &withdraw_money);
				withdraw_money = htonl(withdraw_money);
				if(write(sockfd, &withdraw_money, sizeof(int)) == -1) ERR_EXIT("write()");
				if(read(sockfd, &ack, sizeof(ack)) == -1) ERR_EXIT("read()");
				ack = ntohl(ack);
				//call server() to withdraw money ack =1 successful ack =-1 error;
				if(ack == 0) printf("Withdraw successful.\n");
				else if(ack == -1) printf("Withdraw failed please try again.\n");
				else if(ack == -2) printf("Insufficient funds.\n");
				break;
			}
			case 3:
			{ 
				char buf[1024];
				if(read(sockfd, buf, sizeof(buf)) == -1) ERR_EXIT("read()");
				printf("%s\n", buf);
				break;
			}
			case 4:
			{
				int balance;
				if(read(sockfd,&balance,sizeof(balance)) == -1) ERR_EXIT("read()");
				balance = ntohl(balance);
				printf("Balance: %d\n", balance);       
				break;
			}
			case 5:
			{
				struct individual det;

				char* password;
				password = getpass("Enter password: ");
				if(write(sockfd, password, sizeof(det.password)) == -1) ERR_EXIT("write()");
		
				// printf("Enter new password: ");
				// scanf("%s",det.password);
				// if(write(sockfd, det.password, sizeof(det.password)) == -1) ERR_EXIT("write()");
				
				if(read(sockfd, &ack, sizeof(int)) == -1) ERR_EXIT("read()");
				ack = ntohl(ack);
				if(ack == 0)
					printf("Passowrd changed successfuly.\n");
				else printf("Error in changing password please retry.\n");
				break; 
			}
			default:
			{
				if(close(sockfd) == -1) ERR_EXIT("close()");
				exit(EXIT_SUCCESS);
			}
		}
		// clear the buffer
		while ((getchar()) != '\n');
		printf("Press any key to continue...\n");
		getchar();
	}
}


int main(int argc,char* argv[])
{
	if(argc != 3)
    {
        fprintf(stderr ,"Usage: %s <ip_addr_of_server> <port_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
	
	int sockfd;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ERR_EXIT("socket()");

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	
	if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) != 1)
		ERR_EXIT("inet_pton()");

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    	ERR_EXIT("connect()");

	while(1)
	{
		// clear the screen
		printf("\e[1;1H\e[2J"); 
		
		printf("*****************************\n");
		printf("* WELCOME TO BANKING SYSTEM *\n");
		printf("*****************************\n");
		printf("1. Sign in\n2. Sign up\n3. Exit\n");
		printf("*****************************\n");
		
		int choice;
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				choice = htonl(choice);
				if(write(sockfd, &choice, sizeof(int)) == -1)
					ERR_EXIT("write()");
				signin(sockfd);
			break;
			case 2:
				choice = htonl(choice);
				if(write(sockfd, &choice, sizeof(int)) == -1)
					ERR_EXIT("write()");
				signup(sockfd);
			break;
			case 3:
				choice = htonl(choice);
				if(write(sockfd, &choice, sizeof(int)) == -1)
				if(close(sockfd) == -1) ERR_EXIT("close()");
				exit(EXIT_SUCCESS);
			break;
			default:
				printf("Please enter valid choice.\n");
			break;
		}
	}
}
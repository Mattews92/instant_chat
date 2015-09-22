/*Ch@t ONE is an Instant Chat aplication
*Developed at Experion Technologies
*by Albin k Thomas, Harikumar, Mathews Philip & Swetha K Saseendran
*on 08.08.2015*/ 


# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/ioctl.h>
# include <net/if.h>

# include "login.c"
# include "signup.c"
# include "chat.c"
# include "validate.c"

#define clear() printf("\033[H\033[J")/* Clear function to clear the screen */

int loginstatus = 0;

void chat()
{
	/* first screen */
	clear();
	printf("\n\n\n\t\t\tCh@t ONE\n\n");
	printf("\t\t\t\t\tHELP\n");
	printf("\t           ____________");
	printf("\n\tUsername :|____________|\n");
	printf("\t           ____________");
	printf("\n\tPassword :|____________|");
	printf("\n\n\t\tLOGIN\t\tSIGNUP\n\n");
}

void Cmd_Help()
{
	clear();
	printf("\n\n\n\t\t\tCh@t ONE\n\n");
	printf(" ___________________________________________________________________________\n");
	printf("|	CHAT <nickname>	-	To send message to the chat client <nickname>		|\n");
/*	printf("|	DEACTIVATE		-	To deactivate the user account						|\n");
	printf("|	END <nickname>	-	To terminate the current chat with <nickname>		|\n"); */
	printf("|	EXIT			-	To exit fron Ch@t_ONE								|\n");
	printf("|	FIND	        -	To find and list all the online friends				|\n");
	printf("|	HELP			-	To list all the Ch@t ONE commands					|\n");
	printf("|	LOGIN			-	To login to the Ch@t ONE server						|\n");
	printf("|	LOGOUT			-	To logout from  Ch@t ONE server						|\n");
	printf("|	SIGNUP			-	To register a new client account					|\n");
	printf(" ___________________________________________________________________________\n");
	printf("\n");
}
	
void main()
{
	clear();
	int choice, m,n,sockfd, returnStatus;
	char cmd[16], buf[256], *temp, *string, t_uname[32] , userid[32];
	chat();

	struct sockaddr_in serv_addr,cli_addr;
	serv_addr.sin_family=PF_INET;
	serv_addr.sin_port=htons(4013);
	serv_addr.sin_addr.s_addr=inet_addr("192.168.1.239");
	sockfd=socket(PF_INET,SOCK_DGRAM,0);

	connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)); /* coonecting to socket */

	pid_t childPid;
	
	if ( (childPid = fork() ) == 0)
	{
		while(1)
		{
			printf("\nCh@t>");
			scanf("%s",cmd);

			if ( strcasecmp(cmd,"CHAT") == 0 )
				choice=1;
			/*if ( strcasecmp(cmd,"DEACTIVATE") == 0 )
				choice=2;
			if ( strcasecmp(cmd,"END") == 0 )
				choice=3;*/
			if ( strcasecmp(cmd,"FIND") == 0 )
				choice=4;
			if ( strcasecmp(cmd,"HELP") == 0 )
				choice=5;
			if ( strcasecmp(cmd,"LOGIN") == 0 )
				choice=6;
			if ( strcasecmp(cmd,"LOGOUT") == 0 )
				choice=7;
			if ( strcasecmp(cmd,"SIGNUP") == 0 )
				choice=8;
			if ( strcasecmp(cmd,"EXIT") == 0 )
				choice=9;
			memset(cmd, 0, sizeof(cmd));
			switch ( choice )
			{

				case 1:
	
					//if (loginstatus == 1)
					string = Cmd_Chat();
					/*else
					{
						printf("\n\tPlease login to chat\n");
						sleep(2);
						chat();
					}*/
					break;

				case 4:
					
					printf("\nSearching for online friends..\n");
					sleep(2);
					memset(string, 0, sizeof(string));
					strcpy(string,"find ");
					break;

				case 5:
					Cmd_Help();
					continue;
					break;

				case 6:
					string = Cmd_Login(loginstatus);
					break;

				case 7:
					clear();
					printf("\nSuccessfully Logged Out\n");
					loginstatus = 0;
					chat();
					continue;
					break;

				case 8:
					string = Cmd_Signup();
					break;

				case 9:
					chat();
					exit(1); 

				default:
					printf("\nInvalid Command. Try HELP\n");
					break;
			} 	
			m=sendto(sockfd,string,strlen(string),0,(struct sockaddr  *) &serv_addr,sizeof(serv_addr));
			sleep(2);
		}
	}//fork()
	else
	{
		while(1)
		{
			n=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

			temp = strtok(buf," ");
			if( strcmp(temp,"msg") == 0)
			{
				temp = strtok(NULL , " ");
				printf("\n%s :",temp);
				temp = strtok(NULL, ",");
				printf("%s",temp);
			}
			else
			{
				temp = strtok(NULL,",");
				printf("\n%s\n",temp);
				temp = strtok(NULL,",");
				if (temp[0] == '1')
					loginstatus = 1;
			}
       		printf("\n");
       		continue;
       
        /*waitpid(childPid, &returnStatus, 0);

		if(returnStatus == 0 )
		{
			printf("\nChild terminated normally\n");
			break;
		}
		else if (returnStatus == 1)
		{
			printf("\nChild terminated with error\n");
			break;
		}*/
		}
	
		wait(NULL);
	}
	close(sockfd);
}

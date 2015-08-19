#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define MIN 32
#define MAX 256

struct ConnectedClient
{
    char nickname[MIN];
    struct sockaddr_in cli_addr;
    //struct in_addr sin_addr;
};

struct ConnectedClient clients[MIN];
int noOfClients=0, tocno;

struct sockaddr_in cli_addr;

char buf[MAX], *pch, str[MAX], *fch, *pch1, *pch2, *fch1, *fch2, *c;
char cmd[MIN],f_uname[MIN],t_uname[MIN],pass[MIN],msg[MAX],cmd1[MIN],tmp[MAX];
FILE *fp_register, *fp_ipmanager;
int flag;

void checkLogin(char* nickname, struct sockaddr_in cli_addr)
{
    printf("%s logged in\n",nickname);
    strcpy(clients[noOfClients].nickname,nickname);
    clients[noOfClients].cli_addr=cli_addr;
    noOfClients++;
}

setupConnection()
{
	int n,sockfd,newsockfd,clilen,cli,i=0, choice;
	char copystring[50];

	/* creating the socket */
	cli_addr.sin_family=PF_INET;
	cli_addr.sin_port=htons(4013);
	cli_addr.sin_addr.s_addr=htons(INADDR_ANY);
	sockfd=socket(PF_INET,SOCK_DGRAM,0);

	i=bind(sockfd,(struct sockaddr*) &cli_addr,sizeof(cli_addr)); /* binding the socket */
	printf("\n\nserver started\n");
	printf("waiting for client\n");

	memset(buf, 0, sizeof(buf));
	cli=sizeof(cli_addr);
	n=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *) &cli_addr, &cli); /* recieving data from the client */

	memset(copystring, 0, sizeof(copystring));
	strcpy(copystring,buf);
	pch = strtok(copystring," "); /* chop the request header from the wired string */

	/* assigning integer values for each possible request header */
	if ( strcasecmp(pch,"register") == 0)
		choice = 1;
	else if ( strcasecmp(pch,"login") == 0)
		choice = 2;
	else if ( strcasecmp(pch,"find") == 0)
		choice = 3;
	else if ( strcasecmp(pch,"chat") == 0)
		choice = 4;

	/* switching to corresponding functions based on request header */
	switch(choice)
	{
		case 1:
			signup();
			break;
		
		case 2:
			login();
			break;
		
		case 3:
printf("\ncheck0");
			list();
			break;
		
		case 4:
			chat();
			/* sending the message over the network */
			n=sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr*) &clients[tocno].cli_addr,sizeof(clients[tocno].cli_addr));
			break;
		
		default:
			printf("\nswitch error\n");
	}
        
	n=sendto(sockfd,str,sizeof(str),0,(struct sockaddr*) &cli_addr,sizeof(cli_addr)); /* replying to the client */


    close(sockfd);      	
}

login()
{
	
		flag=0;
		fp_register = fopen ("register.csv", "r"); /* registration file */

		/* tokenizing the recieved string */
		pch = strtok(buf," ");   /* command */
		pch = strtok(NULL,",");  /* username */
		pch1 = strtok(NULL,","); /* password */
		pch2 = strtok(NULL,","); /* user IP */

	 	while ((fscanf(fp_register, "%s", str))!=EOF)
   		{
   			/* tokenizing the string read from file 'register.csv' */
			fch = strtok(str,",");  /* username */
			fch1= strtok(NULL,","); /* password */
			fch2= strtok(NULL,","); /* nickname */

			/* validating the log in cofidentials */
			if((strcmp(pch,fch)==0)&& (strcmp(pch1,fch1)==0))
			{
				flag=1;
				checkLogin(fch2,cli_addr); /* modifying the structure */
				break;
			}
		} 

    	if(flag ==1)
    	{
   			strcpy(str,"cmd Welcome ");
   			strcat(str,fch2);
   			strcat(str,",1,"); /* indexing logged in state */
    	}
    	else
		{
			strcpy(str,"cmd LOGIN UNSUCCESSFUL");
        	strcat(str,",0,");
		}
    	fclose(fp_register);
	
}

signup()
{
	char temp[100] = {0}, *pch;
	fp_register=fopen("register.csv","a");

   	if( fp_register == NULL )
	{
     	printf("Error!");
        strcpy(str,"cmd REGISTERATION UNSUCCESSFUL");
        strcat(str,",0,");
	}
	else
	{
		pch=strtok(buf," ");

		/* serializing the recieved data after chopping request header */
		while(strcmp( pch = strtok(NULL,","), "end") != 0)
		{
			strcat(temp,pch);
			strcat(temp,",");
		}
		strcat(temp,"\n");

		strcpy(str,"cmd REGISTERATION SUCCESSFUL");
		strcat(str,",0,");
		fprintf(fp_register,"%s",temp); /* updating the 'register.csv' file with new account info */

  		fclose(fp_register);

	}

}


list()
{
	int i=0;
   	if( noOfClients == 0 )
	{
     	printf("Error!");
        strcpy(str,"cmd Not Logged in");
        strcat(str,",0,");
	}
	else
	{
printf("\ncheck1");
		/* retrieving online client list from structure 'ConnectedClient' and serializing the same */
		memset(str, 0, sizeof(str));
		strcat(str,"cmd ");
		for(;i<noOfClients;i++)
    	{
	    	/*if(strcasecmp(clients[i].nickname,t_uname)==0)
			{
	       		continue;
        	}*/
        	strcat(str,"\n");
			strcat(str,clients[i].nickname);
printf("str: %s",str);
		}
		strcat(str,",0");
	}
}

chat()
{
    
    tocno=-1;
    memset(msg, 0, sizeof(msg));
    memset(cmd, 0, sizeof(cmd));
    memset(t_uname, 0, sizeof(t_uname));
    sscanf(buf,"%s%s",cmd,t_uname);  
    int i=0, j=0, count=0;

    /* extract message */
    while(buf[i]!='\0')
    {
		for(;count<2;)
		{
        	if(buf[i]==' ')
        	    count++;
        	i++;
        }
            msg[j]=buf[i];
            i++;
            j++;
    }
    msg[j++]=',';
    msg[j]='\0';

memset(f_uname, 0, sizeof(f_uname));

    for(i=0;i<noOfClients;i++)
    {
	    if(strcmp( inet_ntoa(clients[i].cli_addr.sin_addr), inet_ntoa(cli_addr.sin_addr) ) == 0 )
		{
			strcpy(f_uname,clients[i].nickname);
        }
    }
       
    for(i=0;i<noOfClients;i++)
    {
	    if(strcasecmp(clients[i].nickname,t_uname)==0)
		{
	        tocno=i;
        }
    }
			
	
   	memset(str, 0, sizeof(str));
            
    if(tocno==-1)
    {
        strcpy(str,"cmd Invalid user,0");
        return;           
    }
    else
        strcpy(str,"cmd Sent,0");

    memset(buf, 0, sizeof(buf));
    sprintf(buf,"msg %s %s",f_uname,msg);
    strcpy(cmd,"msg");

}


void main()
{

	while(1)
	{
		setupConnection();
	}

}
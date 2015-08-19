# include "password.c"
# include "client_networking.c"

# define clear() printf("\033[H\033[J")

char str[100]={0};

char *Cmd_Login(int loginstatus)
{
	int i,count=0;
	char c,username[20],password[20];
	char  *ip;
	ip=getUserIp();
	//clear();
	if (loginstatus == 1)
	{
		printf("\n\n\n\t\t\tCh@t ONE\n\n\tYou are already logged in\n\n\n");
		return NULL;
	}
	printf("\n\n\n\t\t\tCh@t ONE\n\n");
	printf("\n\n\t\t\tNot a User?? Please sign up\n");
	printf("\n\tUsername : ");
	scanf("%s",username);
	printf("\n\tPassword : ");
	
	/* masks the password and catches it into variable password */
	c=getch();
	while((c=getch())!='\n')/* calls the getch() in file password.c to mask the input */
	{
		printf("*");
		password[count++]=c;/* catches the password to the variable 'password' one character a time */
	}
	password[count]='\0';
	
	printf("\n\n\t\tConnecting to Server...\n\n");

	/* serialize username,password & user IP into the string username */
	strcpy(str,"login ");
	strcat(str,username);
	strcat(str,",");
	strcat(str,password);
	strcat(str,",");
	strcat(str,ip);
	strcat(str,",");
	sleep(2);
	printf("\n\n\t\tLoading...\n\n");

	//loginstatus = setupConnection(str);/* call to networking function in loginclient.c */
	//printf("\n");
	//return loginstatus;	
	return str;			
}

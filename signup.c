# include <ctype.h>

char str[100];

struct signup
{
	char fname[20],lname[20],nickname[20],username[20],password[20],re_password[20];
}s;

char *Cmd_Signup()
{
	int i=-1,flag=0,count,length;
	char  c=0;
	struct signup s;

	strcpy(s.password,"");
	strcpy(s.re_password,"");

	clear();
	printf("\n\n\n\t\t\tCh@t ONE\n\n");
	printf("\n\n\t\t\tAlready a User?? LOGIN..!!!\n");

	/* firstname */	
	while(flag!=1)
	{
	printf("\n\tFirst Name       : ");
	scanf("%s",s.fname);
	length=strlen(s.fname);
	flag=validate_text(s.fname,length);
	if(flag==0)
		printf("Warning: First Name must be alphabetic");
	}
	
	flag=0;


	/* lastname */
	while(flag!=1)
	{
	printf("\n\tLast Name        : ");
	scanf("%s",s.lname);
	length=strlen(s.lname);
	flag=validate_text(s.lname,length);
	if(flag==0)
		printf("Warning: Last Name must be alphabetic");
	}

	flag=0;


	/* username */
	while(flag!=1)
	{
	printf("\n\tUsername         : ");
	scanf("%s",s.username);
	length=strlen(s.username);
	flag=validate_username(s.username,length);
	}

	flag=0;

	
	/* password */
	while(flag!=1)
	{
	printf("\n\tPassword         : ");
	/* masks the password and catches it into variable password */
	count=0;
	c=getch();
	while((c=getch())!='\n')/* calls the getch() in file password.c to mask the input */
	{
		printf("*");
		s.password[count++]=c;/* catches the password to the variable 'password' one character a time */
	}
	s.password[count]='\0';
	length=strlen(s.password);
	flag=validate_password(s.password,length);
	}

	count=0;


	/* confirm password */
	printf("\n\n\tConfirm Password : ");
	/* masks the confirm-password and catches it into variable re_password */
	while((c=getch())!='\n')/* calls the getch() in file password.c to mask the input */
	{
		printf("*");
		s.re_password[count++]=c;/* catches the password to the variable 're_password' one character a time */
	}
	s.re_password[count]='\0';


	/* validates the password and confirm-password */
	if(strcmp(s.password,s.re_password)!=0)
	{
		printf("\n\n\t\tWarning: Password Mismatch");
		printf("\n");
		sleep(2);
		Cmd_Signup();/* Function recall caused by password mismatch */
		return 0;
	}


	/* nickname */
	printf("\n\n\tNickname         : ");
	scanf("%s",s.nickname);
	
	/* serialize user inputs to wire it to server */
	strcpy(str,"register ");
	strcat(str,s.username);
	strcat(str,",");
	strcat(str,s.password);
	strcat(str,",");
	strcat(str,s.nickname);
	strcat(str,",");
	strcat(str,s.fname);
	strcat(str,",");
	strcat(str,s.lname);
	strcat(str,",");
	strcat(str,"end");
	strcat(str,",");

	sleep(2);
	printf("\n\n\t\tLoading...\n\n");

	//flag = setupConnection(str); /* call to networking module in loginclient.c */
	return str;
}
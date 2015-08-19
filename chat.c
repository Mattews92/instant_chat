char msg[256];

char *Cmd_Chat()
{
	int a;
	char buf[256],  t_uname[32];
	memset(t_uname, 0, sizeof(t_uname));
	memset(msg, 0, sizeof(msg));
	printf("\nRecipient :  ");
	scanf("%s",t_uname);
	memset(buf, 0, sizeof(buf));
	read(0,buf,sizeof(buf));
	strcpy(msg,"chat ");
	strcat(msg,t_uname);
	strcat(msg," ");
	strcat(msg,buf);
	return msg;
}
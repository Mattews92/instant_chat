int validate_text(char string[20], int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		if( isalpha(string[i]) )
		{
			continue;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int validate_username(char string[20], int length)
{
	int i=1;
	if( isalpha(string[0]) )
	{
		if( string[i] =='\0' )
		{
			printf("\nInvalid Username: Username must contain @ character");
			return 0;
		}
		for( i=1 ; string[i] != '\0' ; )
		{
			if( string[i] == '@' )
			{
				i++;
				break;
			}
			else
				i++;
			if( string[i+1] == '\0' )
			{
				printf("\nInvalid Username: Username must contain @ character");
				return 0;
			}
		}
		if( string[i] == '.' )
		{
			printf("\nInvalid Username: Alphabets must succeed @");
			return 0;
		}
		while( string[i] != '.' )
		{
			if( isalpha(string[i]) )
			{
				i++;
				continue;
			}
			if( string[i] == '\0' )
			{
				printf("\nInvalid Username: Username must contain . character");
				return 0;
			}
			else
			{
				printf("\nInvalid Username: Only alphabets are permitted succeeding @");
				return 0;
			}
		}
		i++;
		while( string[i] !='\0')
		{
			if( isalpha(string[i]) )
			{
				i++;
				continue;
			}
			else
			{
				printf("\nInvalid Username: Only alphabets are permitted succeeding .");
				return 0;
			}
		}
		return 1;	
	}
	printf("\nInvalid Username: Username must begin with a alphabet");
	return 0;
}

int validate_password(char string[20],int length)
{
	int i=0,flag=1;
	if( length<8 )
	{
		printf("\nWarning: Password too short; must be min 8 chracters long");
		return 0;
	}
	for( i=0 ; (string[i]) != '\0' ; i++ )
	{
		if( isalnum(string[i]) == 0 )
		{
			for( i=0 ; (string[i]) != '\0' ; i++ )
			{
				if( isalpha(string[i]) )
				{
					flag=0;
					break;
				}
			}
			if( flag == 1 )
			{
				printf("\nWarning: Password too weak; must contain an alphabet");
				return 0;
			}
			for( i=0 ; (string[i]) != '\0' ; i++ )
			{
				if( isdigit(string[i]) )
				{
					return 1;
				}
			}
			printf("\nWarning: Password too weak; must contain a digit");
			return 0;
		}
	}
	printf("\nWarning: Password too weak; must contain a special character");
	return 0;
}

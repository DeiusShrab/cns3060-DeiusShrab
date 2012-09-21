/*	
*	
*/	
#include	<stdio.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<string.h>

int main(int argc, char* argv[])
{
	int i = 1;
	int lnNums = 0;
	int ln = 0;
	FILE *file = NULL;
	char ch = 'a';
	char buff[256];

	if (argc > 1)
	{
		for(i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (strcmp(argv[i], "-n") == 0)
				{
					lnNums = 1;
					if (argc == i + 1)
					{
						while (!ferror(stdin) && !feof(stdin))
						{
							ln++;
							if (fgets(buff, 256, stdin) != NULL)
							{
								printf("%5d\t", ln);
								fputs(buff, stdout);
							}
						}
					}
				}
				else
				{
					printf("invalid option\n");
				}
			}
			// if not an option, attempt to open file
			// adds line numbers if option selected, option must be given for each file
			else
			{
				// attempt to open file
				file = fopen(argv[i], "r");
				if (file == NULL)
				{
					printf("error opening file\n");
				}
				else
				{
					while (!ferror(file) && !feof(file))
					{
						if (fgets(buff, 256, file) != NULL)
						{
							if (lnNums == 1)
							{
								ln++;
								printf("%5d\t", ln);	
							}
							fputs(buff, stdout);
						}
					}					

					//printf("opened file successfully!\n");
					fclose(file);
					printf("\n");
				}

				lnNums = 0;
				ln = 0;
			}
		}
	}
	else
	{
		while (!ferror(stdin) && !feof(stdin))
		{
			if (fgets(buff, 256, stdin) != NULL)
			{
				fputs(buff, stdout);
			}
		}
	}	


	return 0;
}

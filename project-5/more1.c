/*	
*	Jacob Christensen CS3060-601
*/	
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<termios.h>
#include	<fcntl.h>
#include	<signal.h>

// global variables
int BUFF = 256;
float fSize = 1;
float bSize = 0;
int fd_tty = 0;
int fromFile = 0;
int firstPage = 1;
struct termios SETTINGS;
FILE *fp_tty = NULL;
char* filename = NULL;


// function prototypes
void sigCatch(int s);
int newPage(FILE *input, char *buffer, int n);
int newLine(FILE *input, char *buffer, int n);

// main function
int main(int argc, char* argv[])
{
	// variables
	int result, n;
	FILE *input = NULL;
	char buffer[BUFF];
	char usrIn = 0;
	struct termios USRINPUT;
	
	// getting terminal info and backing up settings
	fd_tty = open("/dev/tty", O_RDONLY);
	fp_tty = fdopen(fd_tty, "r");
	result = tcgetattr(fd_tty, &SETTINGS);
	if (result != 0)
	{
		printf("Unable to back up terminal settings, aborting...");
		return 0;
	}
	result = tcgetattr(fd_tty, &USRINPUT);
	// setting up the signal catch
	signal( SIGINT, sigCatch );
	// ----------
	
	
	// deciding input based on arguments
	if ( argc == 1 )
		input = stdin;
	else if ( argc == 2 )
	{
		input = fopen(argv[1], "r");
		if ( input == NULL)
		{
			printf("Error opening file\n");
			return 0;
		}
		fromFile = 1;
		filename = argv[1];
		fseek(input, 0L, SEEK_END);
		fSize = ftell(input);
		rewind(input);
	}
	else
	{
		printf("Usage: more1 <file path> OR <program> | more1\n");
		return 0;
	}
	// ----------
	
	
	// setting up the terminal flags
	USRINPUT.c_lflag &= ~ECHO;
	USRINPUT.c_lflag &= ~ICANON;
	// ----------
	
	
	// Getting user input and printing text
	n = newPage(input, buffer, n);
	tcsetattr(fd_tty, TCSANOW, &USRINPUT);
	while (usrIn != 'q' && usrIn != 'Q' && usrIn >= 0)
	{
		usrIn = fgetc(stdin);
		if (usrIn == ' ')
		{
			tcsetattr(fd_tty, TCSANOW, &SETTINGS);
			n = newPage(input, buffer, n);
			tcsetattr(fd_tty, TCSANOW, &USRINPUT);
		}
		else if (usrIn == '\n')
		{
			tcsetattr(fd_tty, TCSANOW, &SETTINGS);
			n = newLine(input, buffer, n);
			tcsetattr(fd_tty, TCSANOW, &USRINPUT);
		}
	}
	// ----------
	
	
	// TEST AREA PLEASE IGNORE
	//printf("\n%.2f\n", fSize);
	// ----------
	
	
	// returning the terminal to normal and exiting
	result = tcsetattr(fd_tty, TCSANOW, &SETTINGS);
	if (result == 0)
	{
		printf("\n");
		return 0;
	}

	
	printf("Unable to restore terminal settings");
	fprintf(stderr, "Unable to restore terminal settings");
	return 0;
	// ----------
}

void sigCatch(int s)
{
	tcsetattr(fd_tty, TCSANOW, &SETTINGS);
	printf("\nRestored terminal settings, exiting...\n");
	exit(0);
}

int newPage(FILE *input, char *buffer, int n)
{
	int i, j;
	float perc;
	
	for (i = 0; i < n; i++)
		printf("\b \b");

	for ( i = 0; i < 23; i++ )
	{
		if ( fgets(buffer, BUFF, input) != NULL)
		{
			for ( j = 0; j < BUFF; j++)
			{
				if ( buffer[j] == '\0' )
					break;
				bSize++;
			}
			
			fputs(buffer, stdout);
			
		}
		else
		{
			printf("\033[7m--END OF FILE--\033[m\n");
			break;
		}
	}
	i = 0;
	if (firstPage == 1)
	{
		i = printf("\033[7m\"%s\" \033[m", filename);
		firstPage = 0;
	}
	if (fromFile == 1)
	{
		perc = (bSize / fSize) * 100;
		i += printf("\033[7m\%.2f%%\033[m", perc);
		return i;
	}
	else
	{
		perc = bSize;
		i += printf("\033[7m\%.0f Bytes\033[m", perc);
		return i;
	}
	
	
}

int newLine(FILE *input, char *buffer, int n)
{
	int i, j;
	float perc;
	
	for (i = 0; i < n; i++)
		printf("\b \b");
	if ( fgets(buffer, BUFF, input) != NULL)
	{
		for ( j = 0; j < BUFF; j++)
		{
			if ( buffer[j] == '\0' )
				break;
			bSize++;
		}
		
		fputs(buffer, stdout);
	}
	else
		return printf("\033[7m--END OF FILE--\033[m\n");
	
	if (fromFile == 1)
	{
		perc = (bSize / fSize) * 100;
		return printf("\033[7m\%.2f%%\033[m", perc);
	}
	else
	{
		perc = bSize;
		return printf("\033[7m\%.0f Bytes\033[m", perc);
	}
}

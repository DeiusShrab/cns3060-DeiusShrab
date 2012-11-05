/*	
*	Jacob Christensen CS3060-601
*/	
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<termios.h>

int main()
{
	// getting terminal info and backing up settings
	int fd_tty;
	FILE *fp_tty;
	fd_tty = open("/dev/tty", O_RDONLY);
	fp_tty = fdopen(fd_tty, "r");
	struct termios SETTINGS;
	result = tcgetattr(fd_tty, &SETTINGS);
	if (result != 0)
	{
		printf("Unable to back up terminal settings, aborting...");
		return 0;
	}
	//----------
	
	
	
	// returning the terminal to normal and exiting
	for (n = 0; n < 5; n++)
	{
		result = tcsetattr(fd_tty, TCSANOW, &SETTINGS);
		if (result == 0)
			return 0;
	}
	
	fprintf(stderr, "Unable to restore terminal settings");
	return 0;
	//----------
}

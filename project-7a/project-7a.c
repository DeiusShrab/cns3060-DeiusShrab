/*	
*	Jacob Christensen CS3060-601
*/	
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<signal.h>


// function prototypes
void parent_sig1(int s);
void parent_sig2(int s);
void child_sig1(int s);
void child_sig2(int s);
void parentCode();
void childCode();
void work_function();

// global variables
static volatile sig_atomic_t sigreceived_P = 0;
static volatile sig_atomic_t sigreceived_C = 0;
pid_t childpid;
sigset_t mask_sig1, mask_sig2, mask_all, mask_old;

// main function
int main()
{
	printf("Jacob Christensen\nCS3060-601\n");
	
	// registering signal handlers for parent
	signal( SIGUSR1, parent_sig1 );
	signal( SIGUSR2, parent_sig2 );
	
	// setting up signal masks
	sigfillset(&mask_all);
	sigfillset(&mask_sig1);
	sigfillset(&mask_sig2);
	sigdelset(&mask_sig1, SIGUSR1);
	sigdelset(&mask_sig2, SIGUSR2);
	
	//spawning child process
	
	childpid = fork();
	if( childpid == -1 )
	{
		perror ("Failed to create child process");
		return 1;
	}
	if( childpid == 0 )
	{
		childCode();
	}
	else
	{
		parentCode();
	} 
	
	return 0;
}

void parentCode()
{
	printf("[P] - Child process successfully created\n");
	sleep(3);
	
	printf("[P] - Sending Task Start Signal to child\n");
	kill(childpid, SIGUSR1);
	
	// waiting for sigusr1 from child
	sigprocmask(SIG_SETMASK, &mask_all, &mask_old);
	if (sigreceived_P == 0)
		sigsuspend(&mask_sig1);
	sigprocmask(SIG_SETMASK, &mask_old, NULL);
	sigreceived_P = 0;
	
	sleep(3);
	kill(childpid, SIGUSR2);
	printf("[P] - Sent status request to child\n");
	
	// waiting for sigusr2 from child
	sigprocmask(SIG_SETMASK, &mask_all, &mask_old);
	if (sigreceived_P == 0)
		sigsuspend(&mask_sig2);
	sigprocmask(SIG_SETMASK, &mask_old, NULL);
	sigreceived_P = 0;
	
	sleep(1);
	printf("[P] - Exiting...\n");
	
	exit(0);
}

void childCode()
{
	// setting child signal handlers
	signal( SIGUSR1, child_sig1 );
	signal( SIGUSR2, child_sig2 );
	
	printf("[C] - Child process running, waiting for Task Start signal\n");
	
	// waiting for sigusr1 from parent
	sigprocmask(SIG_SETMASK, &mask_all, &mask_old);
	if (sigreceived_C == 0)
		sigsuspend(&mask_sig1);
	sigprocmask(SIG_SETMASK, &mask_old, NULL);
	sigreceived_C = 0;
	
	printf("[C] - Notifying parent of beginning work\n");
	sleep(3);
	kill(getppid(), SIGUSR1);
	
	work_function();
	
	printf("[C] - Work complete\n");
	
	// waiting for sigusr2 from parent
	sigprocmask(SIG_SETMASK, &mask_all, &mask_old);
	if (sigreceived_C == 0)
		sigsuspend(&mask_sig2);
	sigprocmask(SIG_SETMASK, &mask_old, NULL);
	sigreceived_C = 0;
	
	printf("[C] - Informing parent that work is complete\n");
	kill(getppid(), SIGUSR2);
	printf("[C] - Exiting...\n");
	
	exit(0);
}

void parent_sig1(int s)
{
	printf("**Parent SIGUSR1 Handler - Received 'Task Started' signal from child**\n");
	sigreceived_P = 1;
}

void parent_sig2(int s)
{
	printf("**Parent SIGUSR2 Handler - Received 'Task Completed' signal from child**\n");
	sigreceived_P = 1;
}

void child_sig1(int s)
{
	printf("**Child SIGUSR1 Handler - Received 'Task Start' signal from parent**\n");
	sigreceived_C = 1;
}

void child_sig2(int s)
{
	printf("**Child SIGUSR2 Handler - Received 'Task Complete Verification' signal from parent**\n");
	sigreceived_C = 1;
}

void work_function()
{
	printf("\nTOMORROW\nI'LL\nINVENT\nTHOSE\nBLUEPRINTS\n\n");
}

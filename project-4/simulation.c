/*	
*	Jacob Christensen CS3060-601
*	According to the grading chart we get 10 points 3 times, a total of 30 points, for showing the first-come-first-serve algorithm.
*	I assume this is an error, and have included all three algorithms
*/	
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<math.h>

// global variables
int TRACKLIM = 100;
int BUFF = 256;

// printTrack, a function that prints the formatted table, takes the start and end tracks as inputs and calculates (and returns) abs(S-E)
int printTrack(int S, int E);

// printList, a function that calls printTrack for each pair of numbers in a list
void printList(int* T, int Siz);

int sstfSort(int* T);

int sstfSortSub(int S, int* T);

void elevSort(int* T, int Siz);

void sort(int* T, int Siz);

int main()
{
	
	int i = 0;
	int j = 0;
	int k = 0;
	int valid = 0;
	int tracks[TRACKLIM];
	char input[BUFF];
	
	int tempTracks[TRACKLIM];

	printf("Jacob Christensen\nCS3060-601\n\n");

	// getting and validating input goes hurr
	printf("Enter track numbers one at a time\nUse a negative number to end\n");
	
	while (valid != 1 && j < TRACKLIM)
	{
		printf("> ");
		fgets(input, BUFF, stdin);
		i = atoi(input);
		if (i >= 0)
		{
			tracks[j] = i;
			j++;
		}
		else
		{
			valid = 1;
		}
	}
	

	// FCFS goes hurr, basically just calling printList
	printList(tracks, j);

	// SSTF goes hurr, see notes for recursive function, then call printList with new sorted list
	// WHOOPS I THOUGHT THIS WAS DUE THURSDAY NOT TODAY SO I DIDN'T DO THIS ONE

	// Elevator goes hurr, 	put all values lower than STARTPOS in a second list and sort the first list LtH
	// then sort the second list HtL and append it to the first list, send final list to printList

	//surprise surprise, this doesn't work. Didn't give myself enough time to figure out why
	//because, again, I thought it was due thursday. MY BAD LOLOL.
	for (i = 0; i < j; i++)
	{
		tempTracks[i] = tracks[i];
	}
	elevSort(tempTracks, j);
	printList(tempTracks, j);

	//for (k = 0; k < j; k++)
	//{
	//	printf("%d, ", tracks[k]);
	//}


	return 0;
}

int printTrack(int S, int E)
{
	// special formatting for table goes here
	// S to E, abs(S-E)
	// return tracks traversed
	int t = abs(S-E);
	printf("Tracks %d - %d\t\t%d\n", S, E, t);

	return t;	
}

void printList(int* T, int Siz)
{
	int i;
	int tot = 0;

	printf("\nHead Movement\t\tTracks Traversed\n");

	for (i = 1; i < Siz; i++)
	{
		tot += printTrack(T[i - 1], T[i]);
	}

	printf("Total Tracks Traversed:\t%d\n\n", tot);
}

int sstfSort(int* T)
{
	// builds a new list of integers in order of closest-first, starting with the first
}

int sstfSortSub(int S, int* T)
{
	// returns the closest integer in the list to the given integer, ignoring '-1'
}

void elevSort(int* T, int Siz)
{
	int S = T[0];
	int T2[TRACKLIM];
	int i;
	int j = 0;
	int k;

	for (i = 1; i < Siz; i++);
	{
		if (T[i] < S)
		{
			T2[j++] = T[i];
			T[i] = -1;
		}
	}
	
	sort(T, Siz);
	sort(T2, j);
	// j now equals Siz of T2, T2 contains all ints lower than S
	k = j;
	for (i = (Siz - j) + 1; i < Siz; i++)
	{
		T[i] = T2[k--];
	}
}

void sort(int *T, int Siz)
{
	int i;
	int k;
	int temp;
	for (i = 1; i < Siz; i++)
	{
		for (k = 1; k < Siz; k++)
		{
			if (T[k-1] > T[k] | T[k] == -1)
			{
				temp = T[k];
				T[k] = T[k-1];
				T[k-1] = temp;
			}
		}
	}
}

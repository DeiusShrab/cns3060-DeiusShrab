Project 6 - Threads

==========

Jacob Christensen

Part A -
The program ran and reported that count was at 0 when it exited. I assume this is because it took much longer to get the four threads running than it did to print the variable.

Part B -
This one scared me for a minute, but only because I forgot there was a sleep inside the loop. It reported '10', which is to be expected since each thread is replacing count with its own copy instead of updating it

Part C -
The program reported '40', which surprised me because I thought it would be some random number in between 10 and 40 as the different threads scrambled to grab their own copy of count. I guess without the sleep, each thread executes in order. (which sort of defeats the purpose of having threads)

Part D -
This part sat there very politely for 40 seconds and reported 40

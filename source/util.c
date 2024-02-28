#include "include/philosophers.h"

//To help user with command
void	helper_print(void)
{
	/*Example: 5 800 200 200 7*/
	printf("Example: \x1b[32m 5 \x1b[33m 800 \x1b[34m 200 \x1b[35m 300"
		 "\x1b[36m 7\x1b[37m\n");
	printf("\x1b[32m 5  \x1b[37m: The number of philosophers\n");
	printf("\x1b[33m 800\x1b[37m: The time a philosopher will die if he"
		 "doesn’t eat\n");
	printf("\x1b[34m 200\x1b[37m: The time it takes a philosopher to eat\n");
	printf("\x1b[35m 300\x1b[37m: The time it takes a philosopher to sleep\n");
	printf("\x1b[36m 7  \x1b[37m: (optional) Number of times all the "
		 "philosophers need to eat before terminating the program\n");
}

//String describes the error to exit program.
void	err_out(char *s)
{
	printf("\x1b[31m%s\x1b[37m\n", s);
	exit (1);
}
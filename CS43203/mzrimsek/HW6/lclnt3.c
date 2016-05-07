/**
 * Mike Zrimsek
 * Systems Programming
 * Homework 6 - lclnt3
 */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
		setup();
		if (get_ticket() != 0){
				exit(0);
		}

		do_regular_work();

		release_ticket();
		shut_down();
}
do_regular_work()
{
		printf("SuperSleep version 1.0 Running - Licensed Software\n");
		sleep(15);

		if (validate_ticket() != 0 && get_ticket() != 0){
				printf("Server errors. Please Try later.\n");
				return;
		}
		sleep(15);
}

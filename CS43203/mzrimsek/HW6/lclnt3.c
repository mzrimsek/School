/**
 * Mike Zrimsek
 * Systems Programming
 * Homework 6 - lclnt3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	setup();
void shut_down();
void do_regular_work();
int	get_ticket();
int	validate_ticket();
void release_ticket();

int main(int ac, char *av[])
{
		setup();
		if (get_ticket() != 0 ){
				exit(0);
		}

		do_regular_work();
		
		release_ticket();
		shut_down();
		return 0;
}

void do_regular_work()
{
		printf("SuperSleep version 1.0 Running - Licensed Software\n");
		sleep(15);

		if (validate_ticket() != 0 && get_ticket() != 0 ){
				printf("Server errors. Please Try later.\n");
				return;
		}
		sleep(15);
}

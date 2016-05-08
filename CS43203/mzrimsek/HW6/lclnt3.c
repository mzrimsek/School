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

		int i;
		for(i = 0; i < 2; i++){
				sleep(10);
				if(do_regular_work() == 0){
						break;
				}
		}
		if(i == 2){
				printf("Server errors. Please Try later.\n");
				exit(0);
		}
		sleep(10);

		release_ticket();
		shut_down();
}
do_regular_work()
{
		printf("SuperSleep version 1.0 Running - Licensed Software\n");
		sleep(15);

		if (validate_ticket() != 0 && get_ticket() != 0){
				return -1;
		}
		sleep(15);
		return 0;
}

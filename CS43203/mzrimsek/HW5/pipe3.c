/*
Mike Zrimsek
Systems Programming
Homework 5 - pipe3
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define	oops(m)  { perror(m); exit(1); }

int pipeCommands(int ac, char *av[]){
		int	thepipe[2];
		pid_t	pid;

		//no commands to pipe
		if (ac == 1){
				fprintf(stderr,"usage: pipe3 cmd1 cmd2 ..\n");
				exit(1);
		}

		//only one command
		if (ac == 2){
				execlp(av[1],av[1],NULL);
				oops(av[1]);
		}

		//get a pipe
		if (pipe(thepipe) == -1){
				oops("Cannot get pipe");
		}

		//get a process
		pid = fork();
		if (pid == -1){
				oops("Cannot fork");
		}

		//write stdout into pipe[1]
		if (pid == 0){
				if (dup2(thepipe[1], 1) == -1){
						oops("dup2");
				}
				if (close(thepipe[0]) == -1 || close(thepipe[1]) == -1){
						oops("close pipe");
				}
				pipeCommands(ac-1, av);
		}

		//read stdin from pipe[0]
		else {
				if (dup2(thepipe[0], 0) == -1){
						oops("dup2");
				}
				if (close(thepipe[0]) == -1 || close(thepipe[1]) == -1){
						oops("close pipe");
				}
				execlp(av[ac-1], av[ac-1], NULL);
				oops(av[ac-1]);
		}
		return 0;
}

int main(int ac, char *av[])
{
		exit(pipeCommands(ac, av));
}

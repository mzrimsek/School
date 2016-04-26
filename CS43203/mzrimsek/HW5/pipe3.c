#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define	oops(m,x)	{ perror(m); exit(x); }
//
// main(int ac, char **av)
// {
// 		int	thepipe[3],			/* two file descriptors	*/
// 		newfd,				/* useful for pipes	*/
// 		pid;				/* and the pid		*/
//
// 		//check num arguments
// 		if (ac != 4){
// 				fprintf(stderr, "usage: pipe3 cmd1 cmd2 cmd3\n");
// 				exit(1);
// 		}
//
// 		//get pipes
// 		if (pipe(thepipe) == -1){
// 				oops("Cannot get a pipe", 1);
// 		}
//
// 	/* ------------------------------------------------------------ */
// 	/*	now we have a pipe, now let's get two processes		*/
//
// 		if ((pid = fork()) == -1){		/* get a proc	*/
// 				oops("Cannot fork", 2);
// 		}
//
// 	/* ------------------------------------------------------------ */
// 	/* 	Right Here, there are two processes			*/
// 	/*             parent will read from pipe			*/
//
// 		if (pid > 0){			/* parent will exec av[2]	*/
// 				close(thepipe[1]);	/* parent doesn't write to pipe	*/
//
// 				if (dup2(thepipe[0], 0) == -1){
// 						oops("could not redirect stdin",3);
// 				}
//
// 				close(thepipe[0]);	/* stdin is duped, close pipe	*/
// 				execlp(av[2], av[2], NULL);
// 				oops(av[2], 4);
// 		}
//
// 	/*	 child execs av[1] and writes into pipe			*/
//
// 		close(thepipe[0]);		/* child doesn't read from pipe	*/
//
// 		if (dup2(thepipe[1], 1) == -1){
// 				oops("could not redirect stdout", 4);
// 		}
//
// 		close(thepipe[1]);		/* stdout is duped, close pipe	*/
// 		execlp(av[1], av[1], NULL);
// 		oops(av[1], 5);
// }

int spawn_process(int in, int out, char **av){
		int pid;

		if((pid = fork()) == 0){
				if(in != 0){
						dup2(in, 0);
						close(in);
				}

				if(out != 1){
						dup2(out, 1);
						close(out);
				}
				return execlp(av[0], av[0], NULL);
		}
		return pid;
}

int fork_pipes(int n, char **av){
		int i, pid, fd[2];
		int in = 0;

		for(i = 0; i < n-1; i++){
				pipe(fd);
				spawn_process(in, fd[1], av[i+1]);
				close(fd[1]);
				in = fd[0];
		}

		if(in != 0){
				dup2(in, 0);
		}
		return execlp(av[i], av[i], NULL);
}

int main(int ac, char **av){
		return fork_pipes(ac, **av);
}

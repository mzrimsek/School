/*
Mike Zrimsek
Systems Programming
Homework 5 - pipe3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define oops(m, x) { perror(m); exit(x); }

main(int ac, char **av){
    int first_pipe[2];
    int second_pipe[2];
    int pid;

    //check argument count
    if(ac != 4){
        fprintf(stderr, "usage: pipe3 cmd1 cmd2 cmd3\n");
        exit(1);
    }

    //make first pipe
    if(pipe(first_pipe) == -1){
        oops("Cannot get pipe", 1);
    }

    //fork for first command
    if((pid = fork()) == -1){
        oops("Cannot fork", 2);
    }
    else{
        dup2(first_pipe[1], 1);

        close(first_pipe[0]);
        close(first_pipe[1]);

        execlp(av[1], av[1], NULL);
        oops(av[1], 4);
    }

    //make second pipe
    if(pipe(second_pipe) == -1){
        oops("Cannot get pipe", 1);
    }

    //fork for second command
    if((pid = fork()) == -1){
        oops("Cannot fork", 2);
    }
    else{
        dup2(first_pipe[0], 0);
        dup2(second_pipe[1], 1);

        close(first_pipe[0]);
        close(first_pipe[1]);
        close(second_pipe[0]);
        close(second_pipe[1]);

        execlp(av[2], av[2], NULL);
        oops(av[2], 4);
    }

    close(first_pipe[0]);
    close(first_pipe[1]);

    if((pid = fork()) != -1){
        oops("Cannot fork", 2);
    }
    else{
        dup2(second_pipe[0], 0);

        close(second_pipe[0]);
        close(second_pipe[1]);

        execlp(av[3], av[3], NULL);
        oops(av[3], 4);
    }
}

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

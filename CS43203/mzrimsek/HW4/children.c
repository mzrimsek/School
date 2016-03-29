/*
Mike Zrimsek
Systems Programming
Homework 4 - children
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int delay= 5;
int num_children;
int num_dead;

void child_code(int num) {
    printf("Child process #%d (%d) will sleep for %d seconds\n", num, getpid(), delay);
    sleep(delay);
    printf("Child process #%d (%d) done sleeping. Exiting now.\n", num, getpid());
    exit(num);
}

void parent_code() {
    void get_status(int);

    while(1){
        printf("Parent process waiting ..%d children still sleeping\n", (num_children-num_dead));
        sleep(1);
    }
}

void get_status(int s) {
    int child_status;

    signal(SIGCHLD, get_status);

    int wait_val = wait(&child_status);
    printf("Parent done waiting for child. Wait returned: %d\n", wait_val);

    int high_8 = child_status >> 8;
    int low_7  = child_status & 0x7F;
    int bit_7  = child_status & 0x80;
    printf("Child status: Exit=%d, Sig=%d, Core=%d\n", high_8, low_7, bit_7);

    num_dead++;
    if(num_dead == num_children){
        exit(0);
    }
}

int oops(s,x) {
    perror(s); exit(x);
}

int main(int ac, char *av[]) {
    pid_t newpid;

    if(ac == 1){
        fprintf(stderr,"Please make sure you enter a number of children.");
        exit(1);
    }

    int n = atoi(av[1]);
    signal(SIGCHLD, get_status);

    num_children = n;
    num_dead = 0;

    int i;
    for(i=0; i<n; i++){
        if ((newpid = fork()) == -1){
            oops("fork",2);
        }
        if (newpid == 0){
            child_code(i+1);
        }
    }
    parent_code();
}

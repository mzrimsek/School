/*
Mike Zrimsek
Systems Programming
Homework 5 - myfingerd
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

#define FINGER_PORT 2345
#define FINGER_COMMAND "usr/bin/finger"
#define oops(m) { perror(m); exit(1); }

main(int ac, char *av[]){
    if(ac != 3){
        oops("Usage: myfingerd <username> <hostname>");
    }

    struct sockaddr_in saddr;
    struct hostent *hp;
    int sock_id, sock_fd, pid, saddr_len;

    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1){
        oops("socket");
    }

    bzero((void *)&saddr, sizeof(&saddr));
    hp = gethostbyname(av[2]);
    bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
    saddr.sin_port = htons(FINGER_PORT);
    saddr.sin_family = AF_INET;

    printf(hp->h_addr);

    if(bind(sock_id, (struct sockaddr_in *)&saddr, sizeof(saddr)) != 0){
        oops("bind");
    }

    while(1){
        sock_fd = accept(sock_id, (struct sockaddr_in *)&saddr, sizeof(saddr));
        if(sock_fd < 0){
            oops("accept");
        }

        printf ("connection from %s\n", inet_ntoa (saddr.sin_addr));

        pid = fork();
        if(pid != 0){
            if(dup2(sock_id, 1) < 0 || dup2(sock_id, 2) < 0){
                oops("dup2");
            }
            close(sock_id);
            execl(FINGER_COMMAND, "finger", "--", av[1], NULL);
            oops(FINGER_COMMAND);
        }
    }
}

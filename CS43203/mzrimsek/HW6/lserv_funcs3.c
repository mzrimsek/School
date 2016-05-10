/**
 * Mike Zrimsek
 * Systems Programming
 * Homework 6 - lserv_funcs3.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <string.h>
#include "dgram.h"

#define SERVER_PORTNUM 2020
#define MSGLEN 128
#define TICKET_AVAIL 0
#define MAXUSERS 3
#define oops(x) { perror(x); exit(-1); }
#define RECLAIM_INTERVAL 5

int setup();
void shut_down();
void handle_request(char *,struct sockaddr *, socklen_t);
void narrate(char *, char *, struct sockaddr *);
void ticket_reclaim();
void free_all_tickets();
void show_tickets_up(int);
void show_tickets_quit(int);
static char *do_hello(char *, struct sockaddr *);
static char *do_goodbye(char *, struct sockaddr *);
static char *do_validate(char *,struct sockaddr *);

struct ticket {
    pid_t pid;
    struct in_addr host;
};

struct ticket tickets[MAXUSERS];
int my_socket = -1;
int num_tickets_out = 0;

static char *do_hello();
static char *do_goodbye();
static char *do_validate();

int setup()
{
    my_socket = make_dgram_server_socket(SERVER_PORTNUM);
    if(my_socket == -1){
        oops("make socket");
    }
    free_all_tickets();
    return my_socket;
}
void free_all_tickets()
{
    int i;
    for(i = 0; i < MAXUSERS; i++){
        tickets[i].pid = TICKET_AVAIL;
    }
}
void shut_down()
{
    close(my_socket);
    exit(1);
}
void handle_request(char *req,struct sockaddr *client, socklen_t addlen)
{
    char *response;
    int ret;

    if(strncmp(req, "HELO", 4) == 0){
        response = do_hello(req, client);
    }
    else if(strncmp(req, "GBYE", 4) == 0){
        response = do_goodbye(req, client);
    }
    else if(strncmp(req, "VALD", 4) == 0){
        response = do_validate(req, client);
    }
    else{
        response = "FAIL invalid request";
    }
    narrate("SAID:", response, client);
    ret = sendto(my_socket, response, strlen(response), 0, client, addlen);
    if (ret == -1){
        perror("SERVER sendto failed");
    }
}
static char *do_hello(char *msg_p, struct sockaddr *client)
{
    static char replybuf[MSGLEN];
    struct in_addr ip_address;

    if(num_tickets_out >= MAXUSERS){
        return("FAIL no tickets available");
    }

    int i;
    for(i = 0; i < MAXUSERS && tickets[i].pid != TICKET_AVAIL; i++);

    if(i == MAXUSERS) {
        narrate("database corrupt", "", NULL);
        return("FAIL database corrupt");
    }

    ip_address = ((struct sockaddr_in *)client)->sin_addr;
    tickets[i].pid  = atoi(msg_p + 5);
    tickets[i].host = ip_address;
    sprintf(replybuf, "TICK %d.%d.%s", tickets[i].pid, i, inet_ntoa(ip_address));
    num_tickets_out++;
    return(replybuf);
}
static char *do_goodbye(char *msg_p, struct sockaddr *client)
{
    int pid, slot;
    char addr[MSGLEN];

    if((sscanf((msg_p + 5), "%d.%d.%s", &pid, &slot, addr) != 3) || (tickets[slot].pid != pid) || (strcmp(addr, inet_ntoa(tickets[slot].host))!=0)){
        narrate("Bogus ticket", msg_p + 5, NULL);
        return("FAIL invalid ticket");
    }
    tickets[slot].pid = TICKET_AVAIL;
    num_tickets_out--;
    return("THNX See ya!");
}
void narrate(char *msg1, char *msg2, struct sockaddr *clientp)
{
    struct sockaddr_in *p = (struct sockaddr_in *) clientp;

    fprintf(stderr,"\t\tSERVER: %s %s ", msg1, msg2);
    if (clientp){
        fprintf(stderr,"(%s:%d)", inet_ntoa(p->sin_addr), ntohs(p->sin_port) );
    }
    putc('\n', stderr);
}
static char *do_validate(char *msg, struct sockaddr *client)
{
    int  pid, slot;
    char addr[MSGLEN];

    struct in_addr caller_ip = ((struct sockaddr_in*)client)->sin_addr;
    int addrlen = sizeof(struct in_addr);

    if (sscanf(msg+5,"%d.%d.%s",&pid,&slot,addr) == 3 && tickets[slot].pid == pid && strcmp(addr, inet_ntoa(tickets[slot].host)) == 0 && memcmp(&caller_ip,&(tickets[slot].host),addrlen) == 0){
        return("GOOD Valid ticket");
    }
    narrate("Bogus ticket", msg+5, NULL);
    return("FAIL invalid ticket");
}
void ticket_reclaim()
{
    char tick[BUFSIZ];

    int i;
    for(i = 0; i < MAXUSERS; i++) {
        if((tickets[i].pid != TICKET_AVAIL) && (kill(tickets[i].pid, 0) == -1) && (errno == ESRCH)) {
            sprintf(tick, "%d.%d.%s", tickets[i].pid, i, inet_ntoa(tickets[i].host));
            narrate("freeing", tick, NULL);
            tickets[i].pid = TICKET_AVAIL;
            num_tickets_out--;
        }
    }
    alarm(RECLAIM_INTERVAL);
}
void show_tickets_up(int s)
{
	int	i;
	for(i = 0; i<MAXUSERS; i++){
		printf("%3d\t", i);
		if (tickets[i].pid == TICKET_AVAIL){
    		printf("FREE\n");
        }
		else{
            printf("%5d\n", tickets[i]);
        }
	}
}
void show_tickets_quit(int s)
{
	show_tickets_up(s);
	printf("Shutting down\n");
	shut_down();
}

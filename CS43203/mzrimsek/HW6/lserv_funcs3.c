/**
 * Mike Zrimsek
 * Systems Programming
 * Homework 6 - lserv_funcs3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <sys/errno.h>

#define SERVER_PORTNUM 2020
#define MSGLEN 128
#define TICKET_AVAIL 0
#define MAXUSERS 3
#define	oops(x)	{ perror(x); exit(-1); }

#define RECLAIM_INTERVAL 5

struct ticket {
		pid_t pid,
		struct in_addr host
};

struct ticket ticket_array[MAXUSERS];
int sd = -1;
int num_tickets_out = 0;

static char *do_hello();
static char *do_goodbye();
static char *do_validate();

setup()
{
		sd = make_dgram_server_socket(SERVER_PORTNUM);
		if (sd == -1){
				oops("make socket");
		}
		free_all_tickets();
		return sd;
}
free_all_tickets()
{
	int	i;

	for(i = 0; i < MAXUSERS; i++)
		ticket_array[i].pid = TICKET_AVAIL;
}
shut_down()
{
	close(sd);
}
handle_request(char *req, struct sockaddr *client, socklen_t addlen)
{
		char *response;
		int	ret;

		if (strncmp(req, "HELO", 4) == 0){
				response = do_hello(req);
		}
		else if (strncmp(req, "GBYE", 4) == 0){
				response = do_goodbye(req);
		}
		else if (strncmp(req, "VALD", 4) == 0){
				response = do_validate(req);
		}
		else{
				response = "FAIL invalid request";
		}
		narrate("SAID:", response, client);
		ret = sendto(sd, response, strlen(response), 0, client, addlen);
		if (ret == -1){
				perror("SERVER sendto failed");
		}
}
static char *do_hello(char *msg_p, struct sockaddr_in *clientp)
{
		int x;
		static char replybuf[MSGLEN];
		struct in_addr ip_address;

		if(num_tickets_out >= MAXUSERS){
				return("FAIL no tickets available");
		}

		for(x = 0; x < MAXUSERS && ticket_array[x].pid != TICKET_AVAIL; x++);

		if(x == MAXUSERS) {
				narrate("database corrupt","",NULL);
				return("FAIL database corrupt");
		}
		ip_address = ((struct sockaddr_in *)client)->sin_addr;
		ticket_array[x].pid = atoi(msg_p + 5);
		ticket_array[x].host = ip_address;
		sprintf(replybuf, "TICK %d.%d", ticket_array[x], x);
		num_tickets_out++;
		return(replybuf);
}
static char *do_goodbye(char *msg_p)
{
		int pid, slot;
		char addr[MSGLEN];

		if((sscanf((msg_p + 5), "%d.%d", &pid, &slot) != 2) || (ticket_array[slot].pid != pid) || (strcmp(addr, inet_ntoa(ticket_array[slot].host))!=0)) {
				narrate("Bogus ticket", msg_p+5, NULL);
				return("FAIL invalid ticket");
		}
		ticket_array[slot].pid = TICKET_AVAIL;
		num_tickets_out--;
		return("THNX See ya!");
}
narrate(char *msg1, char *msg2, struct sockaddr_in *clientp)
{
		struct sockaddr_in *p = (struct sockaddr_in *) clientp;

		fprintf(stderr,"\t\tSERVER: %s %s ", msg1, msg2);
		if (clientp){
				fprintf(stderr,"(%s:%d)", inet_ntoa(clientp->sin_addr), ntohs(clientp->sin_port) );
		}
		putc('\n', stderr);
}
static char *do_validate(char *msg, struct sockaddr_in *clientp)
{
		int pid, slot;
		char addr[MSGLEN];

		struct in_addr caller_ip = ((struct sockaddr_in*)clientp)->sin_addr;
    int addrlen = sizeof(struct in_addr);

		if (sscanf(msg+5, "%d.%d", &pid, &slot)==2 && ticket_array[slot].pid == pid && memcmp(&caller_ip, &(ticket_array[slot].host), addrlen) == 0){
				return("GOOD Valid ticket");
		}
		narrate("Bogus ticket", msg+5, NULL);
		return("FAIL invalid ticket");
}
void ticket_reclaim()
{
		int	i;
		char tick[BUFSIZ];

		for(i = 0; i < MAXUSERS; i++){
				if((ticket_array[i].pid != TICKET_AVAIL) && (kill(ticket_array[i].pid, 0) == -1) && (errno == ESRCH)) {
					sprintf(tick, "%d.%d.%s", ticket_array[i].pid, i, inet_ntoa(ticket_array[i].host));
						narrate("freeing", tick, NULL);
						ticket_array[i].pid = TICKET_AVAIL;
						num_tickets_out--;
				}
		}
		alarm(RECLAIM_INTERVAL);
}

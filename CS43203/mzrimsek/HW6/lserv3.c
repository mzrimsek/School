/**
 * Mike Zrimsek
 * Systems Programming
 * Homework 6 - lserv3
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/errno.h>

#define	MSGLEN 128
#define RECLAIM_INTERVAL 5

int main(int ac, char *av[])
{
		struct sockaddr client_addr;
		socklen_t addrlen;
		char buf[MSGLEN];
		int	value_from_socket, socket;
		void ticket_reclaim();
		void show_tickets_up(int);
		void show_tickets_quit(int);
		unsigned time_left;

		socket = setup();
		signal(SIGALRM, ticket_reclaim);
		signal(SIGHUP, show_tickets_up);
		signal(SIGQUIT, show_tickets_quit);
		alarm(RECLAIM_INTERVAL);

		while(1){
				addrlen = sizeof(client_addr);
				value_from_socket = recvfrom(socket, buf, MSGLEN, 0, (struct sockaddr *)&client_addr, &addrlen);
				if(value_from_socket != -1){
						buf[value_from_socket] = '\0';
						narrate("GOT:", buf, &client_addr);
						time_left = alarm(0);
						handle_request(buf, &client_addr, addrlen);
						alarm(time_left);
				}
				else if(errno != EINTR){
						perror("recvfrom");
				}
		}
}

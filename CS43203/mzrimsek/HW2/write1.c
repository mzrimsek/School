/*
Mike Zrimsek
Systems Programming
Homework 2 - Write
 */

#include	<stdio.h>
#include	<fcntl.h>
#include	<utmp.h>

/*
 * write1.c
 *
 *	purpose: send messages to another terminal
 *	 method: open the other terminal for output then
 *	 	 copy from stdin to that terminal
 *        usage: write1 username
 */


 /*
  * purpose: find the tty at which 'logname' is logged in
  * returns: a string or NULL if not logged in
  *  errors: does not handle multiple logins
  */
char* get_tty(char *logname){
    static struct utmp utrec;
 	  int utfd;
 	  int namelen = sizeof(utrec.ut_name);
 	  char *retval = NULL;

 	  if ((utfd = open(UTMP_FILE, O_RDONLY)) == -1){
 		   return NULL;
    }

    while(read( utfd, &utrec, sizeof(utrec)) == sizeof(utrec)){
        if (strncmp(logname, utrec.ut_name, namelen) == 0){
          retval = utrec.ut_line;
 			    break;
 		    }
    }

 	  close(utfd);
 	  return retval;
 }

int main(int ac, char *av[]){
    int	fd;
    char buf[BUFSIZ];
    char *tty_for_user;

	  if ( ac != 2 ){
		    fprintf(stderr,"usage: write0 logname\n");
		    exit(1);
	  }

	  tty_for_user = get_tty( av[1] );
	  if ( tty_for_user == NULL ){
		    return 1;
    }

    sprintf(buf, "/dev/%s", tty_for_user);
    fd = open(buf, O_WRONLY);
    if (fd == -1){
        perror(buf);
        exit(1);
    }

	  while(fgets(buf, BUFSIZ, stdin) != NULL){
        if (write(fd, buf, strlen(buf)) == -1){
			     break;
        }
	      close(fd);
    }
}

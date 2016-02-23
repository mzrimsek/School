/*
Mike Zrimsek
Systems Programming
Homework 2 - Write
 */

#include	<stdio.h>
#include	<fcntl.h>
#include	<utmp.h>
#include	<sys/stat.h>

int isacdev(char *s){
		struct stat info;

		return(stat(s,&info) != -1 && S_ISCHR(info.st_mode));
}

char* is_a_device(char *s){
    char	*rv;
	  char	*str_add(char*, char*);

		if (isacdev(s))
				return s;

		rv = str_add("/dev/", s);
		if (isacdev(rv))
				return rv;

		return NULL;
}

char* str_add(char *s1, char *s2){
		char *rv;
		if (s1 == NULL)
				return s2;
		if (s2 == NULL)
				return s1;

		rv = (char *)malloc(1 + strlen(s1) + strlen(s2) );
		if (rv == NULL){
				perror("out of memory");
					exit(1);
		}
		sprintf(rv,"%s%s", s1, s2);
		return rv;
}

char* get_tty(char *logname){
   	struct utmp *utrec;
 	  int utfd = 0;
 	  char *retval = NULL;

		setutent();
		while(utrec = getutent())
		{
				if (utrec->ut_type == USER_PROCESS
					&& strcmp(utrec->ut_user,logname)==0
					&& utrec->ut_line[0] != ':'
					&& is_a_device(utrec->ut_line)
		   ){
				 	utfd++;
					if (utfd == 1)
							retval = str_add("/dev/", utrec->ut_line );
				}
		}
		endutent();

		if (utfd > 1)
				printf("Warning: %s is logged in %d times, using %s\n",
				logname, utfd, retval);

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

	  tty_for_user = get_tty(av[1]);
	  if (tty_for_user == NULL){
				printf("No such user logged in");
		    return 1;
    }

    fd = open(tty_for_user, O_WRONLY);
    if (fd == -1){
        perror(tty_for_user);
        exit(1);
    }

	  while(fgets(buf, BUFSIZ, stdin) != NULL){
        if (write(fd, buf, strlen(buf)) == -1){
			     break;
        }
	      close(fd);
    }
}

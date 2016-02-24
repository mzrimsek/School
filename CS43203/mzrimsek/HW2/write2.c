/*
Mike Zrimsek
Systems Programming
Homework 2 - Write
 */

 #include	<stdio.h>
 #include	<fcntl.h>
 #include	<unistd.h>
 #include	<utmp.h>
 #include	<pwd.h>
 #include	<sys/types.h>
 #include	<stdlib.h>
 #include	<sys/stat.h>
 #include	<time.h>

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
 	  int num = 0;
 	  char *result = NULL;

		char	*mytty = ttyname(0);
		char	*ttydev = mytty + strlen("/dev/");

		setutent();
		while(utrec = getutent())
		{
				if (utrec->ut_type == USER_PROCESS
					&& strcmp(utrec->ut_user,logname)==0
					&& strcmp(utrec->ut_line,ttydev)!=0
					&& utrec->ut_line[0] != ':'
					&& is_a_device(utrec->ut_line)
		   ){
				 	num++;
					if (num == 1)
							result = str_add("/dev/", utrec->ut_line );
				}
		}
		endutent();

		if (num > 1)
				printf("Warning: %s is logged in %d times, using %s\n",
				logname, num, result);

 	  return result;
}

char* get_terminal(char *s){
		char *devname;

		if(devname = is_a_device(s)){
				return devname;
		}

		devname = get_tty(s);

		return devname;
}

int main(int ac, char *av[]){
    int	fd;
    char buf[BUFSIZ];
		char *termname;

	  if ( ac != 2 ){
		    fprintf(stderr,"usage: write0 logname\n");
		    exit(1);
	  }

		if((termname = get_terminal(av[1])) == NULL){
				printf("No such user found");
				exit(1);
		}

		fd = open(termname, O_WRONLY);
		if(fd == -1){
				perror(termname);
				exit(1);
		}

	  while(fgets(buf, BUFSIZ, stdin) != NULL){
        if (write(fd, buf, strlen(buf)) == -1){
			     break;
        }
	      close(fd);
    }
}

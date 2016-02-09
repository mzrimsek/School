#include        <stdio.h>
#include        <unistd.h>
#include        <fcntl.h>
#include        <cstdlib>
#include        <sys/stat.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644

void oops(char *, char *);

void copyfile(char *, char *);

main(int ac, char *av[]){
        //check args
        if ( ac != 3 ){
                fprintf( stderr, "usage: %s source destination\n", *av);
                exit(1);
        }
        copyfile(av[1], av[2]);
}

void copyfile(char *src_file, char *dest_file){
        int     in_fd, out_fd, n_chars;
        char    buf[BUFFERSIZE];
        //open files
        if ( (in_fd=open(src_file, O_RDONLY)) == -1 ){
                oops("Cannot open ", src_file);
        }


        if ( (out_fd=creat( dest_file, COPYMODE)) == -1 ){
                oops( "Cannot creat ", dest_file);
        }

        //copy files
        while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 ){
                if ( write( out_fd, buf, n_chars ) != n_chars ){
                        oops("Write error to ", dest_file);
                }
        }

	if ( n_chars == -1 ){
                oops("Read error from ", src_file);
        }

        //copy files
        if ( close(in_fd) == -1 || close(out_fd) == -1 ){
                oops("Error closing files","");
        }
}

void oops(char *s1, char *s2){
        fprintf(stderr,"Error: %s ", s1);
        perror(s2);
        exit(1);
}

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static  char utmpbuf[NRECS * UTSIZE];                /* storage      */
static  int num_recs;                               /* num stored   */
static  int cur_rec;                                /* next to go   */
static  int fd_utmp = -1;                           /* read from    */

utmp_open( char *filename ){
    fd_utmp = open( filename, O_RDONLY );           /* open it      */
    cur_rec = num_recs = 0;                         /* no recs yet  */
    return fd_utmp;                                 /* report       */
}

struct utmp *utmp_next(){
    struct utmp *recp;

    if ( fd_utmp == -1 ){
        return NULLUT;
    }                            /* error ?      */
    if ( cur_rec==num_recs && utmp_reload()==0 ){
        return NULLUT;
    }    /* any more ?   */
                                        /* get address of next record    */
    recp = ( struct utmp *) &utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

int utmp_reload(){
    int amt_read;
                                                /* read them in         */
    amt_read = read( fd_utmp , utmpbuf, NRECS * UTSIZE );

                                                /* how many did we get? */
    num_recs = amt_read/UTSIZE;
                                                /* reset pointer        */
    cur_rec  = 0;
    return num_recs;
}

utmp_close(){
    if ( fd_utmp != -1 ){
        close( fd_utmp );               /* open                 */
    }                   /* don't close if not   */
}

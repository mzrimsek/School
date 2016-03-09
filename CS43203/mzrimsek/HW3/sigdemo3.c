/*
Mike Zrimsek
Systems Programming
Homework 3 - Sigdemo
 */

#include	<stdio.h>
#include    <termios.h>

main()
{
    struct termios attrs;
    tcgetattr(0, &attrs);
    attrs.c_lflag = attrs.c_lflag & ~ISIG;
    tcsetattr(0, TCSANOW, &attrs);

    printf("you can't stop me!\n");
    while(1){
        sleep(1);
		printf("haha\n");
    }
}

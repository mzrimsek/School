#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("python test.py 1 2", "rt");
    char buf[255];

    fgets(buf, 255, fp);
    fclose(fp);

    printf("%s", buf);
    
    return 0;
}
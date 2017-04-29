#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buf[255];
    char *COMMAND = "python test.py 6 7";

    #ifdef _WIN32
        fp = _popen(COMMAND, "rt");
    #else
        fp = popen(COMMAND, "rt");
    #endif

    fgets(buf, 255, fp);

    #ifdef _WIN32
        _pclose(fp);
    #else
        pclose(fp);
    #endif

    printf("%s", buf);
    
    return 0;
}
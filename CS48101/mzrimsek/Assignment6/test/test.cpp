#include <iostream>
#include <thread>
#include <string>

#include <stdio.h>
#include <stdlib.h>

void addNumbersWithPython(int x, int y) {
    FILE *fp;
    char buf[255];

    std::string command = "python test.py " + std::to_string(x) + " " + std::to_string(y);
    const char * convertedCommand = command.c_str();

    #ifdef _WIN32
        fp = _popen(convertedCommand, "rt");
    #else
        fp = popen(convertedCommand, "rt");
    #endif

    fgets(buf, 255, fp);

    #ifdef _WIN32
        _pclose(fp);
    #else
        pclose(fp);
    #endif

    printf("%s", buf);
}

int main() {
    int x, y;

    while(true)
    {
        std::cout << "Enter x: ";
        std::cin >> x;
        std::cout << "Enter y: ";
        std::cin >> y;

        addNumbersWithPython(x, y);
    }
    return 0;
}
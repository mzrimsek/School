#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>

void doPython() {
    system("python test.py 1 2");
}

int main() {
    std::cout << "test";

    std::thread pythonThread(doPython());
    pythonThread.join();
    
    return 0;
}
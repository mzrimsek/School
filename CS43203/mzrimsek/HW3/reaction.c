/*
Mike Zrimsek
Systems Programming
Homework 3 - reaction
 */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

void printChar(char character){
    move(LINES/2, COLS/2);
    addch(character);
    refresh();
}

int testReaction(int roundNum){
    int timeRange = 2;
    char charset[] = "0123456789";

    int characterInput, reactionTime;
    struct timeval startTime, endTime;

    char target = charset[rand() % strlen(charset)];

    move(LINES/2, COLS/2-4);
    printw("Round %2d", roundNum);
    move(LINES-1, COLS-1);

    refresh();
    sleep(2);
    clear();
    refresh();

    printChar(target);

    gettimeofday(&startTime, 0);
    while((characterInput = getch()) != EOF && characterInput != target );
    gettimeofday(&endTime, 0);

    printChar(' ');

    if(characterInput == EOF){
        reactionTime = -1L;
    }
    else{
        reactionTime = 1000000 * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec = startTime.tv_usec);
    }

    return reactionTime;
}

void printTime(long time, int roundNum){
    printf("%3d. %8.4f\n", roundNum, time/1000000.0);
}

void reactionReport(long reportData[], int numRounds){
    int i;
    long sum, min, max;
    printTime(reportData[0], 1);
    for(min = max = sum = reportData[0], i=1; i<numRounds; i++){
        printTime(reportData[i], i+1);
        if(reportData[i] > max){
            max = reportData[i];
        }
        if(reportData[i] < min){
            min = reportData[i];
        }
        sum += reportData[i];
    }
    printf("\nmax time: %8.4f\nmin time: %8.4f\navg time: %8.4f\n", max/1000000.0, min/1000000.0, sum/1000000.0*numRounds);
}

main(){
    int totalTests = 2;
    long resultTimes[totalTests];
    time_t t;

    srand((unsigned) time(&t));

    initscr();
    noecho();
    crmode();

    int i;
    for(i = 0; i < totalTests; i++){
        resultTimes[i] = testReaction(i+1);
    }

    endwin();

    reactionReport(resultTimes, totalTests);
}

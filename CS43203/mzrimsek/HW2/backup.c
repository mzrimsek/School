/*
Mike Zrimsek
Systems Programming
Homework 2 - Backup
 */

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/stat.h>
#include <utime.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

int getDirLen(char *fileName, char *dirName){
    return strlen(fileName) + strlen (dirName) + 1;
}

char* getFullFileName(char *fileName, char *dirName){
    int dirLen = getDirLen(fileName, dirName);
    char *name = (char *) malloc(dirLen);
    strcpy(name, fileName);
    strcat(strcat(name, "/"), dirName);
    return name;
}

struct utimbuf getBackupTimes(char *sourceFile, struct stat statbuf){
    struct utimbuf backupTimes;

    stat(sourceFile, &statbuf);

    backupTimes.actime = statbuf.st_atime;
    backupTimes.modtime = statbuf.st_mtime;

    return backupTimes;
}

void updateBackupTimes(char *sourceFile, char *destFile){
    struct stat statbuf;

    struct utimbuf backupTimes = getBackupTimes(sourceFile, statbuf);
    utime(destFile, &backupTimes);
}

void copyFile(char *sourceFile, char *destFile){
    int numChars;
    char buf[BUFFERSIZE];

    int inFile = open(sourceFile, O_RDONLY);
    int outFile = creat(destFile, COPYMODE);

    while((numChars = read(inFile, buf, BUFFERSIZE)) > 0){
        if( write(outFile, buf, numChars) != numChars){
            printf("Write error to %s\n", destFile);
        }
    }

    close(inFile);
    close(outFile);
}

void processDirectory(DIR *sourceDir, char *av[]){
    struct dirent *pDirent;

    while ((pDirent = readdir(sourceDir)) != NULL) {
        char *sourceFile = getFullFileName(av[1], pDirent->d_name);
        char *destFile = getFullFileName(av[2], pDirent->d_name);

        copyFile(sourceFile, destFile);
        updateBackupTimes(sourceFile, destFile);
    }
}

int main (int ac, char *av[]){
    DIR *sourceDir;
    DIR *targetDir;

    if (ac < 3){
        printf("Please specify source and target directories\n");
        exit(1);
    }

    sourceDir = opendir(av[1]);
    if(sourceDir == NULL){
        printf ("Cannot open directory %s\n", av[1]);
        exit(1);
    }

    targetDir = opendir(av[2]);
    if (targetDir == NULL){
        printf("Creating directory %s\n", av[2]);
        mkdir(av[2], S_IRUSR | S_IWUSR | S_IXUSR);
    }

    printf("Copying files from %s to %s\n", av[1], av[2]);
    processDirectory(sourceDir, av);

    closedir(sourceDir);
    closedir(targetDir);
    return 0;
}

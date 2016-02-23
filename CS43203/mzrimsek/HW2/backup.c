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
    strcat(name, "/");
    strcat(name, dirName);
    return name;
}

struct utimbuf getBackupTimes(char *sourceFile, struct stat statbuf){
    struct utimbuf backupTimes;

    stat(sourceFile, &statbuf);

    backupTimes.actime = statbuf.st_atime;
    backupTimes.modtime = statbuf.st_mtime;

    return backupTimes;
}

void traverseDirectory(struct dirent *pDirent, DIR *sourceDir, char *av[]){
    int inFile, outFile, nChars;
    char buf[BUFFERSIZE];
    struct stat statbuf;

    while ((pDirent = readdir(sourceDir)) != NULL) {
        char *sourceFile = getFullFileName(av[1], pDirent->d_name);
        char *destFile = getFullFileName(av[2], pDirent->d_name);

        inFile = open(sourceFile, O_RDONLY);
        outFile = creat(destFile, COPYMODE);

        struct utimbuf newTimes = getBackupTimes(sourceFile, statbuf);

        while((nChars = read(inFile, buf, BUFFERSIZE)) > 0){
            if( write(outFile, buf, nChars) != nChars){
                printf("Write error to %s\n", destFile);
            }
        }

        utime(destFile, &newTimes);
    }

    close(inFile);
    close(outFile);
}

int main (int ac, char *av[]){
    struct dirent *pDirent;
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
    traverseDirectory(pDirent, sourceDir, av);

    closedir(sourceDir);
    closedir(targetDir);
    return 0;
}

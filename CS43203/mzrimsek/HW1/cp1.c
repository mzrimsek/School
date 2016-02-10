#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

int getDirLen(char *, char *);
char* getFullFileName(int, char *, char *);
void oops(char *, char *);

int main (int ac,char *av[]){
    int outFile, inFile, len, nChars;
    char buf[BUFFERSIZE];
    struct dirent *pDirent;
    DIR *sourceDir;
    DIR *targetDir;

    if ( ac < 3 ){
        fprintf( stderr, "usage: %s source destination\n", *av);
        exit(1);
    }

    sourceDir = opendir(av[1]);
    if(sourceDir == NULL){
        printf ("Cannot Open Directory\n");
        exit(1);
    }

    targetDir = opendir(av[2]);
    if (targetDir == NULL){
        printf("Creating Directory %s\n", av[2]);
        mkdir(av[2], S_IRUSR | S_IWUSR | S_IXUSR);
    }

    printf("Copying files from %s to %s\n", av[1], av[2]);
    while ((pDirent = readdir(sourceDir)) != NULL) {
        int sourceDirLen = getDirLen(av[1], pDirent->d_name);
        char *sourceFile = getFullFileName(sourceDirLen, av[1], pDirent->d_name);
        inFile = open(sourceFile, O_RDONLY);

        int destDirLen = getDirLen(av[2], pDirent->d_name);
        char *destFile = getFullFileName(destDirLen, av[2], pDirent->d_name);
        outFile = creat(destFile, COPYMODE);

        while((nChars = read(inFile, buf, BUFFERSIZE)) > 0){
            if( write(outFile, buf, nChars) != nChars){
                oops("Write error to ", destFile);
            }
        }
    }

    close(inFile);
    close(outFile);
    closedir(sourceDir);
    closedir(targetDir);
    return 0;
}

int getDirLen(char *fileName, char *dirName){
    return strlen(fileName) + strlen (dirName) + 1;
}

char* getFullFileName(int dirLen, char *fileName, char *dirName){
    char *name = (char *) malloc(dirLen);
    strcpy(name, fileName);
    strcat(name, "/");
    strcat(name, dirName);
    return name;
}

void oops(char *s1, char *s2){
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}

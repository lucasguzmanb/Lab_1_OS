// P1-SSOO-23/24

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 1

int main(int argc, char *argv[]) {
    /*If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1*/
    if (argc < 2) {
        printf("Too few arguments\n");
        return -1;
    }

    char *fileName = argv[1];
    char buf[N];
    int wordcounter = 0;
    int linecounter = 0;
    int bytecounter = 0;
    int word_char = 0;
    int fd;
    if ((fd = open(fileName, O_RDONLY, 0666)) < 0) {
        perror("File does not exist\n");
        return -1;
    }
    int n;

    while ((n = read(fd, buf, N)) > 0) {
        bytecounter++;
        if (buf[0] == '\n') {
            linecounter++;
        }
        if (word_char == 1) {
            if (buf[0] == ' ' || buf[0] == '\t' || buf[0] == '\n') {
                word_char = 0;
                wordcounter++;
            } else {
                continue;
            }
        } else {
            if (buf[0] != ' ' && buf[0] != '\t' && buf[0] != '\n') {
                word_char = 1;
            }
        }
    }
    if (word_char == 1) {
        wordcounter++;
    }

    if (n < 0) {
        perror("Read error occured");
        return -1;
    } else
        close(fd);

    printf("%d %d %d %s\n", linecounter, wordcounter, bytecounter, fileName);
    return 0;
}

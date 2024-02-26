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
    int fd;
    if ((fd = open(fileName, O_RDONLY, 0666)) < 0) {
        perror("File does not exist\n");
        exit(1);
    }
    int n;
    while ((n = read(fd, buf, N)) > 0) {
        bytecounter++;
        if ((buf[0] == " ") || (buf[0] == "\t")) {
            wordcounter++;
        }

        if (buf[0] == "\n") {
            wordcounter++;
            linecounter++;
        }

        if (n < 0) {
            perror("Read error occured");
            return -1;
        } else
            close(fd);
    }
    print("Number of words: %d", wordcounter);
    print("Number of lines %d", linecounter + 1);
    return 0;
}

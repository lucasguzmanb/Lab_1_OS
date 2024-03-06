// P1-SSOO-23/24

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 1

int main(int argc, char *argv[]) {
    // If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
    if (argc < 2) {
        printf("Too few arguments\n");
        return -1;
    }

    char *fileName = argv[1]; // argv[1] -> file to process
    char buf[N];              // Buffer of side 1, to read one character at a time
    int wordcounter = 0;
    int linecounter = 0;
    int bytecounter = 0;
    int word_char = 0;
    int fd;
    // If the name of the file is wrong or it does not exist it raises an error
    if ((fd = open(fileName, O_RDONLY, 0666)) < 0) {
        perror("File does not exist\n");
        return -1;
    }
    int n;
    // We start reading the file
    while ((n = read(fd, buf, N)) > 0) {
        bytecounter++; // Each time it reads it adds 1 to the byte counter
        if (buf[0] == '\n') {
            linecounter++; // Each time it reads a line break it adds 1 to the line counter
        }
        if (word_char) { // Only if we are inside a word and in the next character
                         // we read a space, tab or line break we add a word
            if (buf[0] == ' ' || buf[0] == '\t' || buf[0] == '\n') {
                word_char = 0; // We set it to 0 because now it is not inside a word
                wordcounter++;
            } else {
                continue; // If it does not read a space or a tab or a line break it
                          // continues to be in a word so we do not do anything
            }
        } else { // If we are not in a word, only if the next character is different from
                 // a space, a tab and a line break we enter in a word
            if (buf[0] != ' ' && buf[0] != '\t' && buf[0] != '\n') {
                word_char = 1;
            }
        }
    }
    if (word_char) { // As files ususally do not end in a space, tab or line break
                     // if we were in a word we add it to the counter
        wordcounter++;
    }

    if (n < 0) { // If there is an error reading it prints an error and returns -1
        perror("Read error occured");
        return -1;
    } else
        close(fd); // We close the file

    printf("%d %d %d %s\n", linecounter, wordcounter, bytecounter, fileName);
    return 0; // We finally print and return a 0
}

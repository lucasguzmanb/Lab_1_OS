// P1-SSOO-23/24

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // If less than three arguments (argv[0] -> program, argv[1] -> directory to search, argv[2] -> file to find) print an error y return -1
    if (argc < 3) {
        printf("Too few arguments\n");
        return -1;
    }

    char *dirName = argv[1];     // store the directory name
    char *fileName = argv[2];    // store the file name
    DIR *dir = opendir(dirName); // try to open the directory
    struct dirent *entry;        // to read each of the entries of the directory

    if (dir == NULL) { // if there is an error opening the directory or it doesnt exist, print an error an return -1
        printf("Error opening the directory\n");
        return -1;
    } else { // if we can open the directory, start reading each of its entries until we reach the end or we find the file
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, fileName) == 0 && entry->d_type != DT_DIR) { // also check that it is not another directory
                if (strcmp(dirName, ".") == 0) {
                    printf("File %s is in this directory\n", fileName);
                } else {
                    printf("File %s is in directory %s\n", fileName, dirName);
                }
                closedir(dir);
                return 0;
            }
        }
        if (strcmp(dirName, ".") == 0) {
            printf("File %s is not in this directory\n", fileName);
        } else {
            printf("File %s is not in directory %s\n", fileName, dirName);
        }
        closedir(dir);
        return 0;
    }
}

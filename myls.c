//P1-SSOO-23/24

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]){
    struct dirent *entry;        // to read each of the entries of the directory
    char *dirName; // define the directory name

    if (argc == 1) {
       dirName = getcwd(NULL, 0); //usage 2, open current directory
        if (dirName == NULL){
            return -1;
        }
    }else if (argc == 0){
        dirName = argv[1];  //usage 1, directory given as an argument
    }
    int dirSize = 0;
    DIR *dir = opendir(dirName); // try to open the directory
    if (dir == NULL){ // if there is an error opening the directory or it doesnt exist, print an error an return -1
        printf("Error opening the directory\n");
        return -1;
    }else{
        while (((entry = readdir(dir)) != NULL)&& (dirSize != 4097)) { // path size can not be greater tha 4096, 4097 counting the null
            printf("%s\n", entry->d_name);
            dirSize += dirSize;
        }
        closedir(dir);
        printf("the current directory is %s", dirName);
        if (chdir("..") == 0) {
            printf("the parent directory is %s", dirName);
        }else{
            printf("Error getting parent directory");
        }
        return 0;
    }
}
    

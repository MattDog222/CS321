#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
    char fileNameIn[128];
    char fileNameOut[128];
    
    printf("Name of file to be copied:\n\t");
    scanf("%s", fileNameIn);
    
    int fdIn = open(fileNameIn, O_RDONLY);

    // Check if input file exists before wasting user's time asking for output
    if (fdIn < 0) { // fileNameIn DNE
        printf("File \"%s\" does not exist! Aborting process\n", fileNameIn);
        close(fdIn);
        return -1;
    }

    printf("Name of file to be created/pasted into:\n\t");
    scanf("%s", fileNameOut);
    
    int fdOut = open(fileNameOut, O_RDWR | O_EXCL | O_CREAT);
    
    char* buffer[1024];

    // Check if output file exists:
    // If it exists, ask if it should be overwritten
    // Otherwise just create it and then paste
    if (fdOut < 0) {
        char choice[10];
        printf("File \"%s\" already exists! Would you like to overwrite it? [Y/N] ", fileNameOut);
        scanf("%s", choice);
        if (strcmp(choice, "Y") == 0 || strcmp(choice, "y") == 0) {
            // Overwrite file
            fdOut = open(fileNameOut, O_WRONLY | O_TRUNC);
            while (1) {
                size_t readSize = read(fdIn, buffer, 128);
                if (readSize <= 0)
                    break;
                write(fdOut, buffer, readSize);
            }
   		 
            printf("File \"%s\" successfully overwritten\n", fileNameOut);
            close(fdIn);
            close(fdOut);
            return 1;
        } else {
            // Abort
            printf("Aborting operation!\n");
            close(fdIn);
            close(fdOut);
            return -1;
        }
    }
    // File created from O_CREAT, now write to it.
    while (1) {
        size_t readSize = read(fdIn, buffer, 128);
        if (readSize <= 0)
            break;
        write(fdOut, buffer, readSize);
    }

    close(fdIn);
    close(fdOut);
    printf("File \"%s\" successfully copied into \"%s\"\n", fileNameIn, fileNameOut);
    return 0;
}

// Write two different programs (Sender and Receiver) in C to demonstrate IPC using FIFO Named Pipe.
// Process "Sender.c" will write one integer value (Say A) as a message in FIFO. "Receiver.c" will read that message.
// After reading the message, it will find the one’s complement of A and name it as B1. Then, it will write B on to the pipe. 
// "Sender.c" will read the integer value B1 from the pipe and display it.

// Sender.c

//Name: M.Sri Sujan
//Roll No: CS21B1081

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int fd;
    char * myfifo = "/tmp/myfifo";  // creating fifo file
    if (mkfifo(myfifo, 0666) == -1){    // creating fifo file with permission 0666
        printf("Error in creating fifo file\n");
        return 0;
    }        
    
    int A;
    printf("Enter a number A: ");
    scanf("%d", &A);              // reading a number from user

    fd = open(myfifo, O_WRONLY);    // opening fifo file in write only mode
    write(fd, &A, sizeof(A));   // writing the number to fifo file
    printf("written A = %d in fifo file\n", A);  // printing the number
    close(fd);                      // closing fifo file

    int B1;
    fd = open(myfifo, O_RDONLY);    // opening fifo file in read only mode
    read(fd, &B1, sizeof(B1));  // reading the number from fifo file
    printf("reading B1(one's complement of A) from fifo file\n");
    printf("B1 = %d\n", B1);        // printing the number
    close(fd);                      // closing fifo file

    unlink(myfifo);                 // removing fifo file
    return 0;
}
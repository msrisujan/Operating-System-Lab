// Write two different programs (Sender and Receiver) in C to demonstrate IPC using FIFO Named Pipe.
// Process "Sender.c" will write one integer value (Say A) as a message in FIFO. "Receiver.c" will read that message.
// After reading the message, it will find the one’s complement of A and name it as B1. Then, it will write B on to the pipe. 
// "Sender.c" will read the integer value B1 from the pipe and display it.

// Receiver.c

//Name: M.Sri Sujan
//Roll No: CS21B1081

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int fd1;
    char * myfifo = "/tmp/myfifo";  // creating fifo file

    int A;
    fd1 = open(myfifo, O_RDONLY);    // opening fifo file in read only mode
    read(fd1, &A, sizeof(A));  // reading the number from fifo file
    printf("reading A from fifo file\n");
    printf("A = %d\n", A);        // printing the number
    //one's complement
    int B1 = ~A;
    close(fd1);                      // closing fifo file

    int fd2;
    fd2 = open(myfifo, O_WRONLY);    // opening fifo file in write only mode
    write(fd2, &B1, sizeof(B1));   // writing the number to fifo file
    printf("written B1 = %d in fifo file\n", B1);  // printing the number
    close(fd2);                      // closing fifo file

    return 0;
}
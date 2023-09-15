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
    int a[32];
    int i = 0;
    while(A > 0){
        a[i] = A % 2;
        A = A / 2;
        i++;
    }
    int B1 = 0;
    int k = 1;
    for(int j = 0; j < i; j++){
        if(a[j] == 0){
            a[j] = 1;
        }
        else{
            a[j] = 0;
        }
        B1 = B1 + a[j] * k;
        k = k * 2;
    }
    close(fd1);                      // closing fifo file

    int fd2;
    fd2 = open(myfifo, O_WRONLY);    // opening fifo file in write only mode
    write(fd2, &B1, sizeof(B1));   // writing the number to fifo file
    printf("B1 is one's complement of A\n");
    printf("written B1 = %d in fifo file\n", B1);  // printing the number
    close(fd2);                      // closing fifo file

    return 0;
}
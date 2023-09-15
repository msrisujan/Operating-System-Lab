// Write two different programs (Sender and Receiver) in C to demonstrate IPC using message passing.
// Process "Sender.c" will take input of atleast 10 numbers and share these numbers with the "Receiver.c" process using message passing.
// The "Receiver.c" will check each numbers and displays how many odd numbers are there among those numbers and displays them.  

// receiver.c

//Name: M Sri Sujan
//Roll: CS21B1081

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_SIZE 512    // max size of message

typedef struct {     // structure of message
    long int msg_type;
    int msg_num[MAX_SIZE];
} my_msg;

int main() {
    int msgid;
    my_msg some_data;
    msgid = msgget((key_t)12345, 0644 | IPC_CREAT);   // creating message queue with key 12345 and permission 0644
    if(msgid == -1){
        printf("Error in creating message queue\n");
        exit(1);
    }

    some_data.msg_type = 1;     // setting message type to 1 (can be any number) using which receiver will receive the message
    int odd_count = 0;

    if(msgrcv(msgid, (void *)&some_data, MAX_SIZE, some_data.msg_type , 0) == -1){    // receiving message
            printf("Error in receiving message\n");
            exit(1);
    }
    int n = some_data.msg_num[0];
    printf("Odd numbers: ");
    for(int i=1; i<=n; i++){
        if(some_data.msg_num[i] % 2 != 0){               // checking if number is odd
            printf("%d ",some_data.msg_num[i]);
            odd_count++;
        }
    }
    printf("\n");
    printf("Number of odd numbers: %d\n", odd_count);

    msgctl(msgid, IPC_RMID, 0);
    return 0;
}
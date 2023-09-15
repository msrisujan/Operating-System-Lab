// Write two different programs (Sender and Receiver) in C to demonstrate IPC using message passing.
// Process "Sender.c" will take input of atleast 10 numbers and share these numbers with the "Receiver.c" process using message passing.
// The "Receiver.c" will check each numbers and displays how many odd numbers are there among those numbers and displays them.  

// receiver.c

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_SIZE 512

typedef struct {
    long int msg_type;
    int msg_num[MAX_SIZE];
} my_msg;

int main() {
    int msgid;
    my_msg some_data;
    msgid = msgget((key_t)12345, 0644 | IPC_CREAT);
    if(msgid == -1){
        printf("Error in creating message queue\n");
        exit(1);
    }

    long int msg_to_rec = 1;
    int odd_count = 0;

    int n = 10;
    if(msgrcv(msgid, (void *)&some_data, MAX_SIZE, msg_to_rec , 0) == -1){
            printf("Error in receiving message\n");
            exit(1);
    }
    for(int i=0; i<n; i++){
        if(some_data.msg_num[i] % 2 != 0)
            odd_count++;
    }
    printf("Number of odd numbers: %d\n", odd_count);
    return 0;
}
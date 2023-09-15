// Write two different programs (Sender and Receiver) in C to demonstrate IPC using message passing.
// Process "Sender.c" will take input of atleast 10 numbers and share these numbers with the "Receiver.c" process using message passing.
// The "Receiver.c" will check each numbers and displays how many odd numbers are there among those numbers and displays them.  

// sender.c

//Name: M Sri Sujan
//Roll: CS21B1081

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_SIZE 512   // max size of message

typedef struct {          // structure of message
    long int msg_type; 
    int msg_num[MAX_SIZE];  // array to store numbers 
} my_msg;

int main(){
    int msgid;        
    my_msg some_data;
    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);     // creating message queue with key 12345 and permission 0666
    if(msgid == -1){
        printf("Error in creating message queue\n");
        exit(1);
    }
    int n;
    printf("Enter number of numbers to send: ");
    scanf("%d", &n);
    some_data.msg_num[0] = n;
    printf("Enter %d numbers: ", n);         // taking input
    for(int i=1; i<=n; i++){
        scanf("%d", &some_data.msg_num[i]);  
    }
    some_data.msg_type = 1;       // setting message type to 1 (can be any number) using which receiver will receive the message

    if(msgsnd(msgid, (void *)&some_data, MAX_SIZE, 0) == -1){   // sending message
        printf("Error in sending message\n");
        exit(1);
    }
        
    return 0;
    
}
//Write two different programs (Sender and Receiver) in C to demonstrate IPC using shared memory.
//Process "Sender.c" will write atleast 100 bytes of data to the shared memory and process "Receiver.c" will read from the shared memory and displays it.
//Then, "Receiver.c" will write atleast 100 bytes of data to the same shared memory and  "Sender.c" will read and displays it. 

//Name: M.Sri Sujan
//Roll No: CS21B1081

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define SHMSIZE 100

int main()
{
    int c; int shmid; key_t key; int *shm, *s;
    key = 5678;  //key for shared memory segment
    if((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0)  //create shared memory segment
    {
        printf("Error in shmget\n");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (int *) -1)  //attach shared memory segment
    {                                                  //returns void char * pointer
        printf("Error in shmat\n");
        exit(1);
    }
    s = shm;   //pointer to shared memory segment
    printf("Writing to shared memory segment\n");
    for(c = 1; c <= 100; c++)  //write to shared memory segment
    {
        *s++ = c;
    }
    *s = '\0';
    printf("Waiting for receiver to read the data\n");
    while(*shm != -10)  //wait for receiver to read the data
    {
        sleep(1);
    }
    printf("Reading from shared memory segment\n");
    for(s ; *s != '\0'; s++)  //read from shared memory segment
    {
        printf("%d ", *s);
    }
    printf("\n");
    *shm = -10;  //indicate that the data has been read
    exit(0);
}
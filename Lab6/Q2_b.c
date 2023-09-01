// Name: M.Sri Sujan
// Roll No: CS21B1081

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define SHMSIZE 100

int main(){
    int shmid; key_t key; int *shm, *s;
    int c;

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
    printf("Reading from shared memory segment\n");
    for(s = shm; *s != '\0'; s++)  //read from shared memory segment
    {
        printf("%d ", *s);
    }
    printf("\n");
    printf("Writing to shared memory segment\n");
    for(c = 100; c >= 1 ;c--)  //write to shared memory segment
    {
        *s++ = c;
    }
    *s = '\0';
    *shm = -10;//indicate that the data has been read
    exit(0);
}

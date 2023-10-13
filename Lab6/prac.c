#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>

#define SHMSIZE 100

int main(){
    char c;
    int shmid;
    char *stringm = "abc";
    key_t k = 1082;
    char* s,*shm;
    if((shmid = shmget(k, SHMSIZE, IPC_CREAT | 0666)) == -1){
        printf("error");
        exit(1);
    }
    if((shm = shmat(shmid, NULL, 0)) == (char *) -1){
        printf("error");
        exit(1);
    }
    printf("Writing\n");
    s = shm;
    for(int i=0; i<strlen(stringm); i++){
        *s++ = stringm[i];
    }
    *s = '\0';

    while(*shm != '#'){
        sleep(1);
    }
    for(; *s != '\0'; s++){
        putchar(*s);
    }

    shmctl(shmid, IPC_RMID, NULL);
}
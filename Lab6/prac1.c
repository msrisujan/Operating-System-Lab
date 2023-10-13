#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>

#define SHMSIZE 100

int main(){
    char *string = "abc";
    key_t k =1082;
    char *s,*shm;
    int shmid = 32;
    shmid = shmget(k, SHMSIZE, 0666);
    if(shmid == -1){
        printf("error in shmget");
        exit(1);
    }
    printf("%d", shmid);
    shm = shmat(shmid, NULL, 0);
    if(shm == (char *)-1){
        printf("error in shmat");
        exit(1);
    }
    int i = 0;
    for(s = shm; *s != '\0'; s++ ){
        printf("%c ",*s);
    }
    for(int j = 1;j <= strlen(string); j++){
        // printf("%c",string[strlen(string) - j]);
        *s++ = string[strlen(string) - j];
    }
    *s = '\0';
    *shm = '#';
    exit(0);

}
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    pid_t pid[4];
    if((pid[0]=fork()) && (pid[1]=fork())){
        
            wait(NULL);
            wait(NULL);
            printf("parent\n");
    }
    else if(pid[0] == 0){
        printf("C1\n");
    }
    else if(pid[1] == 0){
        if((pid[2]=fork()) && (pid[3]=fork())){
            wait(NULL);
            wait(NULL);
            printf("C2\n");
        }
        else if(pid[2] == 0){
            printf("C3\n");
        }
        else if(pid[3] == 0){
            printf("C4\n");
        }
    }

    // else if(pid[1] == 0){
    //     if((pid[2]=fork()) && (pid[3]=fork())){
        
    //         wait(NULL);
    //         wait(NULL);
    //         printf("C2\n");
    //     }
    //     else if(pid[3]==0){
    //         printf("C4\n");
    //     }
    //     else{
    //         printf("C3\n");
    //     }
    // }
    // else{
    //     printf("C1\n");
    // }
    return 0 ;
}
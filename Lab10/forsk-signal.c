// Create a parent process and its child process using fork(). 

// In the parent process, one array (A) is given as [2, 1, 3, 0, 5, 0, 7, 9]. 
// Now, take one number from the user and find the remainder value when you will divide the same number by values present in each location of the array A. 
// Handle the situation using signal if required. 

// In the child process, print a random value between 10 to 30. Whenever you get a value more than 20, exit form the child process using exit() system call.

// Name: M.Sri Sujan
// Roll no: CS21B1081

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

void sig_handler(int signo){   //signal handler
    printf("FPE ");
}

int main(){
    pid_t pid;
    int arr[8] = {2, 1, 3, 0, 5, 0, 7, 9};//array
    int num;
    printf("Array: ");
    for(int i = 0; i < 8; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
   

    pid = fork();

    if(pid < 0){   //fork failed
        printf("Fork failed\n");
        exit(1);
    }
    else if(pid == 0){   //child process
        while(1){
            // srand(time(NULL));
            int rand_num = rand() % 21 + 10;   //random number between 10 and 30
            printf("\nRandom number: %d", rand_num);
            if(rand_num > 20){
                printf("\n");
                exit(0);
            }
        }
    }
    else{
        wait(NULL);   //wait for child process to finish
        printf("Enter a number: ");
        scanf("%d", &num);
        signal(SIGFPE, sig_handler);   //signal handler
        printf("Remainders: ");
        for(int i = 0; i < 8; i++){
            if(arr[i] == 0){
                raise(SIGFPE);    //raise signal if arr[i] is 0
            }
            else{
                printf("%d ", num % arr[i]);
            }
        }
    }
    return 0;
}
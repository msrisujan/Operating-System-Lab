// Create parent and child processes using fork(). In each process, define an array of integer using malloc. 
//Before that take the size of the array from the user. Insert values in your array (size and array elements may be different for both processes).

 

// In Parent Process:

// (a) Print the array elements and their addresses

// (b) Sort the array and print its values.

 

// In Child Process:

// (a) Print the array elements and their address

// (b) Reverse the array and print its values.



// NOTE: Ensure that first child process should terminate, then Parent Process should start taking input.

//Name: M.Sri Sujan
//Roll No: CS21B1081

#include <stdio.h>
#include <unistd.h>   //for fork()
#include <sys/types.h>  //for pid_t
#include <sys/wait.h>  //for wait()
#include <stdlib.h>

int main(){
    pid_t pid;           //pid_t is a signed integer type which is capable of representing a process ID.
    pid = fork();     //fork() creates a new process by duplicating the calling process.
    if(pid < 0){
        printf("Error\n");
    }
    else if(pid == 0){          //If fork() returns zero, then the newly created process is a child process.
        printf("\t\t------Child Process------\n");
        int n;
        int *arr = (int*)malloc(n*sizeof(int));     //malloc() allocates requested bytes of memory and returns a pointer to it.
        
        printf("Enter number of elements: ");
        scanf("%d",&n);
        printf("Enter %d numbers: ",n);
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        printf("Elements: ");
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
        printf("Address: ");
        for(int i=0;i<n;i++){
            printf("%p ",&arr[i]);
        }
        printf("\n");
        printf("Reversed Array: ");      //Reversing the array
        for(int i=n-1;i>=0;i--){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
    else{                      //If fork() returns a positive value, then the process is the parent process.
        wait(NULL);                     //wait() causes the parent process to pause until the child process has ended.
        printf("\t\t------Parent Process------\n");
        int n;
        int *arr = (int*)malloc(n*sizeof(int));
        printf("Enter number of elements: ");
        scanf("%d",&n);
        printf("Enter %d numbers: ",n);
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        printf("Elements: ");
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
        printf("Address: ");
        for(int i=0;i<n;i++){
            printf("%p ",&arr[i]);
        }
        printf("\n");
        printf("Sorted Array: ");         //Sorting the array
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(arr[i] > arr[j]){
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
    return 0;
}

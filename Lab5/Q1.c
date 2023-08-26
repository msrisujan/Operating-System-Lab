// Write a C program which will create a child process from a parent process. 
//In parent process, define one global array and take input from the user.

 

// Perform following operations.

// In Parent Process:

// (a) Update the array by subtracting 3 from each element of the array.

// (b) Print the elements, address of the elements and find the minimum element after performing (a).

// (c) Print process id and it’s parent process id

 

// In Child Process:

// (a) Update the global array by adding 2 on each element of the array.

// (b) Print the elements, address of the elements and find the maximum element after performing (a)

// (c) Print process id and it’s parent process id.

//Name: M.Sri Sujan
//Roll No: CS21B1081

#include <stdio.h>
#include <unistd.h>  //for fork()
#include <sys/types.h>  //for pid_t


int main(){
    pid_t pid;               //pid_t is a signed integer type which is capable of representing a process ID.
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter %d numbers: ",n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    pid = fork();       //fork() creates a new process by duplicating the calling process.
    if(pid < 0){        //If fork() returns negative value, the creation of a child process was unsuccessful.
        printf("Error\n");
    }
    else if(pid == 0){        //If fork() returns zero, then the newly created process is a child process.
        printf("\t\t------Child Process------\n");
        for(int i=0;i<n;i++){
            arr[i] += 2;
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
        int max = arr[0];
        for(int i=1;i<n;i++){
            if(arr[i] > max){        //Finding maximum element
                max = arr[i];
            }
        }
        printf("Maximum: %d\n",max);
        printf("Process ID: %d\n",getpid());     //getpid() returns the process ID of the calling process.
        printf("Parent Process ID: %d\n",getppid());    //getppid() returns the process ID of the parent of the calling process.
    }
    else{                  //If fork() returns positive value, then the process is the parent process.
        printf("\n");
        printf("\t\t------Parent Process------\n");
        for(int i=0;i<n;i++){
            arr[i] -= 3;
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
        int min = arr[0];
        for(int i=1;i<n;i++){          //Finding minimum element
            if(arr[i] < min){
                min = arr[i];
            }
        }
        printf("Minimum: %d\n",min);
        printf("Process ID: %d\n",getpid());
        printf("Parent Process ID: %d\n",getppid());    
        printf("\n"); 
    }
    return 0;
}
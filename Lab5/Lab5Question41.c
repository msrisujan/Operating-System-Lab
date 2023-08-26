// Write two programs (Given Lab5Question41.c and Lab5Question42.c).

// For Lab5Question41.c:

// In Parent Process:

// (a) Print your name, roll number, and Institution name 

// (b) Print process id and its parent process id and return value of fork() system call.

 

// In Child Process,

// (a) Print id of the process, it’s parent process id, and return value of fork() system call.

// (b) Use exec() system call to execute new program written in Lab5Question42.c. In Lab5Question42.c, write or compute anything of your choice. The executable file for Lab5Question42.c is (Lab5Question42).

// (c) Write a few printf statements after operation (b).

// Analyze the entire creation of the parent and child processes. Make sure that the parent process terminates after the child process has finished its execution.

// Lab5Question41.c

// Name: M.Sri Sujan
// Roll No: CS21B1081

#include <stdio.h>
#include <unistd.h>  //for fork()
#include <sys/types.h>  //for pid_t
#include <sys/wait.h>  //for wait()

int main(){
    pid_t pid;               //pid_t is a signed integer type which is capable of representing a process ID.
    pid = fork();       //fork() creates a new process by duplicating the calling process.
    if(pid < 0){        //If fork() returns negative value, the creation of a child process was unsuccessful.
        printf("Error\n");
    }
    else if(pid == 0){        //If fork() returns zero, then the newly created process is a child process.
        printf("\n");
        printf("\t\t------Child Process------\n");
        printf("Child Process ID: %d\n",getpid());
        printf("Parent Process ID: %d\n",getppid());
        printf("Return Value of fork(): %d\n",pid);
        execlp("./Lab5Question42","Lab5Question42",NULL);  //execlp() executes the program file specified by filename.
        printf("After execlp()\n");
    }
    else{           //If fork() returns a positive value, then the process is the parent process.
        printf("\n");
        printf("\t\t------Parent Process------\n");
        printf("My name is M.Sri Sujan\n");
        printf("My Roll No is CS21B1081\n");
        printf("My Institution name is IITDM Kancheepuram\n");
        printf("Parent Process ID: %d\n",getpid());
        printf("Child Process ID: %d\n",pid);
        printf("Return Value of fork(): %d\n",pid);
        wait(NULL);     //wait() system call suspends execution of the calling process until one of its children terminates.
        printf("After wait()\n");
    }
    return 0;
}

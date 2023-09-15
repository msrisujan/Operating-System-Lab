// Name: M Sri Sujan
// Roll: CS21B1081

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define MAX 1000

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2;
    int p1, p2;

    p1 = pipe(pipe1);
    if(p1 < 0)
        printf("Pipe Failed");
    
    pid1 = fork();
    if(pid1 > 0)
    {
        printf("Parent Process my id = %d and my parent id = %d\n", getpid(), getppid());

        char string[MAX];
        printf("Enter a message : ");
        fgets(string, MAX, stdin);

        close(pipe1[0]);
        write(pipe1[1], string, sizeof(string));
        wait(NULL);
    }
    else if(pid1 == 0)
    {
        char string1[MAX], string2[MAX];

        close(pipe1[1]);
        read(pipe1[0], string1, sizeof(string1));

        p2 = pipe(pipe2);
        if(p2 < 0)
            printf("Pipe Failed"); 

        pid2 = fork();
        if(pid2 > 0)
        {
            printf("\nChild Process my id = %d and my parent id = %d\n", getpid(), getppid());

            printf("Received message from my parent process : %s\n", string1);
            
            close(pipe2[1]);
            read(pipe2[0], string2, sizeof(string2));

            printf("\nChild Process my id = %d and my parent id = %d\n", getpid(), getppid());
            printf("Received message from my child process : %s\n", string2);

            int l1 = strlen(string1), l2 = strlen(string2);

            printf("Difference in length of messages : %d\n", abs(l1 - l2));
        }
        else if(pid2 == 0)
        {
            printf("\nGrandchild Process my id = %d and my parent id = %d\n", getpid(), getppid());

            char string[MAX];
            printf("Enter a message : ");
            fgets(string, MAX, stdin);

            close(pipe2[0]);
            write(pipe2[1], string, sizeof(string));
        }
        else
            printf("Fork Failed");
    }
    else
        printf("Fork Failed");

    return 0;
}
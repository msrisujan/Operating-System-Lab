// Name: M Sri Sujan
// Roll: CS21B1081

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 100

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    int p1, p2;

    p1 = pipe(pipe1);
    p2 = pipe(pipe2);

    if(p1 < 0)
        printf("Pipe Failed");
    if(p2 < 0)
        printf("Pipe Failed");

    pid = fork();
    if(pid > 0)
    {
        printf("Parent Process my id = %d and my parent id = %d\n", getpid(), getppid());

        char string[MAX];
        printf("Enter a string : ");
        scanf("%s", string);

        close(pipe1[0]);
        write(pipe1[1], string, sizeof(string));

        close(pipe2[1]);
        read(pipe2[0], string, sizeof(string));

        wait(NULL);
        printf("Parent Process my id = %d and my parent id = %d\n", getpid(), getppid());
        printf("Reversed string: %s\n", string);
    }
    else if(pid == 0)
    {
        char string[MAX], reversed[MAX];

        close(pipe1[1]);
        read(pipe1[0], string, sizeof(string));
        printf("\nChild Process my id = %d and my parent id = %d\n", getpid(), getppid());
        printf("Received string from parent process : %s\n", string);

        int i = strlen(string) - 1, j = 0;
        while(i >= 0)
            reversed[j++] = string[i--];

        close(pipe2[0]);
        write(pipe2[1], reversed, sizeof(reversed));

        printf("Reversed string sent to parent process\n\n");
    }
    else
        printf("Fork Failed");

    return 0;
}
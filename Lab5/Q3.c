
// #include <stdio.h>
// #include <unistd.h>

// int main(void) {
//     char *file = "/usr/bin/echo";
//     char *arg1 = "Hello world!";
	
//     execl(file, file, arg1, NULL);

//     return 0;
// }




// #include <unistd.h>

// int main(void) {
//     char *file = "/usr/bin/bash";
//     char *arg1 = "-c";
//     char *arg2 = "echo $ENV1 $ENV2!";
//     char *const env[] = {"ENV1=Hello", "ENV2=World", NULL};
	
//     execle(file, file, arg1, arg2, NULL, env);

//     return 0;
// }


// #include <unistd.h>

// int main(void) {
//     char *file = "/usr/bin/echo";
//     char *const args[] = {"/usr/bin/echo", "Hello world!", NULL};
	
//     execv(file, args);

//     return 0;
// }


// #include <unistd.h>

// int main(void) {
//     char *file = "echo";
//     char *arg1 = "Hello world!";

//     execlp(file, file, arg1, NULL);
//     return 0;
// }

// #include <unistd.h>

// int main(void) {
//     char *file = "echo";
//     char *const args[] = {"/usr/bin/echo", "Hello world!", NULL};
	
//     execvp(file, args);

//     return 0;
// }

// #include <unistd.h>

// int main(void) {
//     char *file = "/usr/bin/bash";
//     char *const args[] = {"/usr/bin/bash", "-c", "echo Hello $ENV!", NULL};
//     char *const env[] = {"ENV=World", NULL};
	
//     execve(file, args, env);

//     return 0;
// }


// #include<stdio.h>
// #include<sys/wait.h>
// #include<unistd.h>
 
// int main()
// {
//     if (fork()== 0)
//         printf("HC: hello from child\n");
//     else
//     {
//         printf("HP: hello from parent\n");
//         wait(NULL);
//         printf("CT: child has terminated\n");
//     }
 
//     printf("Bye\n");
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    if ((child_pid = fork()) == 0) {
        // Child process
        printf("Child process running...\n");
        sleep(2);
        printf("Child process completed.\n");
        exit(0);
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process waiting for child...\n");
        int status;
        waitpid(child_pid, &status, 0); // Parent waits for a specific child
        printf("Parent process resumed.\n");
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
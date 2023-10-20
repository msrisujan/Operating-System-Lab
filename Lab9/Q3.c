// Given 2 threads, schedule the order of execution in such a way that Thread A has to wait for Thread B and vice versa. 
// In other words, given the code below you must guarantee that Statement A1 happens before Statement B2 and Statement B1 happens before Statement A2.



// Thread A

// //Statement A1

// //Statement A2


// Thread B

// //Statement B1

// //Statement B2


// Note: Your solution should not enforce too many constraints. For ex: there is no mention about the order of execution of A1 and B1. 
// Therefore, either order should be possible.

// Name: M. Sri Sujan
// Roll No: CS21B1081

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>   // for semaphores

sem_t s1, s2;   // semaphores

void *thread_A(){   // thread A
    sem_wait(&s2);   // wait
    printf("Statement A1\n");
    sem_post(&s1);     // signal
    sleep(0.1);
    sem_wait(&s2);
    printf("Statement A2\n");
    sem_post(&s1);
    return NULL;
}

void *thread_B(){     // thread B
    sem_wait(&s1);
    printf("Statement B1\n");
    sem_post(&s2);
    sleep(0.1);
    sem_wait(&s1);
    printf("Statement B2\n");
    sem_post(&s2);
    return NULL;
}

int main(){
    pthread_t tid[2];
    sem_init(&s1, 0, 1);  // initialize semaphores
    sem_init(&s2, 0, 1);
    pthread_create(&tid[0], NULL, &thread_A, NULL);
    pthread_create(&tid[1], NULL, &thread_B, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
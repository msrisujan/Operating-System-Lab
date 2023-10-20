// Implement the reader-writer problem’s solution using semaphore.

// Create atleast one writer thread and 5 reader threads. Also, clearly define the reader() function and writer() function that reader and writer thread will execute separately.

// Name: M.Sri Sujan
// Roll no: CS21B1081

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t wrt, rd;    // semaphores

int rcount = 0;    // count of items in buffer
int i = 0, j = 0;

void *writer(void *arg){  // writer thread
    while(j < 10){
        sem_wait(&wrt);  // wait for wrt
        printf("Writer-%ld is writing\n", (long int)arg + 1);
        sem_post(&wrt);  // signal wrt
        j++;
    }
}

void *reader(void *arg){  // reader thread
    while(i < 10){
        sem_wait(&rd);  // wait for rd
        rcount++;
        if(rcount == 1){
            sem_wait(&wrt);  // wait for wrt
        }
        sem_post(&rd);  // signal rd
        printf("Reader-%ld is reading\n", (long int)arg + 1);
        sem_wait(&rd);  // wait for rd
        rcount--;
        if(rcount == 0){
            sem_post(&wrt);  // signal wrt
        }
        sem_post(&rd);  // signal rd
        i++;
    }
}

int main(){
    pthread_t reader_threads[5];   // 5 reader threads
    pthread_t writer_threads[3];    // 3 writer threads
    sem_init(&wrt, 0, 1);  // initialize wrt to 1
    sem_init(&rd, 0, 1);  // initialize rd to 1
    for(long int i = 0; i < 3; i++){   // create 3 writer threads
        pthread_create(&writer_threads[i], NULL, &writer, (void *)i);
    }
    for(long int i = 0; i < 5; i++){   // create 5 reader threads
        pthread_create(&reader_threads[i], NULL, &reader, (void *)i);
    }
    
    for(int i = 0; i < 3; i++){   // join all threads
        pthread_join(writer_threads[i], NULL);
    }
    
    for(int i = 0; i < 5; i++){   // join all threads
        pthread_join(reader_threads[i], NULL);
    }
    return 0;
}
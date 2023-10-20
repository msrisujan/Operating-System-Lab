// Implement the producer – consumer problem’s solution using semaphore. 
// Use one producer thread and one consumer thread. Also, clearly define the produce_item() function and consume_item() function.

// Name: M.Sri Sujan
// Roll no: CS21B1081

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 10

sem_t empty, full;    // semaphores
sem_t mutex;
int buffer[BUFFER_SIZE];

int count = 0;    // count of items in buffer

int produce_item(){    // produce item
    int r = rand() % 2;
    sleep(r);
    return rand() % 100;
}

void consume_item(int item){  // consume item
    int r = rand() % 2;
    sleep(r);
    printf("Consumed item: %d\n", item);
}

void insert_item(int item){  // insert item into buffer
    buffer[count] = item;
}

int remove_item(){  // remove item from buffer
    int item = buffer[0];
    for(int i = 0; i < count; i++){
        buffer[i] = buffer[i + 1];
    }
    return item;
}

int k, l = 0;

void *producer(){  // producer thread
    int item;
    while(k < 10){
        item = produce_item();
        sem_wait(&empty);  // wait for empty
        sem_wait(&mutex);  // acquire lock
        insert_item(item);
        count++;
        printf("Produced item: %d\n", item);
        sem_post(&mutex);  // release lock
        sem_post(&full);  // signal full
        k++;
    }
}

void *consumer(){  // consumer thread
    int item;
    while(l < 10){
        sem_wait(&full);  // wait for full
        sem_wait(&mutex);  // acquire lock
        count--;
        item = remove_item();
        sem_post(&mutex);  // release lock
        sem_post(&empty);  // signal empty 
        consume_item(item);
        l++;
    }
}

int main(){
    srand(time(NULL));
    pthread_t tid[2];
    sem_init(&empty, 0, BUFFER_SIZE);  // initialize semaphores
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&tid[0], NULL, &producer, NULL);  // create threads
    pthread_create(&tid[1], NULL, &consumer, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
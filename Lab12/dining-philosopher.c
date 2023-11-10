#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t mutex;
sem_t forks[N];

int phil[N] = {0, 1, 2, 3, 4};

void thinking(int i)
{
    printf("Philosopher-%d is thinking...\n", i + 1);
    sleep(rand()%2+1);
}

void eating(int i)
{
    printf("Philosopher-%d is eating...\n", i + 1);
    sleep(rand()%2+1);
}

int left(int i)
{
    return (i + N - 1) % N;
}

int right(int i)
{
    return i;
}

void *philosopher(void *arg)
{
    int *i = arg;
    while(1)
    {
        thinking(*i);

        printf("Philosopher-%d is hungry...\n", *i + 1);
        while (1)
        {
            sem_wait(&mutex);

            sem_wait(&forks[*i]); // take right fork
            if (sem_trywait(&forks[left(*i)]) != 0) // take left fork if available
            {
                sem_post(&forks[*i]); // if not available, put right fork
            }
            else
            {
                sem_post(&mutex);
                printf("Philosopher-%d 'took-forks' %d and %d\n", *i + 1, left(*i) + 1, *i + 1);
                break;
            }

            sem_post(&mutex);
        }

        eating(*i);

        sem_post(&forks[left(*i)]); // put left fork
        sem_post(&forks[*i]); // put right fork

        printf("Philosopher-%d 'put-forks' %d and %d\n", *i + 1, left(*i) + 1, *i + 1);
    }
}

int main()
{
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    
    for(int i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}
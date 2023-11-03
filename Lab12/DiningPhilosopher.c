// Implement the dining philosopher's problem’s solution using semaphore.
//  Your solution should allow two philosopher's to eat simultaneously if there are five philosophers thread running simultaneously.  
//  Also, clearly define the eating task and thinking task inside the respective functions. 

// NOTE: Use atleast five philosopher threads.

//Name: M.Sri Sujan
//Roll No: CS21bB1081

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t mutex;  // to access the critical section
sem_t s[N];  // to control the access of the philosopher to the fork

int state[N];  // to store the state of the philosopher

void *philosopher(void *arg)    // arg is the philosopher number
{
    int i = *(long int *)arg;
    while (1)
    {
        sleep(1);
        take_fork(i);
        sleep(0);
        put_fork(i);
    }
}

void take_fork(int i)    // i is the philosopher number , function to take fork
{
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is Hungry\n", i + 1);
    test(i);
    sem_post(&mutex);
    sem_wait(&s[i]);
    sleep(1);
}

void put_fork(int i)   // i is the philosopher number , function to put fork
{
    sem_wait(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", i + 1, LEFT + 1, i + 1);
    printf("Philosopher %d is thinking\n", i + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void test(int i)   // i is the philosopher number , function to test the philosopher state
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[i] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", i + 1, LEFT + 1, i + 1);
        printf("Philosopher %d is Eating\n", i + 1);
        sem_post(&s[i]);
    }
}

int main()
{
    long int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&s[i], 0, 0);
    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &i);
        printf("Philosopher %ld is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}
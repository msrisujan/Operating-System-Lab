// Write a program to create five threads using pthread library. Find the sum of first 1000 numbers using five threads,
// where each thread can calculate sum of 200 numbers in each (parallel counting using threads).
// After completion of threads operation, print the final sum from the main function.

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

// int sum[5];

// void *thread_fn(void *arg){
//     int id = (long int)arg;
//     int start = id * 200 + 1;
//     int end = (id + 1) * 200;
//     int i;
//     for(i = start; i <= end; i++){
//         sum[id] += i;
//     }
//     return NULL;
// }

// int main(){
//     pthread_t tid[5];
//     long int i;
//     for(i = 0; i < 5; i++){
//         pthread_create(&tid[i], NULL, &thread_fn, (void *)i);
//     }
//     for(i = 0; i < 5; i++){
//         pthread_join(tid[i], NULL);
//     }
//     int total = 0;
//     for(i = 0; i < 5; i++){
//         total += sum[i];
//     }
//     printf("Sum of first 1000 numbers is %d\n", total);
//     return 0;
// }

typedef struct{     // range of numbers
    int start;
    int end;
    int sum;
} range;

void *sum_in_range(void *arg){   // sum of numbers in range
    range *r = arg;
    r->sum = 0;
    for(int i = r->start; i <= r->end; i++){
        r->sum += i;
    }
    return NULL;
}

int main()
{
    pthread_t tid[5];   // 5 threads
    range r[5];  // 5 ranges
    int n = 1000;
    int t = 5;
    int div = n / t;
    for (int i = 0; i < t; i++){   // create 5 threads
        r[i].start = i * div + 1;
        r[i].end = (i + 1) * div;
        pthread_create(&tid[i], NULL, &sum_in_range, &r[i]);  // create thread
    }
    int total = 0;
    for (int i = 0; i < t; i++){
        pthread_join(tid[i], NULL);   // wait for thread to finish
        total += r[i].sum;
    } 
    printf("Sum of first 1000 numbers is %d\n", total);
    return 0;
}
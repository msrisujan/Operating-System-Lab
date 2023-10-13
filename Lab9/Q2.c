// Write a program where you create 3 threads. Consider two global matrix M1 and M2 of size 3 x 3.
// Perform addition, subtraction and multiplication in individual thread and store in matrix A[3][3], S[3][3] and M[3][3]. 
// Print the individual matrix values (M1 and M2) and computed matrix of addition, subtraction, multiplication operation in the main function . 
// Once all thread process will be completed, then only main function will execute.

// Name: M.Sri Sujan
// Roll No: CS21B1081

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

int M1[3][3] = {     // 3 x 3 matrix
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
int M2[3][3] = {    // 3 x 3 matrix
        {1, 2, 3}, 
        {6, 5, 4}, 
        {7, 8, 9}
    };

int A[3][3];  // addition matrix
int S[3][3];   // subtraction matrix
int M[3][3];  // multiplication matrix

typedef struct{   // size of matrix
    int i;
    int j;
} size;

void *add(void *arg){   // addition
    size *s = arg;
    for(int m = 0; m < s->i; m++){
        for(int n = 0; n < s->j; n++){
            A[m][n] = M1[m][n] + M2[m][n];
        }
    }
    return NULL;
}

void *sub(void *arg){    // subtraction
    size *s = arg;
    for(int m = 0; m < s->i; m++){
        for(int n = 0; n < s->j; n++){
            S[m][n] = M1[m][n] - M2[m][n];
        }
    }
    return NULL;
}

void *mul(void *arg){   // multiplication
    size *s = arg;
    for(int m = 0; m < s->i; m++){
        for(int n = 0; n < s->j; n++){
            M[m][n] = 0;
            for(int k = 0; k < s->j; k++){
                M[m][n] += M1[m][k] * M2[k][n];
            }
        }
    }
    return NULL;
}

int main(){
    pthread_t tid[3];  // 3 threads
    size s = {3, 3};  // size of matrix
    pthread_create(&tid[0], NULL, &add, &s);        // create thread
    pthread_create(&tid[1], NULL, &sub, &s);        // create thread
    pthread_create(&tid[2], NULL, &mul, &s);        // create thread
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);     // wait for thread to finish
    pthread_join(tid[2], NULL);
    printf("Matrix M1:\n");    // print matrix
    for(int m = 0; m < 3; m++){
        for(int n = 0; n < 3; n++){
            printf("%d ", M1[m][n]);
        }
        printf("\n");
    }
    printf("Matrix M2:\n");
    for(int m = 0; m < 3; m++){
        for(int n = 0; n < 3; n++){
            printf("%d ", M2[m][n]);
        }
        printf("\n");
    }
    printf("Matrix A:\n");
    for(int m = 0; m < 3; m++){
        for(int n = 0; n < 3; n++){
            printf("%d ", A[m][n]);
        }
        printf("\n");
    }
    printf("Matrix S:\n");
    for(int m = 0; m < 3; m++){
        for(int n = 0; n < 3; n++){
            printf("%d ", S[m][n]);
        }
        printf("\n");
    }
    printf("Matrix M:\n");
    for(int m = 0; m < 3; m++){
        for(int n = 0; n < 3; n++){
            printf("%d ", M[m][n]);
        }
        printf("\n");
    }
    return 0;
}
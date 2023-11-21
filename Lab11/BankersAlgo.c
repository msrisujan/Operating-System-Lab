// Implement Banker's algorithm. Consider 6 processes and 4 types of resources.

// Define the ALLOCATION and  MAX matrix  and the AVAILABLE array. Find the NEED matrix. 
// You must ensure that your initial allocation will always lead to the system in safe state.

// Now, take the input from the user for any process as additional request. Find that this request will lead to safe or unsafe state.

// For eg. P1=(0, 0, 1, 1)

// Check whether additional P1 request will lead to safe state or not,

// (a) If safe then print "SAFE", sequence of safe processes and update the  ALLOCATION, MAX and NEED Matrix

// (b) If unsafe then print "UNSAFE" and discard the request without updating the above matrix.

// You must take multiple times input from the user.

// Name: M.Sri Sujan
// Roll No: CS21B1081

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int check_safety(int n, int m, int allocation[n][m], int available[m], int need[n][m])  // 1 for safe, 0 for unsafe
{
    int i, j, k;
    int work[m];
    for (i = 0; i < m; i++){
        work[i] = available[i];  // initially work = available
    }
    bool finish[n];
    for (i = 0; i < n; i++){ 
        finish[i] = false;      // initially all processes are unfinished
    }
    
    int count;
    int flag = 0;      
    while (1)    
    {
        count = 0;
        for (i = 0; i < n; i++)   // for each process check if it can be finished
        {
            if (finish[i] == false)
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m)
                {
                    for (k = 0; k < m; k++){
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    count++;
                }
            }
        } 
        if (count == 0){  // if no process can be finished
            break;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (finish[i] == false)   // if any process is unfinished
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void print_table(int n, int m, int allocation[n][m], int available[m], int need[n][m]){  // prints matrices in tabular form
    int i, j;
    printf("Allocation\tNeed\t\tAvailable\n");
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            printf("%d ", allocation[i][j]);
        }
        printf("\t");
        for(j = 0; j < m; j++){
            printf("%d ", need[i][j]);
        }
        if(i == 0){
            printf("\t");
            for(j = 0; j < m; j++){
                printf("%d ", available[j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int n, m;
    n = 6;
    m = 4; 
    int max[6][4] = {{7, 5, 3, 2},       // max matrix
                    {3, 2, 2, 2},
                    {9, 0, 2, 2},
                    {2, 2, 2, 2},
                    {4, 3, 3, 3},
                    {5, 3, 2, 3}};
    int allocation[6][4] = {{0, 0, 1, 0},              // allocation matrix
                            {2, 0, 0, 1},
                            {3, 0, 2, 2},
                            {2, 1, 1, 0},
                            {0, 2, 0, 2},
                            {2, 1, 1, 2}};
    int available[4] = {3, 2, 1, 1};            // available array
    int need[6][4];
    int i, j, k;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            need[i][j] = max[i][j] - allocation[i][j];  // need matrix
        }
    }
    if(check_safety(n, m, allocation, available, need)){    // check if initial state is safe
        printf("Safe state\n");
        print_table(n, m, allocation, available, need);
    }
    else{
        printf("Unsafe state\n");
        exit(0);
    }
    int choice = 1;
    while(choice){          // to take multiple inputs from user
        int flag = 0; 
        printf("0. Exit\n");
        printf("1. To Enter process number\n");
        printf("Enter choice: ");           // 0 to exit, 1 to enter process number
        scanf("%d", &choice);
        if(choice == 0){
            break;
        }
        int process;
        printf("Enter process number: ");
        scanf("%d", &process);
        int request[m];
        printf("Enter request: ");
        for(i = 0; i < m; i++){
            scanf("%d", &request[i]);
        }
        for(i = 0; i < m; i++){
            if(request[i] > need[process][i]){          // check if request is valid
                printf("Request cannot be granted\n");
                flag = 1;
            }
        }
        if(flag){
            continue;
        }
        for(i = 0; i < m; i++){
            if(request[i] > available[i]){              // check if request is valid
                printf("Request cannot be granted\n");
                flag = 1;
            }
        }
        if(flag){                            // if request is invalid
            continue;
        }
        for(i = 0; i < m; i++){         // if request is valid
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }
        if(check_safety(n, m, allocation, available, need)){        // check if state is safe
            printf("Safe state\n"); 
            print_table(n, m, allocation, available, need);
        }
        else{
            printf("Unsafe state\n");           // if state is unsafe
            for(i = 0; i < m; i++){
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
        }
    }
    return 0;
}
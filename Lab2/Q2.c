// Write a C program to implement First Come First Serve CPU Scheduling Algorithm.

// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply FCFS.

// (ii) Your algorithm should work for both scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.

// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.

// (iv) Further compute the average waiting time and average turnaround time.

// (v) Print the schedule for the given input.

// Note: You can use only integers for process id. Use the linked list implementation for the Queue. 

//name: M.Sri Sujan
//rollno: CS21B1081


#include<stdio.h>
#include<stdlib.h>

struct Process {           //structure for process
    int P_id;
    int AT;
    int BT;
    int FT;
    int TAT,WT,RT;
    struct Process *next;    //pointer to next process
};

struct Process *head=NULL;          //head of the queue
struct Process *tail=NULL;          //tail of the queue

void enqueue(int P_id,int AT,int BT){              //function to add process to the queue

    struct Process *proc;
    proc = (struct Process*)malloc(sizeof(struct Process));
    proc->P_id=P_id;
    proc->AT=AT;
    proc->BT=BT;
    proc->next=NULL;

    if(head==NULL){                         
        head=proc;
        tail=proc;
    }
    else{
        tail->next=proc;
        tail=proc;
    }
    
}

int main() {
    int n;
    printf("Enter number of processes: ");         //taking input from user
    scanf("%d",&n);
    int P_id=0;
    int AT,BT;
    int current_time=0;           //current time of the CPU
    
    for(int i=0;i<n;i++){          //adding processes to the queue
        P_id=i+1;
        printf("Enter Arrival Time for pid %d: ",P_id);     
        scanf("%d",&AT);
        printf("Enter Burst Time for pid %d: ",P_id);
        scanf("%d",&BT);
        
        enqueue(P_id,AT,BT);
    }
    float average_TAT=0;        //variables to store average TAT and WT
    float average_WT=0;
    float total_TAT=0;
    float total_WT=0;

    struct Process *ptr = head;
    while(ptr != NULL){                    //calculating FT,TAT,WT,RT for each process
        if(current_time<ptr->AT){           //if current time is less than arrival time of the process 
            current_time = ptr->AT;
        }
        ptr->FT = current_time + ptr->BT;      
        ptr->TAT = ptr->FT - ptr->AT;
        ptr->WT = ptr->TAT - ptr->BT;
        ptr->RT = ptr->WT;
        current_time = ptr->FT;
        total_TAT += ptr->TAT;
        total_WT += ptr->WT;
        ptr = ptr->next;         //moving to next process
    }

    average_TAT = total_TAT/n;
    average_WT = total_WT/n;

    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");     //printing the schedule
    ptr = head;
    while(ptr != NULL){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",ptr->P_id,ptr->AT,ptr->BT,ptr->FT,ptr->TAT,ptr->WT,ptr->RT);
        ptr = ptr->next;
    }
    printf("Average TAT: %f\n",average_TAT);
    printf("Average WT: %f\n",average_WT);

    return 0;

}

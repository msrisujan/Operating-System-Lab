// Write a C program to implement the Shortest Job First Scheduling Algorithm.

// (i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply SJF.

// (ii) Your algorithm should work for both scenarios: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.

// (iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.

// (iv) Further compute the average waiting time and average turnaround time.

// (v) Print the schedule for the given input.

// Note: You can use only integers for process id. Use the min heap data structure (using linked list) to implement SJF Queue.

// name: M.Sri Sujan
// rollno: CS21B1081

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

struct MinHeap {
    struct Process *head;
};

struct MinHeap* createMinHeap(){
    struct MinHeap *minHeap=(struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->head=NULL;
    return minHeap;
};

void swapNodes(struct Process *a,struct Process *b){
    int temp;
    temp=a->P_id;
    a->P_id=b->P_id;
    b->P_id=temp;
    temp=a->AT;
    a->AT=b->AT;
    b->AT=temp;
    temp=a->BT;
    a->BT=b->BT;
    b->BT=temp;
}

void heapify(struct Process* proc){
    struct Process *min=proc;
    struct Process *l=proc->next;
    struct Process *r=l ? l->next : NULL;
    if(l && l->BT<min->BT){
        min=l;
    }
    if(r && r->BT<min->BT){
        min=r;
    }
    if(min!=proc){
        swapNodes(min,proc);
        heapify(min);
    }
}

void insert(struct MinHeap *minHeap,struct Process *proc){
    //if heap is empty
    if(minHeap->head==NULL){
        minHeap->head=proc;
        return;
    }
    struct Process *proc1=(struct Process*)malloc(sizeof(struct Process));
    proc1->P_id=proc->P_id;
    proc1->AT=proc->AT;
    proc1->BT=proc->BT;
    proc1->next=minHeap->head;
    minHeap->head=proc1;

    struct Process *ptr=minHeap->head;
    while(ptr != NULL){
        heapify(ptr);
        ptr=ptr->next;
    }
}



int main(){
    int n;
    printf("Enter no of processes: ");
    scanf("%d",&n);
    int P_id=0;
    int AT,BT;
    int prev_start_time=0;
    struct Process *a[n];
    struct Process *b[n];
    for(int i=0;i<n;i++){
        P_id++;
        printf("Enter arrival time and burst time of process %d: ",P_id);
        scanf("%d %d",&AT,&BT);
        a[i]=(struct Process*)malloc(sizeof(struct Process));
        a[i]->P_id=P_id;
        a[i]->AT=AT;
        a[i]->BT=BT;
        a[i]->next=NULL;
    }
    struct MinHeap *minHeap=createMinHeap();
    int process_completed=0;
    // min arrival time
    int current_time=a[0]->AT;
    struct Process *proc;
    int x=n;
    float avg_TAT=0,avg_WT=0;
    float total_TAT=0,total_WT=0;
    

    while(process_completed<x){
        int i=0;
        while (i<n){
            if(a[i]->AT<=current_time){
                struct Process *proc1=(struct Process*)malloc(sizeof(struct Process));
                proc1->P_id=a[i]->P_id;
                proc1->AT=a[i]->AT;
                proc1->BT=a[i]->BT;
                insert(minHeap,proc1);
            }
            i++;
        }
        if(minHeap->head==NULL){
            current_time++;
            continue;
        }
        proc=minHeap->head;
        proc->FT=current_time+proc->BT;
        proc->TAT=proc->FT-proc->AT;
        proc->WT=proc->TAT-proc->BT;
        proc->RT=proc->WT;
        current_time=proc->FT;
        total_TAT+=proc->TAT;
        total_WT+=proc->WT;

        b[proc->P_id-1]=(struct Process*)malloc(sizeof(struct Process));
        b[proc->P_id-1]->P_id=proc->P_id;
        b[proc->P_id-1]->AT=proc->AT;
        b[proc->P_id-1]->BT=proc->BT;
        b[proc->P_id-1]->FT=proc->FT;
        b[proc->P_id-1]->TAT=proc->TAT;
        b[proc->P_id-1]->WT=proc->WT;
        b[proc->P_id-1]->RT=proc->RT;

        // remove all processes from min heap
        while(minHeap->head!=NULL){
            minHeap->head=minHeap->head->next;
        }
        //remove completed process from array
        for(int k=0;k<n;k++){
            if(a[k]->P_id==proc->P_id){
                for(int j=k;j<n-1;j++){
                    a[j]=a[j+1];
                }
                n--;
            }
        }

        process_completed++;
    }
    avg_TAT=total_TAT/x;
    avg_WT=total_WT/x;

    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");  
    for(int i=0;i<x;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",b[i]->P_id,b[i]->AT,b[i]->BT,b[i]->FT,b[i]->TAT,b[i]->WT,b[i]->RT);
    }
    printf("Average TAT: %f\n",avg_TAT);
    printf("Average WT: %f\n",avg_WT);
    return 0;

}
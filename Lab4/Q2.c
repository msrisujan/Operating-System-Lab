// Write a C program to implement round-robin scheduling.

// (i)Take input from the user as P_id, arrival time, burst Time, and time quantum.

// (ii) Show the turnaround time, waiting time, and response time for each task.

// (iii) Compute average turnaround time, waiting time, and response time.

// (iv) Count the number of context switches (excluding the count at the beginning of the first execution process and the end of the last execution process)

// (v) Your algorithm should work for both the scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time

 

// Note: You can use only integers for process id. Use the array implementation(dynamically using malloc) for the Queue. At the end of the program remove the queue from the memory.


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
    int priority;
    int start_time;
    int running_time;
    int completed;
};

struct Queue{              //structure for queue
    int front,rear;
    int size;
    struct Process *array;
};

struct Queue* createQueue(int n){
    struct Queue *queue=(struct Queue*)malloc(sizeof(struct Queue));
    queue->front=queue->rear=-1;
    queue->size=n;
    queue->array=(struct Process*)malloc(n*sizeof(struct Process));
    return queue;
}

//enqueue function
void enqueue(struct Queue *queue,struct Process *proc){
    if(queue->rear==queue->size-1){
        printf("Queue is full\n");
        return;
    }
    queue->rear++;
    queue->array[queue->rear]=*proc;
    if(queue->front==-1){
        queue->front++;
    }
}

//dequeue function
//delete from front
struct Process* dequeue(struct Queue *queue){
    if(queue->front==-1){
        printf("Queue is empty\n");
        return NULL;
    }
    struct Process *proc=&queue->array[queue->front];
    if(queue->front==queue->rear){
        queue->front=queue->rear=-1;
    }
    else{
        queue->front++;
    }
    return proc;
}
//copy function
void copy(struct Process *proc1,struct Process *proc2){
    proc1->P_id=proc2->P_id;
    proc1->AT=proc2->AT;
    proc1->BT=proc2->BT;
    proc1->FT=proc2->FT;
    proc1->TAT=proc2->TAT;
    proc1->WT=proc2->WT;
    proc1->RT=proc2->RT;
    proc1->priority=proc2->priority;
    proc1->start_time=proc2->start_time;
    proc1->running_time=proc2->running_time;
    proc1->completed=proc2->completed;
}

int main(){
    int n;
    int time_quantum;
    printf("Enter the time quantum: ");
    scanf("%d",&time_quantum);
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int P_id=0;
    int AT,BT;
    struct Queue *queue=createQueue(1000);
    struct Process *a[n];
    struct Process *b[n];
    for(int i=0;i<n;i++){
        P_id++;
        printf("Enter arrival time,burst time of the process %d: ",P_id);
        scanf("%d%d",&AT,&BT);
        a[i] = (struct Process*)malloc(sizeof(struct Process));
        a[i]->P_id=P_id;
        a[i]->AT=AT;
        a[i]->BT=BT;
        a[i]->FT=0;
        a[i]->TAT=0;
        a[i]->WT=0;
        a[i]->RT=0;
        a[i]->start_time=-1;
        a[i]->running_time=0;
        a[i]->completed=0;
    }
    int proc_completed=0;
    int current_time=a[0]->AT;
    float avg_TAT=0,avg_WT=0,avg_RT=0;
    float total_TAT=0,total_WT=0,total_RT=0;
    int context_switch=0;
    while (proc_completed<n){
        for(int i=0;i<n;i++){
            if(a[i]->AT<=current_time && a[i]->start_time==-1 && a[i]->completed==0){
                struct Process *proc1=(struct Process*)malloc(sizeof(struct Process));
                copy(proc1,a[i]);
                a[i]->start_time=0;
                enqueue(queue,proc1);
            }
        }
        if (queue->front==-1){
            current_time++;
            continue;
        }
        struct Process *proc=dequeue(queue);
        struct Process *proc2=(struct Process*)malloc(sizeof(struct Process));
        copy(proc2,proc);


        if(proc2->start_time==-1){
            proc2->start_time=current_time;
        }
        if((proc2->running_time+time_quantum)>=proc2->BT){
            current_time+=proc2->BT-proc2->running_time;
            proc2->running_time=proc2->BT;
            proc2->FT=current_time;
            proc2->TAT=proc2->FT-proc2->AT;
            proc2->WT=proc2->TAT-proc2->BT;
            proc2->RT=proc2->start_time-proc2->AT;
            proc2->completed=1;
            proc_completed++;
            total_TAT+=proc2->TAT;
            total_WT+=proc2->WT;
            total_RT+=proc2->RT;
            b[proc2->P_id-1]=(struct Process*)malloc(sizeof(struct Process));
            copy(b[proc2->P_id-1],proc2);
            context_switch++;
        }
        else{
            current_time+=time_quantum;
            for(int i=0;i<n;i++){
                if(a[i]->AT<=current_time && a[i]->start_time==-1 && a[i]->completed==0){
                    struct Process *proc1=(struct Process*)malloc(sizeof(struct Process));
                    copy(proc1,a[i]);
                    a[i]->start_time=0;
                    enqueue(queue,proc1);
                }
            }
            proc2->running_time+=time_quantum;
            enqueue(queue,proc2);
            context_switch++;
        }
    }
    avg_TAT=total_TAT/n;
    avg_WT=total_WT/n;
    avg_RT=total_RT/n;
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",b[i]->P_id,b[i]->AT,b[i]->BT,b[i]->FT,b[i]->TAT,b[i]->WT,b[i]->RT);
    }
    printf("Average TAT: %f\n",avg_TAT);
    printf("Average WT: %f\n",avg_WT);
    printf("Average RT: %f\n",avg_RT);
    printf("Number of context switches: %d\n",context_switch-1);

}

// Write a C program to Implement a preemptive priority scheduling approach.

// (i) Provide the input as P_id, arrival time (all are arriving at a different time), priority of each process, and burst time.

// (ii) Show the Completion time, turnaround time, waiting time, and response time for each process.

// (iii) Compute average turnaround time, waiting time, and response time.

// (iv) Print the schedule for the given input.

// Note: You can use only integers for process id. Use the array implementation (dynamically using malloc()) for the Queue. At the end of the program remove the queue from the memory.

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
//sort function
void sort(struct Queue *queue){
    for(int i=queue->front;i<queue->rear;i++){
        for(int j=i+1;j<=queue->rear;j++){
            if(queue->array[i].priority>queue->array[j].priority){
                struct Process temp=queue->array[i];
                queue->array[i]=queue->array[j];
                queue->array[j]=temp;
            }
        }
    }
}
//sort by pid for same priority
void sort_pid(struct Queue *queue){
    for(int i=queue->front;i<queue->rear;i++){
        for(int j=i+1;j<=queue->rear;j++){
            if(queue->array[i].priority==queue->array[j].priority){
                if(queue->array[i].P_id>queue->array[j].P_id){
                    struct Process temp=queue->array[i];
                    queue->array[i]=queue->array[j];
                    queue->array[j]=temp;
                }
            }
        }
    }
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
}


int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int P_id=0;
    int AT,BT,priority;
    struct Queue *queue=createQueue(1000);
    struct Process *a[n];
    struct Process *b[n];
    for(int i=0;i<n;i++){
        P_id++;
        printf("Enter arrival time,burst time and priority of the process %d: ",P_id);
        scanf("%d%d%d",&AT,&BT,&priority);
        a[i] = (struct Process*)malloc(sizeof(struct Process));
        a[i]->P_id=P_id;
        a[i]->AT=AT;
        a[i]->BT=BT;
        a[i]->priority=priority;
        a[i]->FT=0;
        a[i]->TAT=0;
        a[i]->WT=0;
        a[i]->RT=0;
        a[i]->start_time=-1;
        a[i]->running_time=0;
    }
    int proc_completed=0;
    int current_time=a[0]->AT;
    float avg_TAT=0,avg_WT=0,avg_RT=0;
    float total_TAT=0,total_WT=0,total_RT=0;

    while(proc_completed<n){
        for(int i=0;i<n;i++){
            if(a[i]->AT==current_time){
                enqueue(queue,a[i]);
            }
        }
        sort(queue);
        sort_pid(queue);
        if(queue->size==0){
            current_time++;
            continue;
        }
        struct Process *proc=dequeue(queue);
        if(proc->start_time==-1){
            proc->start_time=current_time;
        }
        proc->running_time++;
        current_time++;
        if(proc->running_time==proc->BT){
            proc->FT=current_time;
            proc->TAT=proc->FT-proc->AT;
            proc->WT=proc->TAT-proc->BT;
            proc->RT=proc->start_time-proc->AT;
            total_TAT+=proc->TAT;
            total_WT+=proc->WT;
            total_RT+=proc->RT;
            proc_completed++;
            b[proc->P_id-1]=(struct Process*)malloc(sizeof(struct Process));
            copy(b[proc->P_id-1],proc);
        }
        else{
            enqueue(queue,proc);
        }
    }
    printf("P_id\tAT\tBT\tPriority\tFT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",b[i]->P_id,b[i]->AT,b[i]->BT,b[i]->priority,b[i]->FT,b[i]->TAT,b[i]->WT,b[i]->RT);
    }
    avg_TAT=total_TAT/n;
    avg_WT=total_WT/n;
    avg_RT=total_RT/n;
    printf("Average TAT: %f\n",avg_TAT);
    printf("Average WT: %f\n",avg_WT);
    printf("Average RT: %f\n",avg_RT);

    return 0;

}


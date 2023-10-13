#include<stdio.h>
#include<stdlib.h>

struct Process{
    int P_id;
    int AT;
    int BT;
    int start_time;
    int RT,WT,TAT,FT;
    int remaining_time;
};

struct Queue{
    int front,rare,size;
    struct Process *array;
};

struct Queue* createQueue(int n){
    struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rare = -1;
    queue->size = n;
    queue->array = (struct Process*)malloc(n*sizeof(struct Process));
    return queue;
}

void enqueue(struct Queue* queue,struct Process* proc){
    if(queue->rare == queue->size - 1){
        printf("Queue if full");
        return;
    }
    queue->rare++;
    queue->array[queue->rare] = *proc;
    if(queue->front == -1)
        queue->front++;
}

struct Process* dequeue(struct Queue* queue){
    if(queue->front == -1){
        printf("Queue is empty");
        return NULL;
    }
    struct Process* proc = &queue->array[queue->front];
    if(queue->front == queue->rare)
        queue->front = queue->rare = -1;
    else{
        queue->front++;
    }
    return proc;
}

void sort_rt(struct Queue* queue){
    for(int i = queue->front; i < queue->rare; i++){
        for(int j = i + 1; j <= queue->rare; j++){
            if(queue->array[i].remaining_time > queue->array[j].remaining_time){
                struct Process temp = queue->array[i];
                queue->array[i] = queue->array[j];
                queue->array[j] = temp;
            }
        }
    }
}

void sort_pid(struct Queue* queue){
    for(int i = queue->front; i < queue->rare; i++){
        for(int j = i + 1; j <= queue->rare; j++){
            if(queue->array[i].remaining_time == queue->array[j].remaining_time){
                if(queue->array[i].P_id > queue->array[j].P_id){
                    struct Process temp = queue->array[i];
                    queue->array[i] = queue->array[j];
                    queue->array[j] = temp;
                }
            }
        }
    }
}

void copy(struct Process *proc1, struct Process *proc2){
    proc1->P_id=proc2->P_id;
    proc1->AT=proc2->AT;
    proc1->BT=proc2->BT;
    proc1->FT=proc2->FT;
    proc1->TAT=proc2->TAT;
    proc1->WT=proc2->WT;
    proc1->RT=proc2->RT;
    proc1->start_time=proc2->start_time;
    proc1->remaining_time=proc2->remaining_time;
}

int main(){
    struct Queue *queue = createQueue(1000);
    int AT,BT;
    int n;
    printf("Enter no of processes: ");
    scanf("%d",&n);
    struct Process* a[n];
    struct Process* b[n];
    int P_id = 0;
    for(int i = 0; i < n; i++){
        P_id++;
        printf("Enter AT,BT for process-%d: ",P_id);
        scanf("%d %d",&AT,&BT);
        a[i] = (struct Process*)malloc(sizeof(struct Process));
        a[i]->P_id = P_id;
        a[i]->AT = AT;
        a[i]->BT = BT;
        a[i]->remaining_time = BT;
        a[i]->RT = 0;
        a[i]->start_time = -1;
        a[i]->TAT = 0;
        a[i]->WT = 0;
        a[i]->FT = 0;
    }
    int pc = 0;
    int ct = 0;
    while(pc < n){
        for(int i = 0; i < n; i++){
            if(a[i]->AT == ct){
                enqueue(queue,a[i]);
            }
        }
        sort_rt(queue);
        sort_pid(queue);
        if(queue->size == 0){
            ct++;
            continue;
        }
        struct Process* proc2 = dequeue(queue);
        struct Process *proc=(struct Process*)malloc(sizeof(struct Process));
        copy(proc,proc2);
        printf("%d\n",proc->start_time);

        if(proc->start_time == -1){
            proc->start_time == ct;
        }
        proc->remaining_time--;
        ct++;
        if(proc->remaining_time == 0){
            proc->FT = ct;
            proc->RT = proc->start_time - proc->AT;
            proc->TAT = proc->FT - proc->AT;
            proc->WT = proc->TAT - proc->BT;
            b[proc->P_id - 1] = (struct Process*)malloc(sizeof(struct Process));
            b[proc->P_id - 1] = proc;
            pc++;
        }
        else{
            enqueue(queue,proc);
        }
    }
    printf("P_id\tAT\tBT\tFT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",b[i]->P_id,b[i]->AT,b[i]->BT,b[i]->FT,b[i]->TAT,b[i]->WT,b[i]->RT);
    }
    return 0;
}

// 6
// 0 8
// 1 4
// 2 2
// 3 1
// 4 3
// 5 2
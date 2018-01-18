//
// Created by wassim on 25/11/17.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "../../Queue/Queue.h"

#endif

#ifndef FIFO_H
#define FIFO_H

#include "FIFO.h"

#endif

#ifndef LIMITS_H
#define LIMITS_H

#endif

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#endif

#ifndef UNISTD_H
#define UNISTD_H

#include <unistd.h>

#endif

#ifndef EMUORD_EXECUTE_C_H
#define EMUORD_EXECUTE_C_H

#include "../../EmuProcess/execute.h"

#ifndef DATE_H
#define DATE_H

#include "Date.h"
#endif

#endif //EMUORD_EXECUTE_C_H

#ifndef TIME_H
#define TIME_H

#endif

#ifndef EMUORD_LINKEDLIST_H
#define EMUORD_LINKEDLIST_H

#include "../../LinkedList/LinkedList.h"
#endif

PCBNODE *front;
PCBNODE *rear;

pthread_cond_t pthreadCond = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;      /* Création du mutex */

struct pthreadArgs {
    char *procName;
    int procId;
    Date remExecTime;
};

struct syncChannel synchInfo;

/*
  * Execute in Queue Order .. No priority, No interruption
 */
void exec() {
    LinkedList *ExecutionQueue = NULL;
    PCB thisPcb;
    pthread_t tid;                        //Init new Thread ID
    struct pthreadArgs args;              //Args to be passed to process worker
    char processIsRunning = 0;            // process is Runing flag
    int nextIn;

    //We have more process to come from Main Queue, or we are already Executing process ot We have More to Execute
    while ((nextIn = updateExecutionQueue(&ExecutionQueue)) != -1 || processIsRunning || ExecutionQueue != NULL) {
        if (!processIsRunning) {
            if (nextIn > 0) {
                // sleep in seconds
                printf("waiting for %d  seconds : \n", nextIn);
                sleep(nextIn);
            }

            thisPcb = ExecutionQueue->data;
            args.procName = thisPcb.name;
            args.procId = thisPcb.id;
            args.remExecTime = thisPcb.remExecTime;

            // sleep in mS
            printf("Reached !! waiting in milliseconds : \n");
            struct timespec ts;
            ts.tv_sec = 0;
            ts.tv_nsec = 1000000 * thisPcb.creationDate.millisecond;
            nanosleep(&ts, NULL);

            /*
         * Process is Ready !
         */
            thisPcb.state = READY;
            synchInfo.state = READY;

            pthread_create(&tid, NULL, worker, (void *) &args); //Thread created ! process is running
            processIsRunning = 1;
        }

        /*
         * Look for TERMINATED `signal` ..
         * if found :
         *    Change process state and set processIsRuning flag to false to execute next process
         *  else:
         *    continue....
        */

        pthread_mutex_lock(&lock); //lock on shared variables
        if (synchInfo.state == TERMINATED) {
            thisPcb.state = TERMINATED;
            /*
                int s = pthread_cancel(tid);
                if(s != 0)
                    printf("Couldn't terminate thread");
                 */
            processIsRunning = 0;
            //We move to the next process
            ExecutionQueue = ExecutionQueue->next;
        } else if (thisPcb.state != synchInfo.state) {
            // Synchronize PCB with Current State
            thisPcb.state = synchInfo.state;
        }
        pthread_mutex_unlock(&lock); //unlock shared variables .. may thread continue working in peace
    }
}

/*
  * Returns  -1 if ProcessQueue is NULL
  * Returns  seconds till next process execution time
 */
int updateExecutionQueue(LinkedList **head) {
    unsigned int diff = 0;
    short isValidDate;
    PCBNODE *tmp;

    while (front) {
        diff = DateDiffrence(front->current.creationDate, &isValidDate);
        if (!isValidDate) {
            tmp = front;
            front = front->next;
            free(tmp);
        } else if (diff == 0) { //don't think append it
            front->current.state = READY;
            append(head, front->current);
            tmp = front;
            front = front->next;
            free(tmp);
        } else if (*head == NULL) { //we can't return empty handed
            front->current.state = NEW;
            append(head, front->current);
            tmp = front;
            front = front->next;
            free(tmp);
            return diff;
        }
    }
    return -1;
}


/*{
    //pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock (&lock);
}*/
//
// Created by wassim on 25/11/17.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "../../Queue/Queue.h"

#endif

#ifndef LIMITS_H
#define LIMITS_H

#include <limits.h>

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

#include <time.h>

#endif

PCBNODE *front;
PCBNODE *rear;


pthread_cond_t pthreadCond = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

struct pthreadArgs {
    char *procName;
    int procId;
    Date remExecTime;
};

struct syncChannel synchInfo;

//TODO : add NEW process state ! when creation time matches current system time

void exec() {

    //Execute in Queue Order .. No priority, No interruption
    for (front; front != NULL; front = front->next) {

        //verify process creationDate is still valid
        //consume time till creation time comes
        //while(front->current.id == 1575)
        unsigned int diff;
        short isValidDate;
        diff = DateDiffrence(front->current.creationDate, &isValidDate);
        if (!isValidDate)
            continue;
        if ((diff) > 0) // sleep in seconds
        {
            printf("waiting for '%s' %d seconds : \n", front->current.name, diff);
            sleep(diff);
            goto sleepNano;
        } else if (diff == 0) {
            sleepNano:
            printf("Reached !! waiting in milliseconds : \n");
            struct timespec ts;
            ts.tv_sec = 0;
            ts.tv_nsec = 1000000 * front->current.creationDate.millisecond;
            nanosleep(&ts, NULL);
        } else
            continue;

        pthread_t tid; //Init new Thread ID
        //Args to be passed to process worker
        struct pthreadArgs args = {front->current.name, front->current.id, front->current.remExecTime};

        /*
         * Process is Ready !
         */
        front->current.state = READY;
        synchInfo.state = READY;

        pthread_create(&tid, NULL, worker, (void *) &args); //Thread created ! process is running

        /*
         * Keep on looking for TERMINATED `signal` ..
         * if so :
         *    Change process state and break loop (move to next process)
         * else :
         *    Synchronize process state && continue looping
         */
        while (1) {
            pthread_mutex_lock(&lock);//lock on shared variables
            if (synchInfo.state == TERMINATED) {
                front->current.state = TERMINATED;
                /*
                int s = pthread_cancel(tid);
                if(s != 0)
                    printf("Couldn't terminate thread");
                 */
                pthread_mutex_unlock(&lock);
                break;
            } else if (front->current.state != synchInfo.state) {
                // Synchronize PCB with Current State
                front->current.state = synchInfo.state;
            }
            pthread_mutex_unlock(&lock); //unlock shared variables .. may thread continue working in peace
        }
        /*{
            //pthread_cond_signal(&pthreadCond);
            pthread_mutex_unlock (&lock);
        }*/

    }
}
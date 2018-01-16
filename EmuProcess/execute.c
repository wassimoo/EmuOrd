//
// Created by wassim on 20/12/17.
//

#ifndef STDIO_H
#define STDIO_H

#include <stdio.h>

#endif

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif

#ifndef PCB_H
#define PCB_H

#include "../PCB/PCB.h"

#endif

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#endif

#ifndef EMUORD_EXECUTE_C_H
#define EMUORD_EXECUTE_C_H

#include "execute.h"

#endif

#ifndef UNISTD_H
#define UNISTD_H

#include <unistd.h>

#endif

extern pthread_cond_t pthreadCond; /* Création de la condition */
extern pthread_mutex_t lock; /* Création du mutex */

extern struct syncChannel synchInfo;


struct pthreadArgs {
    char *procName;
    int procId;
    Date remExecTime;
};

/*
 * Intro:
 *   *Where Magic Happens*
 * DESC:
 *  EmuOrd needs an EmuProcess, we invented this little piece of magic to Emulate a process.
 *  Worker keeps thread busy for some time (remExecTime).
 *
 * LOGIC:
 *      1 - Initialise SyncInfo process state to RUNNING
 *      2 - Decrement remaining Time by one mS- if we still have one -
 *      3 - Check if interruption signal is sent by the Scheduler
 *          if so:
 *              block current thread & return control to scheduler
 *          else:
 *              continue working in peace
 *              - Return to step 2-
 *     4 - All remaining time has been consumed and Process should end
 *          -> set SyncInfo process state to TERMINATED
 *          -> wait till Scheduler receive TERMINATED signal and terminate thread
 * ARGS:
 *     type : pointer to `pthreadArgs` structure
 *
 */

void *worker(void *args) {

    //Respond to cancel state immediately, no lag should occur
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    //Load args to pthreadArgs structure makes fields access easier
    struct pthreadArgs info = *(struct pthreadArgs *) args;

    printf("Process Name : %s    id : %d \nExecuting... \n", info.procName, info.procId);

    /*
     * Will be Used in nanoSleep()
     * have no idea what this does
     * thanks to StackOverflow xD
     */
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000;


    pthread_mutex_lock(&lock);//lock on shared variables
    synchInfo.state = RUNNING;//Clear the way i'm in hurry bitches
    pthread_mutex_unlock(&lock);// Scheduler can continue to access shared variables

    int i = 0;

    while (dec(&info.remExecTime)) {
        pthread_mutex_lock(&lock);
        if (synchInfo.interrupt) {
            synchInfo.state = SUSPENDED;
            pthread_cond_wait(&pthreadCond, &lock);
        } else {
            pthread_mutex_unlock(&lock);
        }
        i++;
        if (i % 1000 == 0)
            printf("%d\n", i / 1000);
        nanosleep(&ts, NULL);
    }

    pthread_mutex_lock(&lock);
    synchInfo.state = TERMINATED;
    pthread_mutex_unlock(&lock);
    //sleep(1000);        /* Should get canceled while we sleep */
    return NULL;
}
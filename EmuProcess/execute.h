//
// Created by wassim on 20/12/17.
//

#ifndef EMUORD_EXECUTE_C_H
#define EMUORD_EXECUTE_C_H

#endif //EMUORD_EXECUTE_C_H

/*
 * DESCRIPTION:
 * This Structure is Used to Synchronize communication with the current process,
 * Real Values are actually saved within the PCB.
 *
 * NOTE:
 *  We cannot pass the PCB as an argument to the process itself.
 *  why ? because Write access to the PCB within the process
 *  can be violent tho Our Scheduler..
 *  We use these Signals (Channel Like) to Synchronize processes
 *
 * FIELDS DESC:
 * @processState : notify Scheduler of Process State
 * @interrupt: Interruption Signal Sent by the Scheduler
 */
struct syncChannel{
    enum processState state;
    int interrupt;
};

void *worker(void *args);


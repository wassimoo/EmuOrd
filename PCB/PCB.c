//
// Created by wassim on 25/11/17.
//

#ifndef PCB_H
#define PCB_H
#include "PCB.h"

#endif


//TODO: modify pcb functions arguments to satisfy our needs

#ifndef DATE_H
#define DATE_H
#include "../Date/Date.h"
#endif //DATE_H

int initPcb(PCB *pcb) {
    pcb->remExecTime = addDates(pcb->ioTime,pcb->cpuCycles);
}

int updatePcb() {
}

int endPcb() {
}


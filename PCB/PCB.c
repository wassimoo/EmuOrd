//
// Created by wassim on 25/11/17.
//

#ifndef PCB_H
#define PCB_H
#include "PCB.h"
#endif

//TODO: modify pcb functions arguments to satisfy our needs

int initPcb() {
}

int updatePcb() {
}

int endPcb() {
}

int cmpDate(Date d1, Date d2) {
    if (d1.year != d2.year)
        return d1.year - d2.year;

    if (d1.month != d2.month)
        return d1.month - d2.month;

    if (d1.day != d2.day)
        return d1.day - d2.day;

    if (d1.hour != d2.hour)
        return d1.hour - d2.hour;

    if (d1.minute != d2.minute)
        return d1.minute - d2.minute;

    if (d1.second != d2.second)
        return d1.second - d2.second;

    return d1.millisecond - d2.millisecond;
}
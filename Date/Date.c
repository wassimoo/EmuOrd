//
// Created by wassim on 15/01/18.
//

#ifndef TIME_H
#define TIME_H

#include <time.h>

#endif

#ifndef DATE_H
#define DATE_H

#include "Date.h"

#endif

/*
 * cmpDate(Date,Date) : compares two given Dates..
 * 0 is returned if equal otherwise returns difference' between them
 * 'difference > 0 IF d1 > d2 and vise versa
 */
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

/*
 * addDates(Date,Date) : Adds two given Dates and return result
 */
Date addDates(Date d1, Date d2) {

/****************************************************
*              Format Date Fileds                   *
*****************************************************/

    /*
     * No need for year or month,
     * processExecTime can be measured in days
     */
    d1.year = d2.year = 0;
    d1.month = d2.month = 0;

    d1.day = d1.day < 0 ? 0 : d1.day;
    d2.day = d2.day < 0 ? 0 : d2.day;

    d1.hour = d1.hour < 0 ? 0 : d1.hour;
    d2.hour = d2.hour < 0 ? 0 : d2.hour;

    d1.minute = d1.minute < 0 ? 0 : d1.minute;
    d2.minute = d2.minute < 0 ? 0 : d2.minute;

    d1.second = d1.second < 0 ? 0 : d1.second;
    d2.second = d2.second < 0 ? 0 : d2.second;

/****************************************************
*              Add two dates                       *
****************************************************/

    d1.millisecond += d2.millisecond;
    d1.second += d2.second;
    d1.minute += d2.minute;
    d1.hour += d2.hour;
    d1.day += d2.day;
    d1.month += d2.month;
    d1.year += d2.year;

    formatDate(&d1);
    return d1;
}

/*
 * FormatDate(Date) : used to validate Date value ranges
 * (ex. seconds € [0..59] ...)
 */
void formatDate(Date *d) {

    if (d->millisecond > 999) {
        d->second += (int) d->millisecond / 1000;
        d->millisecond = d->millisecond % 1000;
    }

    if (d->second > 59) {
        d->minute += (int) d->second / 60;
        d->second = d->second % 60;
    }

    if (d->minute > 59) {
        d->hour += (int) d->minute / 60;
        d->minute = d->minute % 60;
    }

    if (d->hour > 23) {
        d->day += (int) d->hour / 24;
        d->hour = d->hour % 24;
    }
}

int isNull(Date d) {
    return d.millisecond == 0 &&
           d.second == 0 &&
           d.minute == 0 &&
           d.hour == 0 &&
           d.day == 0 &&
           d.month == 0 &&
           d.year == 0;
}

int dec(Date *d) {
    if (d->millisecond > 0)
        d->millisecond--;
    else {
        d->millisecond = 999;
        if (d->second > 0)
            d->second--;
        else {
            d->second = 59;
            if (d->hour > 0) {
                d->hour--;
            } else {
                d->hour = 23;
                if (d->day > 0)
                    d->day--;
                else
                    return 0; //countdown is done ! process must die ..
            }
        }
    }
    return 1; // process still has more time to run ...
}

/*
 * Returns diffrence between given Date and current date in milliseconds
 */
unsigned int DateDiffrence(Date d, short *isValid) {
    unsigned long diffMs;
    struct tm givenTm;
    struct tm *currentTm;
    time_t given;
    time_t currentTime;
    time(&currentTime);
    currentTm = localtime(&currentTime);
    double diff;
    *isValid = 1;

    givenTm.tm_year = d.year == -1 ? currentTm->tm_year : d.year - 1900;
    givenTm.tm_mon = d.month == -1 ? currentTm->tm_mon : d.month;
    givenTm.tm_mday = d.day == -1 ? currentTm->tm_mday : d.day;
    givenTm.tm_hour = d.hour;
    givenTm.tm_min = d.minute;
    givenTm.tm_sec = d.second;
    givenTm.tm_isdst = -1;

    given = mktime(&givenTm);
    time(&currentTime);

    if ((diff = difftime(given, currentTime)) < 0)
        *isValid = 0;

    return (unsigned int) diff;
}

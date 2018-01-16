//
// Created by wassim on 15/01/18.
//

typedef struct {
    int
            millisecond,
            second,
            minute,
            hour,
            day,
            month,
            year;
} Date;

int cmpDate(Date d1, Date d2);

Date addDates(Date d1, Date d2);

void formatDate(Date *d);

int isNull(Date d);

int dec(Date *d);

unsigned int DateDiffrence(Date d, short *isValid);
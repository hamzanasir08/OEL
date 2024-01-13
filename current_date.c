#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void getCurrentDate(char *currentDate) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(currentDate, 11, "%Y-%m-%d", tm_info);
}
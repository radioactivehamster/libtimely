#include <stdio.h>
#include <string.h>
#include <time.h>

// #include "../include/timely.h"
#include "timely.h"

#include "int_num_digitsl.h"
#include "int_num_recurse_digitsl.h"
#include "time_h_tm_dump.h"

void time_h_scratch(void)
{
    time_t now = time(NULL);
    printf("(ctime) %s\n", ctime(&now));

    printf("-----\n\n");

    struct tm *t = localtime(&now);
    time_h_tm_dump(t);

    char buffer[BUFSIZ] = {0};
    snprintf(buffer, BUFSIZ, "%ld", t->tm_gmtoff);

    printf("\n\"%s\" : %02zu : <log> %f\n", buffer, strlen(buffer), num_digitsl(t->tm_gmtoff));
    printf("<truc log> %f\n", trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int cast log> %d\n", (int) num_digitsl(t->tm_gmtoff));
    printf("<int cast truc log> %d\n", (int) trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int_num_recurse_digitsl> %d\n", int_num_recurse_digitsl(t->tm_gmtoff));
    printf("<int_num_digitsl> %d\n", int_num_digitsl(t->tm_gmtoff));
    printf("<int_num_iter_placesl> %d\n", int_num_iter_placesl(t->tm_gmtoff));

    printf("\n | [(epoc).num_days]: %ld | \n\n", (now / TIMELY_DAY_SECONDS_PER));

    printf("\n-----\n\n");

    t = gmtime(&now);
    time_h_tm_dump(t);

    memset(buffer, 0, BUFSIZ);
    snprintf(buffer, BUFSIZ, "%ld", t->tm_gmtoff);

    printf("\n\"%s\" : %02zu : <log> %f\n", buffer, strlen(buffer), num_digitsl(t->tm_gmtoff));
    printf("<truc log> %f\n", trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int cast log> %d\n", (int) num_digitsl(t->tm_gmtoff));
    printf("<int cast truc log> %d\n", (int) trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int_num_recurse_digitsl> %d\n", int_num_recurse_digitsl(t->tm_gmtoff));
    printf("<int_num_digitsl> %d\n", int_num_digitsl(t->tm_gmtoff));
    printf("<int_num_iter_placesl> %d\n", int_num_iter_placesl(t->tm_gmtoff));

    printf("\n | [(epoc).num_days]: %ld | \n\n", (now / TIMELY_DAY_SECONDS_PER));

    printf("\n");

    // struct timely_epoc timely_epoc_ctor(time_t timer);
    printf("\n | [(ctor).num_days]: %ld | \n\n", (timely_epoc_ctor(now)).num_days);
}

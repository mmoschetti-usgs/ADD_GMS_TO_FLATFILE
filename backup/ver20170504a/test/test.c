#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>



/*--------------------------------------------------------------------------*/
int main (void)
/*--------------------------------------------------------------------------*/
{
  int doy;
  double diffSec;
  struct tm timeCat; 
  struct tm timeCat2;

// time struct and epoch time
  timeCat.tm_year=2001-1900;
  timeCat.tm_mon=1-1;
  timeCat.tm_mday=1;
  timeCat.tm_hour=0;
  timeCat.tm_min=0;
  timeCat.tm_sec=0;
  timeCat.tm_isdst=0;
// time struct and epoch time
  timeCat2.tm_year=2001-1900;
  timeCat2.tm_mon=1-1;
  timeCat2.tm_mday=1;
  timeCat2.tm_hour=1;
  timeCat2.tm_min=0;
  timeCat2.tm_sec=1;
  timeCat2.tm_isdst=0;
/*
  timeCat2.tm_year=2001-1900;
  timeCat2.tm_mon=1-1;
  timeCat2.tm_mday=1;
  timeCat2.tm_hour=0;
  timeCat2.tm_min=0;
  timeCat2.tm_sec=0;
*/

  fprintf(stderr,"Time1 %d %d %d %d %d %d\n", timeCat.tm_year, timeCat.tm_mon, timeCat.tm_mday, timeCat.tm_hour, timeCat.tm_min, timeCat.tm_sec);
  fprintf(stderr,"Time2 %d %d %d %d %d %d\n", timeCat2.tm_year, timeCat2.tm_mon, timeCat2.tm_mday, timeCat2.tm_hour, timeCat2.tm_min, timeCat2.tm_sec);
  fprintf(stderr,"%f seconds \n", (float)mktime(&timeCat));
  fprintf(stderr,"%f seconds \n", (float)mktime(&timeCat2));
  diffSec= difftime(mktime(&timeCat2), mktime(&timeCat));

  fprintf(stderr,"%.f seconds difference\n", diffSec);
 
  exit(1);

// example 2 
  time_t now;
    time(&now);
 
    struct tm beg;
    beg = *localtime(&now);
 
    // set beg to the beginning of the month
    beg.tm_hour = 0;
    beg.tm_min = 0;
    beg.tm_sec = 0;
    beg.tm_mday = 1;
 
    double seconds = difftime(now, mktime(&beg));
 
    printf("%d %d %d %d %d %d\n", beg.tm_year+1900, beg.tm_mon+1, beg.tm_mday, beg.tm_hour, beg.tm_min, beg.tm_sec);
    printf("%.f seconds have passed since the beginning of the month.\n", seconds);

  return 0;
}



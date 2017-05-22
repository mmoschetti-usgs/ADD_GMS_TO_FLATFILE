#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>



/*--------------------------------------------------------------------------*/
int main (int argc, char *argv[])
/*--------------------------------------------------------------------------*/
{
  int doy;
  int yearIn, monthIn, dayIn, hourIn, minIn, secIn;
  double diffSec;
  struct tm timeCat; 
  struct tm timeCatRef;

if ( argc != 7 ) {
    fprintf(stderr,"USAGE: %s [year] [month] [day] [hour] [min] [sec]\n", argv[0]);
    exit(1);
  }
  sscanf(argv[1],"%d", &yearIn);
  sscanf(argv[2],"%d", &monthIn);
  sscanf(argv[3],"%d", &dayIn);
  sscanf(argv[4],"%d", &hourIn);
  sscanf(argv[5],"%d", &minIn);
  sscanf(argv[6],"%d", &secIn);


// time struct and epoch time
  timeCat.tm_year=yearIn-1900;
  timeCat.tm_mon=monthIn-1;
  timeCat.tm_mday=dayIn;
  timeCat.tm_hour=hourIn;
  timeCat.tm_min=minIn;
  timeCat.tm_sec=secIn;
  timeCat.tm_isdst=0;

// time struct and epoch time
  timeCatRef.tm_year=1970-1900;
  timeCatRef.tm_mon=1-1;
  timeCatRef.tm_mday=1;
  timeCatRef.tm_hour=0;
  timeCatRef.tm_min=0;
  timeCatRef.tm_sec=0;
  timeCatRef.tm_isdst=0;
/*
  timeCat2.tm_year=2001-1900;
  timeCat2.tm_mon=1-1;
  timeCat2.tm_mday=1;
  timeCat2.tm_hour=0;
  timeCat2.tm_min=0;
  timeCat2.tm_sec=0;
*/

  fprintf(stderr,"Time1 %d %d %d %d %d %d\n", timeCat.tm_year, timeCat.tm_mon, timeCat.tm_mday, timeCat.tm_hour, timeCat.tm_min, timeCat.tm_sec);
  fprintf(stderr,"TimeRef %d %d %d %d %d %d\n", timeCatRef.tm_year, timeCatRef.tm_mon, timeCatRef.tm_mday, timeCatRef.tm_hour, timeCatRef.tm_min, timeCatRef.tm_sec);
  fprintf(stderr,"%f seconds \n", (float)mktime(&timeCat));
  fprintf(stderr,"%f seconds \n", (float)mktime(&timeCatRef));
  diffSec= difftime(mktime(&timeCat), mktime(&timeCatRef));

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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "params.h"

/*--------------------------------------------------------------------------*/
int main (int argc, char *argv[])
/*--------------------------------------------------------------------------*/
{
  FILE *fptest;
  int cnt1, hlines, cols_found;
  char buff[BUFFLEN];
  char flatFile[200];
  char **columns;
  char delim[] = ",";

/* CHECK INPUT ARGUMENTS */
  if ( argc != 2 ) {
    fprintf(stderr,"USAGE: %s [flatfile]\n", argv[0]);
    exit(1);
  }
  sscanf(argv[1],"%s", flatFile);

// Open flatfile
  if ((fptest = fopen(flatFile, "r")) == NULL) {
    fprintf(stderr,"Could not open flatfile, %s\n", flatFile);
    exit(0);
  }
  fprintf(stderr,"Opened flatfile, %s\n", flatFile);

//
// READ/APPEND FLATFILE
// header lines
  hlines=2;
  for (cnt1=0; cnt1<hlines; cnt1++) {
    fgets(buff,BUFFLEN,fptest);
  }
  cnt1=0;
// loop over data values
  while( fgets(buff,BUFFLEN,fptest) ) {
    columns = NULL;
    cols_found = getcols(buff, delim, &columns);
    fprintf(stderr,"Read columns: %d %d %s %s\n", cols_found, atoi(columns[0]), columns[1], columns[2]);
    free(columns);
  }


//
  fclose(fptest);
  fprintf(stderr,"Completed read of flatfile, %s\n", flatFile);

  return 0;
}

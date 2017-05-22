#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 6371
#define BUFFLEN 6000


/* Calculate distance and azimuth/back-azimuth between two (lon,lat) coordinates 
 * using delaz.f subroutine
 */

void delaz_(float *lat1, float *lon1, float *lat2, float *lon2, float *dist, float *az, float *baz);


/*--------------------------------------------------------------------------*/
int main (int argc, char *argv[])
/*--------------------------------------------------------------------------*/
{
  FILE *fpCat, *fpFlatFileMod, *fpFlatFile;
  int cnt1, cnt2, nf=0, neqs=0, hlines;
  int eqv, eqy, eqmo, eqd, eqh, eqm; 
  float mag, eqlon, eqlat, eqs, eq_radius; 
  float lon1, lat1, dist, az, baz, mindist;
  float lonf[100], latf[100];
  char catalogFile[200], flatFile[200], flatFileMod[200];
  char catf[200], faultsf[200];
  char eqnote[10], buff[BUFFLEN];

/* CHECK INPUT ARGUMENTS */
  if ( argc != 4 ) {
    fprintf(stderr,"USAGE: %s [relocated EQ catalog] [flatfile] [output flatfile]\n", argv[0]);
    fprintf(stderr,"Relocated catalog file, e.g., emm_c2_OK_KS_201702_add_all2.csv\n");
    exit(1);
  }
  sscanf(argv[1],"%s", catalogFile);
  sscanf(argv[2],"%s", flatFile);
  sscanf(argv[3],"%s", flatFileMod);

// open EQ catalog, faults file, and output files
  if ((fpCat = fopen(catalogFile, "r")) == NULL) {
    fprintf(stderr,"Could not open EQ catalog, %s\n", catalogFile);
    exit(0);
  }
  if ((fpFlatFile = fopen(flatFile, "r")) == NULL) {
    fprintf(stderr,"Could not open flatfile, %s\n", flatFile);
    exit(0);
  }
  fpFlatFileMod = fopen(flatFileMod, "w");

// loop through all files in the complete catalog, calculating minimum distance to each
// write out catalog with minimum distance appended and the "local" catalog
// first, remove header lines from catalog
  hlines=1;
  for (cnt1=0; cnt1<hlines; cnt1++) {
    fgets(buff,BUFFLEN,fpCat);
  }
  while( fgets(buff,BUFFLEN,fpCat) ) {
    fprintf(stderr,"%s", buff);
exit(1);
    mindist=999;
    sscanf(buff,"%f %f %f %d %d %d %d %d %d %f %s", &mag, &eqlon, &eqlat, &eqv, &eqy, &eqmo, &eqd, &eqh, &eqm, &eqs, eqnote); 
//    fprintf(stdout,"%.2f %.3f %.3f %3d %4d %02d %02d %02d %02d %04.1f %s\n", mag, eqlon, eqlat, eqv, eqy, eqmo, eqd, eqh, eqm, eqs, eqnote);
    for(cnt1=0; cnt1<nf; cnt1++) {
      lat1=latf[cnt1];
      lon1=lonf[cnt1];
      delaz_(&eqlat,&eqlon,&lat1,&lon1,&dist,&az,&baz);
      if ( dist < mindist ) mindist=dist;
    }
// write to modified catalog and local catalog, if appropriated
//    fprintf(fpcatmod,"%.2f %.3f %.3f %3d %4d %02d %02d %02d %02d %04.1f %s %.3f\n", mag, eqlon, eqlat, eqv, eqy, eqmo, eqd, eqh, eqm, eqs, eqnote, mindist);
//    if ( mindist <= eq_radius ) fprintf(fploc,"%.2f %.3f %.3f %3d %4d %02d %02d %02d %02d %04.1f %s\n", mag, eqlon, eqlat, eqv, eqy, eqmo, eqd, eqh, eqm, eqs, eqnote);
  }

// close files
  fclose(fpCat);
  fclose(fpFlatFile);
  fclose(fpFlatFileMod);
//  fclose(fpcat);
//  fclose(fploc);
//  fclose(fpcatmod);

  return 0;
}

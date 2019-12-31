/* Usage:  ./02 [20077[ 12345]] */

#include <math.h>
#include <stdio.h>

int
main(int argc, char** argv) {
short a = 20077;
short b = 12345;
short lcg;
short bits[2048];
short iword;
int icount;

  if (1<argc) {
  int n;
  int itmp = -1;
    n = sscanf(argv[1], "%d", &itmp);
    if (n!=1 || itmp<0 || itmp > 32767) {
      fprintf(stderr, "Invalid value for a; a=%d; n=%d\n", a, n);
      return 1;
    } else {
      a = (short)itmp;
    }

    if (1<argc) {
      n = sscanf(argv[2], "%d", &itmp);
      if (n!=1 || itmp<0 || itmp > 32767) {
        fprintf(stderr, "Invalid value for b; a=%d; n=%d\n", b, n);
        return 2;
      } else {
        b = (short)itmp;
      }
    }
  }
  printf("(%d,%d)=(a,b)\n",(int)a,(int)b);

  for (iword=0; iword<2048; ++iword) bits[iword] = 0;

  icount = 0;
  lcg = 0;

  while (1) {
  short ibit;
    iword = lcg >> ((short)4);
    ibit = 1 << (lcg & ((short)0x0f));
    if ((bits[iword] & ibit)) break;

    bits[iword] |= ibit;
    ++icount;

    lcg = ((lcg * a) + b) & 0x07fff;
  }

  printf("Found duplicate LCG value = %d after %d steps\n", (int)lcg, icount);

  return 0;
}

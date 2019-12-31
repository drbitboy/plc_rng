/***********************************************************************

Purpose:

  Verify that 16-bit LCG (a,b) pair does
  not repeat in less than 32,768 steps


Usage:

  ./02 [20077[ 12345]]

***********************************************************************/

#include <math.h>
#include <stdio.h>

int
main(int argc, char** argv) {
short a = 20077;          /* Default a of LCG */
short b = 12345;          /* Default b of LCG */
short seed;               /* Linear Congruential Generator seed */
short bits[2048];         /* Store 32,768 bits to look for duplicates */
short iword;              /* Index into bits array */
int isteps;               /* Step counter */

  /* Parse command line */

  if (1<argc) {
  int n;
  int itmp = -1;

    /* - Value for a should be present */

    n = sscanf(argv[1], "%d", &itmp);
    if (n!=1 || itmp<0 || itmp > 32767) {
      fprintf(stderr, "Invalid value for a; a=%d; n=%d\n", a, n);
      return 1;
    } else {
      a = (short)itmp;
    }

    if (2<argc) {

      /* - Value for b should be present */

      itmp = -1;
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

  /* Clear all bits, initialize counter and seed */

  for (iword=0; iword<2048; ++iword) bits[iword] = 0;
  isteps = 0;
  seed = 0;

  /* Loop until duplicate LCG seed is found */

  while (1) {
  short ibit;

    /* seed => index into bits[] array and bit in bits[iword] */

    iword = seed >> ((short)4);
    ibit = 1 << (seed & ((short)0x0f));

    /* Check if bit for seed has been set, indicating that this seed
       is the first duplicate:  if it is, exit the loop
     */

    if ((bits[iword] & ibit)) break;

    /* If it is not a duplicate, set that bit for future checks and
       increment isteps
     */
    bits[iword] |= ibit;
    ++isteps;

    /* Calculate next seed using LCG algorithm */

    seed = ((seed * a) + b) & 0x07fff;

  } /* End of [while (1)] loop */

  /* Output result */

  printf("Found duplicate LCG seed [%d] after %d steps; %s\n"
        ,(int)seed, isteps
        ,32768==isteps ? "success" : "failure"
        );

  return 32768==isteps ? 0 : -1;
}

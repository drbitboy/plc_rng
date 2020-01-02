/***********************************************************************

Purpose:

  Verify that 15-bit or 31-bit LCG (a,b) pair does not
  repeat in less than 1<<15 or 1<<31 steps, respectively


Usage:

  ./02 [1103515245[ 12345]]

***********************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef BIT31
typedef int32_t lcg_t;
#define DEFAULT_a 1103515245
#define DEFAULT_b 12345
#define NBITS 31
#else
typedef int16_t lcg_t;
#define DEFAULT_a 20077
#define DEFAULT_b 12345
#define NBITS 15
#endif

int
main(int argc, char** argv) {
lcg_t a = DEFAULT_a;           /* Default a of LCG */
lcg_t b = DEFAULT_b;           /* Default b of LCG */
lcg_t m = ((lcg_t)-1)<<NBITS;  /* Default m of LCG */
lcg_t minv = ~m;               /* Default m of LCG */
lcg_t seed;                    /* Linear Congruential Generator seed */
lcg_t iword;                   /* Index into pbits array */
uint32_t isteps;               /* Step counter */
size_t nwords = 1<<(NBITS-4);  /* Count of 16-bit ints storing seeds */
int16_t* pbits;                /* Store bits to look for duplicates */

  pbits = (int16_t*) malloc(nwords * sizeof(int16_t));
  /* Parse command line */

  if (1<argc) {
  int32_t n;
  uint32_t itmp = -1;

    /* - Value for a should be present */

    n = sscanf(argv[1], "%d", &itmp);
    if (n!=1 || itmp > minv) {
      fprintf(stderr, "Invalid value for a; a=%d; n=%d\n", a, n);
      return 1;
    } else {
      a = (lcg_t)itmp;
    }

    if (2<argc) {

      /* - Value for b should be present */

      itmp = -1;
      n = sscanf(argv[2], "%d", &itmp);
      if (n!=1 || itmp > minv) {
        fprintf(stderr, "Invalid value for b; a=%d; n=%d\n", b, n);
        return 2;
      } else {
        b = (lcg_t)itmp;
      }
    }
  }
  printf("(%d,%d,%d,%d)=(a,b,m,~m)\n",(int)a,(int)b,(int)m,(int)minv);

  /* Clear all bits, initialize counter and seed */

  for (iword=0; iword<nwords; ++iword) pbits[iword] = 0;
  isteps = 0;
  seed = 0;

  /* Loop until duplicate LCG seed is found */

  while (1) {
  int16_t ibit;

    /* seed => index into pbits[] array and bit in bits[iword] */

    iword = seed >> ((int16_t)4);
    ibit = 1 << (seed & ((int16_t)0x0f));

    /* Check if bit for seed has been set, indicating that this seed
       is the first duplicate:  if it is, exit the loop
     */

    if ((pbits[iword] & ibit)) break;

    /* If it is not a duplicate, set that bit for future checks and
       increment isteps
     */
    pbits[iword] |= ibit;
    ++isteps;

    /* Calculate next seed using LCG algorithm */

#   ifdef DEBUG
    fprintf(stdout,"%d.",(int)seed);fflush(stdout);
#   endif
    seed = ((seed * a) + b) & minv;

  } /* End of [while (1)] loop */

  /* Output result */

  printf("Found duplicate LCG seed [%d] after %u steps; %s\n"
        ,(int)seed, isteps
        ,((uint32_t)(-(int32_t)m))==isteps ? "success" : "failure"
        );

  return (((uint32_t)1)<<NBITS)==isteps ? 0 : -1;
}

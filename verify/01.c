/***********************************************************************

01.c

Verify that negative 32-bit seeds produce functionally identical results
to positive seeds in the random_r TYPE_0 Linear Congruential Generator
(LCG) of STDLIB's random_r as a Random Number Generator (RNG)

========================================================================
=== N.B. this code assumes the [int] (or [int32_t]) type defines a   ===
===      32-bit, signed, twos-complement integer                     ===
========================================================================

Build:  gcc [-D__HELPER_01__] 01.c -o 01

Run (e.g. BASH syntax):  ./01

***********************************************************************/

#ifndef __HELPER_01__

   /* Normal compilation
      - Pick up random_r as a weak_alias of __random_r
      - TYPE_0 is #define'd as naught in random_r.c
    */
#  include <errno.h>
#  include <stdlib.h>
#  define TYPE_0 0

#else

   /********************************************************************
      Cygwin has neither random_r nor __random_r; try helping the
      compiler along by defining macro __HELPER_01__ a la
      [gcc -D__HELPER_01__ ...] to use the contents of 01.h and the
      provided stdlib_random_r.c
    ********************************************************************/

#  include "01.h"

#endif

#include <stdio.h>

/* Macro of mask that has only its 32-bit integer sign bit set */

#define MASKSIGN ((int32_t)0x80000000)

/* Macros for LCG parameters [a] and [b] */
#define a pbuf_neg->rand_deg
#define b pbuf_neg->rand_sep

/***********************************************************************
LCG-like RNG that generates negative seeds

- Background:  a typical LCG generates non-negative seeds e.g.

    next_seed = ((current_seed * a ) + b) % M

  So even if ((current_seed * a) +b) yields a negative result due to
  32-bit signed integer overflow, the [% M] operation will "move" the
  result into the non-negative range [0:M).

- N.B. if M = 0x80000000 = 2**31 = 1<<31, which is typical for TYPE_0
       random_r in STDLIB for 32-bit signed integers, then that LCG
       is equivalent to

         next_seed = ((current_seed * a ) + b) & 0x7fffffff

       where 0x7fffffff = ((2**31)-1) = ((1<<31)-1), and the bit-wise
       AND operation with 0x7fffffff clears the sign bit of the
       32-bit signed integer result.  And in fact, this is exactly
       how the TYPE_0 LCG is coded in random_r cf. stdlib_random_r.c

- With that background as context, **setting** the sign bit of the
  next seed, rather than clearing it via modulo or bit-wise AND
  operators, should yield the same lower 31-bits in all seed
  sequences that start with the same lower 31-bits in the first seed

- And that is exactly what this routine does:  ensures the sign bit
  of the next seed is set
***********************************************************************/

int random_n(struct random_data* pbuf_neg, int32_t* presult) {

  *presult = *(pbuf_neg->state) = ((*(pbuf_neg->state) * a) + b) | MASKSIGN;

  return 0;
}

/***********************************************************************
 Check that int32_t type has expected properties
 **********************************************************************/
void check_int32_t() {
int32_t itmp;

  itmp = sizeof(int32_t);
  if (4!=itmp) {
    ++errno;
    fprintf(stderr,"sizeof(int32_t) is %d; it should be 4\n", itmp);
  }

  itmp = MASKSIGN;
  if (MASKSIGN >= --itmp) {
    ++errno;
    fprintf(stderr,"[%d>=%d] is true; it should be false\n", MASKSIGN, itmp);
  }

  if ((MASKSIGN^itmp)!=((int32_t)-1)) {
    ++errno;
    fprintf(stderr,"[((%d^%d)!=-1] is true; it should be false\n", MASKSIGN, itmp);
  }
}

int main() {
struct random_data buf;
struct random_data* pbuf = &buf;
struct random_data buf_neg;
struct random_data* pbuf_neg = &buf_neg;
int32_t result;
int32_t* presult = &result;
int32_t seed;
int32_t seed_neg;
int32_t i;
int rtn;

  /* Check int32_t properties; exit if results are not as expected */
  check_int32_t();
  if (errno) {
    errno = EINVAL;
    printf("Type int32_t is not 32-bit signed two-complement integer; exiting\n");
    exit(1);
  }

  /* Set up a buffer for random_r to execute a typical, single-stage LCG
     RNG with non-negative seeds
   */

  buf.state = &seed;
  buf.rand_type = TYPE_0;
  
  /* Use seed values of 0 and 1 to extract a and b from random_r */
  seed = 0;
  random_r(pbuf, &b);
  seed = 1;
  random_r(pbuf, &a);
  a -= b;
  printf("%d,%d=a,b\n", a, b);

  /* Set up a buffer for random_n to execute a typical, single-stage LCG
     RNG with negative seeds
   */

  buf_neg.state = &seed_neg;

  /* N.B. Loop control logic assumes 32-bit signed two's complement
     integers, as confirmed by call to check_int32_t above
   */
  for (i=0; i!=MASKSIGN; ++i) {
  int32_t pre_seed_neg;

    /* Set seed to loop counter; seed will be non-negative; seed_neg
       will be negative
     */
    seed = i;
    pre_seed_neg = seed_neg = seed ^ MASKSIGN;

    if (seed < 0 || seed_neg > -1) {
      fprintf(stderr,"Error:  %d is negative or %d is non-negtive; exiting\n", seed, seed_neg);
      return(2);
    }

    /* Run RNGs; ignore presult as it will be identical to next seed */
    random_r(pbuf,presult);
    random_n(pbuf_neg,presult);

    /* Compare updated seeds; they should have opposite sign bits and
       identical non-sign bits
     */
    if (((seed^seed_neg) != MASKSIGN)
      ||(MASKSIGN&seed)
      ||((MASKSIGN^seed_neg)&MASKSIGN)
       ) {
      printf("\n\n%d/%x,%d/%x,%d/%x,%d/%x,%d/%x=MASKSIGN,seed,seed_neg,MASKSIGN&seed,(MASKSIGN^seed_neg)&MASKSIGN\n\n"
            ,MASKSIGN,MASKSIGN
            ,seed,seed
            ,seed_neg,seed_neg
            ,MASKSIGN&seed,MASKSIGN&seed
            ,(MASKSIGN^seed_neg)&MASKSIGN,(MASKSIGN^seed_neg)&MASKSIGN
            );
      printf("\n\nERROR:  %d/%x,%d/%x,%d/%x,%d/%x=pre_seed,pre_seed_neg,post_seed,post_seed_neg\n\n"
            ,i,i,pre_seed_neg,pre_seed_neg
            ,seed,seed,seed_neg,seed_neg
            );
      return -1;
    }

    if (i&0x03ffffff) continue;

    /* Log progress as single [.] when i is a multiple of ~ 64M */

    printf(".");
    fflush(stdout);
  }

  /* Log success */

  printf("-(%d) successful checks\n",i);

  return 0;
}

#ifdef __HELPER_01__
#include "01.h"
#else
#include <stdlib.h>
#define TYPE_0 0
#endif
#include <stdio.h>

#define MASK01 0x80000000
#define a pbuf_neg->rand_deg
#define b pbuf_neg->rand_sep

int random_n(struct random_data* pbuf_neg, int32_t* presult) {
  *presult = *(pbuf_neg->state) = ((*(pbuf_neg->state) * a) + b) | MASK01;
  return 0;
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

  buf.state = &seed;
  buf.rand_type = TYPE_0;
  
  seed = 0;
  random_r(pbuf, &b);
  seed = 1;
  random_r(pbuf, &a);
  a -= b;

  printf("%d,%d=a,b\n", a, b);

  buf_neg.state = &seed_neg;

  seed = seed_neg = 0;

  for (i=0; i!=MASK01; ++i) {
  int32_t pre_seed_neg;

    seed = i;
    pre_seed_neg, seed_neg = seed ^ MASK01;

    random_r(pbuf,presult);
    random_n(pbuf_neg,presult);

    if ((seed^seed_neg) != MASK01) {
      printf("\n\n%d/%x,%d/%x,%d/%x,%d/%x=pre_seed,pre_seed_neg,post_seed,post_seed_neg\n\n"
            ,i,i,pre_seed_neg,pre_seed_neg
            ,seed,seed,seed_neg,seed_neg
            );
      return 1;
    }
    if (i&0x03ffffff) continue;
    printf(".");
    fflush(stdout);
  }

  printf("-(%d) successful checks\n",i);

  return 0;
}

#ifndef __01_H__
#define __01_H__


/* 01.h - optional include file for 01.c

   In Cygwin, [struct random_data], random_r(...) etc. are not
   available in stdlib.h; compensate for those issues so 01.c will
   compile and run

 */

/* Provide int32_t and pointer to same */
typedef int int32_t, *pint32_t;

/* struct random_data */

struct random_data
  {
    int32_t *fptr;              /* Front pointer.  */
    int32_t *rptr;              /* Rear pointer.  */
    int32_t *state;             /* Array of state values.  */
    int rand_type;              /* Type of random number generator.  */
    int rand_deg;               /* Degree of random number generator.  */
    int rand_sep;               /* Distance between front and rear.  */
    int32_t *end_ptr;           /* Pointer behind state table.  */
  };

/* Declare some items so stdlib_random_r.c will compile w/o warnings */

int __random_r(struct random_data* buf, pint32_t presult);
#define __set_errno(E) errno = E

/* Include a copy of stdlib_random_r.c as it's contents are not
   available via STDLIB
 */
#include "stdlib_random_r.c"

/* Re-direct any calls for random_r to __random_r in any code that
   follows
 */
#define random_r __random_r


#endif /* End of __01_H__ */

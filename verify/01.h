typedef int int32_t, *pint32_t;
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

int __random_r(struct random_data* buf, pint32_t presult);
#define __set_errno(E) errno = E
#include "stdlib_random_r.c"
#define random_r __random_r

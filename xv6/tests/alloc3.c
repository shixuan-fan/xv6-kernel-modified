/* many odd sized allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   int i, j;
   void *ptrs[9];
   int sizes[] = {1, 5, 14, 8, 1, 4, 9, 33, 55};

   // All allocations should be successful
   assert(InitWrapper(4096) != NULL);
   for (i = 0; i < 9; i++)
      assert((ptrs[i] = AllocWrapper(sizes[i])) != NULL);

   // Make sure each pointer got a unique value (no double allocations)
   for (j = 1; j < 9; j++)
      for (i = 0; i < j; i++)
         assert(ptrs[i] != ptrs[j]);

   exit(0);
}

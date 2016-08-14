/* a few aligned allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   int i, j;
   void* ptrs[4];
   int sizes[] = {8, 16, 32, 8};

   // All allocations should be successful
   assert(InitWrapper(4096) != NULL);
   for (i = 0; i < 4; i++)
      assert((ptrs[i] = AllocWrapper(sizes[i])) != NULL);
   
   // Make sure each pointer got a unique value (no double allocations)
   for (j = 1; j < 4; j++)
      for (i = 0; i < j; i++)
         assert(ptrs[i] != ptrs[j]);
   
   exit(0);
}

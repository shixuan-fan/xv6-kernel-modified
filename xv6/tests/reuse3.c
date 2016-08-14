/* make sure we can keep reusing space for smaller allocations */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   int i;
   assert(InitWrapper(40960) != NULL);
   void *ptr = AllocWrapper(1024);
   assert(ptr != NULL);
   void *tmp;
   while ((tmp = AllocWrapper(1)) != NULL)
     ;
   for (i=0; i<1000; i++) {
     Mem_Free(ptr);     
     ptr = AllocWrapper(1024-i);
     assert(ptr != NULL);
  }

   exit(0);
}

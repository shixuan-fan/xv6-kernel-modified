/* many odd sized allocations and interspersed frees */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   void * ptr[9];
   ptr[0] = AllocWrapper(1);
   ptr[1] = (AllocWrapper(5));
   ptr[2] = (AllocWrapper(14));
   ptr[3] = (AllocWrapper(8));

   assert(Mem_Free(ptr[1]) == 0);
   assert(Mem_Free(ptr[0]) == 0);
   assert(Mem_Free(ptr[3]) == 0);

   ptr[4] = (AllocWrapper(1));
   ptr[5] = (AllocWrapper(4));
   assert(ptr[4] != NULL);
   assert(ptr[5] != NULL);

   assert(Mem_Free(ptr[5]) == 0);

   ptr[6] = (AllocWrapper(9));
   ptr[7] = (AllocWrapper(33));
   assert(ptr[6] != NULL);
   assert(ptr[7] != NULL);

   assert(Mem_Free(ptr[4]) == 0);

   ptr[8] = (AllocWrapper(55));
   assert(ptr[8] != NULL);

   assert(Mem_Free(ptr[2]) == 0);
   assert(Mem_Free(ptr[7]) == 0);
   assert(Mem_Free(ptr[8]) == 0);
   assert(Mem_Free(ptr[6]) == 0);

   exit(0);
}

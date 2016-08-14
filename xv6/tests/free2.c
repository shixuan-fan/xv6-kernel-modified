/* a few aligned allocations and frees */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   void* ptr[4];

   ptr[0] = AllocWrapper(8);
   ptr[1] = AllocWrapper(16);
   assert(Mem_Free(ptr[0]) == 0);
   assert(Mem_Free(ptr[1]) == 0);

   ptr[2] = AllocWrapper(32);
   ptr[3] = AllocWrapper(8);
   assert(Mem_Free(ptr[2]) == 0);
   assert(Mem_Free(ptr[3]) == 0);

   exit(0);
}

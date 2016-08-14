/* a simple allocation followed by a free */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   void* ptr = AllocWrapper(8);
   assert(ptr != NULL);
   assert(Mem_Free(ptr) == 0);
   exit(0);
}

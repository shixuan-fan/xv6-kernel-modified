/* write to a chunk from Mem_Alloc */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   void* ptr = AllocWrapper(8);
   assert(ptr != NULL);
   *((int*)ptr) = 42;   // check pointer is in a writeable page
   exit(0);
}

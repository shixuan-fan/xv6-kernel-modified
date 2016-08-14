/* a simple 8 byte allocation */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   void* ptr = AllocWrapper(8);
   assert(ptr != NULL);
   exit(0);
}

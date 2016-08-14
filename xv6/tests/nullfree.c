/* free a NULL */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) == 0);
   assert(Mem_Free(NULL) == 0);
   exit(0);
}

/* call Mem_Init with size = 1 page */
#include "mem.h"
#include <assert.h>
#include <stdlib.h>
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   exit(0);
}

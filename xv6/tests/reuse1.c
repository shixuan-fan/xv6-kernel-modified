/* make sure we can keep reusing space */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
  assert(InitWrapper(4096) != NULL);
  int i;
  for (i=0; i<1000; i++) {
    void *ptr = AllocWrapper(1024);
    assert(ptr != NULL);
    Mem_Free(ptr);
  }

   exit(0);
}

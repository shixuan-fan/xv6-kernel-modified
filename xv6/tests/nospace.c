/* second allocation is too big to fit */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(4096) != NULL);
   assert(AllocWrapper(2048) != NULL);

   assert(AllocWrapper(2049) == NULL);

   exit(0);
}

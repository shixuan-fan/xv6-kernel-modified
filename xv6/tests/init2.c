/* init that should be rounded up to 1 page */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(1) != NULL);
   assert(AllocWrapper(4048) != NULL);
   exit(0);
}

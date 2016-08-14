/* Makes sure all space can be used, allocations shouldn't quit early */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(40960) != NULL);
   void *ptr = AllocWrapper(1024);
   void *tmp;
   int i = 0;
   while ((tmp = AllocWrapper(8)) != NULL)
     i++;
   assert(i > 990); // Ideally 997 for overhead, but we'll be generous!
   assert(Mem_Free(ptr) == 0);
   assert(AllocWrapper(10) != NULL);
   assert(AllocWrapper(10) != NULL);

   exit(0);
}

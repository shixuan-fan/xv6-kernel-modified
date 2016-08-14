/* Makes sure all space can be used */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(40960) != NULL);
   void *ptr = AllocWrapper(1024);
   void *tmp;
   while ((tmp = AllocWrapper(1)) != NULL)
     ;
   assert(Mem_Free(ptr) == 0);
   assert(AllocWrapper(10) != NULL);
   assert(AllocWrapper(10) != NULL);

   exit(0);
}

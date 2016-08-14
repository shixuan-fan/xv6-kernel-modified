/* Makes sure all space can be reused, allocations shouldn't quit early */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"
#include "wrapper.h"

int main() {
   assert(InitWrapper(40960) != NULL);
   void *ptr[1000];
   int i = 0;

   // Make 1000 allocations of 8 bytes
   while (i < 1000 && (ptr[i] = AllocWrapper(8)) != NULL)
     i++;
   assert(i == 1000); // should be able to do 1023, but we're generous!

   // Free everything!
   for (i = 0; i < 1000; i++)
       assert(Mem_Free(ptr[i]) == 0);

   // Make 1000 allocations of 8 bytes again
   while (i < 1000 && (ptr[i] = AllocWrapper(8)) != NULL)
     i++;
   assert(i == 1000); 

   exit(0);
}

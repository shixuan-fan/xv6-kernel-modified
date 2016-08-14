#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

#define PGSIZE (4096)

int 
thread_create(void (*start_routine)(void*), void *arg) 
{
  void *stack = malloc(PGSIZE*2);
  if (!stack) {
    printf(1, "Error: malloc failed\n");
    exit();
  }
    
  if((uint)stack % PGSIZE) {
   stack = stack + (4096 - (uint)stack % PGSIZE);
  }

  return clone(start_routine, arg, stack);
}

int
thread_join()
{
  void* ustack;
  int thread_id = join(&ustack);
  if (thread_id != -1) {
    free(ustack);
  }
  
  return thread_id;
}

void lock_init(volatile lock_t *lock) {
  *lock = 0;
}

void lock_acquire(volatile lock_t *lock) {
  while (xchg(lock, 1) == 1)
    ; // spin
}

void lock_release(volatile lock_t *lock) {
  *lock = 0;
}

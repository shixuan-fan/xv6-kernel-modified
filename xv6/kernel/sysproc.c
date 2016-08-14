#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = *(proc->sz);
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the number of existing processes
int
sys_getprocs(void)
{
  return getprocs();
}

// set the priority of the process
int
sys_setpri(void)
{
  int num = 0;
  argint(0, &num);
  // Illegal parameter
  if (num != 1 && num != 2)
    return -1;
  proc->priority = num;
  return 0;
}

// Get the pstat information
int
sys_getpinfo(void) 
{
  struct pstat* pstatTable = NULL;
  argptr(0, (void*)&pstatTable, sizeof(struct pstat*));
  if (pstatTable == NULL) 
    return -1;
  getpinfo(pstatTable);
  return 0;
}

// Share memory access
int
sys_shmem_access(void)
{
  int page_number;
  argint(0, &page_number);
  return (int)shmem_access(page_number);
}

// Return the number of processes which have the access to the given shared memory
int
sys_shmem_count(void)
{
  int page_number = 0;
  argint(0, &page_number);
  if(page_number < 0 || page_number > 3)
    return -1;
  return shmem_count(page_number);
}

int
sys_clone(void)
{
  void (*fcn)(void*), *arg, *stack;
  
  argptr(0, (void*)&fcn, sizeof(void (*)(void*))); 
  argptr(1, (void*)&arg, sizeof(void*));
  argptr(2, (void*)&stack, sizeof(void*));
  
  return clone(fcn, arg, stack);
}

int
sys_join(void) 
{
  void **stack;
  argptr(0, (void*)&stack, sizeof(void**));
  return join(stack);
}

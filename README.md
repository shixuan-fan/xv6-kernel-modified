#xv6-kernel-modified
A new xv6 with modified kernel to support more features.

##Multithreading
The modified kernel could support multithreading within one process.
1. Created clone() function, where we could create a new thread which shares the same address space with its parent (the address space size will also be shared). Also, we created join() function to make the parent thread wait for the child thread. 
2. Made some adjustments to the wait() function. The wait() function will check the address space and only wait for the child process which has different pgdir, while join() function will wait for child thread that has the same address space.
3. Added the reference check to the process, so that wait() could only free the address space only when it is the last reference to it. 
4. Created a thread library that supports thread_create(), thread_join() and spin lock. The thread_create() method will create a page-aligned stack and use clone() to create the thread. The thread_join() will use join() to join with the child thread, and free the user stack correspondingly. 
5. The spin lock has three methods: lock_init(), lock_acquire() and lock_release(). The lock_acquire() will use xchg() in order to do the lock status checking and lock acquiring in the same time. 

##Shared Pages
1. While booting, run shmem_init() to initialize shared memory. Here, we use two arrays, where one is to store the physical address for each page, the other is to store how many processes currently have access to the given shared page.
2. In the process, we add two more fields: an array to store which shared page refers to which virtual address, an integer to store how many shared pages this process has access to. When fork happens, the child process would also inherit the shared memory from its parent, and also increase the shmem counter. When a process exits, its parent will find the zombie process, and reinitialize the two fields of the process, and decrease the shmem counter. Note here the deallocuvm() will stop before the shared memory to make sure the shared memory is not freed.

##Small File Optimization
1. Added small file type for inode and a flag for open instruction of small file.
2. Modified readi() and writei() to add a new support for small file, which means read and write data to the addrs[]. Make sure to always track the size of the file to guarantee it does not grow out of bound. In the writei(), we added a predicate to make sure that if a small file is written, update its inode any way since the data is stored in the inode.
3. in iput(), we added a new predicate in order to avoid freeing blocks for small files.

##Priority-based Scheduler
1. Two new system calls are added: sys_setpri and sys_getpinfo. To support these two new features, we also added three new fields in the proc struct to store the priority and the time running in high/low priority of the process. 
2. The scheduler will also run the process with high priority first if one exists. Only when the scheduler checks all the processes and cannot find any RUNNABLE processes will it run the low-priority processes. However, before running each low-priority process, the scheduler will check all the processes again to make sure there is no new high-processes becomes runnable.
3. The number of ticks each process has accumulated in both priority is calculated after each process finishes its turn, and all the ticks information will be cleared after the process becomes UNUSED.

##getpinfo()
A syscall to get the information of a process, which includes the process ID, the time it has run as a high priority process and the time as a low priority process.

##getProcs()
A syscall to count the number of existing function. 
Basically it will iterate through the process table, check if each process is UNUSED or not, and count those processes in the status which is not UNUSED.

##Null pointer exception
###Workflow:
1. Load all the program at address 0x1000, so that we could make the first page empty in order not to miss any data there (They will never be able to fetched!). 
2. Make new predicates in syscall so than whenever some programs ask for some address in the first page, just throws exception to make sure null pointer could not be dereferenced. Also, when we do the fork and copy the uvm, we should start copying from the second page.



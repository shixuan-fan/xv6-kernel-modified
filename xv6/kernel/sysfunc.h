#ifndef _SYSFUNC_H_
#define _SYSFUNC_H_

struct pstat;

// System call handlers
int sys_chdir(void);
int sys_clone(void);
int sys_close(void);
int sys_dup(void);
int sys_exec(void);
int sys_exit(void);
int sys_fork(void);
int sys_fstat(void);
int sys_getpid(void);
int sys_getpinfo(void);
int sys_getprocs(void);
int sys_join(void);
int sys_kill(void);
int sys_link(void);
int sys_mkdir(void);
int sys_mknod(void);
int sys_open(void);
int sys_pipe(void);
int sys_read(void);
int sys_sbrk(void);
int sys_setpri(void);
int sys_shmem_access(void);
int sys_shmem_count(void);
int sys_sleep(void);
int sys_unlink(void);
int sys_wait(void);
int sys_write(void);
int sys_uptime(void);

#endif // _SYSFUNC_H_

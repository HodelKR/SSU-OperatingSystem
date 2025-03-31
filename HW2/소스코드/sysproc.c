#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#define NLEVEL 4         // 큐 레벨 수
#define AGING_THRESHOLD 250  // 에이징 임계값
#define Q0_QUANTUM 10    // 레벨 0 타임 퀀텀
#define Q1_QUANTUM 20    // 레벨 1 타임 퀀텀
#define Q2_QUANTUM 40    // 레벨 2 타임 퀀텀
#define Q3_QUANTUM 80    // 레벨 3 타임 퀀텀
// 각 레벨별 타임 퀀텀 배열
static int time_quantum[NLEVEL] = {Q0_QUANTUM, Q1_QUANTUM, Q2_QUANTUM, Q3_QUANTUM};

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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_set_proc_info(void) {
  int q_level, cpu_burst, cpu_wait, io_wait_time, end_time;
  
  if(argint(0, &q_level) < 0 || argint(1, &cpu_burst) < 0 ||
     argint(2, &cpu_wait) < 0 || argint(3, &io_wait_time) < 0 ||
     argint(4, &end_time) < 0)
    return -1;
    
  struct proc *curproc = myproc();
  curproc->q_level = q_level;
  curproc->cpu_burst = cpu_burst;
  curproc->cpu_wait = cpu_wait;
  curproc->io_wait_time = io_wait_time;
  curproc->cpu_end = end_time;
  curproc->time_slice = time_quantum[curproc->q_level];
  cprintf("Set process %d's info complete\n", curproc->pid);
  return 0;
}

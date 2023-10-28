#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
sys_wolfie(void)
{
  void *buf;
  uint size;
  if (argptr(0, (void*)&buf, sizeof(buf)) < 0)
    return -1;
  if (argptr(1, (void*)&size, sizeof(size)) < 0)
    return -1;
  char image[] =
"   _    ____   ____ ___ ___   ____    _    _   _ _   _ _____ ____\n\
   / \\  / ___| / ___|_ _|_ _| | __ )  / \\  | \\ | | \\ | | ____|  _ \\\n\
  / _ \\ \\___ \\| |    | | | |  |  _ \\ / _ \\ |  \\| |  \\| |  _| | |_) |\n\
 / ___ \\ ___) | |___ | | | |  | |_) / ___ \\| |\\  | |\\  | |___|  _ < \n\
/_/   \\_\\____/ \\____|___|___| |____/_/   \\_\\_| \\_|_| \\_|_____|_| \\_\\\n";
  if (sizeof(image) > size) return -1;
  strncpy((char*)buf, image, sizeof(image));
  return sizeof(image);
}

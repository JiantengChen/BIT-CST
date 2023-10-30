#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void){
    char buf[500];
    printf(1, "system call wolfie, return: %d\n", wolfie((void*)buf, 500));
    printf(1, "%s", buf);
    exit();
}
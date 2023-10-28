#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    printf(0, "\nargument num : %d\n", argc - 1);
    int n = 100;
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            printf(0, "%s\n", argv[i]);
        }
        n = atoi(argv[1]);
        printf(0, "\ncreate %d int array\n", n);
    }
    else
    {
        printf(0, "\ncreate 100 int array\n");
    }

    int num[n];
    memset(num, 0, sizeof (num));
    printf(0,"the origination address of address num is: %x\n",num);

    int pid = fork();
    if (pid < 0)
    {
        printf(0, "fork error!\n");
    }
    else if (pid == 0)
    {
        printf(0, "\nchild %d fork\n", getpid());

        printf(0, "***child***\n");
    }
    else
    {
        wait();
        printf(0, "parent %d kill\n\n", getpid());
    }
    return 0;
}

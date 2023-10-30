#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define PRODUCER_NUM 2
#define CONSUMER_NUM 3
#define PRODUCER_REPEAT 6
#define CONSUMER_REPEAT 4
#define OK 1
#define ERROR -1
#define BUFFER_LENGTH 3
#define EMPTY 0
#define FULL 1
#define MUTEX 2

struct buffer
{
    int item[BUFFER_LENGTH];
    int head;
    int tail;
    int empty;
};

void print_Buffer(struct buffer *a)
{
    printf("Current Data:");
    for (int i = a->head;;)
    {
        printf("%d  ", a->item[i]);
        i++;
        i %= 3;
        if (i == a->tail)
        {
            printf("\n\n");
            return;
        }
    }
}

int P(int semid, int n)
{
    if (n < 0)
    {
        printf("index of array can not equals a minus value!\n");
        return ERROR;
    }
    sembuf temp;
    temp.sem_num = n;
    temp.sem_op = -1;
    temp.sem_flg = 0;
    semop(semid, &temp, 1);
    return OK;
}

int V(int semid, int n)
{
    if (n < 0)
    {
        printf("index of array can not equals a minus value!\n");
        return ERROR;
    }
    sembuf temp;
    temp.sem_num = n;
    temp.sem_op = 1;
    temp.sem_flg = 0;
    semop(semid, &temp, 1);
    return OK;
}

int main()
{
    int semid = semget(1234, 3, IPC_CREAT | 0600); // create the semaphore with semget
    if (semid < 0)
    {
        printf("semget ERROR\n");
        exit(0);
    }

    // initialize the semaphore, EMPTY->3, FULL ->0, MUTEX->1
    semctl(semid, EMPTY, SETVAL, 3);
    semctl(semid, FULL, SETVAL, 0);
    semctl(semid, MUTEX, SETVAL, 1);

    int shmid = shmget(5678, sizeof(buffer), IPC_CREAT | 0600); // create shared memory with shmget
    if (shmid < 0)
    {
        printf("shmget ERROR\n");
        exit(0);
    }

    buffer *addr = (buffer *)shmat(shmid, 0, 0);

    if (addr == (void *)-1)
    {
        printf("shmat ERROR\n");
        exit(0);
    }

    addr->head = 0;
    addr->tail = 0;
    addr->empty = 1;

    // PRODUCER
    for (int i = 0; i < PRODUCER_NUM; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Producer fork ERROR!\n");
            exit(0);
        }
        if (pid == 0)
        {
            addr = (buffer *)shmat(shmid, 0, 0);
            if (addr == (void *)-1)
            {
                printf("Producer shmat ERROR\n");
                exit(0);
            }

            for (int j = 0; j < PRODUCER_REPEAT; j++)
            {
                srand((unsigned)time(NULL) + getpid());
                sleep(rand() % 1);
                P(semid, EMPTY);
                P(semid, MUTEX);
                int num = rand() % 1000;
                addr->item[addr->tail] = num;
                addr->tail = (addr->tail + 1) % 3;
                addr->empty = 0;

                time_t t;
                time(&t);
                printf("Time: %s", ctime(&t));
                printf("producer No.%d put %d\n", i, num);
                print_Buffer(addr);
                V(semid, FULL);
                V(semid, MUTEX);
            }
            shmdt(addr);
            exit(0);
        }
    }

    // CONSUMER
    for (int i = 0; i < CONSUMER_NUM; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Consumer fork ERROR!\n");
            exit(0);
        }
        if (pid == 0)
        {
            addr = (buffer *)shmat(shmid, 0, 0);
            if (addr == (void *)-1)
            {
                printf("Consumer shmat ERROR!\n");
                exit(0);
            }

            for (int j = 0; j < CONSUMER_REPEAT; j++)
            {
                srand((unsigned)time(NULL) + getpid());
                sleep(rand() % 1);
                P(semid, FULL);
                P(semid, MUTEX);
                int num = addr->item[addr->head];
                addr->head = (addr->head + 1) % 3;
                // the buffer is empty or not
                if (addr->head == addr->tail)
                    addr->empty = 1;
                else
                    addr->empty = 0;

                time_t t;
                time(&t);
                printf("Time: %s", ctime(&t));
                printf("Consumer No.%d remove %d\n", i + 1, num);

                if (addr->empty == 0)
                    print_Buffer(addr);
                else
                    printf("the Buffer is empty\n\n");
                V(semid, EMPTY);
                V(semid, MUTEX);
            }
            shmdt(addr);
            exit(0);
        }
    }

    while (wait(0) != -1);
    shmdt(addr);
    semctl(semid, IPC_RMID, 0);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}

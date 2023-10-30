#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>


int main(int argc, char* argv[]){
	pid_t pid;
	struct timeval startTime, endTime;
	
	if((pid = vfork())<0){
		printf("vfork failed!\n");
		exit(0);
	}else if(pid == 0){
		gettimeofday(&startTime, NULL);
		printf("vfork succedded, now in the child process.\n");
		printf("startTime-- sec: %ld, usec: %ld\n",startTime.tv_sec, startTime.tv_sec);
		execv(argv[1], &argv[1]);
	}else{	
		wait(NULL);
		printf("the created process is finished, now in the parent process.\n");
		gettimeofday(&endTime, NULL);
		printf("endTime-- sec: %ld, usec: %ld\n", endTime.tv_sec, endTime.tv_usec);	
		printf("the running time of the new process is:\nsec: %ld, usec: %ld\n", endTime.tv_sec-startTime.tv_sec, endTime.tv_usec-startTime.tv_usec);
	}
	exit(0);
}

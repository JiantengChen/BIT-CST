#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	printf("the new process has been created.\n");
	for(int n=0; n<argc; n++){
		printf("arg[%d]:%s\n", n, argv[n]);
	}
	sleep(1);
	printf("exit the new process.\n");
}


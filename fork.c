#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int g =2;

int main(void){
	pid_t pid = 15;
	int l=3;

	printf("PID(%d): Parent g=%d,l=%d \n",getpid(),g,l);
	pid = fork(); //child start on this line
	printf("PID(%d): current g= %d,l=%d\n",getpid(),g,l);
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid == 0){
		printf("PID(%d) this prc child so fork-pid==0\n",getpid());
		g++;
		l++;

	}else{
		printf("PID(%d): WAIT fork-pid=%d \n\n",getpid(),pid);
		wait(NULL);
	}


	printf("PID(%d): g=%d l=%d return\n\n",getpid(),g,l);
	return 0;
}

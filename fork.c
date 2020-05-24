#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int g =2;

int main(void){
	pid_t pid = 15;
	int l=3;

	// redirection으로 파일로 printf를 하게되면
	// fully bufferd io를 하게 되면서, flush를 마지막으로 미루다보니까
	// printf의 buffer까지 child에 복사되서 fork()이전의 printf가 두번출력된다. 
	// 일반 write로 stdout을 하면 buffered가 안되므로 1번만 출력된다.
	// stderr는 버퍼링 하지 않고 내보내기 때문에 redirection이여도 이미 flush해서
	// child에게 복사되 지 않았다.
	fprintf(stderr," run on parent, stderr! redirection test\n");
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

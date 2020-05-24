#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int g =2;
// vfork는 자식 프로세스가 같은 주소공간을 가르키고 있기때문에
// 부모 프로세스 주소공간에 영향을 준다.

int main(void){
	pid_t pid = 15;
	int l=3;

	printf("PID(%d): Parent g=%d,l=%d \n",getpid(),g,l);
	pid = vfork();
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


    //g 변수의 경우 전역이기에 잘 출력되지만.
	//l은 자식 프로세스에서 main 함수가 return 되며 지역변수 l이 release 되면 에러가 발생할 수 있다.
	printf("PID(%d): g=%d l=%d return\n\n",getpid(),g,l);
	return 0;
}

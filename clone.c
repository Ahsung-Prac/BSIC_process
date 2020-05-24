#include<stdio.h>
#include<linux/sched.h>

int g=2;
int sub_func(void *arg){
	g++;
	printf("PID(%d): Child g=%d \n",getpid(),g);

	for(int i=1; i < 6; i++){
		printf("chlid: %d \n",i);
	}

	printf("child Thread end\n\n");
	return 0;
}

int main(){
	int child_stack[4096];
	int l =3;

	printf("PID(%d): Parent g=%d, l=%d \n",getpid(),g,l);

	clone(sub_func,(void *)(child_stack+4095),CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);
	
	for(int i=1; i<6; i++){
		printf("main: %d \n",i);
	}

	printf("\nconfig bit : %0x %0x %0x\n",CLONE_VM,CLONE_THREAD,CLONE_SIGHAND);

	printf("\nPID(%d): Parent g=%d,l=%d \n\n",getpid(),g,l);

	sleep(1);
	return 0;
}



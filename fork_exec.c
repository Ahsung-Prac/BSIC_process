#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int g = 3;
int main(){
    pid_t pid;
    int l  = 2;
    int exit_status;

    pid = vfork(); //부모 프로세스 주소공간을 복사하는 과정이 없다. execl하면 어차피 없앨거기때문에 fork는 비효율
                   // vfork는 새로운 프로세스를 생성하지만 일단 부모주소공간을 그저 가르키기만 한다.
                   // 자식 프로세스에서 execl할 경우 새롭게 내용이 변하지만, 부모프로세스에는 영향을 주지 않는다.
    printf("exec_PID(%d)\n",getpid());
    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){
        printf("Child!! Before exec\n");
        //vfork이기 때문에 자식프로세스여도 부모에게 영향을 준다.
        g++;
        l++;
        //execl이후에는 주소공간이 모두 새로워지므로 부모공간과 독립된다.
        execl("./fork","fork",(char *)0);
        printf("After exec\n");
    }
    else{
        printf("exec_PID(%d): Parent Wait..\n",getpid());
        pid = wait(&exit_status);
    }

    printf("exec_PID(%d): Parent g= %d l=%d end\n\n",getpid(),g,l);
    return 0;
}
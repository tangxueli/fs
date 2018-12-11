/*************************************************************************
	> File Name: nice.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月20日 星期二 17时47分47秒
 ************************************************************************/

#include "apue.h"
#include<sys/resource.h>
#include<signal.h>

 unsigned long long  child=0,parent=0;
 pid_t pid;
static void run(int signo);
static void run10(int signo);

int main()
{
    int nzero;

    #if defined(NZERO)
        nzero = NZERO;
    #elif defined(_SC_NZERO)
        nzero = sysconf(_SC_NZERO);
    #else
    #error NZERO undefined
    #endif

    //printf("NZERO=%d\n",nzero);

    signal(SIGALRM,run10);
    alarm(3);
    if((pid=fork())==0)
    {
        nice(10);
        signal(SIGUSR1,run);
        while(1)
            child++;
    }
    else{
        while(1)
            parent++;
    }
}
static void run(int signo)
{
    printf("nice=%d\n",getpriority(PRIO_PROCESS,0));
    printf("childcount=%lld\n",child);
    exit(0);
}
static void run10(int signo)
{
    printf("nice=%d\n",getpriority(PRIO_PROCESS,0));
    printf("parentcount=%lld\n",parent);
    kill(pid,SIGUSR1);
    sleep(2);
    exit(0);
}



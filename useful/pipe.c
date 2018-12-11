/*************************************************************************
	> File Name: pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月13日 星期二 14时28分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    int fd[2];
    char sendbuf[1024]={0};
    char recvbuf[1024]={0};
    pid_t pid;
    pipe(fd);
    if((pid=fork())==-1)
        perror("fork error");
    if(pid==0)
    {
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        while(fgets(recvbuf,sizeof(recvbuf),stdin)!=0)
        {
            fputs(recvbuf,stdout);
            fflush(stdout);}
    }
    close(fd[0]);
    dup2(fd[1],1);
    close(fd[1]);
    while(fgets(sendbuf,sizeof(sendbuf),stdin)!=0)
    { fputs(sendbuf,stdout);fflush(stdout);}
    exit(0);
}

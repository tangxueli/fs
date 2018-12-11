/*************************************************************************
	> File Name: time.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月21日 星期三 16时28分48秒
 ************************************************************************/

#include<stdio.h>
#include<sys/times.h>
    #include<time.h>
    #include<UNIStd.h>
    #include<fcntl.h>

int main()
{
    int i=0;
    long tck=0;
    time_t t;
    tck=sysconf(_SC_CLK_TCK);
    time(&t);
    printf("tloc=%ld\n",t);
    struct tm *tmp;
    tmp=localtime(&t);
    char buf[64];
    strftime(buf,64,"localtime/strftime:time and date:%r,%a %d %d. %Y",tmp);
    printf("%s\n",buf);

    struct tms pb1,pb2;
    clock_t t1,t2;
    t1=times(&pb1);
   // printf("%f\n",t1/(double)tck);
    sleep(2);
    int fp;
    while(i<10000)
    {
        fp=open("nice.c",O_RDONLY);
        close(fp);
        i++;
    }
       // printf("a");mZ
    t2=times(&pb2);
    printf("times:t2-t1=%f\n",t2/(double)tck-t1/(double)tck);
    return 0;
}

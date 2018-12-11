/*************************************************************************
	> File Name: stime.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月23日 星期五 15时03分47秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    long int t = 66666666;
    system("date");
    stime(&t);
    system("date");
    return 0;
}


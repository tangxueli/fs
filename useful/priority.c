/*************************************************************************
	> File Name: priority.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月21日 星期三 12时03分19秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
unsigned long long i=0;
int main()
{
	nice(20);
        while(1)
            i++;
}

/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年12月12日 星期三 11时18分36秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include "btree.h"


int main(int argc,const char *argv[]){
    int i;
    BPnode T;
    T = Initialize();
    clock_t t1=clock();
    i=100;
    while(i>0)
        T = Insert(T,i--);
    i=100;
    printf("1\n");
    while(i<200)
        T = Insert(T,i++);
    i=50;
    while(i>0)
        T= Remove(T,i--);
    Travel(T);
    Destory(T);
    clock_t t2=clock();

    printf("\n用时：%lu秒\n",(t2-t1)/CLOCKS_PER_SEC);
}

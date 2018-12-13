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
    i=10;
    while(i>0)
    { 
        T = Insert(T,i--);
      //  Travel(T);
    }
    i=20;
    while(i<40)
      {  T = Insert(T,i++);
       // Travel(T);
      }
    i=30;
    while(i>10)
      {  T= Remove(T,i--);
        //Travel(T);      
      }
    Travel(T);
    Traveldate(T);
    //Destory(T);
    clock_t t2=clock();

    printf("\n用时：%lu秒\n",(t2-t1)/CLOCKS_PER_SEC);
}

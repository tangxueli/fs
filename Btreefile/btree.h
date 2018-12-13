/*************************************************************************
	> File Name: btree.h
	> Author: 
	> Mail: 
	> Created Time: 2018年11月29日 星期四 13时55分47秒
 ************************************************************************/

#ifndef _BTREE_H
#define _BTREE_H

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define M (4)
#define keymin (M%2 ? (M+1)/2 : M/2)

typedef struct Bnode *BPnode,*Position;
typedef int Keytype;
struct Bnode{
    int Keynum;
    Keytype Key[M+1];
    BPnode Children[M+1];
    BPnode Next;
    BPnode Pro;
};

extern BPnode Initialize();//初始化
extern BPnode Insert(BPnode T,Keytype key);//插入
extern BPnode Remove(BPnode T,Keytype key);//删除
extern BPnode Search(BPnode T,Keytype key);//查找
extern BPnode Destory(BPnode T);//
extern void Travel(BPnode T);//遍历
extern void Traveldate(BPnode T);//

#endif


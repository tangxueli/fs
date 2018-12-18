/*************************************************************************
	> File Name: ufs.h
	> Author: 
	> Mail: 
	> Created Time: 2018年12月14日 星期五 11时54分42秒
 ************************************************************************/

#ifndef _UFS_H
#define _UFS_H
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#define UFSALL ((32*1024+2+4)*1024)
#define BLKONE 1024

//超级快
#define SUPERSIZE 2
#define FEBLKNUM 256
#define FEINONUM 250

//索引节点
#define INODESIZE 4
#define INODEBGN 2
#define DINODENUM 4*1024/64//磁盘上节点数
#define MINODENUM 32 //内存节点数

//数据块
#define BLKSIZE 1
#define DATEBGN 6

//进程文件结构
#define openfilemax 16

//数据结构
//超级快：
struct Superblk{
    int magic;
    int disksize;
    
    int inodesearch;
    int inodeleft;
    int freeinode[FEINONUM];
    int nextinode;

    int blkleft;
    int freeblk[FEBLKNUM];
    int nextblk;
};

//磁盘索引节点：
struct Dinode{
    int type;
    int filesize;
    int flag;
    int linknum;
    int blkadds[12];
};

//内存索引节点：
struct Minode{
    struct Dinode *dinode;
    int offset;
    int openway;
    int inodenum;    
};
//用户描述符表
struct Descrip{
    int num;
    int Minodenum;
}

//目录：
struct Dir{
    int inodenum;
    char name[28];
};
//初始化
int Init(char *path);

//创建文件
int Creatfile(char *path);
int Removefile(char *path);

int Open();
int Close();
int Read();
int Write();
int Link();
int List();

#endif

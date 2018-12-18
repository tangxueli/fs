/*************************************************************************
	> File Name: ufs.c
	> Author: 
	> Mail: 
	> Created Time: 2018年12月17日 星期一 10时02分32秒
 ************************************************************************/

#include "ufs.h"

struct Superblk super;
//struct Dinode dinode[DINODENUM];//磁盘索引节点块
struct Dinode dinode;
struct MInode minode[MINODENUM];//内存索引节点表
struct Descrip dcrp[openfilemax];//文件描述符表


FILE *Ufsfp;//文件系统文件流；
char Cashblk[BLKSIZE];


extern int Initfile(char *path){
    Ufsfp = fopen(path,"wb+");
    char c = 1;
    setbuf(Ufsfp,NULL);
    if(fseek(Ufsfp,UFSALL-1,SEEK_SET)<0)
        return -1;
    if(fwrite(&c,sizeof(char),1,Ufsfp) != 0)
        return -2;
    memset(&super,0,sizeof(super));
    super.disksize=UFSSIZE;
    super.inodeleft=DINODENUM;
    super.blkleft=32*1024-32*4;//所有空闲块数减去用于空闲表的块数
    super.inodeseach=FEINONUM;

    //写超级块
    int i;
    for(i=0;i<FEINONUM;i++)
        super.freeinode[i]=i;
    super.nextinode=0;
    super.nextblk=255;
    super.freeblk[255]=DATEBGN;
    
    if(fseek(Ufsfp,0,SEEK_SET)<0)
        return -3;
    if(fwrite(&super,sizeof(super),1,Ufsfp) != 1)
        return -4;

    //写磁盘索引节点块
    dinode.type=0;
    dinode.fileszie=0;
    dinode.flag=0;
    dinode.linknum=0;
    if(fseek(Ufsfp,INODEBGN*BLKONE,SEEK_SET)<0)
        return -4;
    if(fwrite(&dinode,sizeof(dinode),DINODENUM,Ufsfp) != DINODENUM)
        return -5;

    //写数据块
    int Feblk[256];
    for(i=DATEBGN;i<=UFSALL/BLKONE-SUPERSIZE-INODESIZE;i=i+FEBLKNUM)
    {
        for(int j=0;j<FEBLKNUM;j++)
            Feblk[j]=i+j+1;
        if(fseek(Ufsfp,i*BLKONE,SEEK_SET)<0)
            return -6;
        if(fwrite(&Feblk,sizeof(Feblk),1,Ufsfp) != 1)
            return -7;
    }

    return 0;
}



int Bmap(int num){
    
}
//分配磁盘索引节点，返回磁盘索引节点号
int allocinode(){
    int i.j;
    i=0;j=super.inodeseach;
    struct Dinode inode;
    if(super.inodeleft==0)
        return -8;
    if(super.nextinode==FEINONUM)
    {
        while(i<FEINONUM && j <DINODENUM)
        {
            if(fseek(Ufsfp,j*sizeof(Dinode)+INODEBGN*BLKONE)<0)
                return -8;
            if(fread(&inode,sizeof(inode),1,Ufsfp) != 1)
                return -9;
            if(inode.flag == 0){
                auper.freeinode[i]=j;
                i++;
            }
            j++;
        }
        super.inodeseach=j;
        super.nextinode=0;
    }
    super.nextinode++;
    super.inodeleft--;
    return super.freeinode[super.nextinode-1];
}

int Freeinode(int inodenum){
    struct Dinode inode;
    inode.type=0;
    inode.filesize=0;
    inode.flag=0;
    inode.linknum=0;
    if(fseek(Ufsfp,inodenum*sizeof(inode),SEEK_SET)<0)
        return -10;
    if(fwrite(&inode,sizeof(inode),1,Ufsfp) != 1)
        return -11;
    super.inodeleft++;
}
//分配空闲磁盘块，返回块号
int Allocblk(){
    int num;
    num=super.freeblk[super.nextblk];
    if(super.blkleft == 0)
        return -12;
    if(super.nextblk == 255)
    {
    
        if(fseek(Ufsfp,super.freeblk[255]*BLKONE,SEEK_SET)<0)
            return -13;
        if(fread(super.freeblk,256*sizeof(int),1,Ufsfp) != 1)
            return -14;
        super.nextblk=0;
        return num;
    }
    else{
        super.blkleft--;
        super.nextblk++;
        return super.freeblk[super.nextblk-1];  
    }
}
int Freeblk(int blknum){
    int num;
    if(super.nextblk=0){
        num=super.freeblk[255];
        super.freeblk[255]=super.freeblk[0];
        super.nextblk=255;
        if(fseek(Ufsfp,blknum*BLKONE,SEEK_SET)<0)
            return -15;
        if(fwrite(superblk.freeblk,256*sizeof(int),1,Ufsfp) != 1)
            return -16;
    }
    else{
        super.blkleft++;
        super.nextblk--;
        super.freeblk[super.nextblk]=blknum;
    }
    return 0;
}

int Init(char *path){
    Ufsfp=fopen(path,"ab+");
    long size;
    if(fseek(Ufsfp,0,SEEK_END)<0)
        return -17;
    size=ftell(Ufsfp);
    fclose(Ufsfp);
    if(size==0)
    {
        if(Initfile(path)<0)
            printf("初始化错误!\n");
    }


}

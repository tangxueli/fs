/*************************************************************************
	> File Name: btree.c
	> Author: 
	> Mail: 
	> Created Time: 2018年11月29日 星期四 14时38分40秒
 ************************************************************************/

#include "btree.h"

static Keytype unvalue = INT_MIN;

//生成节点并初始化
static BPnode Mallocnewnode(){
    BPnode Newnode;
    int i;
    Newnode = malloc(sizeof(struct BPnode));
    if(Newnode == NULL)
        exit(EXIT_FAILURE);
    i=0;
    while(i<M)
    {
        Newnode->Key[i] = unvalue;
        Newnode->Children[i] = NULL;
        i++;
    }
    Newnode->Next = NULL;
    Newnode->Keynum = 0;

    return Newnode;
}

//初始化

extern BPnode Initialize(){
    BPnode T;
    if(M < (3)){
        printf("M最小等于3\n");
        exit(EXIT_FAILURE);
    }
    T = Mallocnewnode();

    return T;
}

//寻找一个节点之下最小Key
static Position Findmostleft(Position P){
    Position tmp;
    tmp = p;
    while(tmp != NULL && tmp->Children[0] != NULL)){
        tmp = tmp->Children[0];
    }
    return tmp;
}
//寻找一个节点之下最大Key
static Position Findmostright(Position P){
    Position tmp;
    tem = p;
    while(tmp != NULL && tmp->Children[tmp->Keynum-1] != NULL)
        tmp = tmp->Children[tmp->Keynum-1];
    return tmp;
}

//寻找兄弟节点，其存储关键字未满，否则返回NULL
static Position Findsibling(Position Parent , int i){
    Position Sibling;
    int Limit;

    Limit = M;
    Sibling = NULL;
    if(i == 0){
        if(Parent->Children[1]->Keynum<Limit)
            Sibling = Parent->Children[1];
    }
    else if(Parent->Children[i-1]->Keynum<Limit)
        Sibling = Parent->Children[i-1];
    else if(i+1<Parent->Keynum && Parent->Children[i+1]->Keynum<Limit){
        Sibling = Parent->Children[i+1];
    }

    return Sibling;
}

static Position InsertElement(int iskey ,Position Parent,Position X,Keytype key,int i,int j){
    if(iskey){
        k=X->Keynum -1;
        while(k >= j){
            X->Key[k+1]=X->Key[k];
            k--;
        }
        X->Key[j]=key;
        
        if(Parent != NULL)
            Parent->Key[i]=X->Key[0];
        X->Keynum++;
    }
    else{
        if(X->Children[0]==NULL){
            if(i>0)
                Parent->Children[i-1]->Next = X;
            X->Next = Parent->Children[i];
        }
        k=Parent->Keynum-1;
        while(k>=i){
            Parent->Children[k+1] = Parent->Children[k];
            Parent->Key[k+1] = Parent->Key[k];
            k--;
        }
        Parent->Key[i]=X->Key[0];
        Parent->Children[i]=X;
        Parent->Keynum++;
    }
    return X;

}

static Position Removeelement(int iskey,Position Parent,Position X,int i,int j){
    int k,Limit;

    if(iskey){
        Limit=X->Keynum;
        k=j+1;
        while(k<Limit){
            X->Key[k-1]=X->Key[k];
            k++;
        }
        X->Key[X->Keynum-1]=unvalue;
        Parent->Key[i]=X->Key[0];
        X->Keynum--;
    }else{
        if(X->Children[0]==NULL && i >0){
            Parent->Children[i-1]->Next=Parent->Children[i+1];
        }
        Limit=Parent->Keynum;
        k=i+1;
        while(k<Limit){
            Parent->Children[k-1]=Parent->Children[k];
            Parent->Key[k-1]=Parent->Key[k];
            k++;
        }
        Parent->Children[Parent->Keynum-1]=NULL;
        Parent->Key[Parent->Keynum-1]=unvalue;
        Parent->Keynum++;
    }
    return X;

}

//在兄弟之间移动key
static Position Moveelement(Position X,Position Y,Position Parent,int i,int n){
    Keytype Tmpkey;
    Position Child;
    int j,flag;//先后顺序

    flag=0;
    if(X->Key[0]<Y->Key[0])
        flag=1;
    j=0;
    if(flag){
        if(X->Children[0]!=NULL){
            while(j<n){
                Child=X->Children[X->Keynum-1];
                Removeelement(0,X,Child,)
            }
        }
        
    }
}













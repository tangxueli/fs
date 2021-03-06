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
    Newnode = (BPnode)malloc(sizeof(struct Bnode));
    if(Newnode == NULL)
        exit(EXIT_FAILURE);
    i=0;
    while(i<M+1)
    {
        Newnode->Key[i] = unvalue;
        Newnode->Children[i] = NULL;
        i++;
    }
    Newnode->Next = NULL;
    Newnode->Pro = NULL;
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
    tmp = P;
    while(tmp != NULL && tmp->Children[0] != NULL){
        tmp = tmp->Children[0];
    }
    return tmp;
}
//寻找一个节点之下最大Key
static Position Findmostright(Position P){
    Position tmp;
    tmp = P;
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
static Position Findsiblingkeymin(Position Parent,int i,int *j)
{
    int Limit;
    Position Sibling;
    Sibling = NULL;
    Limit = keymin;

    if(i==0){
        if(Parent->Children[1]->Keynum > Limit){
            Sibling = Parent->Children[1];
            *j=1;
        }
    }
    else{
        if(Parent->Children[i-1]->Keynum > Limit){
            Sibling = Parent->Children[i-1];
            *j=i-1;
        }
        else if(i+1<Parent->Keynum && Parent->Children[i+1]->Keynum > Limit){
            Sibling=Parent->Children[i+1];
            *j=i+1;
        }
    }
    return Sibling;
}

static Position Insertelement(int iskey ,Position Parent,Position X,Keytype key,int i,int j){
    int k;
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
       // if(X->Children[0]==NULL && Parent->Children[i] != NULL){
         ///   X->Next = Parent->Children[i];
          //  X->Pro = Parent->Children[i]->Pro;
         //   if(X->Next != NULL)
            //    X->Next->Pro = X;
           // if(X->Pro != NULL)
           //     X->Pro->Next = X;
        
      //  }
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
       // if(X->Children[0]==NULL){
        //    Parent->Children[i-1]->Next=Parent->Children[i+1];
           // if(X->Pro != NULL)
         //       X->Pro->Next = X-> Next;
         //   if(X->Next != NULL)
       //         X->Next->Pro = X->Pro;
      //  }
        Limit=Parent->Keynum;
        k=i+1;
        while(k<Limit){
            Parent->Children[k-1]=Parent->Children[k];
            Parent->Key[k-1]=Parent->Key[k];
            k++;
        }
        Parent->Children[Parent->Keynum-1]=NULL;
        Parent->Key[Parent->Keynum-1]=unvalue;
        Parent->Keynum--;
    }
   // if(X->Keynum == 0)
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
                Removeelement(0,X,Child,X->Keynum-1,unvalue);
                Insertelement(0,Y,Child,unvalue,0,unvalue);
                j++;
            }
        }
        else{
            while(j<n){
                Tmpkey =X->Key[X->Keynum-1];
                Removeelement(1,Parent,X,i,X->Keynum-1);
                Insertelement(1,Parent,Y,Tmpkey,i+1,0);
                j++;
            }
        }
        Parent->Key[i+1]=Y->Key[0];
        //if(X->Keynum > 0)
         //   Findmostright(X)->Next = Findmostleft(Y);
        
    }
    else{
        if(X->Children[0]!=NULL){
            while(j<n){
            Child=X->Children[0];
            Removeelement(0,X,Child,0,unvalue);
            Insertelement(0,Y,Child,unvalue,Y->Keynum,unvalue);
            j++;
            }
        }
        else{
            while(j<n){
                Tmpkey=X->Key[0];
                Removeelement(1,Parent,X,i,0);
                Insertelement(1,Parent,Y,Tmpkey,i-1,Y->Keynum);
                j++;
            }
        }
        Parent->Key[i] = X->Key[0];
      //  if(X->Keynum > 0)
       //     Findmostright(Y)->Next = Findmostleft(X);
    }

    return Parent;
}

static BPnode Splitnode(Position Parent,Position X,int i){
    Position Newnode;
    Position tmp;
    Newnode=Mallocnewnode();
    int j,k,Limit;
    Limit=X->Keynum;
    k=X->Keynum/2;
    j=0;
    while(k<Limit){
        if(X->Children[0]!=NULL){
            Newnode->Children[j]=X->Children[k];
            X->Children[k]=NULL;
        }
        Newnode->Key[j]=X->Key[k];
        X->Key[k]=unvalue;
        k++;j++;
        X->Keynum--;Newnode->Keynum++;
    }
    if(X->Children[0]==NULL)
    {
        tmp = X->Next;
        X->Next = Newnode;
        Newnode->Next = tmp;
        Newnode->Pro = X;
        if(tmp != NULL){
            Newnode->Next->Pro = Newnode;
        }
    }
    if(Parent!=NULL){
        Insertelement(0,Parent,Newnode,unvalue,i+1,unvalue);
    }
    else{
        Parent=Mallocnewnode();
        Insertelement(0,Parent,X,unvalue,0,unvalue);
        Insertelement(0,Parent,Newnode,unvalue,1,unvalue);

        return Parent;
    }
    return X;
}
static BPnode Mergenode(Position Parent,Position X,Position Y,int i,int j){
    int Limit;
    if(Y->Keynum>keymin)
        Moveelement(Y,X,Parent,j,1);
    else{
        Limit=X->Keynum;
        Moveelement(X,Y,Parent,i,Limit);
        Removeelement(0,Parent,X,i,unvalue);
      //  if(X->Children[0] == NULL)
      //  {
       //     X->
       // }
        if(X->Children[0]==NULL)
        {
            if(X->Next != NULL)
                X->Next->Pro = X->Pro;
            if(X->Pro != NULL)
                X->Pro->Next = X->Next;
        }
        free(X);
        X=NULL;
    }
    return Parent;
}

static Position Findinsert(BPnode T,Keytype key, int i,BPnode Parent){
    int j,Limit;
    Position Sibling;
    j=0;
    while(j<T->Keynum && key >= T->Key[j]){
        if(key==T->Key[j])
            return T;
        j++;
    }
    if(j!=0&&T->Children[0]!=NULL)
        j--;
    if(T->Children[0] == NULL)
        T=Insertelement(1,Parent,T,key,i,j);
    else
        T->Children[j]=Findinsert(T->Children[j],key,j,T);
    
    Limit=M;
    if(T->Keynum > Limit){
        if(Parent == NULL){
            T=Splitnode(Parent,T,i);
        }
        else{
            Sibling=Findsibling(Parent, i);
            if(Sibling != NULL)
                Moveelement(T,Sibling,Parent,i,1);
            else
                T=Splitnode(Parent,T,i);
        }
    }

    if(Parent != NULL)
        Parent->Key[i]=T->Key[0];

    return T;
}

extern Position Insert(BPnode T,Keytype key){
    return Findinsert(T,key,0,NULL);
}

static Position Findremove(BPnode T,Keytype key,int i,BPnode Parent){
    int j,Limit;
    j=0;
    Limit=T->Keynum;
    while(j<Limit && key >= T->Key[j]){
        if(key == T->Key[j])
            break;
        j++;
    }
    if(i==0 && key < T->Key[0])
        return T;
    if(T->Children[0] == NULL)
    {
        if(key != T->Key[j] || j == Limit)
            return T;        
    }
    else{
            if(j == Limit || key < T->Key[j])
                j--;
    }
    
    if(T->Children[0]==NULL)
        T=Removeelement(1,Parent,T,i,j);
    else
        T->Children[j] = Findremove(T->Children[j],key,j,T);

    int Adjust;
    Adjust=0;
    if(Parent == NULL && T->Children[0] != NULL && T->Keynum < 2)
        Adjust = 1;
    else if(Parent != NULL && T->Children[0] != NULL && T->Keynum < keymin)
        Adjust = 1;
    else if(Parent != NULL && T->Children[0] ==NULL && T->Keynum < keymin)
        Adjust = 1;

    BPnode Tmp;
    BPnode Sibling;
    if(Adjust){
        if(Parent == NULL){
           if(T->Children[0] != NULL && T->Keynum < 2){
            Tmp = T;
            T = T->Children[0];
            free(Tmp);
            return T;
            }
        }
        else{
            Sibling = Findsiblingkeymin(Parent, i,&j);
            if(Sibling != NULL)
                Moveelement(Sibling,T,Parent,j,1);
            else{
                if(i == 0)
                {
                    Sibling = Parent->Children[1];
                    j=1;
                }
                else{
                    Sibling = Parent->Children[i-1];
                    j=i-1;
                }
                Parent = Mergenode(Parent,T,Sibling,i,j);
                T = Parent->Children[i];
            }
        }
    }
    return T;
}

extern BPnode Remove(BPnode T,Keytype key){
    return Findremove(T,key,0,NULL);
}

extern BPnode Destory(BPnode T){
    int i,j;
    if(T != NULL){
        i =0;
        while(i < T->Keynum+1){
            Destory(T->Children[i]);
            i++;
        }
        printf("Destory:(");
        j=0;
        while(j < T->Keynum)
            printf("%d:",T->Key[j++]);
        printf(")");
        free(T);
        T = NULL;
    }
    return T;
}

static void Findtravel(BPnode T,int level){
    int i,j;
    if(T != NULL){
        printf("level:%d->",level);
        printf("(");
        i=0;
        while(i<T->Keynum)
            printf(" %d ",T->Key[i++]);
        printf(")");
        level++;

        j=0;
        while(j < T->Keynum){
            Findtravel(T->Children[j],level);
            j++;
        }
    }
}

extern void Travel(BPnode T){
    Findtravel(T,0);
    printf("\n");
}

extern void Traveldate(BPnode T){
    Position Tmp;
    Tmp = T;
    int i;
    if(T == NULL)
        return;
    printf("All date:");
    while(Tmp->Children[0] != NULL)
    Tmp = Tmp->Children[0];
    while(Tmp != NULL){
        i=0;
        while(i<Tmp->Keynum)
            printf(" %d",Tmp->Key[i++]);
        Tmp = Tmp->Next;
    }
}

extern int Getin(BPnode T,int fd){

    Keytype key;
    printf("从磁盘读入：\n");
    while(read(fd,&key,sizeof(Keytype)) != 0)
    {
        //printf("%d",key);
        T=Insert(T,key);}

    return 1;
}
extern int Putout(BPnode T,int fd){
    Position Tmp;
    Tmp = T;
    int i;
    int k;
    k=0;
    int buf[2048];
    if(T == NULL)
        return 0;
    printf("\n写入磁盘----\n");
    while(Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    while(Tmp != NULL)
    {
        i=0;
        //printf("\n%d\n",Tmp->Keynum);
        while(i<Tmp->Keynum){
          //  printf("1");
            buf[k]=Tmp->Key[i];
            k++;
            if(k%2048 == 0 ){
                write(fd,buf,2048*sizeof(Keytype));
                 k=0;
            }
        //printf("2");
        i++;
        }
        Tmp = Tmp->Next;        
    }
    write(fd,buf,k*sizeof(Keytype));
    return 1;
}








#include "c9-3.h"

/* bo9-4.c 动态查找表(B树)的基本操作 */
 Status InitDSTable(BTree *DT)
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BTree *DT)
 { /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
   int i;
   if(*DT) /* 非空树 */
   {
     for(i=0;i<=(*DT)->keynum;i++)
       DestroyDSTable(&(*DT)->node[i].ptr); /* 依次销毁第i棵子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 int Search(BTree p, KeyType K)
 { /* 在p->node[1..keynum].key中查找i,使得p->node[i].key≤K＜p->node[i+1].key */
   int i=0,j;
   for(j=1;j<=p->keynum;j++)
     if(p->node[j].key<=K)
       i=j;
   return i;
 }

 Result SearchBTree(BTree T, KeyType K)
 { /* 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值 */
   /* tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的 */
   /* 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。算法9.13 */
   BTree p=T,q=NULL; /* 初始化，p指向待查结点，q指向p的双亲 */
   Status found=FALSE;
   int i=0;
   Result r;
   while(p&&!found)
   {
     i=Search(p,K); /* p->node[i].key≤K<p->node[i+1].key */
     if(i>0&&p->node[i].key==K) /* 找到待查关键字 */
       found=TRUE;
     else
     {
       q=p;
       p=p->node[i].ptr;
     }
   }
   r.i=i;
   if(found) /* 查找成功 */
   {
     r.pt=p;
     r.tag=1;
   }
   else /*  查找不成功，返回K的插入位置信息 */
   {
     r.pt=q;
     r.tag=0;
   }
   return r;
 }

 void Insert(BTree *q,int i,Record *r,BTree ap)
 { /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
   int j;
   for(j=(*q)->keynum;j>i;j--) /* 空出q->node[i+1] */
     (*q)->node[j+1]=(*q)->node[j];
   (*q)->node[i+1].key=r->key;
   (*q)->node[i+1].ptr=ap;
   (*q)->node[i+1].recptr=r;
   (*q)->keynum++;
 }

 void split(BTree *q,BTree *ap)
 { /* 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap */
   int i,s=(m+1)/2;
   *ap=(BTree)malloc(sizeof(BTNode)); /* 生成新结点ap */
   (*ap)->node[0].ptr=(*q)->node[s].ptr; /* 后一半移入ap */
   for(i=s+1;i<=m;i++)
   {
     (*ap)->node[i-s]=(*q)->node[i];
     if((*ap)->node[i-s].ptr)
       (*ap)->node[i-s].ptr->parent=*ap;
   }
   (*ap)->keynum=m-s;
   (*ap)->parent=(*q)->parent;
   (*q)->keynum=s-1; /* q的前一半保留，修改keynum */
 }

 void NewRoot(BTree *T,Record *r,BTree ap)
 { /* 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针 */
   BTree p;
   p=(BTree)malloc(sizeof(BTNode));
   p->node[0].ptr=*T;
   *T=p;
   if((*T)->node[0].ptr)
     (*T)->node[0].ptr->parent=*T;
   (*T)->parent=NULL;
   (*T)->keynum=1;
   (*T)->node[1].key=r->key;
   (*T)->node[1].recptr=r;
   (*T)->node[1].ptr=ap;
   if((*T)->node[1].ptr)
     (*T)->node[1].ptr->parent=*T;
 }

 void InsertBTree(BTree *T,Record *r,BTree q,int i)
 { /* 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起 */
   /* 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。算法9.14改 */
   BTree ap=NULL;
   Status finished=FALSE;
   int s;
   Record *rx;
   rx=r;
   while(q&&!finished)
   {
     Insert(&q,i,rx,ap); /* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
     if(q->keynum<m)
       finished=TRUE; /* 插入完成 */
     else
     { /* 分裂结点*q */
       s=(m+1)/2;
       rx=q->node[s].recptr;
       split(&q,&ap); /* 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap */
       q=q->parent;
       if(q)
         i=Search(q,rx->key); /* 在双亲结点*q中查找rx->key的插入位置 */
     }
   }
   if(!finished) /* T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap */
     NewRoot(T,rx,ap); /* 生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针 */
 }

 void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   int i;
   if(DT) /* 非空树 */
   {
     if(DT->node[0].ptr) /* 有第0棵子树 */
       TraverseDSTable(DT->node[0].ptr,Visit);
     for(i=1;i<=DT->keynum;i++)
     {
       Visit(*DT,i);
       if(DT->node[i].ptr) /* 有第i棵子树 */
	       TraverseDSTable(DT->node[i].ptr,Visit);
     }
   }
 }

//旋转或合并B树
void SolveUnderflowBTree(BTree *T,BTree q)
 {
   int j=0;
    if ((q->keynum+1)>=(m+1)/2)
    {//当前节点未下溢
      return;
    }
   BTree t=q->parent;
   if (!t)
   {//已到根节点
     if (q->keynum==0 && q->node[0].ptr)
     {
       *T=q->node[0].ptr;
       q->node[0].ptr->parent=NULL;
       q->node[0].ptr=NULL;
       free(q);
     }
     return;
   }

   int k=0;
   while (q!=t->node[k].ptr)
   {
     k++;
   }
   //q是t的第k个孩子，可能是第0个

   if (k>=1)//向左借
   {
     BTree ls=t->node[k-1].ptr;
     if ((ls->keynum+1)>(m+1)/2)
     {
       for(j=q->keynum;j>=1;j--) /* 空出q->node[1] */
         q->node[j+1]=q->node[j];
       q->node[1]=t->node[k];
       q->keynum++;
       q->node[1].ptr=q->node[0].ptr;
       q->node[0].ptr=ls->node[ls->keynum].ptr;

       if (q->node[0].ptr)
       {
         q->node[0].ptr->parent=q;
       }

       t->node[k]=ls->node[ls->keynum];
       t->node[k].ptr=q;

       ls->node[ls->keynum].ptr=NULL;
       ls->keynum--;
       return;
     }
   }

   if (k<t->keynum)//向右借
   {
     BTree rs=t->node[k+1].ptr;
     if ((rs->keynum+1)>(m+1)/2)
     {
       q->keynum++;
       q->node[q->keynum]=t->node[k+1]; //k+1是p右边的key
       q->node[q->keynum].ptr=rs->node[0].ptr;

       if (q->node[q->keynum].ptr)
       {
         q->node[q->keynum].ptr->parent=q;
       }

       t->node[k+1]=rs->node[1];//k+1是p右边的key
       t->node[k+1].ptr=rs;

       rs->node[0].ptr=rs->node[1].ptr;
       for(j=1;j<rs->keynum;j++) /* 空出q->node[1] */
         rs->node[j]=rs->node[j+1];
       rs->node[rs->keynum].ptr=NULL;
       rs->keynum--;
       return;
     }
   }
   if (k>=1)//向左合并
   {
     BTree ls=t->node[k-1].ptr;
     ls->keynum++;
     ls->node[ls->keynum]=t->node[k];
     ls->node[ls->keynum].ptr=q->node[0].ptr;
     if (ls->node[ls->keynum].ptr)
     {
       ls->node[ls->keynum].ptr->parent=ls;
     }

     for ( j=k;j<t->keynum;j++)
     {
       t->node[j]=t->node[j+1];
     }
     t->node[t->keynum].ptr=NULL;
     t->keynum--;

     for ( j=1;j<=q->keynum;j++)
     {
       ls->keynum++;
       ls->node[ls->keynum]=q->node[j];
       if (ls->node[ls->keynum].ptr)
       {
         ls->node[ls->keynum].ptr->parent=ls;
       }
     }
     free(q);
   }
   else//与右合并
   {
     BTree rs=t->node[k+1].ptr;

     q->keynum++;
     q->node[q->keynum]=t->node[k+1];//k+1是p右边的key
     q->node[q->keynum].ptr=rs->node[0].ptr;
     if (q->node[q->keynum].ptr)
     {
       q->node[q->keynum].ptr->parent=q;
     }

     for ( j=k+1;j<t->keynum;j++)
     {
       t->node[j]=t->node[j+1];
     }
     t->node[t->keynum].ptr=NULL;
     t->keynum--;

     for ( j=1;j<=rs->keynum;j++)
     {
       q->keynum++;
       q->node[q->keynum]=rs->node[j];
       if (q->node[q->keynum].ptr)
       {
         q->node[q->keynum].ptr->parent=q;
       }
     }
     free(rs);
   }
   //向上处理下溢
   SolveUnderflowBTree(T, t);
   return;
 }

void DeleteBTree(BTree *T, KeyType K)
 {
   BTree p=NULL;
   int k;
   //先查找
   Result s = SearchBTree(*T, K);
   if (!s.tag)
   {
      return;
   }

   p=s.pt;
   k=s.i;
   if(p->node[0].ptr) //若p非叶子，则K癿后继必属亍某叶节点
   {
     if (p->node[k].ptr)//有右节点
     {
       BTree u=p->node[k].ptr;//从右节点中找到后继
       while (u->node[0].ptr)
       {
         u=u->node[0].ptr;
       }
       p->node[k].key=u->node[1].key;
       //保留右子结点放在最左边，避免被覆盖, 现在最左边是NULL。相当于右边无子结点。
       u->node[0].ptr=u->node[1].ptr;
       p=u;
       k=1;
     }
   }
   //删除p中第k个key
   for (int i=k;i<p->keynum;i++)
   {
     p->node[i]=p->node[i+1];
   }
   p->node[p->keynum].ptr=NULL;
   p->keynum--;

   //旋转或合并B树
   SolveUnderflowBTree(T,p);
 }
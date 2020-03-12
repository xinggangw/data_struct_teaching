/* 
 * the following code is copied from "https://www.cnblogs.com/dplearning/p/3629033.html"
 * for education only
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h> 


typedef int Status;
const int TRUE=1;
const int FALSE=0;
const int OK=1;
const int ERROR=0;
const int INFEASIBLE=-1;
const int overflow=-2;
const int STACK_INIT_SIZE=100;
const int STACKINCREMENT=10;

typedef struct{
    int ArrivalTime;
    int Duration;
    int id;
}QElemType;


//线性链表
typedef struct{
    int OccurTime;
    int id;
    int NType;
}Event, ElemType; //元素类型

typedef struct LNode{
    ElemType data; 
    struct LNode *next;
}LNode, *LinkList;    //线性链表结点

typedef LinkList EventList; 

int cmp(int a , int b)
{
    if(a>b)
        return 1;
    else if(a<b)
        return -1;
    else 
        return 0;
}



//按OccurTime由小到大的顺序排列 相同的则先进来的排前面
Status OrderInsert( LinkList &L, ElemType e, int(* compare)(int, int))
{
    ElemType tmp;
    LinkList s = (LinkList)malloc(sizeof(LNode)); 
    s->data = e;
     
    LinkList p = L;
    if(p->next==NULL) {  //没有元素则直接插入
        s->next = p->next;
        p->next = s;
    }
    else{
        while( compare(e.OccurTime, p->next->data.OccurTime) != -1) {    
            p = p->next; 
            if (NULL == p->next)
                break;
        }
        s->next = p->next;
        p->next = s;
    }
    
    return OK;
}

//删除链表的最后一个元素
Status ListDeleteLast_L(LinkList &L, ElemType &e)
{
    LinkList s;
    LinkList p = L;
    while(p->next->next != NULL)
    {
        p = p->next;
    }
    s = p;
    e = p->next->data;
    free(p->next);
    s->next = NULL;

    return OK;
}

//创建一个新的空链表
Status ListCreate_L(LinkList &L)
{
    if(L == NULL)
    {
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
        return OK;
    }
    else
        return ERROR;
}

//销毁一个链表
Status ListDestroy_L(LinkList &L)
{
    LinkList p=L, s;
    while(p->next != NULL)
    {
        s = p; p = p->next;  free(s);
    }
    return OK;
}

bool ListEmpty_L(LinkList L)
{
    if(L->next==NULL)
        return true;
    else
        return false;
}

//删除链表的第一个元素
Status ListDeleteFirst_L(LinkList &L, ElemType &e)
{
    LinkList s;
    LinkList p = L;

    s = p;
    p = p->next;
    e = p->data;
    s->next = p->next;
    free(p);

    return OK;
}



//循环队列
#define MAXQSIZE 100
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

Status InitQueue(SqQueue &Q)
{
    //构造一个空队列Q
    Q.base = (QElemType * ) malloc (MAXQSIZE * sizeof(QElemType));
    if(!Q.base) exit(overflow);
    Q.front = Q.rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    //返回Q的元素个数，即队列的长度
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue &Q, QElemType e)
{
    //插入元素e为新的队尾元素
    if((Q.rear +1)%MAXQSIZE == Q.front) return ERROR; //队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear +1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
{
    //若队列不空，则删除Q的队头元素, 用e返回其值，并返回OK;
    //否则返回 ERROR
    if(Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1)%MAXQSIZE;
    return OK;
}

Status DestroyQueue(SqQueue &Q)
{
    //删除队列Q
    if(Q.base != NULL)
    {
        free(Q.base);
        Q.front = Q.rear =0;
        return OK;
    }
    return ERROR;
}

Status GetHeadQueue(SqQueue &Q, QElemType &e)
{
    //获取队列队头的元素
    e = Q.base[Q.front];
    return OK;
}


//链队列
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
}LinkQueue;

Status InitQueue_L(LinkQueue &Q)
{
    //构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(Q.front==NULL) exit(overflow);
    Q.front->next=NULL;
    return OK;
}

Status DestroyQueue_L(LinkQueue &Q)
{
    //销毁一个队列
    while(Q.front!=NULL)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

Status EnQueue_L(LinkQueue &Q, QElemType e){
    //插入元素e为Q的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(overflow);
    p->data = e;  p->next =NULL;
    Q.rear->next = p;
    Q.rear  = p;
    return OK;
}

Status DeQueue_L(LinkQueue &Q, QElemType &e)
{
    //若队列不空 删除Q的队头元素，用e返回其值，并返回OK
    //否则返回ERROR
    QueuePtr p;
    if(Q.rear == Q.front) return ERROR;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p) Q.rear = Q.front;
    free(p);
    return OK;
}

int QueueLength_L(LinkQueue Q)
{
    //返回Q的元素个数，即队列的长度
    if(Q.front == Q.rear)
    {
        return 0;
    }
    QueuePtr p = Q.front;
    int i = 1;
    while(p->next != Q.rear)
    {
        i++;
        p=p->next;
    }
    return i;
}

bool QueueEmpty_L(LinkQueue Q)
{
    if(Q.rear == Q.front)
        return true;
    else
        return false;
}

Status GetHeadQueue_L(LinkQueue Q, QElemType &e)
{
    e = Q.front->next->data;
    return OK;
}




#define CloseTime 50
EventList ev; //事件表
Event     en; //事件
LinkQueue  q[5]; //4个客户队列
QElemType customer; //客户记录
int TotalTime,CustomerNum; //累积客户逗留时间，客户数

int Minimum(LinkQueue q[])
{
    int l[5];
    for (int i=1; i<=4; i++)
    {
        l[i]=q[i].rear - q[i].front;
    }
    int a = l[1]>l[2]?2:1;
    int b = l[3]>l[4]?4:3;
    return l[a]>l[b]?b:a;
}

void OpenForDay()
{
    //初始化操作
    TotalTime = 0; CustomerNum = 0; //初始化累积时间和客户数
    ListCreate_L(ev);               //初始化事件链表为空表
    en.OccurTime = 0; en.NType = 0; //设定第一个客户到达事件
    OrderInsert(ev,en,cmp);         //插入事件表
    for(int i=1;i<=4;i++) InitQueue_L(q[i]); //置空队列
}//OpenForDay

void CustomerArrived()
{
    //处理客户到达事件  en.NType = 0;
    int durtime, intertime;
    ElemType tmp;
    QElemType Qtmp;
    ++CustomerNum;
    
    durtime = 1+(int)(30.0*rand()/(RAND_MAX+1.0)); //处理时间
    intertime = 1+(int)(10.0*rand()/(RAND_MAX+1.0)); //下一客户到达时间间隔
    // printf("durtime:%d intertime:%d\n",durtime,intertime);
    
    int t = en.OccurTime + intertime;  //下一客户到达时间
    if(t<CloseTime) //银行未关门 插入事件表
    {
        tmp.OccurTime = t;
        tmp.NType = 0;
        tmp.id = CustomerNum;
        OrderInsert(ev,tmp,cmp);
    }
    
    int i = Minimum(q);
    Qtmp.ArrivalTime = en.OccurTime;
    Qtmp.Duration = durtime;
    Qtmp.id = CustomerNum;
    EnQueue_L(q[i],Qtmp); //将当前到来的客户插入队列
    printf("Arrive: id %d, arrival_time %d, window %d, duration_time %d\n", Qtmp.id, Qtmp.ArrivalTime, i, Qtmp.Duration);
    
    if(QueueLength_L(q[i]) == 1)
    {
        tmp.OccurTime = en.OccurTime+durtime;
        tmp.NType = i;
        // printf("Departure event: occur_time %d, queue_index: %d\n", tmp.OccurTime, tmp.NType);
        OrderInsert(ev,tmp,cmp); //若队列长度为1 则插入一个离开事件 因为只有前一个人离开了 后面的人才能离开
    }

}

void CustomerDeparture()
{
    //处理客户离开事件 ，en.Type>0;
    ElemType tmp;
    int i = en.NType;  
    DeQueue_L(q[i],customer); //删除第i队列的排头客户
    printf("Departure: id %d, arrival_time %d, window %d, duration_time %d\n", customer.id, customer.ArrivalTime, i, customer.Duration);
    
    // printf("time:%d\n",en.OccurTime - customer.ArrivalTime);
    TotalTime += en.OccurTime - customer.ArrivalTime;
    if(!QueueEmpty_L(q[i]))
    {
        GetHeadQueue_L(q[i],customer);
        tmp.NType = i;
        tmp.OccurTime = en.OccurTime + customer.Duration;
        // printf("Departure event: occur_time %d, queue_index: %d\n", tmp.OccurTime, tmp.NType);
        OrderInsert(ev,(tmp),cmp);
    }
}

void Bank_Simulation()
{
    ElemType tmp;
    OpenForDay();
    while(!ListEmpty_L(ev))
    {
        ListDeleteFirst_L(ev, tmp);
        en = tmp;
        if(en.NType == 0)
            CustomerArrived();
        else
            CustomerDeparture();
    }

    printf("The Average Time is %f\n",(float)TotalTime/CustomerNum);
}


int main()
{
    srand((int)time(0));
    for(int i=0; i<1; i++)
    {
        Bank_Simulation();
    }

    return 0;
}

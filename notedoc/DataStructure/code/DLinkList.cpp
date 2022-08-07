#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int N = 5;
typedef int ElemType;

typedef struct DNode
{
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

bool PrintList(DLinkList &L)
{
    if (L->next == NULL) //带头节点判空
        return false;
    DNode *p = L->next; //带头节点第一个元素
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl; //换行
    return true;
}

bool DestroyList(DLinkList &L)
{
    if (L == NULL)
        return true;
    DNode *deDNode = L;
    while (deDNode != NULL)
    {
        L = L->next;
        free(deDNode);
        deDNode = L;
    }
    return true;
}

DLinkList DlistCreat_HeadInsert(DLinkList &L)
{
    DNode *node = NULL;
    ElemType input_data;
    L = (DNode *)malloc(sizeof(DNode)); //带头节点，不带头节点则删除该语句
    L->prior = NULL;                    //初始化投节点的prior指针
    L->next = NULL;                     //初始化投节点的next指针
    while ((cin >> input_data))
    {
        node = (DNode *)malloc(sizeof(DNode)); //创建新节点
        node->data = input_data;               //输入数据
        /*头插法：先让新节点的next指向头节点的next,再让头节点next的prior指向新节点
        再让头节点next指向新节点,新节点prior指向头节点*/
        node->next = L->next;
        L->next->prior = node;
        L->next = node;
        node->prior = L;
    }
    // cout << __FUNCTION__ << __LINE__ << "L addr:" << L << endl;
    return L;
}

DLinkList DlistCreat_TailInsert(DLinkList &L)
{
    DNode *node = NULL, *tail = NULL;
    ElemType input_data;
    L = (DNode *)malloc(sizeof(DNode)); //带头节点，不带头节点则删除该语句
    L->prior = NULL;                    //初始化投节点的prior指针
    L->next = NULL;                     //初始化投节点的next指针
    tail = L;                           // 让tail指向头节点
    while ((cin >> input_data))
    {
        node = (DNode *)malloc(sizeof(DNode)); //创建新节点
        node->data = input_data;               //输入数据
        node->next = NULL;                     //初始化新节点的next
        /*尾插法：让tail指向的节点的next指向新节点,新节点的prior指向tail,然后更改当前tail指针指向新节点*/
        tail->next = node;
        node->prior = tail;
        tail = node;
    }
    // cout << __FUNCTION__ << __LINE__ << "L addr:" << L << endl;
    return L;
}

DNode *GetElem(DLinkList &L, int pos)
{
    if (L->next == NULL)
        return NULL;
    DNode *ptr = L->next;
    int i = 1;
    while (ptr && i < pos)
    {
        ptr = ptr->next;
        i++;
    }
    return ptr;
}

DNode *DListInsert(DLinkList &L, int pos, ElemType data)
{
    if (L->next == NULL)
        return NULL;
    DNode *ptr = GetElem(L, pos - 1); //获取i-1处的节点
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = data;
    /*插入节点*/
    newNode->next = ptr->next;
    ptr->next->prior=newNode;
    ptr->next = newNode;
    newNode->prior=ptr;

    return newNode;
}

DNode *DListDelete(DLinkList &L, int pos, ElemType &data)
{
    if (L->next == NULL)
        return NULL;
    DNode *delNode = GetElem(L, pos ); //获取i处的节点
    data = delNode->data;             //获取被删除内容
    /*从链表中删除*/
    delNode->prior->next=delNode->next;
    delNode->next->prior=delNode->prior;
    DNode *cur=delNode->next;        
    free(delNode);                    //释放内存
    delNode = NULL;                   //置空
    
    return cur;//返回当前在pos处的节点
}

int main()
{
    DLinkList L = NULL;
    DlistCreat_TailInsert(L);
    // cout << __FUNCTION__ << " " << __LINE__ << " L addr:" << L << endl;
    PrintList(L);
    DListInsert(L,3,8);
    int temp;
    DListDelete(L,4,temp);
    DestroyList(L);
    return 0;
}
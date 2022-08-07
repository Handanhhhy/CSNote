#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int N = 5;
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

bool PrintList(LinkList &L)
{
    if (L->next == NULL) //带头节点判空
        return false;
    LNode *p = L->next; //带头节点第一个元素
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl; //换行
    return true;
}

bool DestroyList(LinkList &L)
{
    if (L == NULL)
        return true;
    LNode *delnode = L;
    while (delnode != NULL)
    {
        L = L->next;
        free(delnode);
        delnode = L;
    }
    return true;
}

LinkList listCreat_HeadInsert(LinkList &L)
{
    LNode *node = NULL;
    ElemType input_data;
    L = (LNode *)malloc(sizeof(LNode)); //带头节点，不带头节点则删除该语句
    L->next = NULL;                     //初始化投节点的next指针
    while ((cin >> input_data))
    {
        node = (LNode *)malloc(sizeof(LNode)); //创建新节点
        node->data = input_data;               //输入数据
        /*头插法：先让新节点的next指向头节点的next,再让头节点next指向新节点*/
        node->next = L->next;
        L->next = node;
    }
    // cout << __FUNCTION__ << __LINE__ << "L addr:" << L << endl;
    return L;
}

LinkList listCreat_TailInsert(LinkList &L)
{
    LNode *node = NULL, *tail = NULL;
    ElemType input_data;
    L = (LNode *)malloc(sizeof(LNode)); //带头节点，不带头节点则删除该语句
    L->next = NULL;                     //初始化投节点的next指针
    tail = L;                            // 让tail指向头节点,也是当前的尾节点
    while ((cin >> input_data))
    {
        node = (LNode *)malloc(sizeof(LNode)); //创建新节点
        node->data = input_data;               //输入数据
        node->next = NULL;                     //初始化新节点的next
        /*尾插法：让tail的next指向新节点,然后更改当前tail指针指向新节点*/
        tail->next = node;
        tail = node;
    }
    // cout << __FUNCTION__ << __LINE__ << "L addr:" << L << endl;
    return L;
}

LNode *GetElem(LinkList &L, int pos)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = L->next;
    int i = 1;
    while (ptr && i < pos)
    {
        ptr = ptr->next;
        i++;
    }
    return ptr;
}

LNode *ListInsert(LinkList &L, int pos, ElemType data)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = GetElem(L, pos - 1); //获取i-1处的节点
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = data;
    /*插入节点*/
    newNode->next = ptr->next;
    ptr->next = newNode;
    return newNode;
}

LNode *ListDelete(LinkList &L, int pos, ElemType &data)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = GetElem(L, pos - 1); //获取i-1处的节点
    LNode *delNode = ptr->next;       //得到i处的节点
    data = delNode->data;             //获取被删除内容
    ptr->next = delNode->next;        //从链表中删除
    free(delNode);                    //释放内存
    delNode = NULL;                   //置空
    return ptr;
}

LNode *ListDelete2(LinkList &L, int pos, ElemType &data)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = GetElem(L, pos); //获取i处的节点
    LNode *nextNode = ptr->next;  //得到i+1处的节点
    data = ptr->data;             //获取被删除内容
    ptr->data = nextNode->data;   //将第i+1节点内容复制到第i个节点中
    ptr->next = nextNode->next;    //从链表中删除第i+1个节点
    free(nextNode);                //释放内存
    nextNode = NULL;               //置空
    return ptr;
}

int main()
{
    LinkList L = NULL;
    listCreat_TailInsert(L);
    // cout << __FUNCTION__ << " " << __LINE__ << " L addr:" << L << endl;
    PrintList(L);
    ListInsert(L, 3, 6);
    PrintList(L);
    int temp;
    ListDelete2(L, 4, temp);
    PrintList(L);
    DestroyList(L);
    return 0;
}
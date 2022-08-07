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
    if (L->next == NULL) //��ͷ�ڵ��п�
        return false;
    DNode *p = L->next; //��ͷ�ڵ��һ��Ԫ��
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl; //����
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
    L = (DNode *)malloc(sizeof(DNode)); //��ͷ�ڵ㣬����ͷ�ڵ���ɾ�������
    L->prior = NULL;                    //��ʼ��Ͷ�ڵ��priorָ��
    L->next = NULL;                     //��ʼ��Ͷ�ڵ��nextָ��
    while ((cin >> input_data))
    {
        node = (DNode *)malloc(sizeof(DNode)); //�����½ڵ�
        node->data = input_data;               //��������
        /*ͷ�巨�������½ڵ��nextָ��ͷ�ڵ��next,����ͷ�ڵ�next��priorָ���½ڵ�
        ����ͷ�ڵ�nextָ���½ڵ�,�½ڵ�priorָ��ͷ�ڵ�*/
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
    L = (DNode *)malloc(sizeof(DNode)); //��ͷ�ڵ㣬����ͷ�ڵ���ɾ�������
    L->prior = NULL;                    //��ʼ��Ͷ�ڵ��priorָ��
    L->next = NULL;                     //��ʼ��Ͷ�ڵ��nextָ��
    tail = L;                           // ��tailָ��ͷ�ڵ�
    while ((cin >> input_data))
    {
        node = (DNode *)malloc(sizeof(DNode)); //�����½ڵ�
        node->data = input_data;               //��������
        node->next = NULL;                     //��ʼ���½ڵ��next
        /*β�巨����tailָ��Ľڵ��nextָ���½ڵ�,�½ڵ��priorָ��tail,Ȼ����ĵ�ǰtailָ��ָ���½ڵ�*/
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
    DNode *ptr = GetElem(L, pos - 1); //��ȡi-1���Ľڵ�
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = data;
    /*����ڵ�*/
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
    DNode *delNode = GetElem(L, pos ); //��ȡi���Ľڵ�
    data = delNode->data;             //��ȡ��ɾ������
    /*��������ɾ��*/
    delNode->prior->next=delNode->next;
    delNode->next->prior=delNode->prior;
    DNode *cur=delNode->next;        
    free(delNode);                    //�ͷ��ڴ�
    delNode = NULL;                   //�ÿ�
    
    return cur;//���ص�ǰ��pos���Ľڵ�
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
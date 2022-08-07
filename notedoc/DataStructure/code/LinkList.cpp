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
    if (L->next == NULL) //��ͷ�ڵ��п�
        return false;
    LNode *p = L->next; //��ͷ�ڵ��һ��Ԫ��
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl; //����
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
    L = (LNode *)malloc(sizeof(LNode)); //��ͷ�ڵ㣬����ͷ�ڵ���ɾ�������
    L->next = NULL;                     //��ʼ��Ͷ�ڵ��nextָ��
    while ((cin >> input_data))
    {
        node = (LNode *)malloc(sizeof(LNode)); //�����½ڵ�
        node->data = input_data;               //��������
        /*ͷ�巨�������½ڵ��nextָ��ͷ�ڵ��next,����ͷ�ڵ�nextָ���½ڵ�*/
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
    L = (LNode *)malloc(sizeof(LNode)); //��ͷ�ڵ㣬����ͷ�ڵ���ɾ�������
    L->next = NULL;                     //��ʼ��Ͷ�ڵ��nextָ��
    tail = L;                            // ��tailָ��ͷ�ڵ�,Ҳ�ǵ�ǰ��β�ڵ�
    while ((cin >> input_data))
    {
        node = (LNode *)malloc(sizeof(LNode)); //�����½ڵ�
        node->data = input_data;               //��������
        node->next = NULL;                     //��ʼ���½ڵ��next
        /*β�巨����tail��nextָ���½ڵ�,Ȼ����ĵ�ǰtailָ��ָ���½ڵ�*/
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
    LNode *ptr = GetElem(L, pos - 1); //��ȡi-1���Ľڵ�
    LNode *newNode = (LNode *)malloc(sizeof(LNode));
    newNode->data = data;
    /*����ڵ�*/
    newNode->next = ptr->next;
    ptr->next = newNode;
    return newNode;
}

LNode *ListDelete(LinkList &L, int pos, ElemType &data)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = GetElem(L, pos - 1); //��ȡi-1���Ľڵ�
    LNode *delNode = ptr->next;       //�õ�i���Ľڵ�
    data = delNode->data;             //��ȡ��ɾ������
    ptr->next = delNode->next;        //��������ɾ��
    free(delNode);                    //�ͷ��ڴ�
    delNode = NULL;                   //�ÿ�
    return ptr;
}

LNode *ListDelete2(LinkList &L, int pos, ElemType &data)
{
    if (L->next == NULL)
        return NULL;
    LNode *ptr = GetElem(L, pos); //��ȡi���Ľڵ�
    LNode *nextNode = ptr->next;  //�õ�i+1���Ľڵ�
    data = ptr->data;             //��ȡ��ɾ������
    ptr->data = nextNode->data;   //����i+1�ڵ����ݸ��Ƶ���i���ڵ���
    ptr->next = nextNode->next;    //��������ɾ����i+1���ڵ�
    free(nextNode);                //�ͷ��ڴ�
    nextNode = NULL;               //�ÿ�
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
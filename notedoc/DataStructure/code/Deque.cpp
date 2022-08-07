#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 6 + 1;
typedef int ElemType;

typedef struct queue
{
    ElemType data[MaxSize];
    int front, rear;
} Deque;

void InitQueue(Deque &S)
{
    /*frontָ���ͷ��rearָ���β����һ��λ��*/
    S.front = S.rear = 0;
}

bool QueueEmpty(Deque &S)
{
    if (S.rear == S.front) //ѭ�������п�
        return true;
    return false;
}

bool isQueueFull(Deque &S)
{
    if (S.front == (S.rear + 1) % MaxSize) //ѭ����������
        return true;
    return false;
}

bool EnQueue_Front(Deque &S, ElemType data)
{
    if (isQueueFull(S))
        return false;
    //��--�ٸ�ֵ:��֤frontָ����Ƕ���Ԫ��
    S.front = (S.front - 1 + MaxSize) % MaxSize; // Important
    S.data[S.front] = data;
    return true;
}

bool EnQueue_Back(Deque &S, ElemType data)
{
    if (isQueueFull(S))
        return false;
    //�ȸ�ֵ��--:��֤rearָ����Ƕ�βԪ�ص���һ��λ��
    S.data[S.rear] = data;
    S.rear = (S.rear + 1) % MaxSize; // Important
    return true;
}

bool DeQueue_Front(Deque &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    //�Ȼ�ȡֵ���ƶ�ָ��:��Ϊfrontָ����Ƕ�ͷԪ��
    data = S.data[S.front];
    S.front = (S.front + 1) % MaxSize; // Important
    return true;
}

bool DeQueue_Back(Deque &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    //���ƶ�ָ���ٸ�ֵ:��Ϊrearָ����Ƕ�βԪ�ص���һ��λ��
    S.rear = (S.rear - 1) % MaxSize; // Important
    data = S.data[S.rear];
    return true;
}

bool GetHead(Deque &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[S.front];
    return true;
}

bool GetTail(Deque &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[(S.rear - 1 + MaxSize) % MaxSize];
    return true;
}

void PrintFront(Deque &S)
{
    for (int i = 0; i < (S.rear - S.front + MaxSize) % MaxSize; i++)
        cout << S.data[(S.front + i) % MaxSize] << " ";
    cout << endl;
}

void PrintBack(Deque &S)
{
    for (int i = 0; i < (S.rear - S.front + MaxSize) % MaxSize; i++)
        cout << S.data[(S.rear - 1 - i + MaxSize) % MaxSize] << " ";
    cout << endl;
}

int main()
{
    Deque S;
    InitQueue(S);
    cout << "QueueEmpty: " << QueueEmpty(S) << endl;
    EnQueue_Front(S, 1); // 1
    EnQueue_Front(S, 2); // 2 1
    EnQueue_Front(S, 3); // 3 2 1
    cout << "QueueEmpty: " << QueueEmpty(S) << endl;
    PrintFront(S);
    PrintBack(S);

    EnQueue_Back(S, 4); // 3 2 1 4
    EnQueue_Back(S, 5); // 3 2 1 4 5
    EnQueue_Back(S, 6); // 3 2 1 4 6

    PrintFront(S);
    PrintBack(S);

    int temp;
    GetHead(S, temp);
    cout << "GetHead: " << temp << endl;
    GetTail(S, temp);
    cout << "GetTail: " << temp << endl;

    DeQueue_Front(S, temp);
    cout << "DeQueue_Front: " << temp << endl;

    PrintFront(S);
    PrintBack(S);

    DeQueue_Back(S, temp);
    cout << "DeQueue_Back: " << temp << endl;

    PrintFront(S);
    PrintBack(S);

    return 0;
}
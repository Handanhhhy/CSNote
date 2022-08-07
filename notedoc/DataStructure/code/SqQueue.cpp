#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 3 + 1;
typedef int ElemType;

typedef struct queue
{
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &S)
{
    /*front指向对头，rear指向队尾的下一个位置*/
    S.front = S.rear = 0;
}

bool QueueEmpty(SqQueue &S)
{
    if (S.rear == S.front) //循环队列判空
        return true;
    return false;
}

bool EnQueue(SqQueue &S, ElemType data)
{
    if (S.front == (S.rear + 1) % MaxSize) //循环队列判满
        return false;
    S.data[S.rear] = data;
    S.rear = (S.rear + 1) % MaxSize; //形成循环
    return true;
}

bool DeQueue(SqQueue &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[S.front];
    S.front = (S.front + 1) % MaxSize;
    return true;
}

bool GetHead(SqQueue &S, ElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[S.front];
    return true;
}

void Print(SqQueue &S)
{
    for (int i = 0; i < (S.rear - S.front + MaxSize) % MaxSize; i++)
        cout << S.data[(S.front + i) % MaxSize] << " ";
    cout << endl;
}

int main()
{
    SqQueue S;
    InitQueue(S);
    cout << "QueueEmpty: " << QueueEmpty(S) << endl;
    EnQueue(S, 1);
    EnQueue(S, 2);
    EnQueue(S, 3);
    cout << "QueueEmpty: " << QueueEmpty(S) << endl;
    int temp;
    GetHead(S, temp);
    cout << "GetTop: " << temp << endl;
    DeQueue(S, temp);
    cout << "Pop: " << temp << endl;
    GetHead(S, temp);
    cout << "GetTop: " << temp << endl;
    Print(S);
    return 0;
}
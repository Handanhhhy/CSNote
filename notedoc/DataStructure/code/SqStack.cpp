#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 10;
typedef int ElemType;

typedef struct stack
{
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S)
{
    S.top = -1;
}

bool StackEmpty(SqStack &S)
{
    if (S.top == -1)
        return true;
    return false;
}

bool Push(SqStack &S, ElemType data)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = data;
    return true;
}

bool Pop(SqStack &S, ElemType &data)
{
    if (S.top == -1)
        return false;
    data = S.data[S.top--];
    return true;
}

bool GetTop(SqStack &S, ElemType &data)
{
    if (S.top == -1)
        return false;
    data = S.data[S.top];
    return true;
}

int main()
{
    SqStack S;
    InitStack(S);
    cout << "StackEmpty: " << StackEmpty(S) << endl;
    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    cout << "StackEmpty: " << StackEmpty(S) << endl;
    int temp;
    GetTop(S, temp);
    cout << "GetTop: " << temp << endl;
    Pop(S, temp);
    cout << "Pop: " << temp << endl;
    GetTop(S, temp);
    cout << "GetTop: " << temp << endl;

    return 0;
}
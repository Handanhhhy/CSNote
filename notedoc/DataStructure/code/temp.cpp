#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *create1(Node *p)
{
    p = (Node *)malloc(sizeof(Node));
    p->data = 1;
    return p;
}
void create2(Node *&p)
{
    p = (Node *)malloc(sizeof(Node));
    p->data = 2;
}
Node *create3(Node *p3)
{
    Node *p = p3;
    p = (Node *)malloc(sizeof(Node));
    p->data = 3;
    return p;
}

void create(Node *&p, int data)
{
    p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
}

void print1(Node *p)
{
    cout << __FUNCTION__ << ":";
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
void print2(Node *&p)
{
    cout << __FUNCTION__ << ":";
    while (p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    // Node *p1 = NULL, *p2 = NULL, *p3 = NULL;
    // Node *a = create1(p1);
    // cout << "create1: "
    //      << "p1 addr: " << p1 << endl; // cout << " p1.data: " << p1->data 报错,表示p1并没有指向申请的内存
    // cout << "create1: "
    //      << "a addr: " << a << " a.data: " << a->data << endl;

    // create2(p2);
    // cout << "create2: "
    //      << "p2 addr: " << p2 << " p2.data: " << p2->data << endl;

    // Node *b = create3(p3);
    // cout << "create3: "
    //      << "p3 addr: " << p3 << endl; // cout << " p3.data: " << p3->data 报错,表示p3并没有指向申请的内存
    // cout << "create3: "
    //      << "b addr: " << b << " b.data: " << b->data << endl;

    // free(a), free(p2), free(b);

    Node *c1 = NULL, *c2 = NULL, *c3 = NULL, *c0 = NULL;
    create(c1, 1), create(c2, 2), create(c3, 3);
    c1->next = c2, c2->next = c3; // c1指向c2,c2指向c3
    c0 = c1;                      // c0指向c0
    cout << "c0 addr:" << c0 << endl;
    print1(c0);
    cout << "print1 c0 addr:" << c0 << endl;
    print2(c0);
    cout << "print2 c0 addr:" << c0 << endl;
    free(c1), free(c2), free(c3);

    return 0;
} 
/*输出
create1: p1 addr: 0
create1: a addr: 0x711920 a.data: 1
create2: p2 addr: 0x711960 p2.data: 2
create3: p3 addr: 0
create3: b addr: 0x711d50 b.data: 3

c0 addr:0x6c1920
print1:1 2 3
print1 c0 addr:0x6c1920
print2:1 2 3
print2 c0 addr:0
*/
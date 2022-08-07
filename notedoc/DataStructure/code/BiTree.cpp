#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 10;
typedef char BiNodeElemType;
typedef struct BiNode
{
    BiNodeElemType data;
    struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void Visit(BiNode *r)
{
    cout << r->data << " ";
}

void preOrd(BiNode *r)
{
    if (r == NULL)
        return;
    Visit(r);
    preOrd(r->lchild);
    preOrd(r->rchild);
}

void inOrd(BiNode *r)
{
    if (r == NULL)
        return;

    inOrd(r->lchild);
    Visit(r);
    inOrd(r->rchild);
}

void postOrd(BiNode *r)
{
    if (r == NULL)
        return;

    postOrd(r->lchild);
    postOrd(r->rchild);
    Visit(r);
}

void Free(BiTree &r)
{
    if (r == NULL)
        return;
    Free(r->rchild);
    Free(r->lchild);
    free(r);
    r = NULL;
}

BiNode *createByPre_Mid(char preStr[], char midStr[], int pi, int pj, int mi, int mj, BiNode *&rootNode)
{
    /*����pre��˵piΪ��λ��,����mid��˵miΪ��ʼֵ*/
    int pre_root_pos = pi, mid_root_pos = mi;
    /*����root���*/
    rootNode = (BiNode *)malloc(sizeof(BiNode));
    rootNode->data = preStr[pre_root_pos];
    /*������������������*/
    /*��mid��Ѱ�ҵ���λ��(mid��һ���и�����,���Բ���Ҫ�ж�mid_root_posԽ��)*/
    while (midStr[mid_root_pos] != preStr[pre_root_pos])
    {
        mid_root_pos++;
    }
    /*����������������ʼ�ͽ���*/
    int pls = pre_root_pos + 1, ple = pre_root_pos + (mid_root_pos - mi);
    /*����������������ʼ�ͽ���*/
    int mls = mi, mle = mid_root_pos - 1;
    /*����������������ʼ�ͽ���*/
    int prs = ple + 1, pre = pj;
    /*����������������ʼ�ͽ���*/
    int mrs = mid_root_pos + 1, mre = mj;
    /*����������*/
    if (mid_root_pos == mi) //��������ʼΪrootʱ�������Ϊ��
        rootNode->lchild = NULL;
    else
        rootNode->lchild = createByPre_Mid(preStr, midStr, pls, ple, mls, mle, rootNode->lchild);
    /*����������*/
    if (mid_root_pos == mj) //���������Ϊrootʱ���Ҷ���Ϊ��
        rootNode->rchild = NULL;
    else
        rootNode->rchild = createByPre_Mid(preStr, midStr, prs, pre, mrs, mre, rootNode->rchild);

    return rootNode;
}

BiNode *createByMid_Post(char midStr[], char postStr[], int mi, int mj, int pi, int pj, BiNode *&rootNode)
{
    /*����post��˵pjΪ��λ��,����mid��˵miΪ��ʼֵ*/
    int post_root_pos = pj, mid_root_pos = mi;
    /*����root���*/
    rootNode = (BiNode *)malloc(sizeof(BiNode));
    rootNode->data = postStr[post_root_pos];
    /*������������������*/
    /*��mid��Ѱ�ҵ���λ��(mid��һ���и�����,���Բ���Ҫ�ж�mid_root_posԽ��)*/
    while (midStr[mid_root_pos] != postStr[post_root_pos])
    {
        mid_root_pos++;
    }
    /*����������������ʼ�ͽ���*/
    int pls = pi, ple = pi + (mid_root_pos - mi) - 1;
    /*����������������ʼ�ͽ���*/
    int mls = mi, mle = mid_root_pos - 1;
    /*����������������ʼ�ͽ���*/
    int prs = ple + 1, pre = post_root_pos - 1;
    /*����������������ʼ�ͽ���*/
    int mrs = mid_root_pos + 1, mre = mj;
    /*����������*/
    if (mid_root_pos == mi) //��������ʼΪrootʱ�������Ϊ��
        rootNode->lchild = NULL;
    else
        rootNode->lchild = createByMid_Post(midStr, postStr, mls, mle, pls, ple, rootNode->lchild);
    /*����������*/
    if (mid_root_pos == mj) //���������Ϊrootʱ���Ҷ���Ϊ��
        rootNode->rchild = NULL;
    else
        rootNode->rchild = createByMid_Post(midStr, postStr, mrs, mre, prs, pre, rootNode->rchild);

    return rootNode;
}

BiNode *createByLevel(char str[], int length, BiNode *&rootNode)
{
    /*��������Ŵ�1��ʼ,iΪĳ�����,��ô2iΪ����,2i+1Ϊ�Һ���
    **��iΪ���ӽ��,��ôi/2Ϊ����,(i-1)/2Ϊ�Һ���*/
    BiNode *(que[MaxSize]) = {NULL};
    BiNode *newNode = NULL;
    for (int i = 1; i <= length; i++)
    {
        newNode = (BiNode *)malloc(sizeof(BiNode));
        newNode->data = str[i - 1];
        newNode->lchild = NULL, newNode->rchild = NULL;
        que[i] = newNode;
        if (i == 1)
            rootNode = newNode;
        else if ((i & 1) == 1)
            que[(i - 1) >> 1]->rchild = newNode;
        else if ((i & 1) == 0)
            que[i >> 1]->lchild = newNode;
    }
    return rootNode;
}

void printLeaf(BiTree root)
{
    if (root == NULL)
        return;
    if (root->lchild == NULL && root->rchild == NULL)
    {
        Visit(root);
        return;
    }
    printLeaf(root->lchild);
    printLeaf(root->rchild);
}

int getDepth(BiTree root)
{
    if (root == NULL)
        return 0;
    int lh = getDepth(root->lchild);
    int rh = getDepth(root->rchild);
    return max(lh, rh) + 1;
}

typedef BiNode *StackElemType;
typedef struct stack
{
    StackElemType data[MaxSize];
    int top;
} SqStack;
void InitStack(SqStack &S);
bool StackEmpty(SqStack &S);
bool Push(SqStack &S, StackElemType data);
bool Pop(SqStack &S, StackElemType &data);
bool GetTop(SqStack &S, StackElemType &data);
/*�ڱ���ʱ��һ����������Һ��ӽ���ͬʱ��Ҳ��һ�������
**�������㲻����ʱ������Ϊ�����������ӻ��Һ��Ӳ�����:
**��һ�α�����Ϊ������룬�������жϲ����ھ�����Ϊ���Ӳ�����
**��һ�α�����Ϊ�ҽ����룬�������жϲ����ھ�����Ϊ�Һ��Ӳ�����
**��:if(r == NULL)Ϊ��,�Ϳ�r������һ��r=r->lchild�õ�������r=r->rchild
**�����������ʱ������Ϊ��(��)������
*/
/*DLR�ص�:�����������ڵ�ʱ������Ϊ���ڵ����
**����:��ȥroot���֮�⣬һ���������Ϊ�������������жϵ�֮ǰ��
**�Ѿ���Ϊ�����ӽ��ĸ������������Ե���������ʱ��ֻ��Ҫ�ж���������
*/
void preOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //��Ϊ��������
        {
            Visit(r);       //����������
            Push(stack, r); //�������ջ����Ϊ�Һ��ӻ�δ����
            r = r->lchild;  //��������
        }
        else //��Ϊ����㲻���ڣ�ͬʱ��Ϊ�����������ӻ��Һ��Ӳ�����
        {
            Pop(stack, r); //��ʱ�ø������������ӷ��ʹ��ˣ�������ջ�����Һ��ӣ�
            r = r->rchild;
        }
    }
}
/*LDR�ص�:��������������ʱ������Ϊ���ڵ���������ж�������*/
void inOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //��Ϊ��������
        {
            Push(stack, r); //�������ջ
            r = r->lchild;  //�ȷ�������
        }
        else //��Ϊ����㲻���ڣ�ͬʱ��Ϊ���������ӻ��Һ��Ӳ�����
        {
            Pop(stack, r); //��������
            Visit(r);
            r = r->rchild; //�����Һ���
        }
    }
}
/*LRD�ص�:������������������ʱ����Ϊ���ڵ������Ȼ�����ж�������*/
void postOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    BiNode *visited = NULL;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //��������
        {
            Push(stack, r); //�������ջ
            r = r->lchild;  //�ȷ�������
        }
        else //����㲻����Ҳ����Ϊ���������Ӳ����ڣ������жϷ���������
        {
            //(���ӱ����ʹ��������Ӳ�����)���ظ���㣬�����Һ��ӣ���Ϊ����û����������Ը����ܳ�ջ
            GetTop(stack, r);
            if (r->rchild && r->rchild != visited) //���Һ��Ӳ���δ���ʹ�
            {
                r = r->rchild;
            }
            else //û���Һ��ӻ����Һ��ӱ����ʹ�
            {
                Pop(stack, r); //������
                Visit(r);
                visited = r; //��¼�ý�㱻���ʹ�(Ҳ����Ϊ�����͸��������Һ��ӱ����ʹ�)
                r = NULL;    //Ŀ���Ǵ�ջ����ȡ��һ�θ���㣬���´ν����жϷ���������
                //������GetTop(stack, r);��ʹ������һ��ѭ���ֻ���ʸø���������
            }
        }
    }
}
typedef BiNode *QueElemType;
typedef struct queue
{
    QueElemType data[MaxSize];
    int front, rear;
} SqQueue;
void InitQueue(SqQueue &S);
bool QueueEmpty(SqQueue &S);
bool EnQueue(SqQueue &S, QueElemType data);
bool DeQueue(SqQueue &S, QueElemType &data);
bool GetHead(SqQueue &S, QueElemType &data);

void levelOrd(BiTree root)
{
    if (root == NULL)
        return;
    SqQueue que;
    InitQueue(que);
    EnQueue(que, root);
    BiNode *cur = NULL;
    while (!QueueEmpty(que))
    {
        DeQueue(que, cur);
        Visit(cur);
        if (cur->lchild)
            EnQueue(que, cur->lchild);
        if (cur->rchild)
            EnQueue(que, cur->rchild);
    }
}

int main()
{
    BiTree root = NULL;
    // createByPre_Mid("ABCDEFGH", "BDCEAFHG", 0, 7, 0, 7, root);
    //  postOrd(root);
    //  createByMid_Post("BDCEAFHG", "DECBHGFA", 0, 7, 0, 7, root);
    //  createByMid_Post("BACDE", "BEDCA", 0, 4, 0, 4, root);
    createByLevel("ABCDEFGH", 8, root);
    preOrd(root);
    cout << endl;
    preOrd2(root);
    cout << endl;

    inOrd(root);
    cout << endl;
    inOrd2(root);
    cout << endl;

    postOrd(root);
    cout << endl;
    postOrd2(root);
    cout << endl;

    levelOrd(root);
    cout << endl;

    // printLeaf(root);
    // cout << endl;
    // cout << getDepth(root);
    Free(root);
    return 0;
}

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

bool Push(SqStack &S, StackElemType data)
{
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = data;
    return true;
}

bool Pop(SqStack &S, StackElemType &data)
{
    if (S.top == -1)
        return false;
    data = S.data[S.top--];
    return true;
}

bool GetTop(SqStack &S, StackElemType &data)
{
    if (S.top == -1)
        return false;
    data = S.data[S.top];
    return true;
}

void InitQueue(SqQueue &S)
{
    /*frontָ���ͷ��rearָ���β����һ��λ��*/
    S.front = S.rear = 0;
}

bool QueueEmpty(SqQueue &S)
{
    if (S.rear == S.front) //ѭ�������п�
        return true;
    return false;
}

bool EnQueue(SqQueue &S, QueElemType data)
{
    if (S.front == (S.rear + 1) % MaxSize) //ѭ����������
        return false;
    S.data[S.rear] = data;
    S.rear = (S.rear + 1) % MaxSize; //�γ�ѭ��
    return true;
}

bool DeQueue(SqQueue &S, QueElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[S.front];
    S.front = (S.front + 1) % MaxSize;
    return true;
}

bool GetHead(SqQueue &S, QueElemType &data)
{
    if (QueueEmpty(S))
        return false;
    data = S.data[S.front];
    return true;
}

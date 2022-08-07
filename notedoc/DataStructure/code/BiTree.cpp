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
    /*对于pre来说pi为根位置,对于mid来说mi为初始值*/
    int pre_root_pos = pi, mid_root_pos = mi;
    /*生成root结点*/
    rootNode = (BiNode *)malloc(sizeof(BiNode));
    rootNode->data = preStr[pre_root_pos];
    /*处理左子树和右子树*/
    /*在mid中寻找到根位置(mid中一定有根存在,所以不需要判断mid_root_pos越界)*/
    while (midStr[mid_root_pos] != preStr[pre_root_pos])
    {
        mid_root_pos++;
    }
    /*先序里左子树的起始和结束*/
    int pls = pre_root_pos + 1, ple = pre_root_pos + (mid_root_pos - mi);
    /*中序里左子树的起始和结束*/
    int mls = mi, mle = mid_root_pos - 1;
    /*先序里右子树的起始和结束*/
    int prs = ple + 1, pre = pj;
    /*中序里右子树的起始和结束*/
    int mrs = mid_root_pos + 1, mre = mj;
    /*左子树建立*/
    if (mid_root_pos == mi) //当中序起始为root时，左儿子为空
        rootNode->lchild = NULL;
    else
        rootNode->lchild = createByPre_Mid(preStr, midStr, pls, ple, mls, mle, rootNode->lchild);
    /*右子树建立*/
    if (mid_root_pos == mj) //当中序结束为root时，右儿子为空
        rootNode->rchild = NULL;
    else
        rootNode->rchild = createByPre_Mid(preStr, midStr, prs, pre, mrs, mre, rootNode->rchild);

    return rootNode;
}

BiNode *createByMid_Post(char midStr[], char postStr[], int mi, int mj, int pi, int pj, BiNode *&rootNode)
{
    /*对于post来说pj为根位置,对于mid来说mi为初始值*/
    int post_root_pos = pj, mid_root_pos = mi;
    /*生成root结点*/
    rootNode = (BiNode *)malloc(sizeof(BiNode));
    rootNode->data = postStr[post_root_pos];
    /*处理左子树和右子树*/
    /*在mid中寻找到根位置(mid中一定有根存在,所以不需要判断mid_root_pos越界)*/
    while (midStr[mid_root_pos] != postStr[post_root_pos])
    {
        mid_root_pos++;
    }
    /*后序里左子树的起始和结束*/
    int pls = pi, ple = pi + (mid_root_pos - mi) - 1;
    /*中序里左子树的起始和结束*/
    int mls = mi, mle = mid_root_pos - 1;
    /*后序里右子树的起始和结束*/
    int prs = ple + 1, pre = post_root_pos - 1;
    /*中序里右子树的起始和结束*/
    int mrs = mid_root_pos + 1, mre = mj;
    /*左子树建立*/
    if (mid_root_pos == mi) //当中序起始为root时，左儿子为空
        rootNode->lchild = NULL;
    else
        rootNode->lchild = createByMid_Post(midStr, postStr, mls, mle, pls, ple, rootNode->lchild);
    /*右子树建立*/
    if (mid_root_pos == mj) //当中序结束为root时，右儿子为空
        rootNode->rchild = NULL;
    else
        rootNode->rchild = createByMid_Post(midStr, postStr, mrs, mre, prs, pre, rootNode->rchild);

    return rootNode;
}

BiNode *createByLevel(char str[], int length, BiNode *&rootNode)
{
    /*二叉树编号从1开始,i为某结点编号,那么2i为左孩子,2i+1为右孩子
    **若i为孩子结点,那么i/2为左孩子,(i-1)/2为右孩子*/
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
/*在遍历时，一个结点是左右孩子结点的同时，也是一个根结点
**当这个结点不存在时，先作为它父结点的左孩子或右孩子不存在:
**上一次遍历作为左结点进入，但经过判断不存在就是作为左孩子不存在
**上一次遍历作为右结点进入，但经过判断不存在就是作为右孩子不存在
**即:if(r == NULL)为真,就看r是由上一次r=r->lchild得到还是由r=r->rchild
**当这个结点存在时，先作为根(父)结点存在
*/
/*DLR特点:当左子树存在的时候，先作为根节点输出
**补充:除去root结点之外，一个结点在作为它父结点的左孩子判断的之前，
**已经作为它孩子结点的根结点输出了所以当它不存在时，只需要判断右子树。
*/
void preOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //作为根结点存在
        {
            Visit(r);       //先输出根结点
            Push(stack, r); //根结点入栈，因为右孩子还未访问
            r = r->lchild;  //访问左孩子
        }
        else //作为根结点不存在，同时作为它父结点的左孩子或右孩子不存在
        {
            Pop(stack, r); //此时该父结点自身和左孩子访问过了，父结点出栈访问右孩子，
            r = r->rchild;
        }
    }
}
/*LDR特点:当左子树不存在时，先作为根节点输出，再判断右子树*/
void inOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //作为根结点存在
        {
            Push(stack, r); //根结点入栈
            r = r->lchild;  //先访问左孩子
        }
        else //作为根结点不存在，同时作为父结点的左孩子或右孩子不存在
        {
            Pop(stack, r); //输出根结点
            Visit(r);
            r = r->rchild; //访问右孩子
        }
    }
}
/*LRD特点:当左右子树均不存在时，作为根节点输出，然后再判断右子树*/
void postOrd2(BiTree root)
{
    SqStack stack;
    InitStack(stack);
    BiTree r = root;
    BiNode *visited = NULL;
    while (r != NULL || !StackEmpty(stack))
    {
        if (r != NULL) //根结点存在
        {
            Push(stack, r); //根结点入栈
            r = r->lchild;  //先访问左孩子
        }
        else //根结点不存在也是作为父结点的左孩子不存在，所以判断访问右子树
        {
            //(左孩子被访问过或者左孩子不存在)返回根结点，访问右孩子，因为根还没有输出，所以根不能出栈
            GetTop(stack, r);
            if (r->rchild && r->rchild != visited) //有右孩子并且未访问过
            {
                r = r->rchild;
            }
            else //没有右孩子或者右孩子被访问过
            {
                Pop(stack, r); //输出结点
                Visit(r);
                visited = r; //记录该结点被访问过(也是作为根结点和父结点的左右孩子被访问过)
                r = NULL;    //目的是从栈顶获取上一次根结点，且下次进入判断访问右子树
                //不可以GetTop(stack, r);若使用则下一次循环又会访问该根结点的左孩子
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
    /*front指向对头，rear指向队尾的下一个位置*/
    S.front = S.rear = 0;
}

bool QueueEmpty(SqQueue &S)
{
    if (S.rear == S.front) //循环队列判空
        return true;
    return false;
}

bool EnQueue(SqQueue &S, QueElemType data)
{
    if (S.front == (S.rear + 1) % MaxSize) //循环队列判满
        return false;
    S.data[S.rear] = data;
    S.rear = (S.rear + 1) % MaxSize; //形成循环
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

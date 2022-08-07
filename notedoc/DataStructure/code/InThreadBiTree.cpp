#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 10;

typedef char ElemType;

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;

void Visit(ThreadNode *r);
/*中序非线索遍历*/
void ThreadIndOrd(ThreadNode *r)
{
    if (r == NULL)
        return;
    if (r->ltag == 0)
        ThreadIndOrd(r->lchild);
    Visit(r);
    if (r->rtag == 0)
        ThreadIndOrd(r->rchild);
}

void ThreadTreeFree(ThreadTree &root)
{
    if (root == NULL)
        return;
    if (root->ltag == 0)
        ThreadTreeFree(root->lchild);
    if (root->rtag == 0)
        ThreadTreeFree(root->rchild);
    free(root);
    root = NULL;
}

void printThreadLeaf(ThreadTree root)
{
    if (root == NULL)
        return;
    if (root->ltag == 1 && root->rtag == 1)
    {
        Visit(root);
        return;
    }
    if (root->ltag == 0)
        printThreadLeaf(root->lchild);
    if (root->rtag == 0)
        printThreadLeaf(root->rchild);
}

int getThreadDepth(ThreadTree root)
{
    if (root == NULL)
        return 0;
    int lh = 0, rh = 0;
    if (root->ltag == 0)
        lh = getThreadDepth(root->lchild);
    if (root->rtag == 0)
        rh = getThreadDepth(root->rchild);
    return max(lh, rh) + 1;
}

ThreadNode *createByPre_Mid(char preStr[], char midStr[], int pi, int pj, int mi, int mj, ThreadNode *&rootNode)
{
    /*对于pre来说pi为根位置,对于mid来说mi为初始值*/
    int pre_root_pos = pi, mid_root_pos = mi;
    /*生成root结点*/
    rootNode = (ThreadNode *)malloc(sizeof(ThreadNode));
    rootNode->data = preStr[pre_root_pos];
    rootNode->ltag = 0, rootNode->rtag = 0; //初始化线索
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

ThreadNode *createByMid_Post(char midStr[], char postStr[], int mi, int mj, int pi, int pj, ThreadNode *&rootNode)
{
    /*对于post来说pj为根位置,对于mid来说mi为初始值*/
    int post_root_pos = pj, mid_root_pos = mi;
    /*生成root结点*/
    rootNode = (ThreadNode *)malloc(sizeof(ThreadNode));
    rootNode->data = postStr[post_root_pos];
    rootNode->ltag = 0, rootNode->rtag = 0; //初始化线索
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

ThreadNode *createByLevel(char str[], int length, ThreadNode *&rootNode)
{
    /*二叉树编号从1开始,i为某结点编号,那么2i为左孩子,2i+1为右孩子
    **若i为孩子结点,那么i/2为左孩子,(i-1)/2为右孩子*/
    ThreadNode *(que[MaxSize]) = {NULL};
    ThreadNode *newNode = NULL;
    for (int i = 1; i <= length; i++)
    {
        newNode = (ThreadNode *)malloc(sizeof(ThreadNode));
        newNode->data = str[i - 1];
        newNode->ltag = 0, newNode->rtag = 0; //初始化线索
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

/*中序线索二叉树*/
/*传入的是根结点和前驱节点：根节点是前驱节点的后继。算法在线索化的时候，
**并不是同时建立根节点的前驱和后继，而是建立根节点的前驱和根节点前驱的后继。
**即是:root前驱->pre,pre后继->root
*/
void InTread(ThreadTree &root, ThreadTree &pre)
{
    if (root == NULL)
        return;
    InTread(root->lchild, pre); //先递归线索化左子树
    if (root->lchild == NULL)
    {
        root->ltag = 1;
        root->lchild = pre;
    }
    if (pre != NULL && pre->rchild == NULL)
    {
        pre->rtag = 1;
        pre->rchild = root;
    }
    pre = root;                 // LDR:右子树的前驱是D(root),左子树的最后一个节点也是根节点的前驱
    InTread(root->rchild, pre); //递归线索右子树
}
/**/
ThreadTree CreateInThread(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    ThreadNode *pre = NULL;
    InTread(root, pre);
    pre->rchild = NULL; //处理最后一个结点的后继节点
    pre->rtag = 1;
    return root;
}
/*中序遍历：第一个没有左孩子的节点为中序遍历结果的第一个节点,
**其实就是从根节点一直项左遍历直到结点没有左孩子*/
ThreadNode *FirstNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    /*当ltag=0时，说明有左孩子，就不会是第一个节点，继续循环。直到ltag=1*/
    /*若在创建结点的时候没有对ltag和rtag进行初始化，那么不能使用while(!root.ltag)作为判断*/
    while (root->ltag == 0)
        root = root->lchild;
    return root;
}
/*中序遍历：最后一个没有右孩子的节点为中序遍历结果的最后一个节点，
**其实就是从根节点一直向右遍历直到结点没有右孩子*/
ThreadNode *LastNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    while (root->rtag == 0)
        root = root->rchild;
    return root;
}
/*中序遍历:由于有左孩子就会进入递归，所以一个结点的前驱不一定就是左孩子
**如果该节点的ltag=1说明其左孩子就是前驱，否则其左子树的中序遍历的最后一个节点
**为该节点的前驱*/
ThreadNode *PreNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    if (root->ltag == 1)
        return root->lchild;
    else
        return LastNode(root->lchild);
}
/*中序遍历:由于由左孩子就会进入递归，所以一个结点的后继不一定就是右孩子
**如果该节点的rtag=1说明其右孩子就是后继，否则其右子树的中序遍历的第一个节点
**为该节点的后继*/
ThreadNode *NextNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    if (root->rtag == 1)
        return root->rchild;
    else
        return FirstNode(root->rchild);
}
/*中序线索遍历*/
void InOrder(ThreadTree root)
{
    for (ThreadNode *p = FirstNode(root); p != NULL; p = NextNode(p))
        Visit(p);
}

int main()
{
    ThreadTree root = NULL;
    // createByPre_Mid("ABCDEFGH", "BDCEAFHG", 0, 7, 0, 7, root);
    //  createByMid_Post("BDCEAFHG", "DECBHGFA", 0, 7, 0, 7, root);
    //  createByMid_Post("BACDE", "BEDCA", 0, 4, 0, 4, root);
    createByLevel("ABCDEFGH", 8, root);
    ThreadTree throot = CreateInThread(root);
    cout << "中序遍历:";
    ThreadIndOrd(root);
    cout << endl;
    cout << "FirstNode:" << FirstNode(throot)->data << endl;
    cout << "LastNode:" << LastNode(throot)->data << endl;
    cout << "中序线索遍历:";
    InOrder(throot);
    cout << endl
         << "叶子节点: ";
    printThreadLeaf(throot);
    cout << endl
         << "深度:" << getThreadDepth(throot);

    ThreadTreeFree(root);
    return 0;
}

void Visit(ThreadNode *r)
{
    cout << r->data << " ";
}

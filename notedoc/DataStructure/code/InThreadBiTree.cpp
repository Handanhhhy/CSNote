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
/*�������������*/
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
    /*����pre��˵piΪ��λ��,����mid��˵miΪ��ʼֵ*/
    int pre_root_pos = pi, mid_root_pos = mi;
    /*����root���*/
    rootNode = (ThreadNode *)malloc(sizeof(ThreadNode));
    rootNode->data = preStr[pre_root_pos];
    rootNode->ltag = 0, rootNode->rtag = 0; //��ʼ������
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

ThreadNode *createByMid_Post(char midStr[], char postStr[], int mi, int mj, int pi, int pj, ThreadNode *&rootNode)
{
    /*����post��˵pjΪ��λ��,����mid��˵miΪ��ʼֵ*/
    int post_root_pos = pj, mid_root_pos = mi;
    /*����root���*/
    rootNode = (ThreadNode *)malloc(sizeof(ThreadNode));
    rootNode->data = postStr[post_root_pos];
    rootNode->ltag = 0, rootNode->rtag = 0; //��ʼ������
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

ThreadNode *createByLevel(char str[], int length, ThreadNode *&rootNode)
{
    /*��������Ŵ�1��ʼ,iΪĳ�����,��ô2iΪ����,2i+1Ϊ�Һ���
    **��iΪ���ӽ��,��ôi/2Ϊ����,(i-1)/2Ϊ�Һ���*/
    ThreadNode *(que[MaxSize]) = {NULL};
    ThreadNode *newNode = NULL;
    for (int i = 1; i <= length; i++)
    {
        newNode = (ThreadNode *)malloc(sizeof(ThreadNode));
        newNode->data = str[i - 1];
        newNode->ltag = 0, newNode->rtag = 0; //��ʼ������
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

/*��������������*/
/*������Ǹ�����ǰ���ڵ㣺���ڵ���ǰ���ڵ�ĺ�̡��㷨����������ʱ��
**������ͬʱ�������ڵ��ǰ���ͺ�̣����ǽ������ڵ��ǰ���͸��ڵ�ǰ���ĺ�̡�
**����:rootǰ��->pre,pre���->root
*/
void InTread(ThreadTree &root, ThreadTree &pre)
{
    if (root == NULL)
        return;
    InTread(root->lchild, pre); //�ȵݹ�������������
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
    pre = root;                 // LDR:��������ǰ����D(root),�����������һ���ڵ�Ҳ�Ǹ��ڵ��ǰ��
    InTread(root->rchild, pre); //�ݹ�����������
}
/**/
ThreadTree CreateInThread(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    ThreadNode *pre = NULL;
    InTread(root, pre);
    pre->rchild = NULL; //�������һ�����ĺ�̽ڵ�
    pre->rtag = 1;
    return root;
}
/*�����������һ��û�����ӵĽڵ�Ϊ�����������ĵ�һ���ڵ�,
**��ʵ���ǴӸ��ڵ�һֱ�������ֱ�����û������*/
ThreadNode *FirstNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    /*��ltag=0ʱ��˵�������ӣ��Ͳ����ǵ�һ���ڵ㣬����ѭ����ֱ��ltag=1*/
    /*���ڴ�������ʱ��û�ж�ltag��rtag���г�ʼ������ô����ʹ��while(!root.ltag)��Ϊ�ж�*/
    while (root->ltag == 0)
        root = root->lchild;
    return root;
}
/*������������һ��û���Һ��ӵĽڵ�Ϊ���������������һ���ڵ㣬
**��ʵ���ǴӸ��ڵ�һֱ���ұ���ֱ�����û���Һ���*/
ThreadNode *LastNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    while (root->rtag == 0)
        root = root->rchild;
    return root;
}
/*�������:���������Ӿͻ����ݹ飬����һ������ǰ����һ����������
**����ýڵ��ltag=1˵�������Ӿ���ǰ������������������������������һ���ڵ�
**Ϊ�ýڵ��ǰ��*/
ThreadNode *PreNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    if (root->ltag == 1)
        return root->lchild;
    else
        return LastNode(root->lchild);
}
/*�������:���������Ӿͻ����ݹ飬����һ�����ĺ�̲�һ�������Һ���
**����ýڵ��rtag=1˵�����Һ��Ӿ��Ǻ�̣�����������������������ĵ�һ���ڵ�
**Ϊ�ýڵ�ĺ��*/
ThreadNode *NextNode(ThreadTree root)
{
    if (root == NULL)
        return NULL;
    if (root->rtag == 1)
        return root->rchild;
    else
        return FirstNode(root->rchild);
}
/*������������*/
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
    cout << "�������:";
    ThreadIndOrd(root);
    cout << endl;
    cout << "FirstNode:" << FirstNode(throot)->data << endl;
    cout << "LastNode:" << LastNode(throot)->data << endl;
    cout << "������������:";
    InOrder(throot);
    cout << endl
         << "Ҷ�ӽڵ�: ";
    printThreadLeaf(throot);
    cout << endl
         << "���:" << getThreadDepth(throot);

    ThreadTreeFree(root);
    return 0;
}

void Visit(ThreadNode *r)
{
    cout << r->data << " ";
}

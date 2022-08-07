#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

const int MaxSize = 10;
typedef int BiNodeElemType;
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

void Free(BiTree &r)
{
    if (r == NULL)
        return;
    Free(r->rchild);
    Free(r->lchild);
    free(r);
    r = NULL;
}

BiNode *insert(BiNode *&r, BiNodeElemType data)
{
    if (r == NULL)
    {
        r = (BiNode *)malloc(sizeof(BiNode));
        r->data = data;
        r->lchild = NULL, r->rchild = NULL;
        return r;
    }
    if (data == r->data)
        return r;
    else if (data > r->data)
        return insert(r->rchild, data);
    else
        return insert(r->lchild, data);
}

BiTree CreateSortTree(BiTree &root, BiNodeElemType datas[], int length)
{
    for (int i = 0; i < length; i++)
        insert(root, datas[i]);
}
/*在二叉排序树中查找关键字key,若没有找到则插入*/
BiNode *BsTree_search(BiTree &root, BiNodeElemType key)
{
    if (root == NULL)
    {
        return insert(root, key);
    }
    else
    {
        BiTree p = root;
        while (p != NULL && key != p->data)
        {
            if (key < p->data)
                p = p->lchild;
            else
                p = p->rchild;
        }
        if (p == NULL)
            return insert(root, key);
        else
            return p;
    }
}
BiNode *FindMin(BiTree root)
{
    if (root == NULL)
        return root;
    while (root->lchild != NULL) /*左子树的值都小于根节点*/
        root = root->lchild;
    return root;
}
/*被删除的节点情况分为：没有子树，只有一棵子树，有两棵子树
**没有子树直接删除；有一棵子树则直接将子树填充到被删除的节点处；
**左右子树均存在，在右子树中寻找最小的值代替被删除的位置:
**因为被删除节点的右子树最小值均大于其左子树的值，
**又均小于右子树其他值，并且保证了最多只会有一棵子树
**(这里最小值结点若有子树，一定时有右子树)
**返回值:返回指向被删除结点的指针
*/
BiNode *BsTree_Delete(BiTree root, BiNodeElemType key)
{
    if (root == NULL)
        return NULL;
    if (key < root->data)
        root->lchild = BsTree_Delete(root->lchild, key);
    else if (key > root->data)
        root->rchild = BsTree_Delete(root->rchild, key);
    else // root为被删除节点
    {
        /*左右子树均存在*/
        if (root->lchild && root->rchild)
        {
            BiNode *p = FindMin(root->rchild);                      //寻找右子树中最小值
            root->data = p->data;                                   //将最小值赋值给被删除结点
            root->rchild = BsTree_Delete(root->rchild, root->data); //将右子树最小值结点删除
        }
        else //只有一个节点或者没有节点
        {
            BiNode *delp = root;
            if (!root->lchild) //没有左子树但有右子树或者没有子树
                root = root->rchild;
            else if (!root->rchild) //没有右子树但有左子树或者没有子树
                root = root->lchild;
            free(delp);
            delp = NULL;
        }
    }
    return root;
}

int main()
{
    BiTree root = NULL;
    BiNodeElemType datas[MaxSize] = {6, 2, 4, 8, 1, 5, 2, 7, 0, 3};
    cout << "-----------------------CreateBST-----------------------" << endl;
    CreateSortTree(root, datas, MaxSize);
    inOrd(root);
    cout << endl;
    preOrd(root);
    cout << endl
         << "-----------------------BsTree_search-----------------------" << endl;
    BsTree_search(root, 9);
    inOrd(root);
    cout << endl;

    BsTree_search(root, 6);
    inOrd(root);

    cout << endl
         << "-----------------------BsTree_Delete-----------------------" << endl;
    BsTree_Delete(root, 7);
    inOrd(root);
    cout << endl;
    BsTree_Delete(root, 1);
    inOrd(root);
    cout << endl;
    BsTree_Delete(root, 2);
    inOrd(root);
    cout << endl;

    Free(root);
    return 0;
}

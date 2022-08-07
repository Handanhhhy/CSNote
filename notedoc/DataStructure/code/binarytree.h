#pragma once
#include<iostream>
const int maxsize = 100;

template<typename T>
class binarytree;
template<typename T>
class BinarySortTree;

template<typename T>
class binarynode
{
	friend binarytree<T>;
	friend BinarySortTree<T>;
public:
	binarynode<T>() : lchild(nullptr), rchild(nullptr) {};
	binarynode<T>(T& data) : data(data), lchild(nullptr), rchild(nullptr) {};
	~binarynode<T>() = default;
private:
	T data;
	binarynode<T> *lchild;
	binarynode<T> *rchild;
};

template<typename T>
class binarytree
{
public:
	binarytree() :str(nullptr), root(nullptr), numOfLeaf(0), strLength(0) {}
	binarytree(T * str, const size_t& length) :str(str), root(nullptr), numOfLeaf(0), strLength(length) { --strLength; }
	virtual	~binarytree() {
		if (root) {
			Free(root);
			root = nullptr;
		}
	}
	void setStr(T* str, const size_t& real_length) {
		this->str = str;
		this->strLength = real_length;
	}
	/*层次遍历创建二叉树*/
	virtual	void create() {
		if (strLength == 0 || str == nullptr)
			return;
		if (root != nullptr)
			clear();
		binarynode<T> *(que[maxsize]) = { nullptr };
		int front = 1, rear = 0;
		size_t pos = 0;
		binarynode<T> *node = nullptr;
		while (pos != strLength) {
			node = new binarynode<T>(str[pos]);
			rear++;
			que[rear] = node;
			if (rear == 1) {
				root = node;
			}
			else if (que[front]) {
				if (rear % 2) {
					que[front]->rchild = node;
					front++;
				}
				else {
					que[front]->lchild = node;
				}
			}
			pos++;
		}
	}
	void createByPre_Mid(const char _preOrd[], const char _midOrd[],
		int pi, int pj, int mi, int mj) {
		if (root != nullptr)
			clear();
		root = createByPre_Mid(_preOrd, _midOrd,
			pi, pj, mi, mj, root);
	}
	void createByMid_Suff(const char _midOrd[], const char suffix,
		int mi, int mj, int si, int sj) {
		if (root != nullptr)
			clear();
		root = createByMid_Suff(_midOrd, _midOrd,
			mi, mj, si, sj, root);
	}
	void printPre() {
		preOrd(root);
		std::cout << std::endl;
	}
	void printMid() {
		midOrd(root);
		std::cout << std::endl;
	}
	void printLa() {
		laOrd(root);
		std::cout << std::endl;
	}
	int getDepth() {
		return depth(root);
	}
	void showLeaf() {
		showLeaf(root);
		std::cout << std::endl << "Ҷ�ӽڵ����" << numOfLeaf;
	}
	//��Recursive�������
	void print_pre() {//DLR
		binarynode<T> *(stack[maxsize]) = { nullptr };
		int top = -1;
		if (root == nullptr)
			return;
		++top;
		stack[top] = root;
		binarynode<T> *node = nullptr;
		while (top != -1 && stack[top] != nullptr) {
			node = stack[top];
			std::cout << node->data << " ";
			while (node->lchild != nullptr) {//��������������������ջ
				stack[++top] = node->lchild;
				std::cout << stack[top]->data << " ";
				node = stack[top];
			}
			while (top != -1 && stack[top]->rchild == nullptr) --top;
			if (top != -1) {//�����Һ������Һ��ӽ�ջ
				node = stack[top]->rchild;
				stack[top] = node;
			}
		}
		std::cout << std::endl;
	}
	void print_mid() {
		binarynode<T> *(stack[maxsize]) = { nullptr };
		int top = -1;
		if (root == nullptr)
			return;
		++top;
		stack[top] = root;
		binarynode<T> *node = nullptr;
		while (top != -1 && stack[top] != nullptr) {
			node = stack[top];
			while (node->lchild != nullptr) {//��������������������ջ
				stack[++top] = node->lchild;
				node = stack[top];
			}
			while (top != -1 && stack[top]->rchild == nullptr) {//���Һ������Ԫ�غ��ջ
				std::cout << stack[top]->data << " ";
				--top;
			}
			if (top != -1) {//�����Һ����򽫸��ڵ��ջ�����Һ��ӽ�ջ
				std::cout << stack[top]->data << " ";
				node = stack[top]->rchild;
				stack[top] = node;
			}
		}
		std::cout << std::endl;
	}
	void print_La() {
		binarynode<T> *(stack[maxsize]) = { nullptr };
		int top = -1;
		if (root == nullptr)
			return;
		++top;
		stack[top] = root;
		binarynode<T> *node = nullptr;
		while (top != -1 && stack[top] != nullptr) {
			node = stack[top];
			while (node->lchild != nullptr) {//��������������������ջ
				stack[++top] = node->lchild;
				node = stack[top];
			}
			while (top != -1 && stack[top]->rchild == nullptr) {
				std::cout << stack[top]->data << " ";
				--top;
			}
			if (top != -1) {//�����Һ������Һ��ӽ�ջ
				node = stack[top];
				stack[++top] = node->rchild;
				node->rchild = nullptr;//�����ڵ���Һ�����Ϊ�մ����Ѿ����ʹ��Һ��ӽڵ�
			}
		}
		std::cout << std::endl;
		binarytree::create();
	}
	void print_Floor() {
		if (root == nullptr)
			return;
		binarynode<T> *(que[maxsize]) = { nullptr };
		int front = 0, rear = -1;
		que[++rear] = root;
		binarynode<T> *node = que[front];
		while (node != nullptr) {
			std::cout << node->data << " ";
			if (node->lchild != nullptr) {
				que[++rear] = node->lchild;
			}
			if (node->rchild != nullptr) {
				que[++rear] = node->rchild;
			}
			front++;
			node = que[front];
		}
		std::cout << std::endl;
	}
	void clear() {
		if (root == nullptr)
			return;
		Free(root);
		root = nullptr;
	}
	bool isEmpty() {
		if (root == nullptr)
			return true;
		return false;
	}
protected:
	binarynode<T> *createByPre_Mid(const char _preOrd[], const char _midOrd[],
		int pi, int pj, int mi, int mj, binarynode<T> * r) {
		int rpos = mi;
		r = new binarynode<T>;
		r->data = _preOrd[pi];
		while (_midOrd[rpos] != _preOrd[pi]) {
			rpos++;
		}
		if (rpos == mj) {
			r->rchild = nullptr;//�Ҷ���Ϊ��
		}
		else {
			r->rchild = createByPre_Mid(_preOrd, _midOrd, pj - (mj - rpos) + 1, pj, rpos + 1, mj, r->rchild);
		}
		if (rpos == mi) {
			r->lchild = nullptr;//�����Ϊ��
		}
		else {
			r->lchild = createByPre_Mid(_preOrd, _midOrd, pi + 1, pj - (mj - rpos), mi, rpos - 1, r->lchild);
		}
		return r;
	}
	binarynode<T> *createByMid_Suff(const char _midOrd[], const char suffix[],
		int mi, int mj, int si, int sj, binarynode<T> * r) {
		int rpos = mi;
		r = new binarynode<T>;
		if (r == nullptr) {
			return nullptr;
		}
		r->date = suffix[sj];
		//Ѱ�������еĸ����
		while (_midOrd[rpos] != suffix[sj]) {
			rpos++;
		}
		if (rpos == mj) {
			r->rchild = nullptr;//�Ҷ���Ϊ��
		}
		else {
			r->rchild = createByMid_Suff(_midOrd, suffix, rpos + 1, mj, sj - (mj - rpos), sj - 1, r->rchild);
		}
		if (rpos == mi) {
			r->lchild = nullptr;//�����Ϊ��
		}
		else {
			r->lchild = createByMid_Suff(_midOrd, suffix, mi, rpos - 1, si, sj - (mj - rpos) - 1, r->lchild);
		}
		return r;
	}

	void preOrd(binarynode<T> * r) {
		if (r == nullptr) {
			return;
		}
		std::cout << r->data << " ";
		preOrd(r->lchild);
		preOrd(r->rchild);
	}
	void midOrd(binarynode<T> * r) {
		if (r == nullptr) {
			return;
		}
		midOrd(r->lchild);
		std::cout << r->data << " ";
		midOrd(r->rchild);
	}
	void laOrd(binarynode<T> * r) {
		if (r == nullptr) {
			return;
		}
		laOrd(r->lchild);
		laOrd(r->rchild);
		std::cout << r->data << " ";
	}
	int depth(binarynode<T> * r) {
		if (r == nullptr)
			return 0;
		if (r->lchild == nullptr&&r->rchild == nullptr)
			return 1;
		int dL = depth(r->lchild);
		int dR = depth(r->rchild);
		int h = (dL > dR ? dL : dR) + 1;
		return h;
	}
	void showLeaf(binarynode<T> * r) {
		if (r == nullptr)
			return;
		if (r->lchild == nullptr&&r->rchild == nullptr) {
			std::cout << r->data << " ";
			numOfLeaf++;
		}
		if (r->lchild) {
			showLeaf(r->lchild);
		}
		if (r->rchild) {
			showLeaf(r->rchild);
		}
	}
	void Free(binarynode<T> * r) {
		if (r == nullptr) {
			return;
		}

		Free(r->rchild);
		Free(r->lchild);
		delete r;
		r = nullptr;
	}
protected:
	binarynode<T>* root;
	T* str;
	int numOfLeaf;
	size_t strLength;
};


//#include <iostream>
//#include "binarytree.h"
//using namespace std;
//
//int main() {
//
// char s[100] = "ABCDEFGH";
// char *p = s;
// binarytree<char> tree(p, 8);
//	tree.create();
//	tree.printPre();
//	cout << endl;
//	tree.printMid();
//	cout << endl;
//	tree.printLa();
//	cout << endl;
//	cout << tree.getDepth();
//	cout << endl;
//	tree.showLeaf();
//	cout << endl;
//	tree.print_pre();
//	cout << endl;
//	tree.print_mid();
//	cout << endl;
//	tree.print_La();
//	cout << endl;
//	return 0;
//}
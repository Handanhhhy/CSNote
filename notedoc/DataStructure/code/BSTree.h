#pragma once
#include<iostream>
#include"binarytree.h"
template<typename T>
class BinarySortTree:public binarytree<T>
{
public:
	using binarytree<T>::binarytree;//继承构造
	~BinarySortTree() = default;
	virtual void create() override {
		if (this->root != nullptr)
			this->clear();
		for (int i = 0; i < this->strLength; i++) {
			insert(this->root, this->str[i]);
		}
	}
	bool search(T& data) {
		return insert(this->root, data);
	}
protected:
	bool insert(binarynode<T> *&node, T& data) {//*&node不会拷贝指针
		if (node == nullptr) {
			node = new binarynode<T>(data);
			return false;
		}
		if (data > node->data) {
			return insert(node->rchild, data);
		}
		else if (data < node->data) {
			return insert(node->lchild, data);
		}
		else {
			return true;
		}
	}
};

//#include <iostream>
//#include "BSTree.h"
//using namespace std;
//
//int main() {
//
//	char s[100] = "ABCDEFGH";
//	BinarySortTree<char> tree(s, 9);
//	tree.create();
//	tree.printPre();
//	cout << endl;
//	tree.printMid();
//	cout << endl;
//	tree.printLa();
//	cout << endl;
//	cout << "深度" << tree.getDepth();
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
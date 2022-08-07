#pragma once
#include<map>
#include<vector>

#define MAX 99999
#define INIT -1

template<typename T=char, typename C=int >
class HuffmanCode
{
protected:
	
	class RootNode
	{
	public:
		RootNode();
		RootNode(size_t weight);
		virtual ~RootNode();
	public:
		size_t weight;
		size_t parent;
		size_t lchild;
		size_t rchild;
	};
	class LeafNode :public RootNode
	{
	public:
		LeafNode();
		LeafNode(T data, size_t weight);
		~LeafNode();
	public:
		T data;
	};
	class HFCode
	{
	public:
		HFCode();
		HFCode(T data,std::vector<C> code);
		~HFCode();
		void data_code();
	public:
		T data;
		std::vector<C> code;;
		size_t size;
		T *dataCode;
	};

public:
	HuffmanCode(C codeOne = 0, C codeTwo = 1);
	HuffmanCode(T array[], size_t array_length);
	~HuffmanCode();
	void setArray(T array[], size_t array_length);
	void setCode(C codeOne, C codeTwo);
	void coding();
	//void print();
protected:
	void statistics();
	//在map中查询aim 若查询成功value++ 否则插入
	void find(T aim);
	void create();
	void preCode(size_t pos);
	void Free();
protected:
	T *codeArray;
	size_t length;
	size_t typeNum;
	C codeOne;
	C codeTwo;
	std::map< T, int> codeMap;
	RootNode *root;//数组结构较好处理
	size_t pos;
	std::vector<C> tempCode;
	std::vector<HFCode> hfCode;
};

template<typename T, typename C >
HuffmanCode<T, C>::HuffmanCode(C codeOne, C codeTwo)
{
	typeNum = 0;
	pos = 0; 
	codeArray = nullptr;
	root = nullptr;
	this->codeOne = codeOne;
	this->codeTwo = codeTwo;
}

template<typename T, typename C >
inline HuffmanCode<T, C>::HuffmanCode(T array[], size_t array_length)
{
	setArray(array, array_length);
}

template<typename T, typename C >
HuffmanCode<T, C>::~HuffmanCode()
{
	Free();
}

template<typename T, typename C >
inline void HuffmanCode<T, C>::setArray(T array[], size_t array_length)
{
	if (!this->codeMap.empty()) {
		this->codeMap.clear();
		Free();
	}
	this->codeArray = array;
	this->length = array_length;
	this->typeNum = 0;
	pos = 0;
	statistics();
}

template<typename T, typename C>
inline void HuffmanCode<T, C>::setCode(C codeOne, C codeTwo)
{
	this->codeOne = codeOne;
	this->codeTwo = codeTwo;
}

template<typename T, typename C >
inline void HuffmanCode<T, C>::coding()
{
	create();
	preCode(2 * typeNum - 2]);
}


/*template<typename T, typename C>
inline void HuffmanCode<T, C>::print()
{
	std::vector<HFCode>::iterator<HFCode> it = hfCode.begin();
	while (it != hfCode.end()) {
		for (int i = 0; i < it->size; i++) {
			std::cout << it->dataCode[i];
		}
		std::cout << std::endl;
	}
}*/

template<typename T, typename C >
inline void HuffmanCode<T, C>::statistics()
{
	for (int i = 0; i < length; i++) {
		find(codeArray[i]);
	}
}

template<typename T, typename C >
inline void HuffmanCode<T, C>::find(T aim)
{
	std::map<T, int>::iterator<T, int> it = codeMap.find(aim);
	if (it == codeMap.end()) {
		codeMap.insert(aim, 1);
		this->typeNum++;
	}
	else {
		codeMap[aim] = codeMap[aim] + 1;
	}
}

template<typename T, typename C >
inline void HuffmanCode<T, C>::create()
{
	if (length == 1) {
		return;
	}
	//创建叶结点 /*含有n个叶子结点的哈夫曼树有2n - 1个结点*/
	root = new RootNode[2 * typeNum - 1];
	std::map<T, int>::iterator<T, int> it = codeMap.begin();
	for (int i = 0; i < typeNum; i++, it++) {
		/*将叶子结点存放在下标0 -- typeNum-1处*/
		root[i] = new LeafNode(it->first, it->second);
	}
	for (int i = typeNum; i < 2 * typeNum - 1; i++) {
		int minOne = MAX, minTwo = MAX, curOne = 0, curTwo = 0;
		for (int j = 0; j < i; j++) {
			if (root[j].parent == -1 && root[j].weight < minOne) {
				minTwo = minOne, curTwo = curOne;
				/*第一个始终是最小的，在替换下一个最小的时候，将当前数赋值给第二小，避免丢失*/
				minOne = root[j].weight, curOne = j;
			}
			else if (root[j].parent == -1 && root[i].weight < minTwo) {
				minTwo = root[i].weight, curTwo = j;
			}
		}
		//构建新子树
		root[i] = new RootNode(minOne + minTwo);
		root[i].lchild = curOne;
		root[i].rchild = curTwo;
		root[curOne].parent = i;
		root[curTwo].parent = i;
	}
	
}

template<typename T, typename C>
inline void HuffmanCode<T, C>::preCode(size_t pos)
{
	if (pos == 0) {
		return;
	}
	if (root[pos].lchild == INIT&& root[pos].rchild == INIT) {
		hfCode.push_back(new HFCode(dynamic_cast<HFCode*>(root[pos])->data, tempCode));
		return;
	}
	if (root[pos].lchild != INIT) {
		tempCode.push_back(codeOne);
		preCode(root[pos].lchild);
	}

	if (root[pos].rchild != INIT) {
		tempCode.push_back(codeTwo);
		preCode(root[pos].rchild);
	}
	tempCode.pop_back();
}

template<typename T, typename C >
inline void HuffmanCode<T, C>::Free()
{
	if (root == nullptr)
		return;
	delete[] root;
	root = nullptr;
	tempCode.clear();
	hfCode.clear();
}

template<typename T, typename C >
inline HuffmanCode<T, C>::RootNode::RootNode()
{
	this->parent = INIT;
	this->rchild = INIT;
	this->lchild = INIT;
}

template<typename T, typename C >
inline HuffmanCode<T, C>::RootNode::RootNode(size_t weight)
{
	this->weight = weight;
	this->parent = INIT;
	this->rchild = INIT;
	this->lchild = INIT;
}

template<typename T, typename C >
inline HuffmanCode<T, C>::RootNode::~RootNode()
{
}

template<typename T, typename C >
inline HuffmanCode<T, C>::LeafNode::LeafNode()
{
}

template<typename T, typename C >
inline HuffmanCode<T, C>::LeafNode::LeafNode(T data, size_t weight)
{
	this->data = data;
	this->weight = weight;
}

template<typename T, typename C >
inline HuffmanCode<T, C>::LeafNode::~LeafNode()
{
}

template<typename T, typename C>
inline HuffmanCode<T, C>::HFCode::HFCode()
{
	dataCode = nullptr;
}

template<typename T, typename C>
inline HuffmanCode<T, C>::HFCode::HFCode(T data, std::vector<C> code)
{
	this->data = data;
	std::vector<C> temp(code);
	this->code.swap(temp);
	dataCode = nullptr;
	size = code.size();
	data_code();
}

template<typename T, typename C>
inline HuffmanCode<T, C>::HFCode::~HFCode()
{
	if (dataCode != nullptr) {
		delete[] dataCode;
	}
}

template<typename T, typename C>
inline void HuffmanCode<T, C>::HFCode::data_code()
{
	dataCode = new C[code.size() + 1];
	std::vector<C>::iterator<C> it = code.begin();
	for (int i = 0; i < size; i++, it++) {
		data[i] = *it;
	}
	std::vector<C> temp;
	this->code.swap(temp);
}

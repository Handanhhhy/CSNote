#pragma once
#include<string>

constexpr size_t STACK_SIZE = 100;
constexpr char FLOWER = 'F';
constexpr char OK = 'T';

template<typename T>

class Stack
{	
public:
	Stack();
	~Stack();
	T push(T a);
	T pop();
	T getTopEle()const;
	std::string getStr()const;
private:
	int top;
	T stack[STACK_SIZE];
};
template<typename T>
Stack<T>::Stack()
{
	this->top = -1;
}
template<typename T>
Stack<T>::~Stack()
{
}
template<typename T>
T Stack<T>::push(T a)
{
	// '\0'∑¿÷π‘ΩΩÁ
	if (top == STACK_SIZE - 2) {
		return FLOWER;
	}
	else {
		top++;
		stack[top] = a;
		stack[top + 1] = '\0';
		return OK;
	}
}
template<typename T>
T Stack<T>::pop()
{
	if (top == -1) {
		return FLOWER;
	}
	else {
		T temp = stack[top];
		stack[top] = '\0';
		top--;
		return temp;
	}
}
template<typename T>
T Stack<T>::getTopEle() const
{
	if (top == -1) {
		return FLOWER;
	}
	return stack[top];
}
template<typename T>
std::string Stack<T>::getStr()const
{
	std::string temp(stack);
	return temp;
}
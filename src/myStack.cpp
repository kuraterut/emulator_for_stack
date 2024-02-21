// #include "../include/myStack.hpp"




// template <typename DataType>
// myStack<DataType>::myStack(const DataType& cur_data){
// 	DataType *arr = new DataType[1];
// 	this->data = arr;
// 	this->data[0] = cur_data;
// 	this->size = 1;		
// }

// template <typename DataType>
// myStack<DataType>::~myStack(){
// 	if (data != nullptr){delete[] data;}
// 	size = 0;
// 	data = nullptr;
// }

// template <typename DataType>
// myStack<DataType>::myStack(const myStack<DataType>& stack){
// 	this->data = new DataType[stack.size];
// 	this->size = stack.size;
// 	std::copy(stack.data, this->size, this->data);
// }

// template <typename DataType>
// myStack<DataType>::myStack(myStack<DataType>&& stack){
// 	this->data = stack.data;
// 	this->size = stack.size;
// 	stack.size = 0;
// 	stack.data = nullptr;
// }

// template <typename DataType>
// myStack<DataType>& myStack<DataType>::operator=(const myStack<DataType>& stack){
// 	if(this == &stack){
// 		return *this;
// 	}
// 	delete[] this->data;
// 	this->data = new DataType[stack.size];
// 	this->size = stack.size;
// 	std::copy(stack.data, this->size, this->data);
// 	return *this;
// }

// template <typename DataType>
// myStack<DataType>& myStack<DataType>::operator=(myStack<DataType>&& stack){
// 	delete[] this->data;
// 	this->data = stack.data;
// 	this->size = stack.size;
// 	stack.size = 0;
// 	stack.data = nullptr;
// 	return *this;
// }

// template <typename DataType>
// void myStack<DataType>::push(const DataType& cur_data){
// 	if (this->size != 0){
// 		this->data++;
// 	}
// 	this->data[this->size] = cur_data;
// 	this->size++;
// }

// template <typename DataType>
// void myStack<DataType>::pop(){
// 	VERIFY_CONTRACT(this->size != 0, "Stack is empty");
// 	this->data--;
// 	this->size--;
	
// }

// template <typename DataType>
// DataType myStack<DataType>::top(){
// 	VERIFY_CONTRACT(this->size != 0, "Stack is empty");
// 	return this->data[this->size-1];
// }

// template <typename DataType>
// bool myStack<DataType>::is_empty(){
// 	return this->size == 0;
// }

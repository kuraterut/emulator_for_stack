#include <iostream>
#include "utils.hpp"
#include <algorithm>

template<typename DataType>
class myStack{
	private:
		DataType *data;
		unsigned int size;
	
	public:
		//Конструкторы и деструкторы:
		myStack() {
			this->data = new DataType[1]; 
			this->size = 0;
		}
		
		myStack(const DataType& cur_data){
			this->data = new DataType[1];
			this->data[0] = cur_data;
			this->size = 1;		
		}

		~myStack(){
			delete[] this->data;
		}

		//Конструктор копирования и перемещения
		myStack(const myStack<DataType>& stack){
			this->data = new DataType[stack.size];
			this->size = stack.size;
			std::copy_n(stack.data, this->size, this->data);
		}

		myStack(myStack<DataType>&& stack){
			this->data = stack.data;
			this->size = stack.size;
			stack.size = 0;
			stack.data = nullptr;
		}

		//Копирование и перемещение с присваиванием
		myStack<DataType>& operator=(const myStack<DataType>& stack){
			if(this == &stack){
				return *this;
			}
			delete this->data;
			this->data = new DataType[stack.size];
			this->size = stack.size;
			std::copy(stack.data, this->size, this->data);
			return *this;
		}
		

		myStack<DataType>& operator=(myStack<DataType>&& stack){
			if(this != &stack){
				delete[] this->data;
				this->data = stack.data;
				this->size = stack.size;
				stack.size = 0;
				stack.data = nullptr;
			}
			return *this;
		}

		
		void push(const DataType& cur_data){
			if (this->size != 0){
				DataType *new_arr = new DataType[this->size+1];
				std::copy_n(this->data, this->size, new_arr);
				delete[] this->data;
				this->data = new_arr;
			}
			this->data[this->size] = cur_data;
			this->size++;
		}

		void pop(){
			VERIFY_CONTRACT(this->size != 0, "Stack is empty");
			DataType *less_arr = new DataType[this->size-1];
			std::copy_n(this->data, this->size-1, less_arr);
			delete[] this->data;
			this->data = less_arr;
			this->size--;
		}

		DataType top(){
			VERIFY_CONTRACT(this->size != 0, "Stack is empty");
			return this->data[this->size-1];
		}

		bool is_empty(){
			return this->size == 0;
		}

		unsigned int stack_size(){
			return this->size;
		}
};

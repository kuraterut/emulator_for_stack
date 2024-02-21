#include "../include/myStack.hpp"
#include <iostream>
#include <ctime>
#include <typeinfo>

int main(){
	myStack<int> S;
	S.push(7);
	myStack<int> K(S);
	std::cout<< K.top() << std::endl;

	return 0;
}
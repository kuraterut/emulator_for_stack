#include "../include/myStack.hpp"
#include <iostream>
#include <ctime>
#include <typeinfo>

int main(){
	myStack<int> S;
	S.push(7);
	S.push(15);
	S.pop();
	S.pop();
	// std::cout<< S.top() << std::endl;

	return 0;
}
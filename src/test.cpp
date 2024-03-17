#include <iostream>
#include <ctime>
#include <typeinfo>
#include <vector>

#include "../include/test_system.hpp"
#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/emulator.hpp"
//------------------------------------------
// Creating and Assignment testing functions
//------------------------------------------

using namespace TestSystem;

bool test_empty_stack(){    
    myStack<int> I;
    myStack<long> L;
    myStack<long long> LL;
    myStack<char> c;
    myStack<char*> C;
    myStack<double> D;
    myStack<std::string> S;
    myStack<std::vector<int>> V;
    return OK;
}

bool test_start_val_stack(){
    myStack<int> I(52);
    myStack<long> L(52);
    myStack<long long> LL(52);
    myStack<char> c('c');
    char* arr_ch = new char[1];
    myStack<char*> C(arr_ch);
    myStack<double> D(52.0);
    myStack<std::string> S(std::string("asf"));
    std::vector<int> vec;
    myStack<std::vector<int>> V(vec);

    return OK;
}

bool test_constructor_copy(){
	myStack<long long> LL(52);
    myStack<char> c('c');
	myStack<long long> LL1(LL);
	myStack<char> c1(c);
    return OK;
}

bool test_constructor_move(){
	myStack<long long> LL(52);
    myStack<char> c('c');
	myStack<long long> LL1(std::move(LL));
	myStack<char> c1(std::move(c));
    return OK;
}

bool test_assignment_copy(){
	myStack<long long> LL(52);
    myStack<char> c('c');
	myStack<long long> LL1 = LL;
	myStack<char> c1 = c;
    return OK;
}

bool test_assignment_move(){
	myStack<long long> LL(52);
    myStack<char> c('c');
	myStack<long long> LL1 = std::move(LL);
	myStack<char> c1 = std::move(c);
    return OK;
}

//------------------------------
// Test standard stack functions
//------------------------------



bool test_push(){
    myStack<long long> LL(52);
    myStack<char> C;
    C.push('c');
    LL.push(71);
    return (C.top() == 'c' && C.stack_size() == 1 && LL.top() == 71 && LL.stack_size() == 2)? OK : FAIL;
}


// bool test_push_err(){
//     myStack<long long> LL;
//     try{
//     	char k = '7';
//         LL.push(k);
//         std::cout<< LL.top() << std::endl;
//     }

//     catch (...){
//         return OK;
//     }

//     return FAIL;
// }

bool test_pop(){
    myStack<long long> LL(52);
    myStack<char> C;
    C.push('c');
    LL.push(71);
    LL.push(31);
    LL.pop();
    C.pop();
    return (C.is_empty() && LL.top() == 71 && LL.stack_size() == 2)? OK : FAIL;
}

bool test_pop_err(){
    myStack<long long> LL(52);
    try{
        LL.pop();
        LL.pop();
    }

    catch (...){
        return OK;
    }

    return FAIL;
}

bool test_get_top(){
    myStack<long long> LL(52);
    long ans1 = LL.top();
    LL.push(71);
    long ans2 = LL.top();
    LL.push(31);
    long ans3 = LL.top();
    LL.pop();
    long ans4 = LL.top();
    return (ans1 == 52 && ans2 == 71 && ans3 == 31 && ans4 == 71)? OK : FAIL;
}

bool test_get_top_err(){
    myStack<long long> LL(52);
    try{
        LL.pop();
        long long a = LL.top();
    }

    catch (...){
        return OK;
    }

    return FAIL;
}

//--------------------------
// Test Additional functions
//--------------------------

bool test_is_empty(){
    myStack<long long> LL1(52);
    myStack<long long> LL2;
	bool check1 = LL1.is_empty();
    bool check2 = LL2.is_empty();
    LL1.pop();
    bool check3 = LL1.is_empty();
    return (&check1 && check2 && check3)? OK : FAIL;
}

bool test_stack_size(){
    myStack<long long> LL1(52);
    myStack<long long> LL2;

    int check1 = LL1.stack_size();
    int check2 = LL2.stack_size();
    LL1.push(41);
    LL1.push(41);
    int check3 = LL1.stack_size();
    LL1.pop();
    int check4 = LL1.stack_size();
    return (check1 == 1 && check2 == 0 && check3 == 3 && check4 == 2)? OK : FAIL;
}

//--------------
// Test palette
//--------------

int main(void)
{
    // Creating and assignment tests
    // run_test("create empty Stack",                        test_empty_stack        );
    // run_test("create Stack with start value",             test_start_val_stack    );
    // run_test("constructor copy",                          test_constructor_copy   );
    // run_test("constructor move",                          test_constructor_move   );
    // run_test("copy with assignment",                      test_assignment_copy    );
    // run_test("move with assignment",                      test_assignment_move    );
    
    // run_test("push elements",                             test_push               );
    // // run_test("try to push difftype elements",             test_push_err           );
    // run_test("pop elements",                              test_pop                );
    // run_test("try to pop empty stack",                    test_pop_err            );
    // run_test("get top element of stack",                  test_get_top            );
    // run_test("try to get top of empty stack",             test_get_top_err        );

    // run_test("check stack size",                          test_is_empty           );
    // run_test("check stack is empty",                      test_stack_size         );
    
    // Parser parser("emulator_test.test");

    // Parser parser("fibonacci_test_1_12.test");
    Parser parser("factorial.test");

    // Parser parser("help.test");

    Emulator eml(parser.parse_programm());

    
    eml.run();


    return EXIT_SUCCESS;
}
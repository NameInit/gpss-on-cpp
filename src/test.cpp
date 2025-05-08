#include "List.h"
#include <iomanip>
#include <iostream>
#define GET_VAR_NAME(var) #var

class test
{
private:
    int& _a;
public:
    test(int& a) : _a(a) {}
    int a(){return _a;}
};

class test2
{
private:
    int& _a;
public:
    test2(int& a) : _a(a) {}
    int a(){return _a;}
};

int main() {
    // std::cout<<std::right;
    // std::cout<<std::setw(5)<<' ';
    // std::cout<<10<<std::endl;
    // std::cout<<std::setw(5)<<' ';
    // std::cout<<111<<std::endl;
    // std::cout<<std::setw(5)<<' ';
    // std::cout<<1111<<std::endl;
    int b=5;
    test2 a(b);
    std::cout<<a.a()<<std::endl;
    b+=1;
    std::cout<<a.a()<<std::endl;
    return 0;
}
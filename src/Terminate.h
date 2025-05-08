#ifndef TERMINATE_H
#define TERMINATE_H

#include "Tranzakt.h"


class Terminate{
    private:
        int* __counter;
    public:
        Terminate() : __counter(nullptr) {}
        void link_counter(int* counter);
        void operator()(Tranzakt* tranzakt, int n);
};

void Terminate::link_counter(int* counter){
    __counter=counter;
}

void Terminate::operator()(Tranzakt* tranzakt, int n){
    *__counter-=n;
    delete tranzakt;
}

#endif
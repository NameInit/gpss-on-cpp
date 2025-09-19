#include "../headers/Terminate.h"

void Terminate::link_counter(int* counter){
    __counter=counter;
}

void Terminate::operator()(Tranzakt* tranzakt, int n){
    *__counter-=n;
    delete tranzakt;
}
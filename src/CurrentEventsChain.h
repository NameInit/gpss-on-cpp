#ifndef CURRENT_EVENTS_CHAIN_H
#define CURRENT_EVENTS_CHAIN_H

#include <stdexcept>
#include <random>
#include <fstream>
#include <iomanip>

#include "List.h"
#include "Tranzakt.h"
#include "FutureEventsChain.h"
#include "MyStorage.h"

class CurrentEventsChain{
    private:
        List<Tranzakt*> list;
    public:
        CurrentEventsChain() : list() {}
        Tranzakt* pop(int n);
        void push(Tranzakt* tranzakt); //tail
        bool can_promote(MyStorage* storage);
        Tranzakt* operator[](int n);
        unsigned size();
        void write_in_file(std::ofstream& output);
};

void CurrentEventsChain::write_in_file(std::ofstream& output){
    output<<"CEC:"<<std::endl;
    output<<std::right;
    if(size()==0){
        output<<std::setw(4)<<' ';
        output<<(const char*)"<void>"<<std::endl;
    }
    else
        for(int i=0; i<size(); i++){
            output<<std::setw(4)<<' ';
            output<<*list[i]<<std::endl;
        }
    output<<std::left;
}

unsigned CurrentEventsChain::size(){
    return list.size();
}

Tranzakt* CurrentEventsChain::operator[](int n){
    if(n<0 || n>=list.size()){
        throw std::logic_error("index out of range in CurrentEventsChain::operator[]");
    }
    return list[n];
}

Tranzakt* CurrentEventsChain::pop(int n){
    if(n<0 || n>=list.size()){
        throw std::logic_error("index out of range in CurrentEventsChain::pop");
    }
    return list.pop(n);
}

void CurrentEventsChain::push(Tranzakt* tranzakt){
    list.push_tail(tranzakt);
}

bool CurrentEventsChain::can_promote(MyStorage* storage){
    for(int i=0; i<list.size(); i++){
        if(!(list[i]->current_block()==(const char*)"ENTER" && storage[list[i]->index_blocks()].count_free_space()==0))
            return true;
    }
    return false;
}

#endif
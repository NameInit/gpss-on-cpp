#ifndef STORAGE_H
#define STORAGE_H

#include <stdexcept>

#include "Tranzakt.h"
#include "List.h"


class MyStorage{
    private:
        unsigned __len_storage;
        List<Tranzakt*> __content;
        static unsigned __len_storages;
    public:
        MyStorage() : __len_storage(0), __content() {__len_storages+=1;}
        MyStorage(int n);

        bool have_free_space() { return count_free_space()>0; }
        void set_max_size(int n);
        unsigned len_storages(){ return __len_storages; }
        
        unsigned count_free_space();
        void push(Tranzakt* tranzakt);
        void pop(Tranzakt* tranzakt);
        bool have(Tranzakt* tranzakt);
};

unsigned MyStorage::__len_storages=0; 

MyStorage::MyStorage(int n) : __len_storage(n), __content() {
    if(n<=0){
        std::logic_error("size storage must be positive integer");
    }
}

void MyStorage::set_max_size(int n){
    if(n<=0){
        std::logic_error("size storage must be positive integer");
    }
    __len_storage=n;
}

unsigned MyStorage::count_free_space(){
    return __len_storage-__content.size();
}

void MyStorage::push(Tranzakt* tranzakt){
    __content.push_tail(tranzakt);
}

void MyStorage::pop(Tranzakt* tranzakt){
    for(int i=0; i<__content.size(); i++){
        if(__content[i]==tranzakt)
            __content.pop(i);
    }
}

bool MyStorage::have(Tranzakt* tranzakt){
    for(int i=0; i<__content.size(); i++){
        if(__content[i]->id()==tranzakt->id())
            return true;
    }
    return false;
}

#endif
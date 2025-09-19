#pragma once
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
#include "../headers/MyStorage.h"

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
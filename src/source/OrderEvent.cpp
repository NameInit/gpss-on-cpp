#include "../headers/OrderEvent.h"

std::ostream& operator<<(std::ostream& output, const OrderEvent& status){
    output<<status._all_status[status._ind_cur_status];
    return output;
}

unsigned OrderEvent::ind_cur_status(){
    return _ind_cur_status;
}

bool OrderEvent::operator==(const OrderEvent& other){
    return _ind_cur_status==other._ind_cur_status;
}

bool OrderEvent::operator==(const char* string){
    return strcmp(_all_status[_ind_cur_status],string)==0;
}

OrderEvent& OrderEvent::operator=(const OrderEvent& other){
    if(_all_status!=nullptr){
        _ind_cur_status=other._ind_cur_status;
        return *this;
    }

    _CreateAllStatus();
    _size_all_status=COUNT_BLOCKS;
    _ind_cur_status=other._ind_cur_status;
    return *this;
}

const char* OrderEvent::status(){
    return _all_status[_ind_cur_status];
}

void OrderEvent::_CreateAllStatus(){
    _all_status=new char*[_size_all_status];
    _all_status[0]=strdup("START");
    _all_status[1]=strdup("GENERATE");
    _all_status[2]=strdup("ENTER");
    _all_status[3]=strdup("ADVANCE");
    _all_status[4]=strdup("LEAVE");
    _all_status[5]=strdup("TERMINATE");
    _all_status[6]=strdup("END");
}

OrderEvent::~OrderEvent(){
    for(int i=0; i<_size_all_status; i++)
        delete [] _all_status[i];
    delete [] _all_status;
}

OrderEvent::OrderEvent() : _ind_cur_status(0), _size_all_status(COUNT_BLOCKS) {
    _CreateAllStatus();
}

OrderEvent::OrderEvent(int n) : _ind_cur_status(n), _size_all_status(COUNT_BLOCKS) {
    if(n<0 || n>=COUNT_BLOCKS){
        throw std::logic_error("error in OrderEvent");
    }
    _CreateAllStatus();
}

OrderEvent& OrderEvent::operator++(){
    _ind_cur_status+=1-((_ind_cur_status+1)==_size_all_status);
    return *this;
}

OrderEvent& OrderEvent::operator--(){
    _ind_cur_status-=1-((_ind_cur_status-1)==0);
    return *this;
}
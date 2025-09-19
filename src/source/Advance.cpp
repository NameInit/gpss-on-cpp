#include "../headers/Advance.h"

bool Advance::is_passed(Tranzakt* tranzakt){
    for(int i=0; i<history.size(); i++)
        if(history[i]->id()==tranzakt->id())
            return true;
    return false;
}

void Advance::set_mean_processing_tranzakt(int* mean_processing_tranzakt){
    __mean_processing_tranzakt=mean_processing_tranzakt;
}

void Advance::advance(Tranzakt* tranzakt){
    std::exponential_distribution<double> distr(1.0/__mean_processing_tranzakt[tranzakt->type()-1]);
    tranzakt->set_time(tranzakt->time()+distr(__generator));
    history.push_tail(tranzakt);
}
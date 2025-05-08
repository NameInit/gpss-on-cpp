#ifndef ADVANCE_H
#define ADVANCE_H

#include <random>
#include "Tranzakt.h"
#include "List.h"

class Advance{
    private:
        int* __mean_processing_tranzakt;
		std::random_device __rd;
		std::mt19937 __generator;
        List<Tranzakt*> history;
    public:
        Advance() : __mean_processing_tranzakt(nullptr), __rd(), __generator(__rd()), history() {}

        void set_mean_processing_tranzakt(int* mean_processing_tranzakt);
        void advance(Tranzakt* tranzakt);
        bool is_passed(Tranzakt* tranzakt);
};

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


#endif
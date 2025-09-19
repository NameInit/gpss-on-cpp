#pragma once

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
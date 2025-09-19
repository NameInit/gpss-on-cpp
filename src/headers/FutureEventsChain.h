#pragma once

#include <fstream>
#include <iomanip>

#include "List.h"
#include "Tranzakt.h"

class FutureEventsChain{
    private:
        List<Tranzakt*> list;
    public:
        FutureEventsChain() : list() {}

        unsigned size();
        Tranzakt* operator[](int n);
        Tranzakt* pop(int n);
        void push(Tranzakt* tranzakt);
        void write_in_file(std::ofstream& output);
};
#pragma once

#include <fstream>
#include <iomanip>
#include <random>
#include <stdexcept>

#include "FutureEventsChain.h"
#include "List.h"
#include "MyStorage.h"
#include "Tranzakt.h"

class CurrentEventsChain {
private:
  List<Tranzakt *> list;

public:
  CurrentEventsChain() : list() {}
  Tranzakt *pop(int n);
  void push(Tranzakt *tranzakt); // tail
  bool can_promote(MyStorage *storage);
  Tranzakt *operator[](int n);
  unsigned size();
  void write_in_file(std::ofstream &output);
};
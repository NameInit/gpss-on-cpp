#pragma once

#include "Tranzakt.h"

class Terminate {
private:
  int *__counter;

public:
  Terminate() : __counter(nullptr) {}
  void link_counter(int *counter);
  void operator()(Tranzakt *tranzakt, int n);
};
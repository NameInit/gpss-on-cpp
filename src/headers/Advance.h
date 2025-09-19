#pragma once

#include "List.h"
#include "Tranzakt.h"
#include <random>

class Advance {
private:
  int *__mean_processing_tranzakt;
  std::random_device __rd;
  std::mt19937 __generator;
  List<Tranzakt *> history;

public:
  Advance()
      : __mean_processing_tranzakt(nullptr), __rd(), __generator(__rd()),
        history() {}
  void set_mean_processing_tranzakt(int *mean_processing_tranzakt);
  void advance(Tranzakt *tranzakt);
  bool is_passed(Tranzakt *tranzakt);
};
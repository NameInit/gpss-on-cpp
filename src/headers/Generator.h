#pragma once

#include "Tranzakt.h"
#include <random>

#define None 0

class Generator : public Tranzakt {
private:
  int __mean_born_tranzakt;
  double __last_time_born;
  std::random_device __rd;
  std::mt19937 __generator;

public:
  Generator()
      : __mean_born_tranzakt(None), __last_time_born(None), __rd(),
        __generator(__rd()) {}
  Generator(int mean_born_tranzakt)
      : __mean_born_tranzakt(mean_born_tranzakt), __last_time_born(None),
        __rd(), __generator(__rd()) {}
  void set_generator(int mean_born_tranzakt, unsigned tranzakt_type);
  void update_tranzakt(unsigned new_id, bool shift = true);
  void reset_tranzakt();
  bool is_free();
  Tranzakt *pop_tranzakt();
  friend std::ostream &operator<<(std::ostream &output, const Generator &other);
};

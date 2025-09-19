#pragma once

#include <cstring>
#include <fstream>
#include <iostream>

#define COUNT_BLOCKS 7

class OrderEvent {
protected:
  unsigned _ind_cur_status;
  unsigned _size_all_status;
  char **_all_status;
  void _CreateAllStatus();

public:
  OrderEvent();
  ~OrderEvent();
  OrderEvent(int n);
  OrderEvent &operator=(const OrderEvent &other);
  OrderEvent &operator++(); // next status
  OrderEvent &operator--(); // prev status
  bool operator==(const OrderEvent &other);
  bool operator==(const char *string);
  const char *status();
  unsigned ind_cur_status();
  friend std::ostream &operator<<(std::ostream &output,
                                  const OrderEvent &status);
};
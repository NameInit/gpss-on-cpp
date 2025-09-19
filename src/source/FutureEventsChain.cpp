#include "../headers/FutureEventsChain.h"

unsigned FutureEventsChain::size() { return list.size(); }

Tranzakt *FutureEventsChain::operator[](int n) {
  if (n < 0 || n >= size()) {
    throw std::logic_error(
        "index out of range in FutureEventsChain::operator[]");
  }
  return list[n];
}

Tranzakt *FutureEventsChain::pop(int n) {
  if (n < 0 || n >= list.size()) {
    throw std::logic_error("index out of range in FutureEventsChain::pop");
  }
  return list.pop(n);
}

void FutureEventsChain::push(Tranzakt *tranzakt) {
  int ind = 0;
  while (ind < size()) {
    if (tranzakt->time() < list[ind]->time())
      break;
    ind++;
  }
  list.push(tranzakt, ind);
}

void FutureEventsChain::write_in_file(std::ofstream &output) {
  output << "FEC:" << std::endl;
  output << std::right;
  if (size() == 0) {
    output << std::setw(4) << ' ';
    output << (const char *)"<void>" << std::endl;
  } else
    for (int i = 0; i < size(); i++) {
      output << std::setw(4) << ' ';
      output << *list[i] << std::endl;
    }
  output << std::left;
}
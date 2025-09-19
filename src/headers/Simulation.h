#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Advance.h"
#include "CurrentEventsChain.h"
#include "FutureEventsChain.h"
#include "Generator.h"
#include "MyStorage.h"
#include "Terminate.h"

#define None 0

class Simulation {
private:
  unsigned __current_id;
  double __current_time;
  Generator *__generate;
  unsigned __count_type_tranzakt;
  unsigned __count_type_worker;
  CurrentEventsChain __CEC;
  FutureEventsChain __FEC;
  MyStorage *__storages;
  Advance *__advance;
  Terminate __terminate;
  double *__sum_time_in_queue;
  int *__max_len_queue;

  unsigned __LogicDistributionTranzakts(unsigned type_tranzakt);

  void __WriteStatistic(std::ofstream &logger);
  void __WriteInFile(std::ofstream &logger, const char *phase);
  void __ViewingPhase();
  void __TimerCorrectionPhase();
  void __InputPhase();

public:
  Simulation(int count_type_tranzakt, int count_type_worker,
             int *mean_born_tranzakt, int *count_workers,
             int **mean_processing_tranzakt);
  ~Simulation();

  void start_simulation(std::ofstream &logger, int count_tranz_for_terminate);
  void reset();
};
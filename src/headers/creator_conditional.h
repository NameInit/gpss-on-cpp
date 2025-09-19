#pragma once
#include "../data_io/config.h"
#include <iostream>
#include <stdexcept>

#define None 0

#ifdef INITAL
#define COUNT_TYPE_WORKERS 2
#define COUNT_TYPE_TRANZAKTS 3
#endif

void clear(int *mean_born_tranzakt, int *count_workers,
           int **mean_processing_tranzakt, int count_type_worker);

void show_conditional(int *mean_born_tranzakt, int *count_workers,
                      int **mean_processing_tranzakt, int count_type_tranzakt,
                      int count_type_worker);

int get_count_type_tranzakt();
int get_count_type_worker();
int *get_mean_born_tranzakt(int count_type_tranzakt);
int *get_count_workers(int count_type_worker);
int **get_mean_processing_tranzakt(int count_type_tranzakt,
                                   int count_type_worker);
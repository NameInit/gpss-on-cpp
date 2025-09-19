#include <iostream>
#include <fstream>
#include <filesystem>

#include "headers/creator_conditional.h"
#include "headers/Simulation.h"
#include "data_io/config.h"

#ifndef COUNT_TRANZAKTS_SIMULATION
	#define COUNT_TRANZAKTS_SIMULATION 100
#endif

int main(){
	std::ofstream logger;
	std::filesystem::create_directories("report");
    logger.open("report/report.txt");
    if(!logger.is_open()){
        throw std::logic_error("file is not open");
    }

    int count_type_tranzakt=get_count_type_tranzakt();
    int count_type_worker=get_count_type_worker();
	if(count_type_tranzakt<count_type_worker){
		throw std::logic_error("count_type_tranzakt shouldn't be less count_type_worker");
	}

	int* mean_born_tranzakt=get_mean_born_tranzakt(count_type_tranzakt);
    int* count_workers=get_count_workers(count_type_worker);
    int** mean_processing_tranzakt=get_mean_processing_tranzakt(count_type_tranzakt,count_type_worker);

	Simulation thread1(count_type_tranzakt, count_type_worker, mean_born_tranzakt, count_workers, mean_processing_tranzakt);
	thread1.start_simulation(logger,COUNT_TRANZAKTS_SIMULATION);

	clear(mean_born_tranzakt,count_workers,mean_processing_tranzakt,count_type_worker);
	return 0;
}
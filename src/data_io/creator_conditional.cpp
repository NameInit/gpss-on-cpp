#include "../headers/creator_conditional.h"

void clear(int* mean_born_tranzakt,int* count_workers, int** mean_processing_tranzakt, int count_type_worker){
    delete [] mean_born_tranzakt;
    delete [] count_workers;
    for(int i=0; i<count_type_worker; i++)
        delete [] mean_processing_tranzakt[i];
    delete [] mean_processing_tranzakt;
}

void show_conditional(int* mean_born_tranzakt,int* count_workers,int** mean_processing_tranzakt,
					  int count_type_tranzakt, int count_type_worker){
	std::cout<<"-----MEAN BORN TRANZAKT-----"<<std::endl;
	for(int i=0; i<count_type_tranzakt; i++)
		std::cout << "Tranzakt type="<<i+1<<": "<<mean_born_tranzakt[i]<<std::endl;
	
	std::cout<<std::endl<<"-----COUNT WORKERS-----"<<std::endl;
	for(int i=0; i<count_type_worker; i++)
		std::cout << "Worker type="<<i+1<<": "<<count_workers[i]<<std::endl;

	std::cout<<std::endl<<"-----MEAN PROCESSING TRANZAKT-----"<<std::endl;
	for(int i=0; i<count_type_worker; i++){
		std::cout<<"WORKER "<<i+1<<std::endl;
		for(int j=0; j<count_type_tranzakt; j++){
			std::cout<<"Tranzakt "<<j+1<<": "<<mean_processing_tranzakt[i][j]<<std::endl;
		}
		if((i+1)!=count_type_worker) std::cout<<std::endl;
	}
}

int get_count_type_tranzakt() {
	int count_type_tranzakt;
	#ifdef INITAL
		count_type_tranzakt=COUNT_TYPE_TRANZAKTS;
	#else
		std::cout<<"Write count_type_tranzakt>>";
		std::cin>>count_type_tranzakt;
		if(!std::cin.good() || count_type_tranzakt<=0){
			std::logic_error("error input count_type_tranzakt");
		}
	#endif
	return count_type_tranzakt;
}

int get_count_type_worker() {
	int count_type_worker;
	#ifdef INITAL
		count_type_worker=COUNT_TYPE_WORKERS;
	#else
		std::cout<<"Write count_type_worker>>";
		std::cin>>count_type_worker;
		if(!std::cin.good() || count_type_worker<=0){
			throw std::logic_error("error input count_type_worker");
		}
	#endif
	return count_type_worker;
}

int* get_mean_born_tranzakt(int count_type_tranzakt) {
	int* mean_born_tranzakt=new int[count_type_tranzakt];

	#ifdef INITAL
		mean_born_tranzakt[0]=7; //R1
		mean_born_tranzakt[1]=9; //G1
		mean_born_tranzakt[2]=7; //B1
	#else
		for(int i=0; i<count_type_tranzakt; i++){
			std::cout<<"Write mean born tranzakt type "<<i+1<<">>";
			std::cin>>mean_born_tranzakt[i];
			if(!std::cin.good() || mean_born_tranzakt[i]<=0){
				throw std::logic_error("error input mean_born_tranzakt");
			}
		}
	#endif
	
	return mean_born_tranzakt;}

int* get_count_workers(int count_type_worker) {
	int* count_workers=new int[count_type_worker];

	#ifdef INITAL
		count_workers[0]=2;
		count_workers[1]=2;
	#else
		for(int i=0; i<count_type_worker; i++){
			std::cout<<"Write count workers type "<<i+1<<">>";
			std::cin>>count_workers[i];
			if(!std::cin.good() || count_workers[i]<=0){
				throw std::logic_error("error input count_workers");
			}
		}
	#endif

	return count_workers;}

int** get_mean_processing_tranzakt(int count_type_tranzakt, int count_type_worker) {
	int** mean_processing_tranzakt=new int*[count_type_worker];
	for(int i=0; i<count_type_worker; i++) 
		mean_processing_tranzakt[i]=new int[count_type_tranzakt];
	
	#ifdef INITAL
		//WORKER 1
		mean_processing_tranzakt[0][0]=23; 		//TRANZAKT TYPE 1
		mean_processing_tranzakt[0][1]=None;	//TRANZAKT TYPE 2 don't processing
		mean_processing_tranzakt[0][2]=32;		//TRANZAKT TYPE 3
		//WORKER 2
		mean_processing_tranzakt[1][0]=None;	//TRANZAKT TYPE 1 don't processing
		mean_processing_tranzakt[1][1]=29;		//TRANZAKT TYPE 2
		mean_processing_tranzakt[1][2]=28;		//TRANZAKT TYPE 3
	#else
		for(int i=0; i<count_type_worker; i++){
			bool flag_input=true;
			for(int j=0; j<count_type_tranzakt; j++){
				std::cout<<"Write mean processing tranzakt type="<<j+1<<
				" the worker type="<<i+1<<" (to specify None, enter 0) >>";
				std::cin>>mean_processing_tranzakt[i][j];
				if(!std::cin.good() || mean_processing_tranzakt[i][j]<0){
					throw std::logic_error("error mean_processing_tranzakt");
				}
				if(mean_processing_tranzakt[i][j]!=None) flag_input=false;
			}
			if(flag_input){
				throw std::logic_error("you need to initialize at least one");
			}
		}

		for(int j=0; j<count_type_tranzakt; j++){
			bool flag_input=true;
			for(int i=0; i<count_type_worker; i++){
				if(mean_processing_tranzakt[i][j]!=None) flag_input=false;
			}
			if(flag_input){
				throw std::logic_error("error don't processing tranzakt");
			}
		}
	#endif
	
	return mean_processing_tranzakt;}
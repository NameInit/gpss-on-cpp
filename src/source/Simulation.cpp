#include "../headers/Simulation.h"

Simulation::Simulation(int count_type_tranzakt, int count_type_worker, int* mean_born_tranzakt,
        int* count_workers, int** mean_processing_tranzakt) : __current_id(0), __current_time(0.),
        __count_type_tranzakt(count_type_tranzakt), __count_type_worker(count_type_worker){
    __generate=new Generator[count_type_tranzakt];
	for(int i=0; i<count_type_tranzakt; i++)
		__generate[i].set_generator(mean_born_tranzakt[i], i+1);

    __storages=new MyStorage[count_type_worker];
    for (int i=0; i<count_type_worker; i++)
        __storages[i].set_max_size(count_workers[i]);

    __advance=new Advance[count_type_worker];
    for(int i=0; i<count_type_worker; i++)
        __advance[i].set_mean_processing_tranzakt(mean_processing_tranzakt[i]);
    
    __sum_time_in_queue=new double[count_type_worker];
    for(int i=0; i<count_type_worker; i++)
        __sum_time_in_queue[i]=0.;
    
    __max_len_queue=new int[count_type_worker];
    for(int i=0; i<count_type_worker; i++) __max_len_queue[i]=0;
}

void Simulation::start_simulation(std::ofstream& logger, int count_tranz_for_terminate){
    if(count_tranz_for_terminate<=0){
        throw std::logic_error("count tranzakts for terminate must be positive integer");
    }
    bool flag_exit=true;
    __terminate.link_counter(&count_tranz_for_terminate);

    __InputPhase();
    __WriteInFile(logger,(const char*)"input phase");
    logger<<std::endl<<std::string(80,'#')<<std::endl<<std::endl;



    while(flag_exit){
        __TimerCorrectionPhase();
        __WriteInFile(logger,(const char*)"timer correction phase");
        logger<<std::endl<<std::string(80,'#')<<std::endl<<std::endl;
            
        while(__CEC.can_promote(__storages)){
            __ViewingPhase();
            __WriteInFile(logger,(const char*)"viewing phase");
            logger<<std::endl<<std::string(80,'#')<<std::endl<<std::endl;
            if(count_tranz_for_terminate<=0){
                flag_exit=false;
                break;
            }
        }
    }
    __WriteStatistic(logger);
}

void Simulation::__ViewingPhase(){
    bool flag_exit=false;
    for(int i=0; i<__CEC.size()*(!flag_exit); i++){
        if(__CEC[i]->current_block()==(const char*)"START"){
            __CEC[i]->go_next_block();
            flag_exit=true;
        }
        else if(__CEC[i]->current_block()==(const char*)"GENERATE"){
            __CEC[i]->go_next_block();
            __generate[__CEC[i]->type()-1].update_tranzakt(++__current_id);
            __FEC.push(__generate[__CEC[i]->type()-1].pop_tranzakt());
            flag_exit=true;
        }
        else if(__CEC[i]->current_block()==(const char*)"ENTER"){
            unsigned necessary_type=__LogicDistributionTranzakts(__CEC[i]->type());
            if(__CEC[i]->index_blocks()==None) __CEC[i]->index_blocks(necessary_type-1);
            if(__storages[__CEC[i]->index_blocks()].count_free_space()!=0){
                __CEC[i]->go_next_block();
                __storages[__CEC[i]->index_blocks()].push(__CEC[i]);
                flag_exit=true;
            }
        }
        else if(__CEC[i]->current_block()==(const char*)"ADVANCE"){
            if(!__advance[__CEC[i]->index_blocks()].is_passed(__CEC[i])){
                
                //start collecting statistic
                int* temp=new int[__count_type_worker];
                for(int i=0; i<__count_type_worker; i++) temp[i]=0;
                for(int i=0; i<__CEC.size(); i++)
                    if(__CEC[i]->time()<__current_time) temp[__CEC[i]->index_blocks()]+=1;
                for(int i=0; i<__count_type_worker; i++)
                    if(__max_len_queue[i]<temp[i]) __max_len_queue[i]=temp[i];
                __sum_time_in_queue[__CEC[i]->index_blocks()]+=__current_time-__CEC[i]->time();
                delete [] temp;
                //end

                __CEC[i]->set_time(__current_time);
                __advance[__CEC[i]->index_blocks()].advance(__CEC[i]);
                __FEC.push(__CEC.pop(i));
                flag_exit=true;
            }
            else{
                __CEC[i]->go_next_block();
                flag_exit=true;
            }
        }
        else if(__CEC[i]->current_block()==(const char*)"LEAVE"){
            __storages[__CEC[i]->index_blocks()].pop(__CEC[i]);
            __CEC[i]->go_next_block();
            flag_exit=true;
        }
        else if(__CEC[i]->current_block()==(const char*)"TERMINATE"){
            __terminate(__CEC.pop(i),1);
            flag_exit=true;
        }
    }
}

unsigned Simulation::__LogicDistributionTranzakts(unsigned type_tranzakt){
    if(type_tranzakt<=__count_type_worker)
        return type_tranzakt;
    
    unsigned type=1;
    unsigned max_free_space_storage=__storages[0].count_free_space();
    for(int i=1; i<__count_type_worker; i++)
        if(max_free_space_storage<__storages[i].count_free_space()){
            max_free_space_storage=__storages[i].count_free_space();
            type=i+1;
        }
    return type;
}

void Simulation::__TimerCorrectionPhase(){
    __current_time=__FEC[0]->time();
    for(int i=0; i<__FEC.size(); i++){
        if(__current_time!=__FEC[0]->time()) break;
        __CEC.push(__FEC.pop(0));
    }
}

void Simulation::__InputPhase(){
    for(int i=0; i<__count_type_tranzakt; i++){
        __generate[i].update_tranzakt(++__current_id);
        __FEC.push(__generate[i].pop_tranzakt());
    }
}

void Simulation::__WriteStatistic(std::ofstream& logger){
    int* temp=new int[__count_type_worker];
    for(int i=0; i<__count_type_worker; i++) temp[i]=0;
    for(int i=0; i<__CEC.size(); i++)
        if(__CEC[i]->time()<__current_time) temp[__CEC[i]->index_blocks()]+=1;
    for(int i=0; i<__count_type_worker; i++)
        if(__max_len_queue[i]<temp[i]) __max_len_queue[i]=temp[i];
    delete [] temp;

    for(int i=0; i<__CEC.size(); i++){
        if(__CEC[i]->current_block()==(const char*)"ENTER");
            __sum_time_in_queue[__CEC[i]->index_blocks()]+=__current_time-__CEC[i]->time();
    }

    logger<<(const char*)"AVERAGE QUEUE LENGTH:"<<std::endl;
    logger<<std::right;
    for(int i=0; i<__count_type_worker; i++){
        logger<<std::setw(4)<<' ';
        logger<<(const char*)"Queue "<<i+1<<(const char*)": "<<__sum_time_in_queue[i]/__current_time<<(const char*)" (MAX_LEN="<<__max_len_queue[i]<<')'<<std::endl;
    }
    logger<<std::left;
}

void Simulation::__WriteInFile(std::ofstream& logger, const char* phase){
    logger<<(const char*)"PHASE: "<<phase<<std::endl;
    logger<<(const char*)"MODEL TIME: "<<__current_time<<std::endl;
    logger<<(const char*)"STATUS:"<<std::endl;
    logger<<std::right;
    for(int i=0; i<__count_type_worker; i++){
        logger<<std::setw(4)<<' ';
        logger<<std::setw(4)<<(const char*)"Workers type="<<i+1<<(const char*)" have "<<__storages[i].count_free_space()<<(const char*)" places"<<std::endl;
    }
    logger<<std::left;
    __CEC.write_in_file(logger);
    __FEC.write_in_file(logger);
}

void Simulation::reset(){
    for(int i=0; i<__count_type_worker; i++) __sum_time_in_queue[i]=0;
    for(int i=0; i<__CEC.size(); i++) delete __CEC[i];
    for(int i=0; i<__FEC.size(); i++) delete __FEC[i];
    __current_id=0;
    __current_time=0;
}

Simulation::~Simulation(){
    for(int i=0; i<__CEC.size(); i++) delete __CEC[i];
    for(int i=0; i<__FEC.size(); i++) delete __FEC[i];
    delete [] __generate;
    delete [] __storages;
    delete [] __advance;
    delete [] __sum_time_in_queue;
    delete [] __max_len_queue;
}
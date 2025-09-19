#include "../headers/Tranzakt.h"


std::ostream& operator<<(std::ostream& output, const Tranzakt& tranzakt){
	output<<(const char*)"{ID: "<<tranzakt._id<<(const char*)", TIME: "<<tranzakt._time<<
	(const char*)", TYPE: "<<tranzakt._tranzakt_type<<(const char*)", CUR_BLOCK: "<<
	tranzakt._current_block<<(const char*)", NEXT_BLOCK: "<< tranzakt._next_block<<'}';
	return output;
}

unsigned Tranzakt::index_blocks(){
	return __index_in_blocks;
}

void Tranzakt::index_blocks(int n){
	__index_in_blocks=n;
}

OrderEvent& Tranzakt::current_block(){
	return _current_block;
}

OrderEvent& Tranzakt::next_block(){
	return _next_block;
}

void Tranzakt::go_next_block(){
	_current_block=_next_block;
	++_next_block;
}

Tranzakt::Tranzakt(unsigned id, double time, unsigned type) : _id(id), _time(time), _tranzakt_type(type), _current_block(0), _next_block(1),__index_in_blocks(None) {
	if(time<0){
		throw std::logic_error("time cannot be negative");
	}
}

int Tranzakt::num_current_block(){
	return _current_block.ind_cur_status();
}

int Tranzakt::num_next_block(){
	return _next_block.ind_cur_status();
}

unsigned Tranzakt::id(){
	return _id;
}

double Tranzakt::time(){
	return _time;
}

void Tranzakt::set_time(double new_time){
	if(new_time<0){
		throw std::logic_error("time cannot be negative");
	}
	_time=new_time;
}

unsigned Tranzakt::type(){
	return _tranzakt_type;
}
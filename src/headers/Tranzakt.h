#pragma once

#include <iostream>
#include <stdexcept>

#include "OrderEvent.h"

#define None 0

class Tranzakt{
	protected:
		unsigned _id;
		double _time; // TIME LOCATION
		unsigned _tranzakt_type; //1,2, ... MAX_COUNT_tranzakt_type
		OrderEvent _current_block;
		OrderEvent _next_block;
		unsigned __index_in_blocks;
	public:
		Tranzakt() : _id(None), _time(None), _tranzakt_type(None), _current_block(0), _next_block(1), __index_in_blocks(None) {}
		Tranzakt(unsigned id, double time, unsigned type);
		unsigned id();
		double time();
		void set_time(double n);
		unsigned type();
		OrderEvent& current_block();
		OrderEvent& next_block();
		int num_current_block();
		int num_next_block();
		void go_next_block();
		unsigned index_blocks();
		void index_blocks(int n);
		friend std::ostream& operator<<(std::ostream& output, const Tranzakt& tranzakt);
};
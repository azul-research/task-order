#pragma once
#include "company.h"
#include "pdw_structs.hpp"
#include <deque>


struct Stat {
	unsigned long type = 0;
	double m1 = 0; // sum{w * (t_f - t_st) / t_st} / cost
};

bool my_comparator(Stat& a, Stat& b);


class evr_1 {
	
public:
	ulong result;
	deque<ulong> task_order;

	evr_1();
	void calculate_result(std::vector<Task>& Tasks, std::vector<Manager>& Managers, std::vector<Worker>& Workers);
};


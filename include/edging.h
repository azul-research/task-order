#pragma once
#include "company.h"
#include "pdw_structs.hpp"

class edging_algorithm {
	vector<pdw_task> _Tasks;
	vector<pdw_worker> _Workers;
	size_t n_tasks;
	size_t max_t;

	type_sort sort_type;

	ulong sum_p(ulong start, ulong end);

public:
	ulong result;
	vector<ulong> task_order;

	edging_algorithm(vector<Worker>& Workers, vector<Task>& Tasks, type_d type = LAST_START, type_sort sort_type = MAX_MIN);
	void calculate_order();
	void calculate_result(vector<Task>& Tasks, vector<Manager> &Manangers, vector<Worker>& Workers);
	void calculate(vector<Task>& Tasks, vector<Manager>& Manangers, vector<Worker>& Workers);
};
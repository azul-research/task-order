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
	vector<ulong> task_order;

	edging_algorithm(vector<Worker>& Workers, vector<Task>& Tasks, type_d type = LAST_START, type_sort sort_type = MIN_MAX);
	void calculate();
};
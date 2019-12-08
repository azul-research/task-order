#pragma once

#include "company.h"


class local_search_neigh {

public:
	unsigned long result;
	std::vector<unsigned long> task_order;

	local_search_neigh(std::vector<unsigned long>& order, std::vector<Task>& Tasks, 
		std::vector<Manager>& Managers, std::vector<Worker>& Workers);

};
#pragma once

#include "company.h"


Result local_search_neigh(Result& res, std::vector<Task>& our_tasks,
		std::vector<Manager>& Managers, std::vector<Worker>& Workers);
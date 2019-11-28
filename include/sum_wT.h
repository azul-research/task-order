#pragma once

#include "company.h"
#include "pdw_structs.hpp"
#include <algorithm>
#include <deque>

class sum_wT_algorithm {
private:
    vector<pdw_task> _Tasks;
    vector<pdw_worker> _Workers;
    vector<Worker> Workers;
    size_t num_of_tasks;
    size_t max_t;

    ulong sum_p(ulong start, ulong end);

public:
    ulong result;
    std::vector<Task> task_order;

    sum_wT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks, calculate_d::type_d type = calculate_d::FS);
    void calculate_result();
};
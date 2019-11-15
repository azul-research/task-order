#include "pdw_structs.hpp"
#include <algorithm>
#include <deque>

using namespace std;

class GT_algorithm {
    vector<pdw_task> _Tasks;
    vector<pdw_worker> _Workers;
    size_t num_of_tasks;
    size_t max_t;

    bool sort_type;

    ulong sum_p(ulong start, ulong end);

public:
    ulong result;
    deque<ulong> task_order;

    GT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks, calculate_d::type_d type = calculate_d::type_d::FS, bool sort_type = 1);  // sort_type == 1 <=> a_i.d > a_j.d, i < j
    void calculate_result();
};

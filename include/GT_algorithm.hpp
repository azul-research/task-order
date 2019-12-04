#include "pdw_structs.hpp"
#include <deque>

using namespace std;

class GT_algorithm {
    vector<Task> Tasks;
    vector<Manager> Managers;
    vector<Worker> Workers;
    vector<pdw_task> _Tasks;
    vector<pdw_worker> _Workers;
    size_t num_of_tasks;
    size_t max_t;

    type_sort sort_type;

    ulong sum_p(ulong start, ulong end);

public:
    ulong result;
    deque<ulong> task_order;

    GT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks, vector<Manager> &Managers, type_d type = FIRST_START, type_sort sort_type = MAX_MIN);
    void calculate_result();
    ulong get_result_with_managers();
};

#include "company.h"
#include <algorithm>
#include <deque>

using namespace std;

typedef unsigned long ulong;

class GT_algorithm {
    struct my_task {
        ulong d;    // first start
        ulong p;    // task cost
        ulong id;   // task id

        my_task();
        my_task(ulong d, ulong p, ulong id);
    };

    vector<my_task> My_Tasks;
    size_t num_of_tasks;
    size_t max_t;
    vector<Worker> _Workers;
    vector<Task> _Tasks;

    ulong sum_p(ulong start, ulong end);
    ulong find_first_start(int i);

public:
    ulong result;
    deque<ulong> task_order;

    GT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks);
    void calculate_result();
};

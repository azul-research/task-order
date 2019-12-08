#include "GT_algorithm.hpp"

ulong GT_algorithm::sum_p(ulong start, ulong end) {
    ulong s = 0;
    for (size_t i = start; i <= end; ++i)
        s += _Tasks[i].p;
    return s;
}

GT_algorithm::GT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks, vector<Manager> &Managers, type_d type, type_sort sort_type) :
    Workers(Workers), Tasks(Tasks), Managers(Managers), sort_type(sort_type) {
    num_of_tasks = Tasks.size();
    _Tasks.resize(num_of_tasks);

    for (auto w : Workers)
        _Workers.push_back(pdw_worker(w.get_salary(), w.get_type(), w.get_start(), w.get_finish()));
    calculate_d CD(_Workers);

    for (size_t i = 0; i < Tasks.size(); ++i)
        this->_Tasks[i] = pdw_task(CD.find_d(i, type), Tasks[i].get_cost(), i);

    max_t = sum_p(0, num_of_tasks - 1) + 1;
}

void GT_algorithm::calculate_result() {
    if (sort_type == MAX_MIN)
        sort(_Tasks.begin(), _Tasks.end(), [](pdw_task a, pdw_task b) -> bool {return a.d > b.d;});
    else
        sort(_Tasks.begin(), _Tasks.end(), [](pdw_task a, pdw_task b) -> bool {return a.d < b.d;});

    vector<vector<deque<ulong>>> pi(num_of_tasks, vector<deque<ulong>>(max_t));
    vector<vector<ulong>> f(num_of_tasks, vector<ulong>(max_t));

    for (size_t t = 0; t <= sum_p(1, num_of_tasks - 1); ++t) {
        pi[0][t].push_back(0);

        for (auto w : _Workers)
            if (w.type == _Tasks[0].id)
                f[0][t] += GT(w.w, t + _Tasks[0].p, w.start, w.finish);
    }

    for (size_t j = 1; j < num_of_tasks; ++j)
        for (size_t t = 0; t <= sum_p(j + 1, num_of_tasks - 1); ++t) {
            deque<ulong> pi_1(pi[j - 1][t + _Tasks[j].p]), pi_2(pi[j - 1][t]);
            vector<ulong> f_1(max_t), f_2(max_t);

            pi_1.push_front(j);
            pi_2.push_back(j);

            f_1[t] = f[j - 1][t + _Tasks[j].p];
            f_2[t] = f[j - 1][t];
            for (auto w : _Workers) {
                if (w.type == _Tasks[j].id) {
                    f_1[t] += GT(w.w, t + _Tasks[j].p, w.start, w.finish);
                    f_2[t] += GT(w.w, t + sum_p(0, j), w.start, w.finish);
                }
            }

            if (f_1[t] < f_2[t]) {
                f[j][t] = f_1[t];
                pi[j][t] = pi_1;
            }
            else {
                f[j][t] = f_2[t];
                pi[j][t] = pi_2;
            }
        }

    result = f[num_of_tasks - 1][0];

    for (auto i : pi[num_of_tasks - 1][0])
        task_order.push_back(_Tasks[i].id);
}

ulong GT_algorithm::get_result_with_managers() {
    Result result = Result();

    std::vector<Task> _Tasks(Tasks.size());
    for (size_t i = 0; i < _Tasks.size(); i++) {
        _Tasks[i] = Tasks[task_order[i]];
    } 
    return result.calculate_result(_Tasks, Managers, Workers).get_value();
}

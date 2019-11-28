#include "sum_wT.h"

ulong sum_wT_algorithm::sum_p(ulong start, ulong end) {
    ulong s = 0;
    for (size_t i = start; i <= end; ++i)
        s += _Tasks[i].p;
    return s;
}

sum_wT_algorithm::sum_wT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks, calculate_d::type_d type) : Workers(Workers) {
    num_of_tasks = Tasks.size();
    _Tasks.resize(num_of_tasks);

    for (auto w : Workers) {
        _Workers.push_back(pdw_worker(w.get_salary(), w.get_type(), w.get_start(), w.get_finish()));
    }
    calculate_d CD(_Workers);

    for (size_t i = 0; i < Tasks.size(); ++i) {
        this->_Tasks[i] = pdw_task(CD.find_d(i, type), Tasks[i].get_cost(), Tasks[i].get_type());
    }

    max_t = sum_p(0, num_of_tasks - 1) + 1;
}

void sum_wT_algorithm::calculate_result() {
    sort(_Tasks.begin(), _Tasks.end(), [](pdw_task a, pdw_task b) -> bool {return a.p > b.p;});

    vector<vector<deque<ulong>>> pi(num_of_tasks, vector<deque<ulong>>(max_t));
    vector<vector<ulong>> f(num_of_tasks, vector<ulong>(max_t));

    for (size_t t = 0; t <= sum_p(1, num_of_tasks - 1); ++t) {
        pi[0][t].push_back(1);
        for (auto w : _Workers) {
            if (w.type == _Tasks[0].id) {
                f[0][t] += w.w * min(w.finish - w.start, t + _Tasks[0].p - _Tasks[0].d);
            }
        }
    }

    for (size_t j = 1; j < num_of_tasks; ++j) {
        for (size_t t = 0; t <= sum_p(j + 1, num_of_tasks - 1); ++t) {
            deque<ulong> pi_1(pi[j - 1][t + _Tasks[j].p]), pi_2(pi[j - 1][t]);
            vector<ulong> f_1(max_t), f_2(max_t);

            pi_1.push_front(j);
            pi_2.push_back(j);

            //f_1[t] = f[j - 1][t + _Tasks[j].p];
            //f_2[t] = f[j - 1][t];
            for (auto w : _Workers) {
                if (w.type == _Tasks[j].id) {
                    f_1[t] += w.w * min(w.finish - w.start, (ulong)max(0ULL, 1LL * t + _Tasks[j].p - _Tasks[j].d)) + f[j - 1][t + _Tasks[j].p];

                    f_2[t] += w.w * min(w.finish - w.start, (ulong)max(0ULL, t * 1LL + sum_p(0, j) - _Tasks[j].d)) + f[j - 1][t];
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
    }
    for (auto i : pi[num_of_tasks - 1][0]) {
        task_order.push_back(Task(_Tasks[i].id, _Tasks[i].p));
    }
    vector<Manager> Managers = {Manager(0, 1)};
    Result result_object = Result();    
    result = result_object.calculate_result(task_order, Managers, Workers).get_value();
}
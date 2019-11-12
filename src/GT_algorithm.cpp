#include "GT_algorithm.hpp"

GT_algorithm::my_task::my_task() {
}

GT_algorithm::my_task::my_task(ulong d, ulong p, ulong id) : d(d), p(p), id(id) {
}

ulong GT_algorithm::sum_p(ulong start, ulong end) {
    ulong s = 0;
    for (size_t i = start; i <= end; ++i)
        s += My_Tasks[i].p;
    return s;
}

ulong GT_algorithm::find_first_start(int i) {
    for (auto w : _Workers)
        if (w.get_type() == i)
            return w.get_start();
    return (ulong)(-1);
}

GT_algorithm::GT_algorithm(vector<Worker> &Workers, vector<Task> &Tasks) : _Tasks(Tasks), _Workers(Workers) {
    num_of_tasks = Tasks.size();
    My_Tasks.resize(num_of_tasks);

    for (size_t i = 0; i < Tasks.size(); ++i)
        this->My_Tasks[i] = my_task(find_first_start(i), Tasks[i].get_cost(), i);

    max_t = sum_p(0, num_of_tasks - 1) + 1;
}

void GT_algorithm::calculate_result() {
    sort(My_Tasks.begin(), My_Tasks.end(), [](my_task a, my_task b) -> bool {return a.d > b.d;});

    vector<vector<deque<ulong>>> pi(num_of_tasks, vector<deque<ulong>>(max_t));
    vector<vector<ulong>> f(num_of_tasks, vector<ulong>(max_t));

    for (size_t t = 0; t <= sum_p(1, num_of_tasks - 1); ++t) {
        pi[0][t].push_back(0);

        for (auto w : _Workers)
            if (w.get_type() == My_Tasks[0].id)
                f[0][t] += w.get_salary() * min((ulong)max(1LL * 0, t * 1LL + My_Tasks[0].p - w.get_start()), w.get_finish() - w.get_start());
    }

    for (size_t j = 1; j < num_of_tasks; ++j)
        for (size_t t = 0; t <= sum_p(j + 1, num_of_tasks - 1); ++t) {
            deque<ulong> pi_1(pi[j - 1][t + My_Tasks[j].p]), pi_2(pi[j - 1][t]);
            vector<ulong> f_1(max_t), f_2(max_t);

            pi_1.push_front(j);
            pi_2.push_back(j);

            f_1[t] = f[j - 1][t + My_Tasks[j].p];
            f_2[t] = f[j - 1][t];
            for (auto w : _Workers) {
                if (w.get_type() == My_Tasks[j].id) {
                    f_1[t] += w.get_salary() * min((ulong)max(0 * 1LL, t * 1LL + My_Tasks[j].p - w.get_start()), w.get_finish() - w.get_start());

                    f_2[t] += w.get_salary() * min((ulong)max(0 * 1LL, t * 1LL + sum_p(0, j) - w.get_start()), w.get_finish() - w.get_start());
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
        task_order.push_back(My_Tasks[i].id);
}

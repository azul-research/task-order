#include "edging.h"
#include "ls.h"
#include <algorithm>
#include <deque>


ulong edging_algorithm::sum_p(ulong start, ulong end) {
	ulong s = 0;
	for (size_t i = start; i <= end; ++i)
		s += _Tasks[i].p;
	return s;
}

edging_algorithm::edging_algorithm(vector<Worker>& Workers, vector<Task>& Tasks, 
									type_d type, type_sort sort_type) : sort_type(sort_type) {
	n_tasks = Tasks.size();
	_Tasks.resize(n_tasks);

	for (auto w : Workers)
		_Workers.push_back(pdw_worker(w.get_salary(), w.get_type(), w.get_start(), w.get_finish()));

	calculate_d CD(_Workers);

	for (size_t i = 0; i < n_tasks; ++i)
		this->_Tasks[i] = pdw_task(CD.find_d(i, type), Tasks[i].get_cost(), i);

	max_t = sum_p(0, n_tasks - 1) + 1;
}
	
void edging_algorithm::calculate() {
	if (sort_type == MAX_MIN)
		sort(_Tasks.begin(), _Tasks.end(), [](pdw_task a, pdw_task b) -> bool {return a.d > b.d; });
	else
		sort(_Tasks.begin(), _Tasks.end(), [](pdw_task a, pdw_task b) -> bool {return a.d < b.d; });

	std::vector<ulong> wage(n_tasks);
	for (size_t i = 0; i < n_tasks; ++i) {
		wage[i] = 0;
	}
	for (auto w : _Workers) {
		wage[w.type] += w.w * (w.finish - w.start);
	}
	std::vector<std::vector<unsigned long> > f(n_tasks, std::vector<unsigned long>(max_t));
	std::vector<std::vector<std::deque<unsigned long> > > order(n_tasks, std::vector<std::deque<unsigned long> >(max_t));
	for (unsigned long t = 0; t <= sum_p(1, n_tasks - 1); ++t) {
		order[0][t].push_back(_Tasks[0].id);
		if (t + _Tasks[0].p <= _Tasks[0].d) {
			f[0][t] = wage[_Tasks[0].id];
		}
		else {
			f[0][t] = 0;
		}
	}
	unsigned long F1, F2;
	for (size_t j = 1; j < n_tasks; ++j) {
		for (unsigned long t = 0; t <= sum_p(j + 1, n_tasks - 1); ++t) {
			if (t + _Tasks[j].p <= _Tasks[j].d) {
				F1 = wage[_Tasks[j].id] + f[j - 1][t + _Tasks[j].p];
			}
			else {
				F1 = f[j - 1][t + _Tasks[j].p];
			}
			if (t + sum_p(0, j) <= _Tasks[j].d) {
				F2 = wage[_Tasks[j].id] + f[j - 1][t];
			}
			else {
				F2 = f[j - 1][t];
			}
			if (F1 < F2) {
				f[j][t] = F2;
				order[j][t] = order[j - 1][t];
				order[j][t].push_back(_Tasks[j].id);
			}
			else {
				f[j][t] = F1;
				order[j][t] = order[j - 1][t + _Tasks[j].p];
				order[j][t].push_front(_Tasks[j].id);
			}
		}
	}
	for (size_t i = 0; i < n_tasks; ++i) {
		this->task_order.push_back(order[n_tasks - 1][0][i]);
	}
}
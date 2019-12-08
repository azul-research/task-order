#include "ls.h"

local_search_neigh::local_search_neigh(std::vector<unsigned long>& task_order, std::vector<Task>& Tasks, 
										std::vector<Manager>& Managers, std::vector<Worker>& Workers) {
	std::vector<Task> our_tasks;
	for (size_t i = 0; i < Tasks.size(); ++i) {
		our_tasks.push_back(Task(task_order[i], Tasks[task_order[i]].get_cost()));
	}
	Result res = Result();
	res = res.calculate_result(our_tasks, Managers, Workers);
	unsigned long min_evr = res.get_value();
	for (size_t n_steps = 0; n_steps < 2 * our_tasks.size(); ++n_steps) {
		Result new_res;
		int to_swap = -1;
		for (size_t i = 0; i < our_tasks.size() - 1; ++i) {
			std::iter_swap(our_tasks.begin() + i, our_tasks.begin() + i + 1);
			new_res = new_res.calculate_result(our_tasks, Managers, Workers);
			if (new_res.get_value() < min_evr) {
				min_evr = new_res.get_value();
				to_swap = i;
			}
			std::iter_swap(our_tasks.begin() + i, our_tasks.begin() + i + 1);
		}
		if (to_swap != -1) {
			std::iter_swap(our_tasks.begin() + to_swap, our_tasks.begin() + to_swap + 1);
		}
		else {
			break;
		}
	}
	Result r;
	r = r.calculate_result(our_tasks, Managers, Workers);
	this->result = r.get_value();
	for (size_t i = 0; i < our_tasks.size(); ++i) {
		this->task_order.push_back(our_tasks[i].get_type());
	}
}
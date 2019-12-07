#include "ls.h"

Result local_search_neigh(Result& res, std::vector<Task>& our_tasks, 
						std::vector<Manager>& Managers, std::vector<Worker>& Workers) {
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
	return r;
}
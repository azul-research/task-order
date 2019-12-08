#include "evr_1.h"
#include "ls.h"
#include <algorithm>

bool my_comparator(Stat& a, Stat& b) {
	return (a.m1 > b.m1);
}


evr_1::evr_1() {
}

void evr_1::calculate_result(std::vector<Task>& Tasks, std::vector<Manager>& Managers, std::vector<Worker>& Workers) {
	std::vector<Stat> stats(Tasks.size());
	for (auto w : Workers) {
		stats[w.get_type()].m1 += (double) w.get_salary() * (w.get_finish() - w.get_start()) / w.get_start();
	}

	for (size_t i = 0; i < Tasks.size(); ++i) {
		stats[i].type = i;
		stats[i].m1 /= (double) Tasks[i].get_cost();
	}
	std::sort(stats.begin(), stats.end(), my_comparator);
	std::vector<Task> our_tasks;
	for (size_t i = 0; i < Tasks.size(); ++i) {
		our_tasks.push_back(Task(stats[i].type, Tasks[stats[i].type].get_cost()));
	}
	Result res;
	res = res.calculate_result(our_tasks, Managers, Workers);
	this->result = res.get_value();
	for (size_t i = 0; i < Tasks.size(); ++i) {
		this->task_order.push_back(our_tasks[i].get_type());
	}
}
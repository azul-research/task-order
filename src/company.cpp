#include "company.h"
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <set>
#include <limits.h>
#include <cassert>
#include <map>

unsigned long res_naive;

Worker::Worker() {}

Worker::Worker(unsigned long start, unsigned long finish, unsigned long type, unsigned long salary, unsigned long id) {
	w_start = start;
	w_finish = finish;
	assert(w_start < w_finish);
	w_type = type;
	w_salary = salary;
	w_id = id;
}

unsigned long Worker::get_type() {
	return w_type;
}

unsigned long Worker::get_start() {
	return w_start;
}

unsigned long Worker::get_finish() {
	return w_finish;
}

unsigned long Worker::get_salary() {
	return w_salary;
}

bool operator<(const Worker w_1, const Worker w_2) {
	return w_1.w_start <= w_2.w_start;
}

std::istream& operator>> (std::istream &is, Worker &w) {
	is >> w.w_start;
	is >> w.w_finish;
	is >> w.w_type;
	is >> w.w_salary;
	is >> w.w_id;
	return is;
}

Task::Task() {}

Task::Task(unsigned long type, unsigned long cost) {
	t_type = type;
	t_cost = cost;
}

bool operator<(const Task t_1, const Task t_2) {
	return t_1.t_type <= t_2.t_type;
}

bool Task::operator==(const Task& other) const {
	return t_type == other.t_type && t_cost == other.t_cost;
}

unsigned long Task::get_cost() {
	return t_cost;
}

unsigned long Task::get_type() {
	return t_type;
}

std::istream &operator>> (std::istream &is, Task &t) {
	is >> t.t_type;
	is >> t.t_cost;
	return is;
}

std::ostream &operator<< (std::ostream &os, const Task &t) {
	os << t.t_type;
	return os;
}

Manager::Manager() {}

Manager::Manager(unsigned long start, unsigned long id) {
	m_start = start;
	m_id = id;
}

unsigned long Manager::get_id() {
	return m_id;
}

unsigned long Manager::get_start() {
	return m_start;
}

bool operator<(const Manager m_1, const Manager m_2) {
	return m_1.m_start <= m_2.m_start;
}


std::istream &operator>> (std::istream &is, Manager &m) {
	is >> m.m_start;
	is >> m.m_id;
	return is;
}

Result::Result() {
	r_value = ULONG_MAX;
}

Result::Result(unsigned long value, std::map<Manager, std::vector<Task>> task_order) {
	r_value = value;
	r_task_order = task_order;
}

unsigned long Result::get_value() {
	return r_value;
}

std::map<Manager, std::vector<Task>> Result::get_task_order() {
	return r_task_order;
}

void Result::calculate_minimum(std::vector<Task> Tasks, std::vector<Manager> Managers, std::vector<Worker> Workers) {
	std::vector<unsigned long> order(Tasks.size());
	do {
		Result new_result = calculate_result(Tasks, Managers, Workers);
		r_value = std::min(r_value, new_result.get_value());
		if (r_value == new_result.get_value()) {
			r_task_order = new_result.get_task_order();
			for (size_t i = 0; i < Tasks.size(); ++i) {
				order[i] = Tasks[i].get_type();
			}
		}
		if (r_value == 0) {
			break;
		}
	} while (std::next_permutation(Tasks.begin(), Tasks.end()));
	res_naive = r_value;
	std::cout << r_value << "\n";
	for (size_t i = 0; i < Tasks.size(); ++i) {
		std::cout << order[i] << " ";
	}
	std::cout << "\n";
}

Result Result::calculate_result(std::vector<Task> Tasks, std::vector<Manager> Managers, std::vector<Worker> Workers) {
	std::vector<unsigned long> completion_time(Tasks.size());
	std::set<std::pair<unsigned long, Manager>> Managers_set;
	std::map<Manager, std::vector<Task>> new_r_task_order;
	for (auto m : Managers) {
		Managers_set.insert({m.get_start(), m});
		new_r_task_order[m] = {};
	}
	unsigned long new_r_value = 0; 
	for (size_t i = 0; i < Tasks.size(); i++) {
		std::pair<unsigned long, Manager> m = *Managers_set.begin();
		Managers_set.erase(Managers_set.begin());
		m.first += Tasks[i].get_cost();
		completion_time[i] = m.first;
		Managers_set.insert(m);
		new_r_task_order[m.second].push_back({Tasks[i]});
	} 
	for (size_t i = 0; i < Tasks.size(); i++) {
		for (auto w : Workers) {
			if (Tasks[i].get_type() == w.get_type()) {
				if (completion_time[i] >= w.get_start() && completion_time[i] <= w.get_finish()) {
					new_r_value += (completion_time[i] - w.get_start()) * w.get_salary();
				}
				if (completion_time[i] > w.get_finish()) {
					new_r_value += (w.get_finish() - w.get_start()) * w.get_salary();
				}
			}
		}
	}
	return {Result(new_r_value, new_r_task_order)};
}

void local_search_neigh(Result &res, std::vector<Task> &our_tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers) {
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
		} else {
			break;
		}
	}
	for (size_t i = 0; i < our_tasks.size(); ++i) {
			std::cout << our_tasks[i].get_type() << " ";
	}
	std::cout << "\n";
	std::cout << min_evr << "\n";
	std::cout << min_evr / (double) res_naive << "\n";
}

struct due_date_task {
	unsigned long type;
	unsigned long d;
	unsigned long p;
	unsigned long w;
};

bool tsk_comparator(due_date_task &a, due_date_task &b) {
	return (a.d < b.d);
}

void edging(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers) {
	std::cout << "\nEDGING\n";
	unsigned long n = Tasks.size();
	std::vector<due_date_task> tsk(n);
	std::vector<std::vector<unsigned long> > sum_p(n + 1, std::vector<unsigned long>(n));
	sum_p[n][n-1] = 0;
	for (size_t i = 0; i < n; ++i) {
		tsk[i].type = i;
		tsk[i].d = 0;
		tsk[i].p = Tasks[i].get_cost();
		tsk[i].w = 0;
		for (auto w : Workers) {
			if (w.get_type() == i) {
				tsk[i].d = std::max(tsk[i].d, w.get_finish());
				tsk[i].w += w.get_salary() * (w.get_finish() - w.get_start());
			}
		}
	}
	std::sort(tsk.begin(), tsk.end(), tsk_comparator);
	/*for (size_t i = 0; i < n; ++i) {
		std::cout << tsk[i].type << " " << tsk[i].d << " " << tsk[i].p << " " << tsk[i].w << "\n";
	}*/
	for (size_t i = 0; i < n; ++i) {
		sum_p[i][i] = tsk[i].p;
		for (size_t j = i + 1; j < n; ++j) {
			sum_p[i][j] = sum_p[i][j-1] + tsk[j].p;
			//std::cout << i << " " << j << " " << sum_p[i][j] << "\n";
		}	
	}
	unsigned long Tmax = sum_p[0][n-1] + 1;
	std::vector<std::vector<unsigned long> > f(n, std::vector<unsigned long>(Tmax));
	std::vector<std::vector<std::deque<unsigned long> > > order(n, std::vector<std::deque<unsigned long> >(Tmax));
	for (unsigned long t = 0; t <= sum_p[1][n-1]; ++t) {
		order[0][t].push_back(tsk[0].type);
		if (t + tsk[0].p <= tsk[0].d) {
			f[0][t] = tsk[0].w;
		} else {
			f[0][t] = 0;
		}
	}
	unsigned long F1, F2;
	for (size_t j = 1; j < n; ++j) {
		for (unsigned long t = 0; t <= sum_p[j+1][n-1]; ++t) {
			if (t + tsk[j].p <= tsk[j].d) {
				F1 = tsk[j].w + f[j-1][t + tsk[j].p];
			} else {
				F1 = f[j-1][t + tsk[j].p];
			}
			if (t + sum_p[0][j] <= tsk[j].d) {
				F2 = tsk[j].w + f[j-1][t];
			} else {
				F2 = f[j-1][t];
			}
			if (F1 < F2) {
				f[j][t] = F2;
				order[j][t] = order[j-1][t];
				order[j][t].push_back(tsk[j].type);
			} else {
				f[j][t] = F1;
				order[j][t] = order[j-1][t+tsk[j].p];
				order[j][t].push_front(tsk[j].type);
			}
			if (t == 0) {
				/*std::cout << "check\n";
				for (size_t i = 0; i < order[j][0].size(); ++i) {
					std::cout<< order[j][0][i] << " ";
				}
				std::cout << "\ncheck\n";*/
			}
			//std::cout << j << " end ";
		}
	}
	/*for (size_t i = 0; i < order[n-1][0].size(); ++i) {
		std::cout<< order[n-1][0][i] << " ";
	}*/
	//std::cout << "\n" << f[n-1][0] << "\n";
	std::vector<Task> our_tasks;
	for (size_t i = 0; i < n; ++i) {
		our_tasks.push_back(Task(order[n-1][0][i], Tasks[order[n-1][0][i]].get_cost()));
	}
	Result res;
	res = res.calculate_result(our_tasks, Managers, Workers);
	/*std::cout << "\n" << res.get_value() << "\n";
	std::cout << res.get_value() / (double) res_naive << "\n";*/
	local_search_neigh(res, our_tasks, Managers, Workers);
}

struct Stat {
	unsigned long n_workers_type = 0;
	unsigned long type = 0;
	unsigned long sum_salary_type = 0;
	double avg_start_type = 0;
	double m1 = 0; // (sum{w * (t_f - t_st) / t_st}) / cost
};

bool my_comparator(Stat &a, Stat &b) {
	return (a.m1 > b.m1);
}

void evr_1(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers) {
	std::cout << "\nEvr_1 (sort by sum{w * (t_f - t_st) / t_st}) / cost)\n";
	std::vector<Stat> stats(Tasks.size());
	for (auto w : Workers) {
		++stats[w.get_type()].n_workers_type;
		stats[w.get_type()].sum_salary_type += w.get_salary() * (w.get_finish() - w.get_start());
		stats[w.get_type()].avg_start_type += w.get_start();
		stats[w.get_type()].m1 += w.get_salary() * (w.get_finish() - w.get_start()) / (double) w.get_start();		
	}
	
	//std::cout << "Number of workers per task type\n";
	for (size_t i = 0; i < Tasks.size(); ++i) {
		stats[i].type = i;
		//std::cout << i << " " << stats[i].n_workers_type << "\n";
	}
	//std::cout << "Total salary per task type\n";
	for (size_t i = 0; i < Tasks.size(); ++i) {
		//std::cout << i << " " << stats[i].sum_salary_type << "\n";
	}
	//std::cout << "Avg start time per task type\n";
	for (size_t i = 0; i < Tasks.size(); ++i) {
		stats[i].avg_start_type /= (double) stats[i].n_workers_type;
		//std::cout << i << " " << stats[i].avg_start_type << "\n";
	}
	//std::cout << "sum w/t_st per task type\n";
	for (size_t i = 0; i < Tasks.size(); ++i) {
		stats[i].m1 /= (double) Tasks[i].get_cost();
		//std::cout << i << " " << stats[i].m1 << "\n";
	}
	std::sort(stats.begin(), stats.end(), my_comparator);
	/*for (size_t i = 0; i < Tasks.size(); ++i) {
		std::cout << stats[i].type << " ";
	}
	std::cout << "\n";*/
	std::vector<Task> our_tasks;
	for (size_t i = 0; i < Tasks.size(); ++i) {
		our_tasks.push_back(Task(stats[i].type, Tasks[stats[i].type].get_cost()));
	}
	Result res;
	res = res.calculate_result(our_tasks, Managers, Workers);
	/*std::cout << res.get_value() << "\n";
	std::cout << res.get_value() / (double) res_naive << "\n";*/
	local_search_neigh(res, our_tasks, Managers, Workers);
}
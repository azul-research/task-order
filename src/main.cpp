#include "company.h"
#include <iostream>
#include <vector>

int main() {
	unsigned long  m_size, t_size, w_size;
	std::vector<Task> Tasks;
	std::vector<Manager> Managers;
	std::vector<Worker> Workers;
	std::cin >> t_size;
	for (size_t i = 0; i < t_size; i++) {
		Task t;
		std::cin >> t;
		Tasks.push_back(t);
	}
	std::cin >> m_size;
	for (size_t i = 0; i < m_size; i++) {
		Manager m;
		std::cin >> m;
		Managers.push_back(m);
	}
	std::cin >> w_size;
	for (size_t i = 0; i < w_size; i++) {
		Worker w;
		std::cin >> w;
		Workers.push_back(w);
	}
	Result result = Result();
	auto task_order = result.get_task_order();
	result.calculate_minimum(Tasks, Managers, Workers);
}
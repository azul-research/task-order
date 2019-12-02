#include "company.h"
#include <iostream>
#include <vector>
#include "sum_wT.h"

int main(int argc, char **argv) {
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
	if (argc > 1) {
		if (argv[1] == (char *)"naive") {
			Result result = Result();
			result.calculate_minimum(Tasks, Managers, Workers);
			std::cout << result.get_value() << "\n";
		}
		if (argv[1] == (char *)"sum_wT") {
			sum_wT_algorithm wT = sum_wT_algorithm(Workers, Tasks, type_d::LAST_START);
			wT.calculate_result();
		}
	}
	return 0;
}
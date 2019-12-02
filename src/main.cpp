#include "company.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ls.h"
#include "evr_1.h"
#include "edging.h"
#include "GT_algorithm.hpp"
#include "sum_wT.h"

int main(int argc, char **argv) {
	if (argc == 1) {
	    std::cout << "*.exe input_file output_file algorithm\nAlgorithms: naive, sum_wT, GT, edging, evr_1\n";
		return 0;
	}
	std::ifstream file(argv[1]);
	std::cin.rdbuf(file.rdbuf());
	std::ofstream cout(argv[2]);
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
	std::string algo = argv[3];
	if (!algo.compare("naive")) {
		Result result = Result();
		result.calculate_minimum(Tasks, Managers, Workers);
		cout << result.get_value() << "\n";
	}
	if (!algo.compare("sum_wT")) {
		sum_wT_algorithm wT = sum_wT_algorithm(Workers, Tasks, type_d::LAST_START);
		wT.calculate_result();
		cout << wT.result << "\n";
	}
	if (!algo.compare("GT")) {
		GT_algorithm GT = GT_algorithm(Workers, Tasks, type_d::LAST_START);
		GT.calculate_result();
		cout << GT.result << "\n";
	}
	if (!algo.compare("edging")) {
		edging_algorithm ea = edging_algorithm(Workers, Tasks, type_d::LAST_START);
		ea.calculate(Tasks, Managers, Workers);
		cout << ea.result << "\n";
	}
	if (!algo.compare("evr_1")) {
		evr_1 e1 = evr_1();
		e1.calculate_result(Tasks, Managers, Workers);
		cout << e1.result << "\n";
	}
	return 0;
}
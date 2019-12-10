#include "company.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ls.h"
#include "evr_1.h"
#include "edging.h"
#include "GT_algorithm.hpp"
#include "limits.h"
#include "sum_wT.h"

void print_lsn(vector<ulong> &task_order, bool& verbose, vector<Task>& Tasks, vector<Manager>& Managers, vector<Worker>& Workers) {
	local_search_neigh l = local_search_neigh(task_order, Tasks, Managers, Workers);
	if (verbose) {
		for (size_t i = 0; i < l.task_order.size(); ++i)
			cout << l.task_order[i] << " ";
		cout << "\n";
	}
	cout << l.result << "\n";
}

int main(int argc, char **argv) {
	if (argc == 1) {
		std::cout << "*.exe input [algorithm] [type_d] [type_sort] [local_search] [-v | --verbose]\n";
		std::cout << "algorithm: all | all-n | naive | sum_wT | GT | edging | evr_1\n";
		std::cout << "type_d (for sum_wT, GT, edging): ls | le | fs | fe | M\n";
		std::cout << "type_sort(for GT, edging): max_min | min_max\n";
		std::cout << "local_search: -lsn\n";
		std::cout << "Example: Azul.exe input all-n ls max_min -lsn -v\n";
		return 0;
	}
	std::string input_args;
	for (int i = 2; i < argc; ++i) {
		input_args.append(argv[i]);
	}
	bool naive = 0;
	bool sum_wT = 0;
	bool GT = 0;
	bool edging = 0;
	bool e_1 = 0;
	if ((input_args.find("all") != string::npos) && (input_args.find("all-n") == string::npos)) {
		naive = 1;
		sum_wT = 1;
		GT = 1;
		edging = 1;
		e_1 = 1;
	}
	if (input_args.find("all-n") != string::npos) {
		sum_wT = 1;
		GT = 1;
		edging = 1;
		e_1 = 1;
	}
	if (input_args.find("naive") != string::npos) {
		naive = 1;
	}
	if (input_args.find("sum_wT") != string::npos) {
		sum_wT = 1;
	}
	if (input_args.find("GT") != string::npos) {
		GT = 1;
	}
	if (input_args.find("edging") != string::npos) {
		edging = 1;
	}
	if (input_args.find("evr_1") != string::npos) {
		e_1 = 1;
	}
	type_d d_type;
	if (input_args.find("ls") != string::npos) {
		d_type = LAST_START;
	}
	if (input_args.find("le") != string::npos) {
		d_type = LAST_END;
	}
	if (input_args.find("fs") != string::npos) {
		d_type = FIRST_START;
	}
	if (input_args.find("fe") != string::npos) {
		d_type = FIRST_END;
	}
	if (input_args.find("m") != string::npos) {
		d_type = MIDDLE;
	}
	type_sort sort_type;
	if (input_args.find("min_max") != string::npos) {
		sort_type = MIN_MAX;
	}
	if (input_args.find("max_min") != string::npos) {
		sort_type = MAX_MIN;
	}
	bool lsn = 0;
	if (input_args.find("-lsn") != string::npos) {
		lsn = 1;
	}
	bool verbose = 0;
	if ((input_args.find("-v") != string::npos) || (input_args.find("--verbose") != string::npos)) {
		verbose = 1;
	}
	std::ifstream file(argv[1]);
	std::cin.rdbuf(file.rdbuf());
	std::string line;
	std::vector<std::string> input_files;
	std::vector<long long> naive_results;
	while (getline(cin, line)) {
		size_t pos = line.find(" ");
		input_files.push_back(line.substr(0, pos));
		if (pos == string::npos) {
			naive_results.push_back(-1);
		} else {
			naive_results.push_back(stoll(line.substr(pos + 1)));
		}
	}
	for (size_t i = 0; i < input_files.size(); ++i) {
		std::ifstream file(input_files[i]);
		std::cin.rdbuf(file.rdbuf());
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
		if (naive) {
			Result result = Result();
			result.calculate_minimum_parallel(Tasks, Managers, Workers);
			if (verbose) {
				for (size_t i = 0; i < result.task_order.size(); ++i)
					cout << result.task_order[i] << " ";
				cout << "\n";
			}
			cout << result.get_value() << "\n";
		}
		if (sum_wT) {
			sum_wT_algorithm wT = sum_wT_algorithm(Workers, Tasks, d_type);
			wT.calculate_result();
			if (lsn) {
				vector<ulong> wTtask_order;
				for (auto t : wT.task_order) {
					wTtask_order.push_back(t.get_type());
				}
				print_lsn(wTtask_order, verbose, Tasks, Managers, Workers);
			}
			else {
				if (verbose) {
					for (size_t i = 0; i < wT.task_order.size(); ++i)
						cout << wT.task_order[i].get_type() << " ";
					cout << "\n";
				}
				cout << wT.result << "\n";
			}
		}
		if (GT) {
			GT_algorithm GT = GT_algorithm(Workers, Tasks, Managers, d_type, sort_type);
			GT.calculate_result();
			if (lsn) {
				print_lsn(GT.task_order, verbose, Tasks, Managers, Workers);
			}
			else {
				if (verbose) {
					for (auto num : GT.task_order)
						cout << num << " ";
					cout << "\n";
				}
				cout << GT.get_result_with_managers() << "\n";
			}
		}
		if (edging) {
			edging_algorithm ea = edging_algorithm(Workers, Tasks, d_type, sort_type);
			ea.calculate(Tasks, Managers, Workers);
			if (lsn) {
				print_lsn(ea.task_order, verbose, Tasks, Managers, Workers);
			}
			else {
				if (verbose) {
					for (size_t i = 0; i < ea.task_order.size(); ++i)
						cout << ea.task_order[i] << " ";
					cout << "\n";
				}
				cout << ea.result << "\n";
			}
		}
		if (e_1) {
			evr_1 e1 = evr_1();
			e1.calculate_result(Tasks, Managers, Workers);
			if (lsn) {
				print_lsn(e1.task_order, verbose, Tasks, Managers, Workers);
			}
			else {
				if (verbose) {
					for (size_t i = 0; i < e1.task_order.size(); ++i)
						cout << e1.task_order[i] << " ";
					cout << "\n";
				}
				cout << e1.result << "\n";
			}
		}
	}
	return 0;
}
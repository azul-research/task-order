#pragma once

#include <vector>
#include <iostream>
#include <set>

class Worker {
public:
	Worker();
	Worker(long long start, long long finish, long long type, long long salary, long long id);

	friend bool operator<(const Worker w_1, const Worker w_2);
	friend std::istream &operator>> (std::istream &is, Worker &w); 

	long long get_type();
	long long get_start();
	long long get_finish();
	long long get_salary();
private:
	long long w_start;
	long long w_finish;
	long long w_type;
	long long w_salary;
	long long w_id;	
};

class Task {
public:
	Task();
	Task(long long type, long long cost);

	bool operator==(const Task& other) const;
	friend bool operator<(const Task t_1, const Task t_2);
	friend std::istream &operator>> (std::istream &is, Task &t); 
	friend std::ostream &operator<< (std::ostream &os, const Task &t);

	long long get_cost();
	long long get_type();
private:
	long long t_type;
	long long t_cost;
};

class Manager {
public:
	Manager();
	Manager(long long start, long long id);

	friend bool operator<(const Manager m_1, const Manager m_2);
	friend std::istream &operator>> (std::istream &is, Manager &m); 

	long long get_id();
	long long get_start();
private:
	long long m_start;
	long long m_id;
};

class Result {
public:
	Result();

	void calculate_result(std::vector<Task> Tasks, std::vector<Manager> Manangers, std::vector<Worker> Workers);
private:
	std::vector<std::vector<Task>> r_task_order;
	long long r_value;
};
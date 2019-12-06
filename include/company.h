#pragma once

#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "big_integer.h"

class Worker {
public:
    Worker();
    Worker(unsigned long start, unsigned long finish, unsigned long type, unsigned long salary, unsigned long id);

    friend bool operator<(const Worker w_1, const Worker w_2);
    friend std::istream &operator>> (std::istream &is, Worker &w);

    unsigned long get_type();
    unsigned long get_start();
    unsigned long get_finish();
    unsigned long get_salary();
private:
    unsigned long w_start;
    unsigned long w_finish;
    unsigned long w_type;
    unsigned long w_salary;
    unsigned long w_id;
};

class Task {
public:
    Task();
    Task(unsigned long type, unsigned long cost);

    bool operator==(const Task& other) const;
    friend bool operator<(const Task t_1, const Task t_2);
    friend std::istream &operator>> (std::istream &is, Task &t);
    friend std::ostream &operator<< (std::ostream &os, const Task &t);

    unsigned long get_cost();
    unsigned long get_type();
private:
    unsigned long t_type;
    unsigned long t_cost;
};

class Manager {
public:
    Manager();
    Manager(unsigned long start, unsigned long id);

    friend bool operator<(const Manager m_1, const Manager m_2);
    friend std::istream &operator>> (std::istream &is, Manager &m);

    unsigned long get_id();
    unsigned long get_start();
private:
    unsigned long m_start;
    unsigned long m_id;
};

class Result {
public:
    Result();

    void calculate_minimum(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers);
    void calculate_minimum_parallel(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers);
    Result calculate_result(std::vector<Task> &Tasks, std::vector<Manager> &Manangers, std::vector<Worker> &Workers);


    std::vector<big_integer> count_factorials(int n);

    unsigned long get_value();
    std::map<Manager, std::vector<Task>> get_task_order();
private:
    Result(unsigned long value, std::map<Manager, std::vector<Task>> &task_order);

    std::map<Manager, std::vector<Task>> r_task_order;
    unsigned long r_value;
    big_integer status;
};


//add function f(managers, workers, permutation) - result
//minimum calculation is another function


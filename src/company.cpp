#include "company.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <limits.h>
#include <cassert>
#include <map>

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
    return m_1.m_start < m_2.m_start || (m_1.m_start == m_2.m_start && m_1.m_id < m_2.m_id);
}


std::istream &operator>> (std::istream &is, Manager &m) {
    is >> m.m_start;
    is >> m.m_id;
    return is;
}

Result::Result() {
    r_value = ULONG_MAX;
}

Result::Result(unsigned long value, std::map<Manager, std::vector<Task>> &task_order) {
    r_value = value;
    r_task_order = task_order;
}

unsigned long Result::get_value() {
    return r_value;
}

std::map<Manager, std::vector<Task>> Result::get_task_order() {
    return r_task_order;
}

void Result::calculate_minimum(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers) {
    do {
        Result new_result = calculate_result(Tasks, Managers, Workers);
        r_value = std::min(r_value, new_result.get_value());
        if (r_value == new_result.get_value()) {
            r_task_order = new_result.get_task_order();
        }
        if (r_value == 0) {
            break;
        }
    } while (std::next_permutation(Tasks.begin(), Tasks.end()));
}

Result Result::calculate_result(std::vector<Task> &Tasks, std::vector<Manager> &Managers, std::vector<Worker> &Workers) {
    std::vector<unsigned long> completion_time(Tasks.size());
    std::set<std::pair<unsigned long, Manager>> Managers_set;
    std::map<Manager, std::vector<Task>> new_r_task_order;
    for (auto m : Managers) {
        Managers_set.insert({ m.get_start(), m });
        new_r_task_order[m] = {};
    }
    unsigned long new_r_value = 0;
    for (size_t i = 0; i < Tasks.size(); i++) {
        std::pair<unsigned long, Manager> m = *Managers_set.begin();
        Managers_set.erase(Managers_set.begin());
        m.first += Tasks[i].get_cost();
        completion_time[i] = m.first;
        Managers_set.insert(m);
        new_r_task_order[m.second].push_back({ Tasks[i] });
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
    return { Result(new_r_value, new_r_task_order) };
}

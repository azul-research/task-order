#include "company.h"

typedef unsigned long ulong;

using namespace std;

struct pdw_task {
    ulong d;
    ulong p;
    ulong id;

    pdw_task();
    pdw_task(ulong d, ulong p, ulong id);
};

struct pdw_worker {
    ulong w;
    ulong type;
    ulong start;
    ulong finish;

    pdw_worker();
    pdw_worker(ulong w, ulong type, ulong start, ulong finish);
};

enum type_d {
    FIRST_START, FIRST_END, LAST_START, LAST_END, MIDDLE
};

enum type_sort {
    MIN_MAX, MAX_MIN
};

class calculate_d {
    vector<pdw_worker> _Workers;

    ulong find_first_start(size_t id);
    ulong find_first_end(size_t id);
    ulong find_last_start(size_t id);
    ulong find_last_end(size_t id);
    ulong find_middle(size_t id);

public:
    calculate_d(vector<pdw_worker> &Workers);
    ulong find_d(size_t id, type_d type);
};

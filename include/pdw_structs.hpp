#include "company.h"

typedef unsigned long ulong;

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

    pdw_worker(ulong w, ulong type, ulong start, ulong finish);
};

class calculate_d {
    vector<pdw_worker> _Workers;
    vector<pdw_task> _Tasks;

    ulong find_first_start(int i);
    ulong find_first_end(int i);
    ulong find_last_start(int i);
    ulong find_last_end(int i);
    ulong find_middle(int i);

public:
    enum type_d {
        FS, FE, LS, LE, M
    };

    calculate_d(vector<pdw_worker> &Workers, vector<pdw_task> &Tasks);
    ulong find_d(type_d type, int i);
};

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

class calculate_d {
    vector<pdw_worker> _Workers;

    ulong find_first_start(size_t id);
    ulong find_first_end(size_t id);
    ulong find_last_start(size_t id);
    ulong find_last_end(size_t id);
    ulong find_middle(size_t id);

public:
    enum type_d {
        FS, FE, LS, LE, M
    };

    calculate_d(vector<pdw_worker> &Workers);
    ulong find_d(size_t id, type_d type);
};

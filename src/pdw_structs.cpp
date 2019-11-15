#include "pdw_structs.hpp"

calculate_d::calculate_d(vector<pdw_worker> &Workers, vector<pdw_task> &Tasks) : _Workers(Workers), _Tasks(Tasks) {

}

ulong calculate_d::find_d(type_d type, int i) {
    switch (type) {
    case FS:
        return find_first_start(i);
    case FE:
        return find_first_end(i);
    case LS:
        return find_last_start(i);
    case LE:
        return find_last_end(i);
    case M:
        return find_middle(i);
    }
}

ulong calculate_d::find_first_start(int i) {
    ulong fs = (ulong)(-1);

    for (auto w : _Workers)
        if (w.type == i && w.start < fs)
            fs = w.start;
    return fs;
}

ulong calculate_d::find_first_end(int i) {
    ulong fe = (ulong)(-1);

    for (auto w : _Workers)
        if (w.type == i && w.finish < fe)
            fe = w.finish;
    return fe;
}

ulong calculate_d::find_last_start(int i) {
    ulong ls = 0;

    for (auto w : _Workers)
        if (w.type == i && w.start > ls)
            ls = w.start;
    return ls;
}

ulong calculate_d::find_last_end(int i) {
    ulong le = 0;

    for (auto w : _Workers)
        if (w.type == i && w.finish > le)
            le = w.finish;
    return le;
}

ulong calculate_d::find_middle(int i) {
    ulong m = 0;

    return m;
}

pdw_task::pdw_task() {
}

pdw_task::pdw_task(ulong d, ulong p, ulong id) : d(d), p(p), id(id) {
}

pdw_worker::pdw_worker(ulong w, ulong type, ulong start, ulong finish) : w(w), type(type), start(start), finish(finish) {
}

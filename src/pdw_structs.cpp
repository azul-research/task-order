#include "pdw_structs.hpp"

calculate_d::calculate_d(vector<pdw_worker> &Workers) : _Workers(Workers) {

}

ulong calculate_d::find_d(size_t id, type_d type) {
    switch (type) {
    case FS:
        return find_first_start(id);
    case FE:
        return find_first_end(id);
    case LS:
        return find_last_start(id);
    case LE:
        return find_last_end(id);
    case M:
        return find_middle(id);
    }
    return -1;
}

ulong calculate_d::find_first_start(size_t id) {
    ulong fs = (ulong)(-1);

    for (auto w : _Workers)
        if (w.type == id && w.start < fs)
            fs = w.start;
    return fs;
}

ulong calculate_d::find_first_end(size_t id) {
    ulong fe = (ulong)(-1);

    for (auto w : _Workers)
        if (w.type == id && w.finish < fe)
            fe = w.finish;
    return fe;
}

ulong calculate_d::find_last_start(size_t id) {
    ulong ls = 0;

    for (auto w : _Workers)
        if (w.type == id && w.start > ls)
            ls = w.start;
    return ls;
}

ulong calculate_d::find_last_end(size_t id) {
    ulong le = 0;

    for (auto w : _Workers)
        if (w.type == id && w.finish > le)
            le = w.finish;
    return le;
}

ulong calculate_d::find_middle(size_t id) {
    ulong m = 0;

    return m;
}

pdw_task::pdw_task() {
}

pdw_task::pdw_task(ulong d, ulong p, ulong id) : d(d), p(p), id(id) {
}

pdw_worker::pdw_worker() {
}

pdw_worker::pdw_worker(ulong w, ulong type, ulong start, ulong finish) : w(w), type(type), start(start), finish(finish) {
}

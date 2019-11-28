#include "pdw_structs.hpp"

ulong GT(ulong w, ulong c, ulong start, ulong end) {
    return w * min((ulong)max(1LL * 0, 1LL * c - 1LL * start), end - start);
}

calculate_d::calculate_d(vector<pdw_worker> &Workers) : _Workers(Workers) {

}

ulong calculate_d::find_d(size_t id, type_d type) {
    switch (type) {
    case FIRST_START:
        return find_first_start(id);
    case FIRST_END:
        return find_first_end(id);
    case LAST_START:
        return find_last_start(id);
    case LAST_END:
        return find_last_end(id);
    case MIDDLE:
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
    ulong denom = 0;
    for (auto w : _Workers)
        if (w.type == id) {
            m += w.start * w.w;
            denom += w.w;
        }
    m /= (double)denom;
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

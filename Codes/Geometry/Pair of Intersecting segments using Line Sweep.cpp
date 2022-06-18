/*
Checking for the intersection of two segments is carried out by the intersect ()
function, using an algorithm based on the oriented area of the triangle.

The queue of segments is the global variable s, a set<event>. Iterators that
specify the position of each segment in the queue (for convenient removal of
segments from the queue) are stored in the global array where.

Two auxiliary functions prev() and next() are also introduced, which return
iterators to the previous and next elements (or end(), if one does not exist).
*/
Tf yvalSegment(const Line &s, Tf x) {
    if (dcmp(s.a.x - s.b.x) == 0) return s.a.y;
    return s.a.y + (s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
}

struct SegCompare {
    bool operator()(const Segment &p, const Segment &q) const {
        Tf x = max(min(p.a.x, p.b.x), min(q.a.x, q.b.x));
        return dcmp(yvalSegment(p, x) - yvalSegment(q, x)) < 0;
    }
};

multiset<Segment, SegCompare> st;
typedef multiset<Segment, SegCompare>::iterator iter;

iter prev(iter it) { return it == st.begin() ? st.end() : --it; }

iter next(iter it) { return it == st.end() ? st.end() : ++it; }

struct Event {
    Tf x;
    int tp, id;
    Event(Ti x, int tp, int id) : x(x), tp(tp), id(id) {}
    bool operator<(const Event &p) const {
        if (dcmp(x - p.x)) return x < p.x;
        return tp > p.tp;
    }
};

bool anyIntersection(const vector<Segment> &v) {
    using Linear::segmentsIntersect;
    vector<Event> ev;
    for (int i = 0; i < (int)v.size(); ++i) {
        ev.push_back(Event(min(v[i].a.x, v[i].b.x), +1, i));
        ev.push_back(Event(max(v[i].a.x, v[i].b.x), -1, i));
    }
    sort(ev.begin(), ev.end());

    st.clear();
    vector<iter> where(v.size());
    for (auto &cur : ev) {
        int id = cur.id;
        if (cur.tp == 1) {
            iter nxt = st.lower_bound(v[id]);
            iter pre = prev(nxt);
            if (pre != st.end() && segmentsIntersect(*pre, v[id])) return true;
            if (nxt != st.end() && segmentsIntersect(*nxt, v[id])) return true;
            where[id] = st.insert(nxt, v[id]);
        } else {
            iter nxt = next(where[id]);
            iter pre = prev(where[id]);
            if (pre != st.end() && nxt != st.end() &&
                segmentsIntersect(*pre, *nxt))
                return true;
            st.erase(where[id]);
        }
    }
    return false;
}

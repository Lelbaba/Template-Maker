Tf distancePointLine(Point p, Line l) {
    return abs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
}

// returns the shortest distance from point a to segment s
Tf distancePointSegment(Point p, Segment s) {
    if (s.a == s.b) return length(p - s.a);
    Point v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
    if (dcmp(dot(v1, v2)) < 0)
        return length(v2);
    else if (dcmp(dot(v1, v3)) > 0)
        return length(v3);
    else
        return abs(cross(v1, v2) / length(v1));
}

// returns the shortest distance from segment p to segment q
Tf distanceSegmentSegment(Segment p, Segment q) {
    if (segmentsIntersect(p, q)) return 0;
    Tf ans = distancePointSegment(p.a, q);
    ans = min(ans, distancePointSegment(p.b, q));
    ans = min(ans, distancePointSegment(q.a, p));
    ans = min(ans, distancePointSegment(q.b, p));
    return ans;
}

// returns the projection of point p on line l
Point projectPointLine(Point p, Line l) {
    static_assert(is_same<Tf, Ti>::value);
    Point v = l.b - l.a;
    return l.a + v * ((Tf)dot(v, p - l.a) / dot(v, v));
}
// returns the left side of polygon u after cutting it by ray a->b
Polygon cutPolygon(Polygon u, Point a, Point b) {
    using Linear::lineLineIntersection, Linear::onSegment;

    Polygon ret;
    int n = u.size();
    for (int i = 0; i < n; i++) {
        Point c = u[i], d = u[(i + 1) % n];
        if (dcmp(cross(b - a, c - a)) >= 0) ret.push_back(c);
        if (dcmp(cross(b - a, d - c)) != 0) {
            Point t;
            lineLineIntersection(a, b - a, c, d - c, t);
            if (onSegment(t, Segment(c, d))) ret.push_back(t);
        }
    }
    return ret;
}
// returns false if points are collinear, true otherwise
// circle p touch each arm of triangle abc
bool inscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::distancePointLine;
    static_assert(is_same<Tf, Ti>::value);
    if (orient(a, b, c) == 0) return false;
    Tf u = length(b - c);
    Tf v = length(c - a);
    Tf w = length(a - b);
    p.o = (a * u + b * v + c * w) / (u + v + w);
    p.r = distancePointLine(p.o, Line(a, b));
    return true;
}

// set of points A(x, y) such that PA : QA = rp : rq
Circle apolloniusCircle(Point P, Point Q, Tf rp, Tf rq) {
    static_assert(is_same<Tf, Ti>::value);
    rq *= rq;
    rp *= rp;
    Tf a = rq - rp;
    assert(dcmp(a));
    Tf g = (rq * P.x - rp * Q.x) / a, h = (rq * P.y - rp * Q.y) / a;
    Tf c =
        (rq * P.x * P.x - rp * Q.x * Q.x + rq * P.y * P.y - rp * Q.y * Q.y) / a;
    Point o(g, h);
    Tf R = sqrt(g * g + h * h - c);
    return Circle(o, R);
}
// returns false if points are collinear
bool circumscribedCircle(Point a, Point b, Point c, Circle &p) {
    using Linear::lineLineIntersection;
    if (orient(a, b, c) == 0) return false;
    Point d = (a + b) / 2, e = (a + c) / 2;
    Point vd = rotate90(b - a), ve = rotate90(a - c);
    bool f = lineLineIntersection(d, vd, e, ve, p.o);
    if (f) p.r = length(a - p.o);
    return f;
}

// Following three methods implement Welzl's algorithm for
// the smallest enclosing circle problem: Given a set of
// points, find out the minimal circle that covers them all.
// boundary(p) determines (if possible) a circle that goes
// through the points in p. Ideally |p| <= 3.
// welzl() is a recursive helper function doing the most part
// of Welzl's algorithm. Call minidisk with the set of points
// Randomized Complexity: O(CN) with C~10 (practically lesser)
// TESTED: ICPC Dhaka 2019 - I (CodeMarshal)

Circle boundary(const vector<Point> &p) {
    Circle ret;
    int sz = p.size();
    if (sz == 0)
        return Circle({0, 0}, 0);
    else if (sz == 1)
        ;
    else if (sz == 2)
        ret.o = (p[0] + p[1]) / 2, ret.r = length(p[0] - p[1]) / 2;
    else if (!circumscribedCircle(p[0], p[1], p[2], ret))
        ret.r = 0;
    return ret;
}
Circle welzl(const vector<Point> &p, int fr, vector<Point> &b) {
    if (fr >= (int)p.size() || b.size() == 3) return boundary(b);

    Circle c = welzl(p, fr + 1, b);
    if (!c.contains(p[fr])) {
        b.push_back(p[fr]);
        c = welzl(p, fr + 1, b);
        b.pop_back();
    }
    return c;
}
Circle minidisk(vector<Point> p) {
    random_shuffle(p.begin(), p.end());
    vector<Point> q;
    return welzl(p, 0, q);
}

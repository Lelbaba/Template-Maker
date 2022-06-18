// returns the signed area of polygon p of n vertices
using Polygon = vector<Point>;
Tf signedPolygonArea(Polygon p) {
    Tf ret = 0;
    for (int i = 0; i < (int)p.size() - 1; i++)
        ret += cross(p[i] - p[0], p[i + 1] - p[0]);
    return ret / 2;
}
// given a polygon p of n vertices, generates the convex hull in ch
// in CCW && returns the number of vertices in the convex hull
int convexHull(Polygon p, Polygon &ch) {
    sort(p.begin(), p.end());
    int n = p.size();
    ch.resize(n + n);
    int m = 0;  // preparing lower hull
    for (int i = 0; i < n; i++) {
        while (m > 1 &&
               dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;  // preparing upper hull
    for (int i = n - 2; i >= 0; i--) {
        while (m > k &&
               dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    ch.resize(m);
    return m;
}

// for a point o and polygon p returns:
//   -1 if o is strictly inside p
//  0 if o is on a segment of p
//  1 if o is strictly outside p
// computes via winding numbers
int pointInPolygon(Point o, Polygon p) {
    int wn = 0, n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (onSegment(o, Segment(p[i], p[j])) || o == p[i]) return 0;
        int k = dcmp(cross(p[j] - p[i], o - p[i]));
        int d1 = dcmp(p[i].y - o.y);
        int d2 = dcmp(p[j].y - o.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return wn ? -1 : 1;
}

// returns the longest line segment of l that is inside or on the
// simply polygon p. O(n lg n). TESTED: TIMUS 1955
Tf longestSegInPoly(Line l, const Polygon &p) {
    int n = p.size();
    vector<pair<Tf, int>> ev;
    for (int i = 0; i < n; ++i) {
        Point a = p[i], b = p[(i + 1) % n], z = p[(i - 1 + n) % n];
        int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b),
            orz = orient(l.a, l.b, z);
        if (!ora) {
            Tf d = dot(a - l.a, l.b - l.a);
            if (orz && orb) {
                if (orz != orb) ev.emplace_back(d, 0);
            } else if (orz)
                ev.emplace_back(d, orz);
            else if (orb)
                ev.emplace_back(d, orb);
        } else if (ora == -orb) {
            Point ins;
            lineLineIntersection(l, Line(a, b), ins);
            ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
        }
    }
    sort(ev.begin(), ev.end());

    Tf ret = 0, cur = 0, pre = 0;
    bool active = false;
    int sign = 0;
    for (auto &qq : ev) {
        int tp = qq.second;
        Tf d = qq.first;
        if (sign) {
            cur += d - pre;
            ret = max(ret, cur);
            if (tp != sign) active = !active;
            sign = 0;
        } else {
            if (active) cur += d - pre, ret = max(ret, cur);
            if (tp == 0)
                active = !active;
            else
                sign = tp;
        }
        pre = d;
        if (!active) cur = 0;
    }

    ret /= length(l.b - l.a);
    return ret;
}

// EVERYTHING AFTER THIS ONLY FOR CONVEX POLYGON
/// Tested on Kattis::fenceortho
void rotatingCalipersGetRectangle(Point *p, int n, Tf &area, Tf &perimeter) {
    static_assert(is_same<Tf, Ti>::value);
    p[n] = p[0];
    int l = 1, r = 1, j = 1;
    area = perimeter = 1e100;

    for (int i = 0; i < n; i++) {
        Point v = (p[i + 1] - p[i]) / length(p[i + 1] - p[i]);
        while (dcmp(dot(v, p[r % n] - p[i]) - dot(v, p[(r + 1) % n] - p[i])) <
               0)
            r++;
        while (j < r || dcmp(cross(v, p[j % n] - p[i]) -
                             cross(v, p[(j + 1) % n] - p[i])) < 0)
            j++;
        while (l < j || dcmp(dot(v, p[l % n] - p[i]) -
                             dot(v, p[(l + 1) % n] - p[i])) > 0)
            l++;
        Tf w = dot(v, p[r % n] - p[i]) - dot(v, p[l % n] - p[i]);
        Tf h = distancePointLine(p[j % n], Line(p[i], p[i + 1]));
        area = min(area, w * h);
        perimeter = min(perimeter, 2 * w + 2 * h);
    }
}

// returns the left side of polygon u after cutting it by ray a->b
Polygon cutPolygon(Polygon u, Point a, Point b) {
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

// returns true if point p is in or on triangle abc
bool pointInTriangle(Point a, Point b, Point c, Point p) {
    return dcmp(cross(b - a, p - a)) >= 0 && dcmp(cross(c - b, p - b)) >= 0 &&
           dcmp(cross(a - c, p - c)) >= 0;
}

// Tested : https://www.spoj.com/problems/INOROUT
// pt must be in ccw order with no three collinear points
// returns inside = -1, on = 0, outside = 1
int pointInConvexPolygon(const Polygon &pt, Point p) {
    int n = pt.size();
    assert(n >= 3);

    int lo = 1, hi = n - 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (dcmp(cross(pt[mid] - pt[0], p - pt[0])) > 0)
            lo = mid;
        else
            hi = mid;
    }

    bool in = pointInTriangle(pt[0], pt[lo], pt[hi], p);
    if (!in) return 1;

    if (dcmp(cross(pt[lo] - pt[lo - 1], p - pt[lo - 1])) == 0) return 0;
    if (dcmp(cross(pt[hi] - pt[lo], p - pt[lo])) == 0) return 0;
    if (dcmp(cross(pt[hi] - pt[(hi + 1) % n], p - pt[(hi + 1) % n])) == 0)
        return 0;
    return -1;
}

// Extreme Point for a direction is the farthest point in that direction
// O'Rourke, page 270, http://crtl-i.com/PDF/comp_c.pdf
// also https://codeforces.com/blog/entry/48868
// poly is a convex polygon, sorted in CCW, doesn't contain redundant points
// u is the direction for extremeness
int extremePoint(const Polygon &poly, Point u = Point(0, 1)) {
    int n = (int)poly.size();
    int a = 0, b = n;
    while (b - a > 1) {
        int c = (a + b) / 2;
        if (dcmp(dot(poly[c] - poly[(c + 1) % n], u)) >= 0 &&
            dcmp(dot(poly[c] - poly[(c - 1 + n) % n], u)) >= 0) {
            return c;
        }

        bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
        bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
        bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;

        if (a_up && !c_up)
            b = c;
        else if (!a_up && c_up)
            a = c;
        else if (a_up && c_up) {
            if (a_above_c)
                b = c;
            else
                a = c;
        } else {
            if (!a_above_c)
                b = c;
            else
                a = c;
        }
    }

    if (dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 &&
        dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
        return a;
    return b % n;
}

// For a convex polygon p and a line l, returns a list of segments
// of p that are touch or intersect line l.
// the i'th segment is considered (p[i], p[(i + 1) modulo |p|])
// #1 If a segment is collinear with the line, only that is returned
// #2 Else if l goes through i'th point, the i'th segment is added
// If there are 2 or more such collinear segments for #1,
// any of them (only one, not all) should be returned (not tested)
// Complexity: O(lg |p|)
vector<int> lineConvexPolyIntersection(const Polygon &p, Line l) {
    assert((int)p.size() >= 3);
    assert(l.a != l.b);

    int n = p.size();
    vector<int> ret;

    Point v = l.b - l.a;
    int lf = extremePoint(p, rotate90(v));
    int rt = extremePoint(p, rotate90(v) * Ti(-1));
    int olf = orient(l.a, l.b, p[lf]);
    int ort = orient(l.a, l.b, p[rt]);

    if (!olf || !ort) {
        int idx = (!olf ? lf : rt);
        if (orient(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
            ret.push_back((idx - 1 + n) % n);
        else
            ret.push_back(idx);
        return ret;
    }
    if (olf == ort) return ret;

    for (int i = 0; i < 2; ++i) {
        int lo = i ? rt : lf;
        int hi = i ? lf : rt;
        int olo = i ? ort : olf;

        while (true) {
            int gap = (hi - lo + n) % n;
            if (gap < 2) break;

            int mid = (lo + gap / 2) % n;
            int omid = orient(l.a, l.b, p[mid]);
            if (!omid) {
                lo = mid;
                break;
            }
            if (omid == olo)
                lo = mid;
            else
                hi = mid;
        }
        ret.push_back(lo);
    }
    return ret;
}

// Tested : https://toph.co/p/cover-the-points
// Calculate [ACW, CW] tangent pair from an external point
constexpr int CW = -1, ACW = 1;
bool isGood(Point u, Point v, Point Q, int dir) {
    return orient(Q, u, v) != -dir;
}
Point better(Point u, Point v, Point Q, int dir) {
    return orient(Q, u, v) == dir ? u : v;
}
Point pointPolyTangent(const Polygon &pt, Point Q, int dir, int lo, int hi) {
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        bool pvs = isGood(pt[mid], pt[mid - 1], Q, dir);
        bool nxt = isGood(pt[mid], pt[mid + 1], Q, dir);

        if (pvs && nxt) return pt[mid];
        if (!(pvs || nxt)) {
            Point p1 = pointPolyTangent(pt, Q, dir, mid + 1, hi);
            Point p2 = pointPolyTangent(pt, Q, dir, lo, mid - 1);
            return better(p1, p2, Q, dir);
        }

        if (!pvs) {
            if (orient(Q, pt[mid], pt[lo]) == dir)
                hi = mid - 1;
            else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        if (!nxt) {
            if (orient(Q, pt[mid], pt[lo]) == dir)
                lo = mid + 1;
            else if (better(pt[lo], pt[hi], Q, dir) == pt[lo])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
    }

    Point ret = pt[lo];
    for (int i = lo + 1; i <= hi; i++) ret = better(ret, pt[i], Q, dir);
    return ret;
}
// [ACW, CW] Tangent
pair<Point, Point> pointPolyTangents(const Polygon &pt, Point Q) {
    int n = pt.size();
    Point acw_tan = pointPolyTangent(pt, Q, ACW, 0, n - 1);
    Point cw_tan = pointPolyTangent(pt, Q, CW, 0, n - 1);
    return make_pair(acw_tan, cw_tan);
}


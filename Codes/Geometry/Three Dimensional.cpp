
point get_perp(point p){ // returns a random perpendicular line to the vector p
    assert(sgn(norm(p)));

    point ret = point(-p.y, p.x, 0);
    if(sgn(norm(ret))) return ret;

    ret = point(0, -p.z, p.y);
    if(sgn(norm(ret))) return ret;

    assert(false)
}

struct plane{ // Caution: directed plane, directed on the direction of (p2 x p3)

	point n; // {a, b, c}
	double d; //ax + by + cz = d
	// d = n . p [ where p is any point on the plane ]

	plane(){;}
	plane(point _n, double _d){
        n = _n;
        d = _d;
	}
	plane(point p1, point p2, point p3){
		n = crsp(p2 - p1, p3 - p1);
		if(norm(n) < eps) {assert(false);} // doesn't define a plance
		d = dotp(p1, n);
	}

    //Preserves the direction
	point get_p1(){ return univ(n) * d / norm(n);}
	point get_p2(){ return get_p1() + get_perp(n);}
	point get_p3(){ return crsp(n, get_p2() - get_p1()) + get_p1();}

	int get_side(point p){ return sgn(dotp(n, p) - d);} ///OK
	double sgn_dist(point p) {return (dotp(n, p) - d) / norm(n);}
	double dist(point p) {return fabs(sgn_dist(p));}

	point project(point p){ return p - sgn_dist(p) * univ(n);}
	point reflect(point p){ return p - 2 * sgn_dist(p) * univ(n);}

    ///OK
    point get_coords(point p){ // "2-D"-fies the plane. All points on this plane have z = 0
        point O = get_p1();
        point ox = univ(get_p2() - O);
        point oy = univ(get_p3() - O);
        point oz = univ(n);
        p = p - O;
        return {dotp(p, ox), dotp(p, oy), dotp(p, oz)};
    }
};

plane translate(plane p, point t) {return {p.n, p.d + dotp(p.n, t)};}
plane shiftUp(plane p, double d) {return {p.n, p.d + d * norm(p.n)};}


point projection(point p, point st, point ed) { return dotp(ed - st, p - st) / norm(ed - st) * univ(ed - st) + st;} //OK
point extend(point st, point ed, double len) { return ed + univ(ed-st) * len;} //OK

point rtt(point axis, point p, double theta){
    axis = univ(axis);
    return p * cos(theta) +  sin(theta) * crsp(axis, p) + axis * (1-cos(theta)) * dotp(axis, p);
} //OK

point segmentProjection(point p, point st, point ed)
{
    double d = dotp(p - st, ed - st) / norm(ed - st);
    if(d < 0) return st;
    if(d > norm(ed - st) + eps) return ed;
    return st + univ(ed - st) * d;
} //OK

double distPointSegment(point p, point st, point ed) {return norm(p - segmentProjection(p, st, ed)); } //OK
double distPointLine( point P, point st, point ed) { return norm( projection(P, st, ed) - P ); } //OK

double pointPlanedist(plane P, point q){ return fabs(dotp(P.n, q) - P.d) / norm(P.n);}
double pointPlanedist(point p1, point p2, point p3, point q){ return pointPlanedist(plane(p1,p2,p3), q); } //OK

point reflection(point p, point st, point ed){
    point proj = projection(p, st, ed);
    if(p != proj) return extend(p, proj, norm(p - proj));
    return proj;
} //OK

bool coplanar(point p1, point p2, point p3, point q)
{
    p2 = p2-p1, p3 = p3-p1, q = q-p1;
    if( fabs( dotp(q, crsp(p2, p3)) ) < eps ) return true;
    return false;
}

int linePlaneIntersection(point u, point v, point l, point m, point r, point &x){
    /*
        -> l, m, r defines the plane
        -> u, v defines the line
        -> returns 0 when does not intersect
        -> returns 1 when there exists one unique common point
        -> returns -1 when there exists infinite number of common point
    */

    assert(l != m && m != r && l != r && u != v);
    if(coplanar(l, m, r, u) && coplanar(l, m, r, v)) return -1;
    l = l - m;
    r = r - m;
    u = u - m;
    v = v - m;

    point C = crsp(l, r);
    double denom = dotp(v - u, C);
    if(fabs(denom) < eps) return 0;

    double alpha = -dotp(C, u) / denom;
    x = u + (v - u) * alpha + m;

    return 1;
}

double angle(point u, point v) { return acos( max(-1.0, min(1.0, dotp(u, v) / (norm(u) * norm(v)))) );}

struct line3d{ //directed
    point d, o; // dir = direction, o = online point

    line3d(point p, point q){
        d = q - p;
        o = p;
        assert(sgn(norm(d)));
    }

    line3d(plane p1, plane p2){
        d = crsp(p1.n, p2.n);
        o = (crsp(p2.n*p1.d - p1.n*p2.d, d))/sq(d);
    }

    point get_p1(){return o;}
    point get_p2(){return o + d;}

    double dist(point p){ return norm(crsp(d, p - o)) / norm(d);};
    point project(point p){ return projection(p, o, o + d); }
    point reflect(point p) {return reflection(p, o, o + d);}
};

line3d perpThrough(plane p, point o){return line3d(o, o + p.n);}
plane perpThrough(line3d l, point o){return plane(l.d, dotp(l.d, o));}

double dist(line3d l1, line3d l2) {
    point n = crsp(l1.d, l2.d);
    if (!sgn(norm(n))) return l1.dist(l2.o);
    return abs(dotp(l2.o-l1.o, n))/norm(n);
}

point closestOnL1(line3d l1, line3d l2) {
    point n2 = crsp(l2.d, crsp(l1.d, l2.d));
    return l1.o + (l1.d * (dotp(l2.o-l1.o, n2))) / dotp(l1.d,n2);
}

double angle(plane p1, plane p2){return angle(p1.n, p2.n);}
bool isparallel(plane p1, plane p2){return !sgn(norm(crsp(p1.n, p2.n)));}
bool isperp(plane p1, plane p2) {return !sgn(dotp(p1.n, p2.n));}


double angle(line3d l1, line3d l2){return angle(l1.d, l2.d);}
bool isparallel(line3d l1, line3d l2){return !sgn(norm(crsp(l1.d, l2.d)));}
bool isperp(line3d l1, line3d l2) {return !sgn(dotp(l1.d, l2.d));}


double angle(plane p, line3d l) {return pi/2 - angle(p.n, l.d);}
bool isParallel(plane p, line3d l) {return !sgn(dotp(p.n, l.d));}
bool isPerpendicular(plane p, line3d l) {return !sgn(norm(crsp(p.n, l.d)));}

point vector_area2(vector <point> &poly){
    point S = {0, 0, 0};
    for(int i = 0; i < (int) poly.size(); i++)
        S = S + crsp(poly[i], poly[ (i + 1) % poly.size()]);
    return S;
}

double area(vector < point > &poly){ // All points must be co-planer
    return norm(vector_area2(poly)) * 0.5;
}

/*
    Polyhedrons
*/

bool operator <(point p, point q) { ///OK
    return tie(p.x, p.y, p.z) < tie(q.x, q.y, q.z);
}

struct edge {
    int v;
    bool same; // = is the common edge in the same order?
};

// Given a series of faces (lists of points), reverse some of them
// so that their orientations are consistent [ every face then will point in the same direction, inside / outside ]
void reorient(vector< vector<point> > &fs) {
    int n = fs.size();
    // Find the common edges and create the resulting graph
    vector< vector<edge>    > g(n);
    map<pair<point,point>, int> es;
    for (int u = 0; u < n; u++) {
        for (int i = 0, m = fs[u].size(); i < m; i++) {
            point a = fs[u][i], b = fs[u][(i+1)%m];
            // Let look at edge [AB]
            if (es.count({a,b})) { // seen in same order
                int v = es[{a,b}];
                g[u].push_back({v,true});
                g[v].push_back({u,true});
            }
            else if (es.count({b,a})) { // seen in different order
                    int v = es[{b,a}];
                    g[u].push_back({v,false});
                    g[v].push_back({u,false});
            }
            else es[{a,b}] = u;
        }
    }

    vector<bool> vis(n,false), flip(n);
    flip[0] = false;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (edge e : g[u]) {
            if (!vis[e.v]) {
                vis[e.v] = true;
                // If the edge was in the same order,
                // exactly one of the two should be flipped
                flip[e.v] = (flip[u] ^ e.same);
                q.push(e.v);
            }
        }
    }

    for (int u = 0; u < n; u++)
        if (flip[u])
            reverse(fs[u].begin(), fs[u].end());
}

double volume(vector< vector<point> > fs) {
    double vol6 = 0.0;
    for (vector<point> f : fs)
        vol6 += dotp(vector_area2(f), f[0]);
    return abs(vol6) / 6.0;
}


/*
    Spherical Co-ordinate System
*/

point sph(double r, double lat, double lon) { // lat, lon in degrees
    lat *= pi/180, lon *= pi/180;
    return {r*cos(lat)*cos(lon), r*cos(lat)*sin(lon), r*sin(lat)};
}

double greatCircleDist(point o, double r, point a, point b) {
    return r * angle(a-o, b-o);
}

int main()
{

    plane p = {point(0, 0, 10), point(0, 1, 10), point(1, 0, 10)};
//    plane q = {p.get_p1(), p.get_p2(), p.get_p3()};
    double d = dotp(p.get_p2() - p.get_p1(), p.get_p3() - p.get_p1());

    D(eq(d, 0))
    return 0;
}


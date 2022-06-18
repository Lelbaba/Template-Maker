template <typename DT>
class line{
    public:
        point <DT> dir, O; // direction of vector and starting point
    line(point <DT> p,point <DT> q): dir(q - p), O(p) {};

    bool Contains(const point <double> &p){ 
        return fabs(p - O & dir ) < EPS;
    } // checks whether the line Contains a certain point
    template <typename XT> point <XT> At(XT t){
        return point <XT> (dir) * t + O;
    } // inserts value of t in the vector representation, finds the point which is O + Dir*t
    double AtInv(const point <double> &p){
        return abs(dir.x) > 0 ? (p - O).x / dir.x : (p - O).y / dir.y;
    } // if the line Contains a point, gives the value t such that, p = O+Dir*t
    line Perp(point <DT> p){
        return line(p, p + (-dir.y,dir.x));
    }
    point <DT> ProjOfPoint(const point <DT> &P) {
        return O + dir * ((P - O) ^ dir) / (~dir);
    }
    double DisOfPoint(const point <DT> &P) {
        return fabs(dir & (P - O))/sqrt(~(dir));   
    }
    friend bool Parallel(line& L, line& R){
        return fabs(R.dir & L.dir) < EPS;
    }
    friend int Intersects(line& L, line& R){
        return Parallel(L, R) ? R.Contains(L.O) ? -1 : 0 : 1;
    }
    friend pair <double, double> IntersectionAt(line &L, line &R){
        double r = double((L.O - R.O) & L.dir)/(R.dir & L.dir);
        double l = double((R.O - L.O) & R.dir)/(L.dir & R.dir);
        return {l, r};
    }
    friend pair <int, point<double>> IntersectionPoint(line L, line R,int _L = 0, int _R = 0){
        // _L and _R can be 0 to 3, 0 is a normal line, 3 is a segment, 1 and 2 are rays (considered bitwise)
        int ok = Intersects(L, R);
        if(ok == 0)
            return {0, {0, 0}};
        if(ok == 1){
            auto [l,r] = IntersectionAt(L, R);
            if(l < (0-EPS) and _L & 2 )
                return {0, {0, 0}};
            if(l > (1+EPS) and _L & 1)
                return {0, {0, 0}};
            if(r < (0-EPS) and _R & 2 )
                return {0, {0, 0}};
            if(r > (1+EPS) and _R & 1)
                return {0, {0, 0}};
            return {1, L.At(l)};
        }
        return {-1, {0,0}}; // they are the same line
    }
};
template <typename DT> 
class circle {
    public:
        point <DT> O;
        DT R;
    circle(const point <DT> &O = {0, 0},  DT R = 0) : O(O), R(R) {}
    // the next two make sense only on circle <double>
    circle(const point <DT> &A, const point <DT> &B, const point <DT> &C){
        point <DT> X = (A + B) / 2, Y = (B + C) / 2, d1 = Perp(A - B), d2 = Perp(B - C);
        O = IntersectionPoint(line(X, d1), line(Y, d2)).second;
        R = sqrt(~(O - A));
    }
    circle(const point <DT> &A, const point <DT> &B, DT R){
        point <DT> X = (A + B) / 2, d = Perp(A - B);
        d = d * (R / sqrt(~(d)));
        O = X + d;
        R = sqrt(~(O - A));
    }
    double SectorArea(double ang) {
        // Area of a sector of cicle
        return ang* R * R * .5;
    }
    double SectorArea(const point <DT> &a, const point <DT> &b) {
        return SectorArea(Angle(a - O, b - O));
    }
    double ChordArea(const point <DT> &a, const point <DT> &b) {
        // Area between sector and its chord
        return SectorArea(a, b) - 0.5 * TriArea(O, a, b);
    }
    int Contains(const point <DT> &p){
        // 0 for outside, 1 for inside, -1 for on the circle
        DT d = DisSq(O, p);
        return d > R * R ? 0 : (d == R * R ? -1 : 1);
    }
    friend tuple <int, point <DT>, point <DT>> IntersectionPoint(const circle &a,const circle &b) {
        if(a.R == b.R and a.O == b.O)
            return {-1, {0, 0}, {0, 0}};
        double d = sqrt(DisSq(a.O, b.O));
        if(d > a.R + b.R or d < fabs(a.R - b.R))
            return {0, {0, 0}, {0, 0}};
        double z = (sq(a.R) + sq(d) - sq(b.R)) / (2 * d);
        double y = sqrt(sq(a.R) - sq(z));
        point <DT> O = b.O - a.O, h = Perp(O) * (y / sqrt(~O));
        O = a.O + O * (z / sqrt(~O));
        return make_tuple(1 + (~(h) > EPS), O - h, O + h);
    }
    friend tuple <int, point <DT>, point <DT>> IntersectionPoint(const circle &C, line <DT> L) {
        point <DT> P = L.ProjOfPoint(C.O);
        double D = DisSq(C.O, P);
        if(D > C.R * C.R)
            return {0, {0, 0}, {0, 0}};
        double x = sqrt(C.R * C.R - D); 
        point <DT> h = L.dir * (x / sqrt(~L.dir));
        return {1 + (x > EPS), P - h, P + h};
    } 
    double SegmentedArea(point <DT> &a,  point <DT> &b) {
        // signed area of the intersection between the circle and triangle OAB
        double ans = SectorArea(a, b);
        line <DT> L(a, b);
        auto [cnt, p1, p2] = IntersectionPoint(*this, L);
        if(cnt < 2)
            return ans;
        double t1 = L.AtInv(p1), t2 = L.AtInv(p2);
        if(t2 < 0 or t1 > 1)
            return ans;
        if(t1 < 0)
            p1 = a;
        if(t2 > 1)
            p2 = b;
        return ans - ChordArea(p1, p2);
    }
};

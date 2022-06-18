const double PI = acos(-1), EPS = 1e-10;
template <typename DT> DT sq(DT x) {return x * x; }
template <typename DT> int dcmp(DT x) { return fabs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

template <typename DT> 
class point{
    public:
        DT x,y;
    point() = default;
    point(DT x, DT y): x(x), y(y) {};
    template <typename X> point(point <X> p): x(p.x), y(p.y) {};
    //opeartions on complex numbers
    point operator * (point rhs) const { return point(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);}
    point operator / (point rhs) const { return *this * point(rhs.x, - rhs.y) / ~(rhs);}

    bool  operator < (point rhs) const { return x < rhs.x or (x == rhs.x and y < rhs.y); }
    DT operator & (point rhs)     const { return x * rhs.y - y * rhs.x; }     // cross product
    DT operator ^ (point rhs)     const { return x * rhs.x + y * rhs.y; }     // dot product
    DT operator ~()     const {return sq(x) + sq(y); }                        //square of norm
    friend istream& operator >> (istream &is, point &p) { return is >> p.x >> p.y; }
    
    friend DT DisSq(point a, point b){ return sq(a.x-b.x) + sq(a.y-b.y); }
    friend DT TriArea(point a, point b, point c) { return (b-a) & (c-a); }
    friend DT UTriArea(point a, point b, point c) { return abs(TriArea(a, b, c)); }
    friend bool Collinear(point a, point b, point c) { return UTriArea(a, b, c) < EPS; }
    friend double Angle(point u) { return atan2(u.y, u.x); }
    friend double Angle(point a, point b) {
        double ans = Angle(b) - Angle(a);
        return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
    }
    friend point Perp(point a){
        return point(-a.y, a.x);
    }
    friend operator Orientation(point a, point b, point c) {return dcmp(TriArea(a, b, c));}
};
template <typename DT> using polygon = vector <point <DT>>; 
template <typename DT> 
class polarComp {
    point <DT> O, dir;
    bool half(point  <DT> p) {
        return dcmp(dir & p) < 0 || (dcmp(dir & p) == 0 && dcmp(dir ^ p) > 0);
    }
    public:
    polarComp(point <DT> O = point(0, 0), point <DT> dir = point(1, 0))
        : O(O), dir(dir) {}
  
    bool operator() (point <DT> p, point <DT> q) {
        return make_tuple(half(p), 0) < make_tuple(half(q), (p & q));
    }
}; // given a pivot point and an initial direction, sorts by Angle with the given direction

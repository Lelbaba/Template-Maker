
template <typename DT> DT FarthestPairOfPoints(polygon <DT> p){
    p = ConvexHull(p);
    int n = p.size();
    DT ans = -1e9;
    for(int i = 0, j = 1; i < n; i++)
    {   
        for( ; UTriArea(p[i], p[(i + 1) % n], p[(j + 1) % n]) > UTriArea(p[i], p[(i + 1) % n], p[j]) ; j = (j + 1) % n ) ;
        ans = max(ans, DisSq(p[i], p[j]));
        ans = max(ans, DisSq(p[(i + 1) % n], p[j]));
    }
    return ans; // will return square of the answer.
}
template <typename DT> int PointInConvexPolygon(polygon <int> :: iterator b, polygon <int> :: iterator e, const point <DT> &O){
    polygon <int> :: iterator lo = b + 2, hi = e - 1, ans = e;
    while(lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        if(TriArea(*b, O, *mid) >= 0) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    if (ans == e or abs(UTriArea(*b, *(ans - 1), *ans) - UTriArea(*b, *(ans - 1), O) - UTriArea(*b, *ans, O) - UTriArea(*(ans - 1), *ans, O)) > EPS)
        return 0;
    else return (Collinear(*b, *(b + 1), O) or Collinear(*(e - 1), *b, O) or Collinear(*(ans), *(ans - 1), O)) ? -1 : 1;
} // 0 for outside, -1 for on border, 1 for inside

template <typename DT> int PointInPolygon(polygon <DT> &P, point <DT> pt) {
    int n = P.size();
    int cnt = 0;
    for(int i = 0, j = 1; i < n; i++, j = (j + 1) % n) {
        if(TriArea(pt, P[i], P[j]) == 0 and min(P[i], P[j]) <= pt and pt <= max(P[i], P[j]))
            return -1;
        cnt += ((P[j].y >= pt.y) - (P[i].y >= pt.y)) * TriArea(pt, P[i], P[j]) > 0; 
    }
    return cnt & 1;
}

// returns 1e9 if the point is on the polygon 
int winding_number(vector<PT> &p, const PT& z) { // O(n)
    if (is_point_on_polygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].y < z.y;
        if (below != (p[j].y < z.y)) {
            auto orient = orientation(z, p[j], p[i]);
            if (orient == 0) return 0;
            if (below == (orient > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { // O(n)
    int k = winding_number(p, z);
    return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}
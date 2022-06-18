template <typename DT> polygon <DT> ConvexHull(polygon <DT> &PT){
    sort(PT.begin(), PT.end());
    int m = 0, n = PT.size();
    
    polygon <DT> hull(n + n + 2);
    for(int i = 0; i < n; i++){ 
        for( ; m > 1 and TriArea(hull[m-2], hull[m-1], PT[i]) <= 0; m-- );
        hull[m++] = PT[i];
    }
    for(int i = n - 2, k = m; i >= 0; i--){
        for( ; m > k and TriArea(hull[m - 2], hull[m - 1], PT[i]) <= 0; m--);
        hull[m++] = PT[i];
    }
    if(n > 1) 
        m--;
    while(hull.size() > m) 
        hull.pop_back();
    return hull;
}

template <typename DT> double MinimumBoundingBox(polygon <DT> P){
    auto p = ConvexHull(P);
    int n = p.size();
    double area = 1e20 + 5;
    for(int i = 0, l = 1, r = 1, u = 1 ;   i < n ;   i++){
        point <DT> edge = (p[(i+1)%n]- p[i])/sqrt(DisSq(p[i], p[(i+1)%n]));

        for( ; (edge ^ p[r%n]-p[i]) < (edge ^ p[(r+1)%n] - p[i]); r++); 
        for( ; u<r || (edge & p[u%n] - p[i]) < (edge & p[(u+1)%n] - p[i]); u++) ;
        for( ; l<u || (edge ^ p[l%n] - p[i]) > (edge ^ p[(l+1)%n] - p[i]); l++);
        
        double w = (edge ^ p[r%n]-p[i]) - (edge ^ p[l%n] - p[i]);
        double h = UTriArea(p[u%n], p[i], p[(i+1)%n])/sqrt(DisSq(p[i], p[(i+1)%n]));
        area = min(area,w*h);
    }
    if(area>1e19) 
        area = 0;
    return area;
}

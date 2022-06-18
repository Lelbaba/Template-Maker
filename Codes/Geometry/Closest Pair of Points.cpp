LL ClosestPair(vector<pii> pts) {
    int n = pts.size();
    sort(all(pts));
    set<pii> s;

    LL best_dist = 1e18;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        int d = ceil(sqrt(best_dist));
        while (pts[i].ff - pts[j].ff >= best_dist) {
            s.erase({pts[j].ss, pts[j].ff});
            j += 1;
        }

        auto it1 = s.lower_bound({pts[i].ss - d, pts[i].ff});
        auto it2 = s.upper_bound({pts[i].ss + d, pts[i].ff});

        for (auto it = it1; it != it2; ++it) {
            int dx = pts[i].ff - it->ss;
            int dy = pts[i].ss - it->ff;
            best_dist = min(best_dist, 1LL * dx * dx + 1LL * dy * dy);
        }
        s.insert({pts[i].ss, pts[i].ff});
    }
    return best_dist;
}

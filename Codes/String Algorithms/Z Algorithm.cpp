vector<int> calcz(string s) {
    int n = s.size();
    vector<int> z(n);
    int l, r; l = r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r] == s[r - l]) r++;
            z[i] = r - l; r--;
        } else {
            int k = i - l;
            if (z[k] < r - i + 1) z[i] = z[k];
            else {
                l = i;
                while (r < n && s[r] == s[r - l]) r++;
                z[i] = r - l; r--;
            }
        }
    }
    return z;
}

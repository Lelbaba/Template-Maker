vector<vector<int> >c;
vector<int>sort_cyclic_shifts(string const& s) {
  int n = s.size();
  const int alphabet = 256;
  vector<int> p(n), cnt(alphabet, 0);
  c.clear(); c.emplace_back(); c[0].resize(n);
  for (int i = 0; i < n; i++) cnt[s[i]]++;
  for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
  c[0][p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; i++) {
    if (s[p[i]] != s[p[i - 1]]) classes++;
    c[0][p[i]] = classes - 1;
  }
  vector<int> pn(n), cn(n); cnt.resize(n);
  for (int h = 0; (1 << h) < n; h++) {
    for (int i = 0; i < n; i++) {
      pn[i] = p[i] - (1 << h);
      if (pn[i] < 0) pn[i] += n;
    }
    fill(cnt.begin(), cnt.end(), 0);
    /// radix sort
    for (int i = 0; i < n; i++) cnt[c[h][pn[i]]]++;
    for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) p[--cnt[c[h][pn[i]]]] = pn[i];
    cn[p[0]] = 0; classes = 1;
    for (int i = 1; i < n; i++) {
      pii cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
      pii prev = {c[h][p[i - 1]], c[h][(p[i - 1] + (1 << h)) % n]};
      if (cur != prev) ++classes;
      cn[p[i]] = classes - 1;
    }
    c.push_back(cn);
  }
  return p;
}
vector<int> suffix_array_construction(string s) {
  s += "!";
  vector<int> sorted_shifts = sort_cyclic_shifts(s);
  sorted_shifts.erase(sorted_shifts.begin());
  return sorted_shifts;
}
/// compare two suffixes starting at i and j with length 2^k
int compare(int i, int j, int n, int k) {
  pii a = {c[k][i], c[k][(i + 1 - (1 << k)) % n]};
  pii b = {c[k][j], c[k][(j + 1 - (1 << k)) % n]};
  return a == b ? 0 : a < b ? -1 : 1;
}
int lcp(int i, int j) {
  int log_n = c.size() - 1;
  int ans = 0;
  for (int k = log_n; k >= 0; k--) {
    if (c[k][i] == c[k][j]) {
      ans += 1 << k;
      i += 1 << k; j += 1 << k;
    }
  }
  return ans;
}
vector<int> lcp_construction(string const& s, vector<int> const& p) {
  int n = s.size();
  vector<int> rank(n, 0);
  for (int i = 0; i < n; i++) rank[p[i]] = i; 
  int k = 0;
  vector<int> lcp(n, 0);
  for (int i = 0; i < n; i++) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = p[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[rank[i]] = k;
    if (k) k--;
  }
  return lcp;
}
//kth lexicographically smallest substring (considering duplicates)
int arr[MAX], lg[MAX], mn[MAX][25];
vector<int>p, lcp;
string s;
int k;

// sparse table for min in lcp goes here

///find the rightmost position where get(l,r) > val
int khoj(int l, int r, int val) {
  int lo = l + 1, hi = r, ret = -1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (get(l, mid - 1) > val) {
      ret = mid; lo = mid + 1;
    } else hi = mid - 1;
  }
  return ret;
}
int done[MAX];
int arr[MAX];
int main() {
  fastio;
  cin >> s >> k;
  p = suffix_array_construction(s);
  lcp = lcp_construction(s, p);
  build();
  int n = s.size();
  int milaisi = 0;
  for (int i = 0; i < n; i++) {
    milaisi += done[i];
    int len = n - p[i];
    int cur = milaisi;
    /// cur = i ? lcp[i-1] : 0; this can replace all the milaisi and done parts
    while (cur < len) {
      int r = khoj(i, n - 1, cur);
      int koyta, milabo;
      if (r == -1) {
        milabo = len - cur;
        koyta = 1;
      } else {
        milabo = get(i, r - 1) - cur;
        koyta = r - i + 1;
      }
      if (koyta * milabo < k) k -= (koyta * milabo);
      else {
        int d = k / koyta; int m = k % koyta;
        if (!m) {
          cout << s.substr(p[i], cur + d) << "\n";
          return 0;
        } else {
          cout << s.substr(p[i], cur + d + 1) << "\n";
          return 0;
        }
      }
      if (r == -1) break;
      done[r + 1] -= milabo;
      cur = get(i, r - 1);
      milaisi += milabo;
    }
  }
  cout << "No such line.\n";
}

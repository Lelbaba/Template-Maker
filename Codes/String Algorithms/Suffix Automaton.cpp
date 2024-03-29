struct state {
  int len, link;
  map<char, int> next;
  bool is_clone;
  int first_pos;
  vector<int>inv_link;
};
state st[2 * MAX];
int mn[2 * MAX], mx[2 * MAX];
int sz, last;
void sa_init() {
  st[0].len = 0;
  st[0].link = -1;
  st[0].next.clear();
  sz = 1;
  last = 0;
}
void sa_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  st[cur].first_pos = st[cur].len - 1;
  st[cur].is_clone = false;
  st[cur].next.clear();
  ///for lcs of n strings
  // mn[cur] = st[cur].len;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      st[clone].next = st[q].next;
      st[clone].link = st[q].link;
      st[clone].first_pos = st[q].first_pos;
      st[clone].is_clone = true;
      ///for lcs of n strings
      // mn[clone] = st[clone].len;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}
void radix_sort() {
  for (int i = 0; i < sz; i++) cnt[st[i].len]++;
  for (int i = 1; i < sz; i++) cnt[i] += cnt[i - 1];
  for (int i = 0; i < sz; i++) order[--cnt[st[i].len]] = i;
}
// after constructing the automaton
for (int v = 1; v < sz; v++) {
  st[st[v].link].inv_link.push_back(v);
}
// output all positions of occurrences
void output_all_occurrences(int v, int P_length) {
  if (!st[v].is_clone)
    cout << st[v].first_pos - P_length + 1 << endl;
  for (int u : st[v].inv_link)
    output_all_occurrences(u, P_length);
}
//lcs of two strings
string lcs (string S, string T) {
  sa_init();
  for (int i = 0; i < S.size(); i++) sa_extend(S[i]);
  int v = 0, l = 0, best = 0, bestpos = 0;
  for (int i = 0; i < T.size(); i++) {
    while (v && !st[v].next.count(T[i])) {
      v = st[v].link; l = st[v].len;
    }
    if (st[v].next.count(T[i])) {
      v = st[v].next[T[i]]; l++;
    }
    if (l > best) best = l; bestpos = i;
  }
  return T.substr(bestpos - best + 1, best);
}
//lcs of n strings
void add_str(string s) {
  for (int i = 0; i < sz; i++) mx[i] = 0;
  int v = 0, l = 0;
  for (int i = 0; i < s.size(); i++) {
    while (v && !st[v].next.count(s[i])) {
      v = st[v].link; l = st[v].len;
    }
    if (st[v].next.count(s[i])) {
      v = st [v].next[s[i]]; l++;
    }
    mx[v] = max(mx[v], l);
  }
  for (int i = sz - 1; i > 0; i--) mx[st[i].link] = max(mx[st[i].link], mx[i]);
  for (int i = 0; i < sz; i++) mn[i] = min(mn[i], mx[i]);
}
int lcs() {
  int ret = 0;
  for (int i = 0; i < sz; i++) ret = max(ret, mn[i]);
  return ret;
}
string s[15];
int arr[MAX];
int main() {
  fastio;
  int n = 0;
  while (cin >> s[n]) n++;
  sa_init();
  for (int i = 0; i < s[0].size(); i++) sa_extend(s[0][i]);
  for (int i = 1; i < n; i++) add_str(s[i]);
  cout << lcs() << "\n";
}

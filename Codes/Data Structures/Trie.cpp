int trie[30 * 100000 + 5][2];
int mark[30 * 100000 + 5];
int node = 1;
void add(int n) {
  int now = 1;
  for (int i = 27; i >= 0; i--) {
    int d = (bool)(n & (1 << i));
    if (!trie[now][d]) trie[now][d] = ++node;
    now = trie[now][d];
    mark[now]++;
  }
}
void del(int n) {
  int now = 1;
  deque<int>v;
  for (int i = 27; i >= 0; i--) {
    int d = (bool)(n & (1 << i));
    if (trie[now][d]) {
      v.push_front(now);
      now = trie[now][d];
      mark[now]--;
    }
  }
  v.push_front(now);
  for (int i = 1; i < v.size(); i++) {
    if (!mark[v[i - 1]]) {
      if (trie[v[i]][0] == v[i - 1]) trie[v[i]][0] = 0;
      if (trie[v[i]][1] == v[i - 1]) trie[v[i]][1] = 0;
    }
  }
}

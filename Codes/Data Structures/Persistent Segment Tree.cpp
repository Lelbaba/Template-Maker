struct node {
  int val, lft, rt;
  node(int val = 0, int lft = 0, int rt = 0) : val(val), lft(lft), rt(rt) {}
};
node nodes[30 * MAX]; ///take at least 2*n*log(n) nodes
int root[MAX], sz;
inline int update(int &now, int L, int R, int idx, int val) {
  if (L > idx || R < idx) return now;
  if (L == R) {
    ++sz;
    nodes[sz] = nodes[now];
    nodes[sz].val += val;
    return sz;
  }
  int mid = (L + R) >> 1;
  int ret = ++sz;
  if (idx <= mid) {
    if (!nodes[now].lft) nodes[now].lft = ++sz;
    nodes[ret].lft = update(nodes[now].lft, L, mid, idx, val);
    nodes[ret].rt = nodes[now].rt;
  } else {
    if (!nodes[now].rt) nodes[now].rt = ++sz;
    nodes[ret].rt = update(nodes[now].rt, mid + 1, R, idx, val);
    nodes[ret].lft = nodes[now].lft;
  }
  nodes[ret].val = nodes[ nodes[ret].lft ].val + nodes[ nodes[ret].rt ].val;
  return ret;
}
inline int query(int &now, int L, int R, int i, int j) {
  if (L > j || R < i) return 0;
  if (L >= i && R <= j) return nodes[now].val;
  int mid = (L + R) >> 1;
  return query(nodes[now].lft, L, mid, i, j) + query(nodes[now].rt, mid + 1, R, i, j);
}
/// in main(make segtree for every prefix)
root[0] = 0;
for (int i = 1; i <= n; i++) root[i] = update(root[i - 1], 1, n, p[i], 1);

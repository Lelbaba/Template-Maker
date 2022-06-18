bool ap[MAX];
int id[MAX], koyta[MAX];
int d[MAX], low[MAX];
bool vis[MAX];
vii g[MAX], tree[MAX];
int d_t;
stack<int>st;
vector<vector<int>>comp;
void articulation(int u, int p) {
  vis[u] = true;
  d[u] = low[u] = ++d_t;
  int child = 0; st.push(u);
  for (int v : g[u]) {
    if (v == p) continue;
    if (!vis[v]) {
      child++;
      articulation(v, u);
      low[u] = min(low[u], low[v]);
      if (p == -1 && child > 1) ap[u] = true;
      if (low[v] >= d[u]) {
        if (p != -1) ap[u] = true;
        comp.pb({u}); int top;
        do {
          top = st.top(); st.pop();
          comp.back().pb(top);
        } while (top != v);
      }
    } else low[u] = min(low[u], d[v]);
  }
}
int node = 0;
void make_tree(int n) {
  for (int i = 1; i <= n; i++) {
    if (ap[i]) id[i] = ++node;
  }
  for (int i = 0; i < comp.size(); i++) {
    ++node;
    int cnt = 0;
    for (int u : comp[i]) {
      if (ap[u]) tree[node].pb(id[u]), tree[id[u]].pb(node), koyta[id[u]] = 1;
      else id[u] = node, cnt++;
    }
    koyta[node] = cnt;
  }
}

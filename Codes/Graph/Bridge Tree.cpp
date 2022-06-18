vector<int> tree[MAX];
bool vis[MAX];
int d[MAX], low[MAX];
int id[MAX];
int d_t;

struct edge {
  int v, rev;
  edge() {}
  edge(int v, int rev) : v(v), rev(rev) {}
};
vector<edge>g[MAX];
vector<bool>is_bridge[MAX];
queue<int>q[MAX];
int comp = 1;

void add_edge(int u, int v) {
  edge _u = edge(v, g[v].size());
  edge _v = edge(u, g[u].size());
  g[u].pb(_u);
  g[v].pb(_v);
  is_bridge[u].pb(false);
  is_bridge[v].pb(false);
}

void bridge(int u, int p) {
  vis[u] = true;
  d[u] = low[u] = ++d_t;

  for (int i = 0; i < g[u].size(); i++) {
    edge e = g[u][i]; int v = e.v;
    if (v == p) continue;
    if (!vis[v]) {
      bridge(v, u);
      low[u] = min(low[v], low[u]);
      if (low[v] > d[u]) {
        is_bridge[u][i] = true;
        is_bridge[v][e.rev] = true;
      }
    } else low[u] = min(low[u], d[v]);
  }
}

void make_tree(int node) {
  int cur = comp; q[cur].push(node);
  vis[node] = true; id[node] = cur;
  while (!q[cur].empty()) {
    int u = q[cur].front(); q[cur].pop();
    for (int i = 0; i < g[u].size(); i++) {
      edge e = g[u][i]; int v = e.v;
      if (vis[v]) continue;
      if (is_bridge[u][i]) {
        comp++;
        tree[cur].pb(comp);
        tree[comp].pb(cur);
        make_tree(v);
      } else {
        q[cur].push(v);
        vis[v] = true; id[v] = cur;
      }
    }
  }
}

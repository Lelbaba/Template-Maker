int src, sink;
int dis[MAX], q[MAX], work[MAX];
int n, m, nodes;

struct edge {
  int v, rev, cap, flow;
  edge() {}
  edge(int v, int rev, int cap) : v(v), rev(rev), cap(cap), flow(0) {}
};
vector<edge>g[MAX];

void add_edge(int u, int v, int cap, int rev = 0) {
  edge _u = edge(v, g[v].size(), cap);
  edge _v = edge(u, g[u].size(), rev);
  g[u].pb(_u);
  g[v].pb(_v);
}

bool dinic_bfs(int s) {
  fill(dis, dis + nodes, -1);
  dis[s] = 0;
  int id = 0;
  q[id++] = s;

  for (int i = 0; i < id; i++) {
    int u = q[i];
    for (int j = 0; j < g[u].size(); j++) {
      edge &e = g[u][j];
      if (dis[e.v] == -1 && e.flow < e.cap) {
        dis[e.v] = dis[u] + 1;
        q[id++] = e.v;
      }
    }
  }
  return dis[sink] >= 0;
}

int dinic_dfs(int u, int f) {
  if (u == sink) return f;
  for (int &i = work[u]; i < g[u].size(); i++) {
    edge &e = g[u][i];
    if (e.cap <= e.flow) continue;
    if (dis[e.v] == dis[u] + 1) {
      int flow = dinic_dfs(e.v, min(f, e.cap - e.flow));
      if (flow) {
        e.flow += flow;
        g[e.v][e.rev].flow -= flow;
        return flow;
      }
    }
  }
  return 0;
}

int max_flow(int _src, int _sink) {
  src = _src;
  sink = _sink;
  int ret = 0;
  while (dinic_bfs(src)) {
    fill(work, work + nodes, 0);
    while (int flow = dinic_dfs(src, INT_MAX)) {
      ret += flow;
    }
  }
  return ret;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct edge {
  int v, rev;
  ll cap, cost, flow;
  edge() {}
  edge(int v, int rev, ll cap, ll cost) : v(v), rev(rev), cap(cap), cost(cost), flow(0) {}
};
struct mcmf {
  int src, sink, nodes;
  vector<int> par, idx, Q;
  vector<bool> inq;
  vector<ll> dis;
  vector<vector<edge>> g;
  mcmf() {}
  mcmf(int src, int sink, int nodes) : src(src), sink(sink), nodes(nodes),
    par(nodes), idx(nodes), inq(nodes),
    dis(nodes), g(nodes), Q(10000005) {} // use Q(nodes) if not using random
  void add_edge(int u, int v, ll cap, ll cost, bool directed = true) {
    edge _u = edge(v, g[v].size(), cap, cost);
    edge _v = edge(u, g[u].size(), 0, -cost);
    g[u].pb(_u);
    g[v].pb(_v);
    if (!directed) add_edge(v, u, cap, cost, true);
  }
  bool spfa() {
    for (int i = 0; i < nodes; i++) {
      dis[i] = inf, inq[i] = false;
    }
    int f = 0, l = 0;
    dis[src] = 0, par[src] = -1, Q[l++] = src, inq[src] = true;
    while (f < l) {
      int u = Q[f++];
      for (int i = 0; i < g[u].size(); i++) {
        edge &e = g[u][i];
        if (e.cap <= e.flow) continue;
        if (dis[e.v] > dis[u] + e.cost) {
          dis[e.v] = dis[u] + e.cost;
          par[e.v] = u, idx[e.v] = i;
          if(!inq[e.v]) inq[e.v] = true, Q[l++] = e.v;
          // if (!inq[e.v]) {
          //   inq[e.v] = true;
          //   if (f && rnd() & 7) Q[--f] = e.v;
          //   else Q[l++] = e.v;
          // }
        }
      }
      inq[u] = false;
    }
    return (dis[sink] != inf);
  }
  pair<ll, ll> solve() {
    ll mincost = 0, maxflow = 0;
    while (spfa()) {
      ll bottleneck = inf;
      for (int u = par[sink], v = idx[sink]; u != -1; v = idx[u], u = par[u]) {
        edge &e = g[u][v];
        bottleneck = min(bottleneck, e.cap - e.flow);
      }
      for (int u = par[sink], v = idx[sink]; u != -1; v = idx[u], u = par[u]) {
        edge &e = g[u][v];
        e.flow += bottleneck;
        g[e.v][e.rev].flow -= bottleneck;
      }
      mincost += bottleneck * dis[sink], maxflow += bottleneck;
    }
    return make_pair(mincost, maxflow);
  }
}; 
// want to minimize cost and don't care about flow
// add edge from sink to dummy sink (cap = inf, cost = 0)
// add edge from source to sink (cap = inf, cost = 0)
// run mcmf, cost returned is the minimum cost

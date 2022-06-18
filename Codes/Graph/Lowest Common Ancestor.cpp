int lvl[MAX], P[MAX][25];
void dfs(int u, int par, int d) {
  lvl[u] = d;
  P[u][0] = par;
  for (int v : g[u]) {
    if (v == par) continue;
    dfs(v, u, d + 1);
  }
}

void init() {
  for (int j = 0; j < 25; j++) {
    for (int i = 0; i <= n; i++) P[i][j] = -1;
  }

  dfs(1, -1, 0);

  for (j = 1; j < 25; j++) {
    for (int i = 1; i <= n; i++) {
      if (P[i][j - 1] != -1) {
        P[i][j] = P[ P[i][j - 1] ][j - 1];
        ///to find max weight between two edges
        // weight[i][j] = max(weight[i][j-1], weight[p[i][j-1]][j-1]);
      }
    }
  }
}


int lca(int u, int v) {
  int i, lg;
  if (lvl[u] < lvl[v]) swap(u, v);

  for (lg = 0; (1 << lg) <= lvl[u]; lg++);
  lg--;

  for (i = lg; i >= 0; i--) {
    if (lvl[u] - (1 << i) >= lvl[v]) {
      u = P[u][i];
    }
  }

  if (u == v) return u;

  for (i = lg; i >= 0; i--) {
    if (P[u][i] != -1 && P[u][i] != P[v][i]) {
      u = P[u][i], v = P[v][i];
      // ret = max(ret, weight[u][i]);
      // ret = max(ret, weight[v][i]);
    }
  }
  // ret = max(ret, weight[u][0]);
  return P[u][0];
}

//Get the ancestor of node "u"
//which is "dis" distance above.
int getAncestor(int u, int dis) {
  dis = lvl[u] - dis;
  int i, lg = 0;
  for (; (1 << lg) <= lvl[u]; lg++) continue;
  lg--;

  for (i = lg; i >= 0; i--) {
    if (lvl[u] - (1 << i) >= dis) {
      u = P[u][i];
    }
  }
  return u;
}

//returns the distance between
//two nodes "u" and "v".
int dis(int u, int v) {
  if (lvl[u] < lvl[v]) swap(u, v);
  int p = lca(u, v);
  return lvl[u] + lvl[v] - 2 * lvl[p];
}

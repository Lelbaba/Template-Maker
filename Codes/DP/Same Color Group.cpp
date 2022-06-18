int prv[21]; ll cost[21][21];
ll dp[1 << 21]; int m, n;
bool ok[1 << 21];
ll solve(ll mask) {
  if (mask == (1 << m) - 1) return 0ll;
  ll &ret = dp[mask];
  if (ok[mask]) return ret;
  ok[mask] = true; ret = inf;
  for (int i = 0; i < m; i++) {
    if (!(mask & (1 << i) )) {
      ll c = 0;
      for (int j = 0; j < m; j++) {
        if ((mask & (1 << j)))
          c += cost[i][j];
      }
      ret = min(ret, c + solve((mask | (1 << i))));
    }
  }
  return ret;
}
int arr[MAX];
int main() {
  for (int i = 0; i < n; i++) {
    int val = arr[i];
    val--; prv[val]++;
    for (int j = 0; j < m; j++) {
      if (val == j) continue;
      cost[val][j] += prv[j];
    }
  }
  ll ans = solve(0);
}


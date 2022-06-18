inline void compute(int cur, int L, int R, int best_L, int best_R) {
  if (L > R) return;
  int mid = (L + R) >> 1;
  pair<ll, int>best = {inf, -1};
  for (int k = best_L; k <= min(best_R, mid); k++) {
    best = min(best, {dp[cur ^ 1][k - 1] + getCost(k, mid), k});
  }
  dp[cur][mid] = best.ff;
  int best_id = best.ss;
  compute(cur, L, mid - 1, best_L, best_id);
  compute(cur, mid + 1, R, best_id, best_R);
}
// in main
int cur = 0;
for (int i = 1; i <= n; i++) dp[1][i] = inf;
for (int guard = 1; guard <= g; guard++) {
  compute(cur, 1, n, 1, n); cur ^= 1;
}
ll ans = dp[cur ^ 1][n];

ll solve(int st, int ed) { ///recursive
  if (st == ed) {
    path[st][ed] = st;
    return 0;
  }
  ll &ret = dp[st][ed];
  if (ret != -1) return ret;
  solve(st, ed - 1); solve(st + 1, ed);
  int L = max(st, path[st][ed - 1]);
  int R = min(ed - 1, path[st + 1][ed]);
  ret = inf;
  for (int i = L; i <= R; i++) {
    ll cur = solve(st, i) + solve(i + 1, ed);
    cur += (arr[ed] - arr[st - 1]);
    if (cur < ret) ret = cur; path[st][ed] = i;
  }
  return ret;
}
///knuth for divide and conquer
int solve(int group, int pos) {
  if (!pos) return dp[group][pos] = 0;
  if (!group) return dp[group][pos] = INT_MAX;
  int &ret = dp[group][pos];
  if (ret != -1) return ret;
  int L = 1, R = pos;
  if (pos - 1 > 0) {
    solve(group, pos - 1);
    L = max(L, path[group][pos - 1]);
  }
  if (group + 1 <= m) {
    solve(group + 1, pos);
    R = min(R, path[group + 1][pos]);
  }
  ret = INT_MAX;
  for (int i = L; i <= R; i++) {
    int cur = solve(group - 1, i - 1) + 1ll * (arr[pos] - arr[i]) * (arr[pos] - arr[i]);
    if (cur < ret) {
      ret = cur;
      path[group][pos] = i;
    }
  }
  return ret;
}

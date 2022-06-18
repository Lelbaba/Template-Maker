for (int i = 1; i <= n; i++) {
  path[i][i] = i;
  dp[i][i] = 0;
}

for (int len = 2; len <= n; len++) {
  for (int st = 1; st + len - 1 <= n; st++) {
    int ed = st + len - 1;
    int L = max(st, path[st][ed - 1]);
    int R = min(ed - 1, path[st + 1][ed]);
    dp[st][ed] = INT_MAX;
    for (int i = L; i <= R; i++) {
      int cur = dp[st][i] + dp[i + 1][ed] + arr[ed] - arr[st - 1];
      if (dp[st][ed] > cur) {
        dp[st][ed] = cur;
        path[st][ed] = i;
      }
    }
  }
}
cout << dp[1][n] << "\n";
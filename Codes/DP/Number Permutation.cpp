ll dp[2][3005]; ll sum[2][3005];
int dir[3005];
int arr[MAX];
int main() {
  fastio;
  int n;
  string s;
  cin >> n >> s;
  s = '#' + s;
  s.pb('<'); ///last element less than the element placed after it
  sum[1][0] = 1;
  int cur = 0;
  for (int baki = 1; baki <= n; baki++) {
    if (s[baki] == '<') dp[cur][0] = 0;
    else dp[cur][0] = sum[cur ^ 1][baki - 1];
    for (int small = 1; small <= baki; small++) {
      if (s[baki] == '<') dp[cur][small] = sum[cur ^ 1][small - 1];
      else {
        int big = baki - small;
        dp[cur][small] = sum[cur ^ 1][small + big - 1];
        dp[cur][small] -= sum[cur ^ 1][small - 1];
        if (dp[cur][small] < 0) dp[cur][small] += MOD;
      }
    }
    sum[cur][0] = dp[cur][0];
    for (int small = 1; small <= baki; small++) {
      sum[cur][small] = (sum[cur][small - 1] + dp[cur][small]);
      if (sum[cur][small] >= MOD) sum[cur][small] -= MOD;
    }
    cur ^= 1;
  }
  ll ans = dp[cur ^ 1][n];
  cout << ans << "\n";
}


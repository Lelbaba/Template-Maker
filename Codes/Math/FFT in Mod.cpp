// need to add modulo to res[i] in Mul
vector<ll> Mul_mod(vector<ll>& a, vector<ll>& b, ll mod) {
  ll sqrt_mod = (ll)sqrtl(mod);
  vector<ll> a0(a.size()), a1(a.size());
  vector<ll> b0(b.size()), b1(b.size());
  for (int i = 0; i < a.size(); i++) {
    a0[i] = a[i] % sqrt_mod;
    a1[i] = a[i] / sqrt_mod;
  }
  for (int i = 0; i < b.size(); i++) {
    b0[i] = b[i] % sqrt_mod;
    b1[i] = b[i] / sqrt_mod;
  }
  vector<ll> a01(a.size()), b01(b.size());
  for (int i = 0; i < a.size(); i++) {
    a01[i] = a0[i] + a1[i];
    if (a01[i] >= mod) a01[i] -= mod;
  }
  for (int i = 0; i < b.size(); i++) {
    b01[i] = b0[i] + b1[i];
    if (b01[i] >= mod) b01[i] -= mod;
  }
  vector<ll> mid = Mul(a01, b01);
  vector<ll> a0b0 = Mul(a0, b0);
  vector<ll> a1b1 = Mul(a1, b1);
  for (int i = 0; i < mid.size(); i++) {
    mid[i] = (mid[i] - a0b0[i] + mod) % mod;
    mid[i] = (mid[i] - a1b1[i] + mod) % mod;
  }
  vector<ll> res = a0b0;
  for (int i = 0; i < res.size(); i++) {
    res[i] += (sqrt_mod * mid[i]) % mod;
    if (res[i] >= mod) res[i] -= mod;
  }
  sqrt_mod = (sqrt_mod * sqrt_mod) % mod;
  for (int i = 0; i < res.size(); i++) {
    res[i] += (sqrt_mod * a1b1[i]) % mod;
    if (res[i] >= mod) res[i] -= mod;
  }
  return res;
} 

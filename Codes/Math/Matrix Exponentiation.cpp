
struct matrix {
  vector<vector<ll>> mat;
  int n, m;
  matrix() {}
  matrix(int n, int m) : n(n), m(m), mat(n) {
    for (int i = 0; i < n; i++) mat[i] = vector<ll>(m);
  }

  void identity() { for (int i = 0; i < n; i++) mat[i][i] = 1; }
  void print() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) cout << mat[i][j] << " ";
      cout << "\n";
    }
  }
  vector<ll> &operator[](int i) {
    return mat[i];
  }
};

// make sure a.m == b.n
matrix operator * (matrix &a, matrix &b) {
  int n = a.n, m = b.m;
  matrix ret(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < a.m; k++) {
        ll val = (1ll * a[i][k] * b[k][j]) % MOD;
        ret[i][j] = (ret[i][j] + val) % MOD;
      }
    }
  }
  return ret;
}

matrix mat_exp(matrix &mat, ll p) {
  int n = mat.n, m = mat.m;
  matrix ret(n, m);
  ret.identity();
  matrix x = mat;

  while (p) {
    if (p & 1) ret = ret * x;
    x = x * x;
    p = p >> 1;
  }
  return ret;
}
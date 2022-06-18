vector<int> to_factoradic(ll n, int sz = 0) {
  vector<int> ret;
  int base = 1;
  while (n) {
    ret.pb(n % base);
    n /= base; base++;
  }
  while ((int)ret.size() < sz) ret.pb(0);
  reverse(ret.begin(), ret.end());
  return ret;
}
ll to_decimal(vector<int> &v) {
  int n = (int)v.size();
  ll ret = 0, base = n;
  for (int i = 0; i < n; i++, base--) {
    ret = ( ( (ret * base) % MOD ) + v[i] ) % MOD;
  }
  return ret;
}
// returns permutation of size n from given factoradic number
vector<int> to_permutation(vector<int> &v) {
  vector<int> ret;
  ordered_set<int> st;
  int n = (int)v.size();
  for (int i = 0; i < n; i++) st.insert(i);
  for (int x : v) {
    int val = *st.find_by_order(x);
    st.erase(val); ret.pb(val);
  }
  return ret;
}
// returns lexicographical index of permutation in factoradic system
vector<int> order_of_permutation(vector<int> &p) {
  vector<int> ret; ordered_set<int> st;
  int n = (int)p.size();
  for (int i = 0; i < n; i++) st.insert(i);
  for (int x : p) {
    int idx = st.order_of_key(x);
    st.erase(x); ret.pb(idx);
  }
  return ret;
}
// returns sum of indices a and b in factoradic system
vector<int> add_order(vector<int> &a, vector<int> &b) {
  int n = (int)a.size();
  vector<int> ret(n); int carry = 0;
  for (int i = n - 1, base = 1; i >= 0; i--, base++) {
    ret[i] = a[i] + b[i] + carry;
    carry = ret[i] / (base); ret[i] %= base;
  }
  return ret;
}
// returns kth lexicographically smallest permutation of size n
// 0th permutation is 0 1 2 ... n-1
vector<int> kth_permutation(int k, int n) {
  // need to handle k >= n! if necessary
  vector<int> k_factoradic = to_factoradic(k, n);
  return to_permutation(k_factoradic);
} 

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
  const ll rnd = chrono::high_resolution_clock::now().time_since_epoch().count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  ll operator() (ll x) const { return hash_f(x) ^ rnd; }
  // static int combine_hash(pii hash) { return hash.ff * 31 + hash.ss; }
  // static ll combine_hash(pll hash) { return (hash.ff << 32) ^ hash.ss; }
  // ll operator() (pll x) const { 
  //   x.ff = hash_f(x.ff) ^ rnd; x.ss = hash_f(x.ss) ^ rnd;
  //   return combine_hash(x); 
  // }
};
gp_hash_table<ll, int, custom_hash> mp;
unordered_map<ll, int, custom_hash> mp;

void compress(int n) {
  vector<int> v;
  for (int i = 0; i < n; i++) v.pb(arr[i]);
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < n; i++) {
    int zipped = lower_bound(v.begin(), v.end(), arr[i]) - v.begin() + 1;
    arr[i] = zipped;
  }
} 

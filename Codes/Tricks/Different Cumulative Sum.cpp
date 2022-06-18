///cost = sum of (i * a[i]) where i starts from the beginning for every range
///sum[] = prefix sum of value[i]
///isum[] = prefix sum of i*value[i]
ll cost(int i, int j) {
  ll ret = isum[j];
  if (i) ret -= isum[i - 1];
  ll baad = sum[j];
  if (i) baad -= sum[i - 1];
  return ret - i * baad;
} 

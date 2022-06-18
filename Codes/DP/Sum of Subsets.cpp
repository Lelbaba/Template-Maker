 //submask == all i such that mask&i == i || mask&i == mask (all i such that all 0 in mask are fixed and the 1's change)
 //sos dp memory optimized
 for (int i = 0; i < (1 << N); ++i) F[i] = A[i];
 for (int i = 0; i < N; ++i) {
   for (int mask = 0; mask < (1 << N); ++mask) {
     if (mask & (1 << i)) F[mask] += F[mask ^ (1 << i)]; /// doing -= can work like inclusion-exclusion on unset bits
   }
 } 

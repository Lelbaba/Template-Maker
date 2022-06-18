struct Bitset {
    const static int B = 6, K = 64, X = 63;
    ///returns mask with bits l to r set, and others reset
    static inline ULL getmask(int l, int r) {
        if (r==X)  return -(1ULL<<l);
        return (1ULL<<(r+1)) - (1ULL<<l);
    }
    vector<ULL> bs;
    int N;
    Bitset(int n) {
        N = n/K+1;
        bs.resize(N);
    }
    void assign(ULL x) {
        fill(bs.begin()+1, bs.end(), 0);
        bs[0] = x;
    }
    bool get(int i) {
        return bs[i>>B] & (1ULL<<(i&X));
    }
    void set(int i) {
        bs[i>>B] |= (1ULL<<(i&X));
    }
    void reset(int i) {
        bs[i>>B] &= ~(1ULL<<(i&X));
    }
    void flip(int i) {
        bs[i>>B] ^= (1ULL<<(i&X));
    }
    void set(int l, int r) {
        int idl = l>>B, idr = r>>B;
        int posl = l&X, posr = r&X;
        if (idl == idr) {
            bs[idl] |= getmask(posl, posr);
            return;
        }
        bs[idl] |= getmask(posl, X);
        bs[idr] |= getmask(0, posr);
        for (int id = idl+1; id < idr; id++)    bs[id] = -1;
    }
    void reset(int l, int r) {
        int idl = l>>B, idr = r>>B;
        int posl = l&X, posr = r&X;
        if (idl == idr) {
            bs[idl] &= ~getmask(posl, posr);
            return;
        }
        bs[idl] &= ~getmask(posl, X);
        bs[idr] &= ~getmask(0, posr);
        for (int id = idl+1; id < idr; id++)    bs[id] = 0;
    }
    void flip(int l, int r) {
        int idl = l>>B, idr = r>>B;
        int posl = l&X, posr = r&X;
        if (idl == idr) {
            bs[idl] ^= getmask(posl, posr);
            return;
        }
        bs[idl] ^= getmask(posl, X);
        bs[idr] ^= getmask(0, posr);
        for (int id = idl+1; id < idr; id++)    bs[id] = ~bs[id];
    }
};


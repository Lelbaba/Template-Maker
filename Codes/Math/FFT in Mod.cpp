const int M = 1e9 + 7, B = sqrt(M) + 1;
vector<LL> anyMod(const vector<LL> &a, const vector<LL> &b) {
    int n = 1;
    while (n < a.size() + b.size())  n <<= 1;
    vector<CD> al(n), ar(n), bl(n), br(n);

    for (int i = 0; i < a.size(); i++)  al[i] = a[i] % M / B, ar[i] = a[i] % M % B;
    for (int i = 0; i < b.size(); i++)  bl[i] = b[i] % M / B, br[i] = b[i] % M % B;

    pairfft(al, ar); pairfft(bl, br);
//        fft(al); fft(ar); fft(bl); fft(br);

    for (int i = 0; i < n; i++) {
        CD ll = (al[i] * bl[i]), lr = (al[i] * br[i]);
        CD rl = (ar[i] * bl[i]), rr = (ar[i] * br[i]);
        al[i] = ll; ar[i] = lr;
        bl[i] = rl; br[i] = rr;
    }

    pairfft(al, ar, true); pairfft(bl, br, true);
//        fft(al, true); fft(ar, true); fft(bl, true); fft(br, true);

    vector<LL> ans(n);
    for (int i = 0; i < n; i++) {
        LL right = round(br[i].real()), left = round(al[i].real());;
        LL mid = round(round(bl[i].real()) + round(ar[i].real()));
        ans[i] = ((left % M) * B * B + (mid % M) * B + right) % M;
    }
    return ans;
}

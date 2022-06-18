/*
Given n 3D point. Find a point from where distance to farthest of those n point is minimum.
*/
int main(){
    int n;
    cin >> n;
    double x[n],y[n],z[n];
    REP(i,n) cin >> x[i] >> y[i] >> z[i];
    double px=0.0,py=0.0,pz=0.0,alpha=1.0;
    REP(loop,100000){
        int idx=0;
        double dis=-1.0;
        REP(i,n){
            double tmp=SQ(x[i]-px)+SQ(y[i]-py)+SQ(z[i]-pz);
            if(tmp>dis) {
                dis=tmp;
                idx=i;
            }
        }
        px+=alpha*(x[idx]-px);
        py+=alpha*(y[idx]-py);
        pz+=alpha*(z[idx]-pz);
        alpha*=0.999;
    }
    cout << px << ' ' << py << ' ' << pz;
}

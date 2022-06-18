#define bitwiseXOR 1
//#define bitwiseAND 2
//#define bitwiseOR 3

void FWHT(vector< LL >&p, bool inverse){
    LL n = p.size();
    assert((n&(n-1))==0);

    for (LL len = 1; 2*len <= n; len <<= 1) {
        for (LL i = 0; i < n; i += len+len) {
            for (LL j = 0; j < len; j++) {
                LL u = p[i+j];
                LL v = p[i+len+j];

                #ifdef bitwiseXOR
                p[i+j] = u+v;
                p[i+len+j] = u-v;
                #endif // bitwiseXOR

                #ifdef bitwiseAND
                if (!inverse) {
                    p[i+j] = v % MOD;
                    p[i+len+j] = (u+v) % MOD;
                } else {
                    p[i+j] = (-u+v) % MOD;
                    p[i+len+j] = u % MOD;
                }
                #endif // bitwiseAND

                #ifdef bitwiseOR
                if (!inverse) {
                    p[i+j] = u+v;
                    p[i+len+j] = u;
                } else {
                    p[i+j] = v;
                    p[i+len+j] = u-v;
                }
                #endif // bitwiseOR
            }
        }
    }

    #ifdef bitwiseXOR
    if (inverse) {
        //LL val=BigMod(n,MOD-2); //Option 2: Exclude
        for (LL i = 0; i < n; i++) {
            //assert(p[i]%n==0); //Option 2: Include
            //p[i] = (p[i]*val)%MOD; //Option 2: p[i]/=n;
            p[i]/=n;
        }
    }
    #endif // bitwiseXOR
}

vector<pair<int,int> >V[100005];
int dis[100005];

void dfs(int s,int pr){
    for(auto p:V[s]){
        if(p.first==pr) continue;
        dis[p.first]=dis[s]^p.second;
        dfs(p.first,s);
    }
}

int main(){
    int t;
    cin >> t;
    const int len=(1<<16);
    for(int tc=1;tc<=t;tc++){
        LL n;
        cin >> n;
        for(int i=1;i<=n-1;i++){
            int u,v,w;
            cin >> u >> v >> w;
            V[u].push_back({v,w});
            V[v].push_back({u,w});
        }
        dfs(1,0);
        vector<LL>a(len,0);
        for(int i=1;i<=n;i++) a[dis[i]]++;
        FWHT(a,false);
        for(int i=0;i<len;i++) a[i]*=a[i];
        FWHT(a,true);
        a[0]-=n;
        cout << "Case " << tc << ":\n";
        for(int i=0;i<len;i++) cout << a[i]/2 << '\n';
        memset(dis,0,sizeof(dis));
        for(int i=1;i<=n;i++) V[i].clear();
    }
}

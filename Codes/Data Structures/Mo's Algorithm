int vis[1000005];
int y[1000005];
int main()
{
    fastio;
    long long a=0,b=0,c,d,e,f=0,l,g,m,r,n,k,i,j,t,p,q;
    cin>>n;
    vector<long long>v;
    d=sqrt(1.0*n);
    vector<pair<long long,pair<long long,long long> > >x[d+2];
    //map<pair<long long,long long> ,long long>mp;
    v.push_back(-37);
    for(i=0;i<n;i++){
        cin>>a;
        v.push_back(a);
    }
    cin>>q;
    for(i=0;i<q;i++){
        cin>>a>>b;
        e=a/d;
        x[e].push_back({b,{a,i}});
    }
    for(i=0;i<=d+1;i++){
        sort(x[i].begin(),x[i].end());
    }
    for(i=0;i<=d;i++){
        memset(vis,0,sizeof(vis));
        l=i*d+1;
        r=i*d;
        p=x[i].size();
        f=0;
        for(j=0;j<p;j++){
            b=x[i][j].first;
            a=x[i][j].second.first;
            while(r<b){
                r++;
                vis[v[r]]++;
                if(vis[v[r]]==1)f++;
            }
            //cout<<l<<' '<<r<<'='<<f<<endl;
            if(l<a){
            while(l<a){
                vis[v[l]]--;
                if(vis[v[l]]==0)f--;
                l++;
            }}
            else if(l>a){
                while(l>a){
                    l--;
                    vis[v[l]]++;
                    if(vis[v[l]]==1)f++;
                }
            }
            //cout<<l<<' '<<r<<'='<<f<<endl;
            y[x[i][j].second.second]=f;
            //cout<<a<<' '<<b<<'='<<f<<endl;
        }
    }
    for(i=0;i<q;i++){
        cout<<y[i]<<'\n';
    }

    return 0;
}

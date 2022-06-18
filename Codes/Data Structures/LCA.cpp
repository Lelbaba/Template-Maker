/*Hey, What's up?*/

#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1.0)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
vector<long long>v[100005],vc;
long long x[200005][40],mp[100005],ml[100005],nd,pos[100005];
void build(long long n)
{
    long long a,i,j,k,b,c;
    a=1;
    for(i=0; i<n; i++)
    {
        x[i][0]=vc[i];
    }
    b=1;
    while(a<n)
    {
        for(i=0; i<n-a; i++)
        {
            x[i][b]=min(x[i][b-1],x[i+a][b-1]);
        }
        a*=2;
        b++;
    }
    return;
}
long long query(long long a, long long b)
{
    long long c,d,e,f;
    //if(a==b)return x[a][0];
    c=log2(1.0*(b-a+1));
    //cout<<c<<' ';
    f=powl(1.0*2,1.0*c);
    d=x[a][c];
    e=x[b-f+1][c];
    //cout<<b-f+1<<' ';
    return min(d,e);

}
void tour_de_euler(long long p, long long q)
{
    vc.push_back(mp[p]);
    //nd++;
    if(!pos[mp[p]])pos[mp[p]]=nd;
    nd++;
    for(int i=0;i<v[p].size();i++){
        if(v[p][i]==q)continue;
        tour_de_euler(v[p][i],p);
        vc.push_back(mp[p]); nd++;
    }
    return;

}
void dfs(long long p, long long q)
{
    mp[p]=nd;
    ml[nd]=p;
    nd++;
    for(int i=0;i<v[p].size();i++){
        if(v[p][i]==q)continue;
        dfs(v[p][i],p);
    }
    return;

}

long long lca(long long a, long long b)
{
    a=pos[mp[a]];
    b=pos[mp[b]];
    if(a>b)
        swap(a,b);
    long long c=query(a,b);
    return ml[c];
}

int main()
{
    //fastio;
    long long a=0,b=0,c,d,e,f=0,l,g,m,n,k,i,j,t,p,q;
    cin>>n;
    for(i=1; i<n; i++)
    {
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    nd=1;
    dfs(1,-1);
    vc.push_back(696969696969);
    nd=1;
    tour_de_euler(1,-1);
    l=vc.size();
    build(l+2);
    cin>>q;
    while(q--){
        cin>>a>>b;
        cout<<lca(a,b)<<endl;
    }

    return 0;
}

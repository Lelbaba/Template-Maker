/*Hey, What's up?*/

#include<bits/stdc++.h>
using namespace std;
#define pi acos(-1.0)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
vector <int> v[100005], vc;
int x[200005][40], mp[100005], ml[100005], nd, pos[100005];

void build(int n) {
    for (int i = 0; i < n; i++)
        x[i][0] = vc[i];
    for (int a = 1, b = 1 ; a < n; a *= 2, b++)
        for (int i = 0; i < n - a; i++)
            x[i][b] = min(x[i][b - 1], x[i + a][b - 1]);
}
int query(int a, int b) {
    //if(a==b)return x[a][0];
    int c = 31 - __builtin_clz(b - a + 1); // log2(b - a + 1)
    int f = 1 << c;
    int d = x[a][c];
    int e = x[b - f + 1][c];
    return min(d, e);
}
void tour_de_euler(int p, int q) {
    vc.push_back(mp[p]);
    //nd++;
    if (!pos[mp[p]])pos[mp[p]] = nd;
    nd++;
    for (int e: v[p]) if(e != q) {
        tour_de_euler(e, p);
        vc.push_back(mp[p]); nd++;
    }
}
void dfs(int p, int q) {
    mp[p] = nd, ml[nd] = p;
    nd++;
    for (int e: v[p]) if (p != q)
        dfs(e, p);
}

int lca(int a, int b) {
    a = pos[mp[a]];
    b = pos[mp[b]];
    if (a > b)
        swap(a, b);
    int c = query(a, b);
    return ml[c];
}

int main()
{
    //fastio;
    int a = 0, b = 0, c, d, e, f = 0, l, g, m, n, k, i, j, t, p, q;
    cin >> n;
    for (i = 1; i < n; i++)
    {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    // nd = 1;
    // dfs(1, -1);
    // vc.push_back(6969696);
    // nd = 1;
    // tour_de_euler(1, -1);
    // l = vc.size();
    // build(l + 2);
    // cin >> q;
    // while (q--) {
    //     cin >> a >> b;
    //     cout << lca(a, b) << endl;
    // }

    return 0;
}

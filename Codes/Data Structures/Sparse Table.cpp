const int maxn = (1<<20)+5 ;
int logs[maxn] = {0};

void compute_logs(){
    logs[1] = 0;
    for(int i=2;i<(1<<20);i++){
        logs[i] = logs[i/2]+1;
    }
}

class Sparse_Table
{
    public:
        vector <vector<LL>> table; 
        function < LL(LL,LL) > func;
        LL identity;

    Sparse_Table(vector <LL> &v, function <LL(LL,LL)> _func, LL id){
        if(logs[2] != 1) compute_logs();
        int sz = v.size();
        table.assign(sz,vector <LL>(logs[sz]+1) );
        func = _func, identity = id;

        for(int j=0;j<=logs[sz];j++){
            for(int i=0;i+(1<<j)<=sz;i++){
                if(j==0) table[i][j] = func(v[i],id);    // base case, when only 1 element in range
                else table[i][j] = func(table[i][j-1], table[i + (1<<(j-1))][j-1] );
            }
        }
    }
    // when intersection of two ranges wont be a problem like min, gcd,max
    LL query(int l, int r){
        assert(r>=l);
        int pow = logs[r-l+1];
        return func(table[l][pow], table[r- (1<<pow) + 1][pow]);
    }
    // other cases like sum
    LL Query(int l,int r){
        if(l>r) return identity; // handle basecase
        int pow = logs[r - l + 1];
        return func(table[l][pow], Query(l+(1<<pow), r));
    }
};
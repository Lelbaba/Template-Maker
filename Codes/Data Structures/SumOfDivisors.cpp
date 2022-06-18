#include<bits/stdc++.h>
using namespace std;
#define hlw ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
long long sod[10000007];
bool pm[10000007];
vector<long long>prm;
int main()
{
    hlw;
    long long i,j,n,t,d,p;
    sod[1]=1;
    prm.push_back(2);
    for(i=3; i<10000007; i+=2)
    {
        if(!pm[i])
        {
            prm.push_back(i);
            for(j=i*i; j<10000007; j+=2*i)
            {
                pm[j]=1;

            }
        }
    }
    for(i=1; i<=10000007;i++)
        sod[i]=1;
    for(i=0; i<prm.size(); i++)
    {
        p=prm[i];
        for(j=p; j<10000007; j+=p)
        {
            d=p;
            while(j%d==0)
                d*=p;
            d--;
            d/=(p-1);
            sod[j]*=d;
        }
    }


    return 0;
}

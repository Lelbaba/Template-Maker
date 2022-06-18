int r,c;
scanf("%d %d",&r,&c);
int nim=0;
FOR(i,1,r){
    FOR(j,1,c){
        int tmp;
        scanf("%d",&tmp);
        if(((r-i)+(c-j))%2){
            nim^=tmp;
        }
    }
}
if(nim) printf("Case %d: win\n",tc);
else printf("Case %d: lose\n",tc);

int cnt=0,B,anc[N],stk[N],top=0,id[N];
void dfs(int u,int fa){    
    for(int i=head[u],v,re=top;i;i=e[i].nxt)
        if((v=e[i].to)!=fa){
            dfs(v,u);
            if(top-re>=B){
                for(++cnt;top!=re;--top)id[stk[top]]=cnt;
                anc[cnt]=u;
            }
        }
    stk[++top]=u;
}
void divide(){
    dfs(1,0);
    //cnt块的数量
    //anc每块的根
    //id每个点属于哪个块
    //B  B<=每个块的的大小<=3B
    if(top){
        if(!cnt)anc[++cnt]=1;
        for(;top;--top)id[stk[top]]=cnt;
    }
}

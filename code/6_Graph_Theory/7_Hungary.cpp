namespace Hungary{
	const int N=500+10;
	int nx,ny;
	bool vis[N],w[N][N];
	int boy[N],girl[N];
	int dfs(int x){
		for(int y=1;y<=ny;++y)
			if(w[x][y]&&!vis[y]){
				vis[y]=1;
				if(!boy[y]||dfs(boy[y])){
					girl[x]=y,boy[y]=x;
					return 1;
				}
			}
		return 0;
	}
	int run(){
		int res=0;
		for(int x=1;x<=nx;++x)
			if(!girl[x]){
				memset(vis,0,sizeof (bool)*(ny+1));
				res+=dfs(x);
			}
		return res;
	}
}

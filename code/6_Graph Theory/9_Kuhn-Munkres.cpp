namespace KM {
	using namespace std;
	const int N=400+10;
	const int oo=2e9+10;
	int n,boy[N],girl[N],slack[N],pre[N],q[N],lx[N],ly[N],w[N][N];
	bool visx[N],visy[N];
	void aug(int y){//翻转匹配边和非匹配边，使匹配点对+1
		for(int x,z;y;y=z){
			x=pre[y],z=girl[x];//pre为增广路径的上一个点
			girl[x]=y,boy[y]=x;
		}//girl[x]为男生x的伴侣，boy[y]为女生y的伴侣
	}
	void bfs(int s){
		memset(visx,0,sizeof (bool)*(n+1));
		memset(visy,0,sizeof (bool)*(n+1));
		for(int i=1;i<=n;++i)slack[i]=oo;
		int h=0,t=1;q[0]=s;
		for(;;){
			for(;h!=t;){
				int x=q[h++];
				visx[x]=1;
				for(int y=1;y<=n;++y)
					if(!visy[y]){
						if(lx[x]+ly[y]==w[x][y]){
							pre[y]=x;
							if(!boy[y]){
								aug(y);
								return;//找到完备匹配
							}else{
								visy[y]=1;
								q[t++]=boy[y];
							}
						}else if(lx[x]+ly[y]-w[x][y]<slack[y]){
							pre[y]=x;
							slack[y]=lx[x]+ly[y]-w[x][y];//更新slack
						}
					}
			}
			int d=oo;
			for(int y=1;y<=n;++y)
				if(!visy[y])d=min(d,slack[y]);
			for(int i=1;i<=n;++i){
				if(visx[i])lx[i]-=d;
				if(visy[i])ly[i]+=d;else slack[i]-=d;//松弛操作
			}
			for(int y=1;y<=n;++y){
				if(!visy[y]&&!slack[y]){
					if(!boy[y]){
						aug(y);
						return;
					}else{
						visy[y]=1;
						q[t++]=boy[y];//松弛之后加入新的点
					}
				}
			}
		}
	}
	long long run(int nx,int ny){//nx为男生数量,ny为女生数量
		n=max(nx,ny);//补足人数
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				lx[i]=max(lx[i],w[i][j]);//lx,ly为点标,w为边权
		for(int i=1;i<=n;++i)bfs(i);
		long long res=0;
		for(int i=1;i<=n;++i)res+=lx[i]+ly[i];
		return res;
		//w[i][girl[i]]?girl[i]:0
	}
}

int main() {

}

namespace KM {
	using namespace std;
	const int N=400+10;
	const int oo=2e9+10;
	int n,boy[N],girl[N],slack[N],pre[N],q[N],lx[N],ly[N],w[N][N];
	bool visx[N],visy[N];
	void aug(int y){//��תƥ��ߺͷ�ƥ��ߣ�ʹƥ����+1
		for(int x,z;y;y=z){
			x=pre[y],z=girl[x];//preΪ����·������һ����
			girl[x]=y,boy[y]=x;
		}//girl[x]Ϊ����x�İ��£�boy[y]ΪŮ��y�İ���
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
								return;//�ҵ��걸ƥ��
							}else{
								visy[y]=1;
								q[t++]=boy[y];
							}
						}else if(lx[x]+ly[y]-w[x][y]<slack[y]){
							pre[y]=x;
							slack[y]=lx[x]+ly[y]-w[x][y];//����slack
						}
					}
			}
			int d=oo;
			for(int y=1;y<=n;++y)
				if(!visy[y])d=min(d,slack[y]);
			for(int i=1;i<=n;++i){
				if(visx[i])lx[i]-=d;
				if(visy[i])ly[i]+=d;else slack[i]-=d;//�ɳڲ���
			}
			for(int y=1;y<=n;++y){
				if(!visy[y]&&!slack[y]){
					if(!boy[y]){
						aug(y);
						return;
					}else{
						visy[y]=1;
						q[t++]=boy[y];//�ɳ�֮������µĵ�
					}
				}
			}
		}
	}
	long long run(int nx,int ny){//nxΪ��������,nyΪŮ������
		n=max(nx,ny);//��������
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				lx[i]=max(lx[i],w[i][j]);//lx,lyΪ���,wΪ��Ȩ
		for(int i=1;i<=n;++i)bfs(i);
		long long res=0;
		for(int i=1;i<=n;++i)res+=lx[i]+ly[i];
		return res;
		//w[i][girl[i]]?girl[i]:0
	}
}

int main() {

}

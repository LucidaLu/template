const int N=1e5,XN=N+11;

int prime[XN*2],pcnt;
void Prep() {
	static bool notPrime[XN*2];
	for(int i=2;i<=N*2;++i) {
		if(!notPrime[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt && i*prime[j]<=N*2;++j) {
			notPrime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
		}
	}
}

namespace Min25 {
	typedef unsigned long long ans_t;

	std::function<ans_t(int,int)> F;
	
	long long n;
	int lim,psz;

	struct Identifier {
		int id[2][XN],cnt;
		int &operator [](long long x) {
			int &res=x<=lim?id[0][x]:id[1][n/x];
			if(res==0)
				res=++cnt;
			return res;
		}
	}id;

	ans_t g[XN*2],fps[XN];

	ans_t H(long long n,int m) {
		if(n<=1 || m>psz)
			return 0;
		ans_t res=g[id[n]]-fps[m-1];
		for(int i=m;i<=psz && (long long)prime[i]*prime[i]<=n;++i) {
			long long pt=prime[i],pt1=pt*prime[i];
			for(int t=1;pt1<=n;++t,pt=pt1,pt1*=prime[i])
				res+=F(prime[i],t)*H(n/pt,i+1)+F(prime[i],t+1);
		}
		return res;
	}

	ans_t Solve(long long n,std::function<ans_t(int,int)> F,std::function<ans_t(long long)> gInit) {
		static long long kp[XN*2];
		int kpc=0;
		lim=sqrt(n)+0.5,psz=std::upper_bound(prime+1,prime+1+pcnt,lim)-prime;
		for(int i=id.cnt=0;i<=lim;++i)
			id.id[0][i]=id.id[1][i]=0;
		Min25::F=F;
		Min25::n=n;
		for(long long l=1,r;l<=n;l=r+1) {
			r=n/(n/l);
			g[id[kp[++kpc]=n/l]]=gInit(n/l);
		}
		for(int i=1;i<=psz;++i)
			fps[i]=fps[i-1]+F(prime[i],1);
		for(int j=1;j<=psz;++j)
			for(int i=1;i<=kpc && (long long)prime[j]*prime[j]<=kp[i];++i)
				g[id[kp[i]]]-=F(prime[j],1)*(g[id[kp[i]/prime[j]]]-fps[j-1]);
		return H(n,1);
	}
}

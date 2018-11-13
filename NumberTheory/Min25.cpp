namespace Min25 {// \sum_{i=1}^n\mu(i*x)=\mu(x)\sum_{i=1}^n\mu(i)[gcd(i,x)==1]
	const int N=5e4,XN=N+11;

	int prime[XN],pcnt;
	void Prep() {
		static bool notPrime[XN];
		for(int i=2;i<=N;++i) {
			if(!notPrime[i])
				prime[++pcnt]=i;
			for(int j=1;j<=pcnt && i*prime[j]<=N;++j) {
				notPrime[i*prime[j]]=1;
				if(i%prime[j]==0)
					break;
			}
		}
	}

	int n,lim,psz;long long x;
	struct Identifier {
		int id[2][XN],cnt;
		int &operator [](int x) {
			int &res=x<=lim?id[0][x]:id[1][n/x];
			if(res==0)
				res=++cnt;
			return res;
		}
	}id;

	long long dv[100];int dt;
	int Mu(long long x) {
		int res=1;long long cx=x;
		for(long long d=2;d*d<=cx && x!=1;++d)
			if(x%d==0) {
				x/=d;
				dv[++dt]=d;
				if(x%d==0)
					return 0;
				else
					res*=-1;
			}
		if(x!=1) {
			res*=-1;
			dv[++dt]=x;
		}
		return res;
	}

	int F(int p,int t) {
		return t==1 && x%p?-1:0;
	}

	int g[XN*2],fsum[XN];

	long long H(int n,int m) {
		if(n<=1 || m>psz)
			return 0;
		long long res=g[id[n]]-fsum[m-1];
		for(int i=m;i<=psz && prime[i]*prime[i]<=n;++i) {
			long long pt=prime[i],pt1=pt*prime[i];
			for(int t=1;pt1<=n;++t,pt=pt1,pt1*=prime[i])
				res+=F(prime[i],t)*H(n/pt,i+1)+F(prime[i],t+1);
		}
		return res;
	}

	void Solve() {
		Prep();
		static int kp[XN*2],kpc;
		fin>>n>>x;
		int mun=Mu(x);
		if(mun==0)
			fout<<0<<'\n';
		else {
			lim=sqrt(n)+0.5,psz=std::upper_bound(prime+1,prime+1+pcnt,lim)-prime;
			for(int l=1,r;l<=n;l=r+1) {
				r=n/(n/l);
				g[id[kp[++kpc]=n/l]]=n/l-1;
			}
			for(int j=1;j<=psz;++j)
				for(int i=1;i<=kpc && prime[j]*prime[j]<=kp[i];++i)
					g[id[kp[i]]]-=g[id[kp[i]/prime[j]]]-(j-1);
			for(int i=1;i<=psz;++i)
				fsum[i]=fsum[i-1]+F(prime[i],1);
			for(int i=1;i<=kpc;++i)
				g[i]=std::upper_bound(dv+1,dv+1+dt,kp[i])-dv-1-g[i];
			fout<<mun*(H(n,1)+1)<<'\n';
		}
	}
}

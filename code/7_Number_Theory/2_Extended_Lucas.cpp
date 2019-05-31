int Exgcd(int a,int b,long long &x,long long &y) {
	if(!b) {
		x=1,y=0;
		return a;
	} else {
		int d=Exgcd(b,a%b,x,y);
		long long t=y;y=x-(a/b)*y,x=t;
		return d;
	}
}

int Inverse(int a,int n) {
	long long x,y;
	int d=Exgcd(a,n,x,y);
	assert(d==1);
	return (x%n+n)%n;
}

int Pow(long long base,long long v,int P) {
	long long res=1;
	for(;v;v>>=1,(base*=base)%=P)
		if(v&1)
			(res*=base)%=P;
	return res;
}

struct Lucas {
	struct Divisor {
		int p,t,pt,tM;
		std::vector<int> table;
		
		Divisor(int p,int t,int pt,int tM):p(p),t(t),pt(pt),tM(tM),table(pt) {
			table[0]=1;
			for(int i=1;i<pt;++i)//0?
				table[i]=i%p==0?table[i-1]:(long long)table[i-1]*i%pt;
		}
		
		int Calc(long long n) {
			if(n<p)//pt..
				return table[n];
			else
				return (long long)Calc(n/p)*Pow(table[pt-1],n/pt,pt)%pt*table[n%pt]%pt;
		}

		long long CalcTimes(long long x) {
			long long res=0;
			for(;x;x/=p)
				res+=x/p;
			return res;
		}

		long long Solve(long long n,long long m) {
			long long times=CalcTimes(n)-CalcTimes(m)-CalcTimes(n-m);
			if(times>=t)
				return 0;
			else
				return (long long)Pow(p,times,pt) *Calc(n)%pt *Inverse((long long)Calc(m)*Calc(n-m)%pt,pt)%pt *tM;
		}
	};
	
	int P;
	std::vector<Divisor> ps;

	Lucas(int P):P(P) {
		for(int d=2,x=P;x!=1;d=(long long)d*d<=P?d+1:x)
			if(x%d==0) {
				int t=0,pt=1;
				do {
					++t;pt*=d;
					x/=d;
				} while(x%d==0);
				ps.push_back(Divisor(d,t,pt,(long long)Inverse(P/pt,pt)*(P/pt)%P));
			}
	}

	int operator ()(long long n,long long m) {
		long long res=0;
		for(Divisor &d : ps)
			(res+=d.Solve(n,m))%=P;
		return res;
	}
};

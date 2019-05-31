namespace Simplex {//(<=)+(Maximize)
	const int XN=0,XM=0;
	const double eps=1e-5,inf=1e100;

	int sgn(double const &x) {
		return (x>-eps)-(x<eps);
	}

	int n,m;
	double a[XM][XN],b[XM],c[XN],v;

	void Pivot(int l,int e) {
		b[l]/=a[l][e];
		for(int i=1;i<=n;++i)
			if(i!=e) a[l][i]/=a[l][e];
		a[l][e]=1/a[l][e];
		for(int i=1;i<=m;++i) 
			if(i!=l && sgn(a[i][e])) {
				b[i]-=a[i][e]*b[l];
				for(int j=1;j<=n;++j)
					if(j!=e)
						a[i][j]-=a[i][e]*a[l][j];
				a[i][e]*=-a[l][e];
			}
		v+=c[e]*b[l];
		for(int i=1;i<=n;++i)
			if(i!=e)
				c[i]-=c[e]*a[l][i];
		c[e]*=-a[l][e];
	}

	double Run() {
		for(int l,e;(e=std::find_if(c+1,c+1+n,[&](double const &x)->bool {
						return sgn(x)>0;} )-c)!=n+1;) {
			double lim=inf;
			for(int i=1;i<=m;++i)
				if(IsPositive(a[i][e]) && Reduce(lim,b[i]/a[i][e]))
					l=i;
			if(lim==inf)
				return inf;
			else
				Pivot(l,e);
		}
		return v;
	}
}



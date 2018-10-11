namespace Simplex {
	const int XN=,//变量
		  XM=;//限制
	//解的是(<=)+(Maximize)
	const double eps=1e-5,inf=1e100;

	int sgn(double const &x) {
		return (x>-eps)-(x<eps);
	}

	bool IsPositive(double const &x) {
		return sgn(x)>0;
	}

	int n,m;
	double a[XM][XN],b[XM],c[XN],v;

	void Pivot(int l,int e) {//把第e个变量变成第l个式子的松弛变量
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
		for(int l,e;(e=std::find_if(c+1,c+1+n,IsPositive)-c)!=n+1;) {
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

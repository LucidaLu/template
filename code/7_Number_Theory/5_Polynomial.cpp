const int XN=1<<19,//MAKE2(XN)*2
	 	P=998244353;

int inv[XN];
/*
inv[1]=1;
for(int i=2;i<XN;++i)
	inv[i]=1LL*(P-P/i)*inv[P%i]%P;
 */
void M(int &x) {
	((x>=P) && (x-=P)) || ((x<0) && (x+=P));
}

int Pow(long long base,int v) {
	long long res;
	for(res=1;v;v>>=1,(base*=base)%=P)
		if(v&1)
			(res*=base)%=P;
	return res;
}

int Make2(int x) {
	return 1<<((32-__builtin_clz(x))+((x&(-x))!=x));
}

void NTT(int a[],int n,int op) {
	for(int i=0,j=0;i<n;i++) {
		if(i>j)
			std::swap(a[i],a[j]);
		for(int k=n>>1;(j^=k)<k;k>>=1);
	}
	for(int len=2;len<=n;len<<=1) {
		int rt=Pow(3,(P-1)/len);
		for(int i=0;i<n;i+=len) {
			int w=1;
			for(int j=i;j<i+len/2;++j) {
				int u=a[j],t=1LL*a[j+len/2]*w%P;
				M(a[j]=u+t);M(a[j+len/2]=u-t);
				w=1LL*w*rt%P;
			}
		}
	}
	if(op==-1) {
		std::reverse(a+1,a+n);
		for(int i=0;i<n;++i)
			a[i]=1LL*a[i]*inv[n]%P;
	}
}

using Polynomial=std::vector<int>;

Polynomial operator *(Polynomial const &A,Polynomial const &B) {
	static int a[XN],b[XN];
	int n=Make2((int)A.size()+(int)B.size()-1);
	for(int i=0;i<n;++i) {
		a[i]=i<(int)A.size()?A[i]:0;
		b[i]=i<(int)B.size()?B[i]:0;
	}
	NTT(a,n,1);NTT(b,n,1);
	for(int i=0;i<n;++i)
		a[i]=1LL*a[i]*b[i]%P;
	NTT(a,n,-1);
	return Polynomial(a,a+(int)A.size()+(int)B.size()-1);
}

Polynomial Inverse(Polynomial const &A){
	static int a[XN],b[XN];
	int n=Make2((int)A.size());
	b[0]=Pow(A[0],P-2);
	for(int len=2;len<=n;len*=2) {
		for(int i=0;i<len*2;++i) {
			a[i]=i<std::min((int)A.size(),len)?A[i]:0;
			b[i]=i<len/2?b[i]:0;
		}
		NTT(a,len*2,1);NTT(b,len*2,1);
		for(int i=0;i<len*2;++i)
			M(b[i]=1LL*b[i]*(2-1LL*a[i]*b[i]%P)%P);
		NTT(b,len*2,-1);
	}
	return Polynomial(b,b+(int)A.size());
}

Polynomial Diff(Polynomial const &A) {
	Polynomial B((int)A.size()-1);
	for(int i=0;i<(int)A.size()-1;++i)
		B[i]=1LL*A[i+1]*(i+1)%P;
	return B;
}

Polynomial Int(Polynomial const &A) {
	Polynomial B((int)A.size()+1);
	for(int i=(int)B.size()-1;i>=1;--i)
		B[i]=1LL*A[i-1]*inv[i]%P;
	return B;
}

Polynomial SquareRoot(Polynomial const &A) {
	static int a[XN],b[XN],c[XN];
	int n=Make2((int)A.size());
	assert(A[0]==1);b[0]=1;
	for(int len=2;len<=n;len*=2) {
		std::fill(b+len/2,b+len,0);
		auto t=Inverse(Polynomial(b,b+len));
		for(int i=0;i<len;++i) {
			a[i]=i<std::min((int)A.size(),len)?A[i]:0;
			b[i]=i<len/2?b[i]:0;
			c[i]=i<len/2?t[i]:0;
		}
		NTT(c,len,1);NTT(b,len,1);NTT(a,len,1);
		for(int i=0;i<len;++i)
			b[i]=1LL*inv[2]*(1LL*a[i]*c[i]%P+b[i])%P;
		NTT(b,len,-1);
	}
	return Polynomial(b,b+(int)A.size());
}

Polynomial Log(Polynomial const &A) {
	auto B=Int(Diff(A)*Inverse(A));
	B.resize(A.size());
	return B;
}

Polynomial Exp(Polynomial const &A) {
	static int a[XN],b[XN],c[XN];
	int n=Make2((int)A.size());
	b[0]=1;
	for(int len=2;len<=n;len*=2) {
		std::fill(b+len/2,b+len,0);
		auto logb=Log(Polynomial(b,b+len));
		for(int i=0;i<len*2;++i) {
			a[i]=i<std::min((int)A.size(),len)?A[i]:0;
			b[i]=i<len/2?b[i]:0;
			c[i]=i<len?logb[i]:0;
		}
		NTT(a,len*2,1);NTT(b,len*2,1);NTT(c,len*2,1);
		for(int i=0;i<len*2;++i)
			M(b[i]=1LL*b[i]*(1-c[i]+a[i])%P);
		NTT(b,len*2,-1);
	}
	return Polynomial(b,b+(int)A.size());
}

Polynomial Pow(Polynomial const &A,int v) {
	static int a[XN];
	int A0=A[0],inv0=Pow(A[0],P-2);
	for(int i=0;i<(int)A.size();++i)
		a[i]=1LL*A[i]*inv0%P;
	auto loga=Log(Polynomial(a,a+(int)A.size()));
	for(int i=0;i<(int)A.size();++i)
		loga[i]=1LL*loga[i]*v%P;
	auto exp=Exp(loga);
	int k=Pow(A0,v);
	for(int i=0;i<(int)A.size();++i)
		exp[i]=1LL*exp[i]*k%P;
	return exp;
}

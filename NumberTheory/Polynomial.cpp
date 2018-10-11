const int XN=1<<18;//Make2(n)*2?

namespace Polynomial {

	const int P=998244353;

	int Add(int x,int const &y) {
		return (x+=y)>=P?x-P:x;
	}

	int Minus(int x,int const &y) {
		return (x-=y)<0?x+P:x;
	}

	int Mul(long long x,int const &y) {
		return x*y%P;
	}

	int Pow(long long base,int v) {
		long long res;
		for(res=1;v;v>>=1,(base*=base)%=P)
			if(v&1)
				(res*=base)%=P;
		return res;
	}

	int Inverse(int x,int P=Polynomial::P) {
		return Pow(x,P-2);
	}

	int Make2(int x) {
		return 1<<((32-__builtin_clz(x))+((x&(-x))!=x));
	}

	void NTT(int a[],int n,int op) {
		for(int i=1,j=n>>1;i<n-1;++i) {
			if(i<j)
				std::swap(a[i],a[j]);
			int k=n>>1;
			while(k<=j) {
				j-=k;
				k>>=1;
			}
			j+=k;
		}
		for(int len=2;len<=n;len<<=1) {
			int rt=Pow(3,(P-1)/len);
			for(int i=0;i<n;i+=len) {
				int w=1;
				for(int j=i;j<i+len/2;++j) {
					int u=a[j],t=Mul(a[j+len/2],w);
					a[j]=Add(u,t),a[j+len/2]=Minus(u,t);
					w=Mul(w,rt);
				}
			}
		}
		if(op==-1) {
			std::reverse(a+1,a+n);
			int in=Inverse(n);
			for(int i=0;i<n;++i)
				a[i]=Mul(a[i],in);
		}
	}

	int Mul(int A[],int An,int B[],int Bn,int R[]) {
		static int a[XN],b[XN];
		int n=Make2(An+Bn-1);
		for(int i=0;i<n;++i) {
			a[i]=i<An?A[i]:0;
			b[i]=i<Bn?B[i]:0;
		}
		NTT(a,n,1);NTT(b,n,1);
		for(int i=0;i<n;++i)
			a[i]=Mul(a[i],b[i]);
		NTT(a,n,-1);
		std::copy(a,a+An+Bn-1,R);
		return An+Bn-1;
	}

	void Inverse(int A[],int An,int R[]) {
		int n=Make2(An);
		static int inv[XN],a[XN];
		inv[0]=Inverse(A[0]);
		for(int len=2;len<=n;len*=2) {
			for(int i=0;i<len*2;++i) {
				inv[i]=i<len/2?inv[i]:0;
				a[i]=i<std::min(An,len)?A[i]:0;
			}
			NTT(inv,len*2,1);NTT(a,len*2,1);
			for(int i=0;i<len*2;++i)
				inv[i]=Mul(inv[i],Minus(2,Mul(a[i],inv[i])));
			NTT(inv,len*2,-1);
		}
		std::copy(inv,inv+An,R);
	}

	void Differentiate(int A[],int n,int R[]) {
		for(int i=0;i<n-1;++i)
			R[i]=Mul(A[i+1],i+1);
		R[n-1]=0;
	}

	void Integrate(int A[],int n,int R[]) {
		for(int i=n-1;i>=1;--i)
			R[i]=Mul(A[i-1],Inverse(i));
		R[0]=0;
	}

	void SquareRoot(int A[],int An,int R[]) {
		int n=Make2(An);
		static int irt[XN],rt[XN],a[XN];
		assert(A[0]==1);rt[0]=1;
		int i2=Inverse(2);
		for(int len=2;len<=n;len*=2) {
			std::fill(rt+len/2,rt+len,0);
			Inverse(rt,len,irt);
			for(int i=0;i<len;++i) {
				a[i]=i<std::min(An,len)?A[i]:0;
				rt[i]=i<len/2?rt[i]:0;
				irt[i]=i<len/2?irt[i]:0;
			}
			NTT(irt,len,1);NTT(rt,len,1);NTT(a,len,1);
			for(int i=0;i<len;++i)
				rt[i]=Mul(i2,Add(Mul(a[i],irt[i]),rt[i]));
			NTT(rt,len,-1);
		}
		std::copy(rt,rt+An,R);
	}

	void Logarithm(int A[],int An,int R[]) {
		static int a[XN],b[XN];
		Differentiate(A,An,b);
		std::copy(A,A+An,a);
		Inverse(a,An,a);
		Mul(a,An,b,An,b);
		Integrate(b,An,b);
		std::copy(b,b+An,R);
	}

	void Exponent(int A[],int An,int R[]) {
		static int a[XN],b[XN],c[XN];
		int n=Make2(An);
		b[0]=1;
		for(int len=2;len<=n;len*=2) {
			std::fill(b+len/2,b+len,0);
			Logarithm(b,len,c);
			for(int i=0;i<len*2;++i) {
				a[i]=i<std::min(An,len)?A[i]:0;
				b[i]=i<len/2?b[i]:0;
				c[i]=i<len?c[i]:0;
			}
			NTT(a,len*2,1);NTT(b,len*2,1);NTT(c,len*2,1);
			for(int i=0;i<len*2;++i)
				b[i]=Mul(b[i],Add(Minus(1,c[i]),a[i]));
			NTT(b,len*2,-1);
		}
		std::copy(b,b+An,R);
	}

	void Pow(int A[],int An,int v,int R[]) {
		static int a[XN];
		int A0=A[0],i0=Inverse(A[0]);
		for(int i=0;i<An;++i)
			a[i]=Mul(i0,A[i]);
		Logarithm(a,An,a);
		for(int i=0;i<An;++i)
			a[i]=Mul(a[i],v);
		Exponent(a,An,a);
		int k=Pow(A0,v);
		for(int i=0;i<An;++i)
			R[i]=Mul(a[i],k);
	}
}

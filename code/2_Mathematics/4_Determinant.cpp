typedef int Square[XN][XN];
//Matrix-Tree 度数-邻接
int Determinant(Square a,int n) {
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			((a[i][j]%=P)+=P)%=P;
	int f=1;
	for(int i=1;i<=n;++i) {
		int &A=a[i][i];
		for(int j=i+1;j<=n;++j) {
			for(int &B=a[j][i];B;f=P-f) {
				int t=A/B;
				for(int k=1;k<=n;++k)
					a[i][k]=Minus(a[i][k],Mul(a[j][k],t));
				std::swap_ranges(a[i]+1,a[i]+1+n,a[j]+1);
			}
		}
	}
	int res=f;
	for(int i=1;i<=n;++i)
		res=Mul(a[i][i],res);
	return res;
}

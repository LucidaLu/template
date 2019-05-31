typedef double Square[XN][XN];
void Gauss(Square A,int n) {
    for(int i=1;i<=n;++i) {
        int id=i;
        for(int j=i+1;j<=n;++j)
			if(abs(A[j][i])>abs(A[id][i]))
				id=j;
		std::swap_ranges(A[i]+1,A[i]+n+2,A[id]+1);
        for(int k=i+1;k<=n+1;++k)
            A[i][k]/=A[i][i];
        A[i][i]=1;
        for(int j=i+1;j<=n;++j) {
            for(int k=i+1;k<=n+1;++k)
                A[j][k]-=A[j][i]*A[i][k];
            A[j][i]=0;
        }
    }
    for(int i=n;i>=1;--i) {
        for(int j=i+1;j<=n;++j) {
            A[i][n+1]-=A[j][n+1]*A[i][j];
            A[i][j]=0;
        }
    }
}


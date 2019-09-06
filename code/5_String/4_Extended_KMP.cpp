//nxt 表示B[i..m]与B的最长公共前缀
//extend 表示A[i..n]与B的最长公共前缀长度
void exKMP(char *A,char *B,int nxt[],int extend[]) {
	int n=strlen(A+1),m=strlen(B+1),x=1;
	nxt[1]=m;
	for(;x<m&&B[x]==B[x+1];++x);
	nxt[2]=x-1;x=2;
	
	for(int i=3;i<=m;++i)
		if(i+nxt[i-x+1]-1<nxt[x]+x-1)nxt[i]=nxt[i-x+1];
		else{
			int j=nxt[x]+x-i+1;
			if(j<1)j=1;
			for(;j+i-1<=m&&B[j]==B[j+i-1];++j);
			nxt[i]=j-1;
			x=i;
		}
	
	x=1;
	for(;A[x]==B[x];++x);
	extend[1]=x-1;
	x=1;
	for(int i=2;i<=n;++i)
		if(i+nxt[i-x+1]-1<extend[x]+x-1)extend[i]=nxt[i-x+1];
		else{
			int j=extend[x]+x-i+1;
			if(j<1)j=1;
			for(;j+i-1<=n&&B[j]==A[j+i-1];++j);
			nxt[i]=j-1;
			if(nxt[x]<=nxt[i])x=i;
		}
}

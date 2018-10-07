int MinRep(int b[],int n) {
	static int a[XN*2];
	for(int i=1;i<=n;++i)
		a[i]=a[i+n]=b[i];
	int p1=1,p2=2;
	while(p1<=n && p2<=n) {
		static int len;
		for(len=0;len<n && a[p1+len]==a[p2+len];++len);
		if(len==n)
			break;
		else
			a[p1+len]>a[p2+len]?p1=p1+len+1:p2=p2+len+1;
		if(p1==p2)
			++p2;
	}
	return std::min(p1,p2);
}


struct SuffixArray {
	int sa[XN],rank[XN],height[XN],n;

	SuffixArray(const char *s):n(strlen(s+1)) {
		static int temp[2][XN],cnt[XN],*x=temp[0],*y=temp[1];
		int m=256;
		std::fill(cnt+1,cnt+1+m,0);
		for(int i=1;i<=n;++i) cnt[x[i]=s[i]]++;
		std::partial_sum(cnt+1,cnt+1+m,cnt+1);
		for(int i=n;i>=1;--i) sa[cnt[x[i]]--]=i;
		for(int len=1;len<n;len<<=1) {
			int p=0;
			for(int i=n-len+1;i<=n;++i) y[++p]=i;
			for(int i=1;i<=n;++i) if(sa[i]>len) y[++p]=sa[i]-len;
			std::fill(cnt+1,cnt+1+m,0);
			for(int i=1;i<=n;++i) cnt[x[i]]++;
			std::partial_sum(cnt+1,cnt+1+m,cnt+1);
			for(int i=n;i>=1;--i) sa[cnt[x[y[i]]]--]=y[i];
			std::swap(x,y);x[sa[1]]=p=1;
			for(int i=2;i<=n;++i)
				x[sa[i]]=y[sa[i-1]]==y[sa[i]] 
					  && (sa[i-1]+len<=n?y[sa[i-1]+len]:0)==(sa[i]+len<=n?y[sa[i]+len]:0)?p:++p;
			if((m=p)==n) break;
		}
		for(int i=1;i<=n;++i) rank[sa[i]]=i;
		for(int i=1,len=0;i<=n;++i)
			if(rank[i]!=1) {
				int j=sa[rank[i]-1];
				while(s[i+len]==s[j+len]) ++len;
				height[rank[i]]=len;
				if(len) len--;
			}
	}
};

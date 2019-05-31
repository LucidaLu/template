bool OnLeft(const Point &p,Line const &l) {
	return sgn(Outer(l.v,p-l.p))>0;
}

bool Paral(Line const &l1,Line const &l2) {
	return sgn(Outer(l1.v,l2.v))==0;
}

int Intersect(Line l[],int n,Line uni[]) {
	std::sort(l+1,l+1+n,[](Line const &a,Line const &b) { return a.ang<b.ang; });
	static Point Qp[XN];static Line Ql[XN];
	int head,tail;Ql[head=tail=1]=l[1];
	for(int i=2;i<=n;++i) {
		while(tail-head>=1 && !OnLeft(Qp[tail-1],l[i]))
			tail--;
		while(tail-head>=1 && !OnLeft(Qp[head],l[i]))
			head++;
		Ql[++tail]=l[i];
		if(Paral(Ql[tail-1],Ql[tail])){
			--tail;
			if(OnLeft(l[i].p,Ql[tail]))
				Ql[tail]=l[i];
		}
		if(tail-head>=1)
			Qp[tail-1]=Cross(Ql[tail-1],Ql[tail]);
	}
	while(tail-head>=1 && !OnLeft(Qp[tail-1],Ql[head]))
		tail--;
	if(tail-head>=1) {
		std::copy(Ql+head,Ql+tail+1,uni+1);
		return tail-head+1;
	} else
		return 0;
}

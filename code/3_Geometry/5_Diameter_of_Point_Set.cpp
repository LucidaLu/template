double MaxDist(Point p[],int n) {
	//输入必须有序
	if(n==2) {
		return Dist(p[1],p[2]);
	} else {
		double res=0;
		for(int i=1,cp=2;i<=n;++i) {
			Line cl(p[i],p[i%n+1]-p[i]);
			while(Dist(p[cp],cl)<Dist(p[cp%n+1],cl))
				cp=cp%n+1;
			Enlarge(res,std::max(Dist(p[cp],p[i]),Dist(p[cp],p[i%n+1])));
		}
		return res;
	}
}

struct Circle {
	Point o;
	double r;
	Circle(Point o,double r):o(o),r(r) {}
};

Line PerpendicularBisector(Point p1,Point p2) {
	return Line((p1+p2)/2,(p2-p1).Normal());
}

Point CircleCenter(Point p1,Point p2,Point p3) {
	return Cross(PerpendicularBisector(p1,p2),PerpendicularBisector(p2,p3));	
}

Circle MinCoveringCircle(Point p[],int n) {
	std::random_shuffle(p+1,p+1+n);
	Point o=p[1];double r=0;
	for(int i=2;i<=n;i++)
		if(sgn(Dist(o,p[i])-r)>0) {
			o=p[i],r=0;
			for(int j=1;j<i;j++)
				if(sgn(Dist(o,p[j])-r)>0) {
					o=(p[i]+p[j])/2;
					r=Dist(o,p[i]);
					for(int k=1;k<j;k++)
						if(sgn(Dist(o,p[k])-r)>0) {
							o=CircleCenter(p[i],p[j],p[k]);
							r=Dist(o,p[k]);
						}
				}
		}
	return Circle(o,r);
}

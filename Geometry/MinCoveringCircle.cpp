struct Circle {
	Point o;
	double r;
	Circle(Point o,double r):o(o),r(r) {}
};

Point CircleCenter(Point p1,Point p2,Point p3) {
	long double a1=p2.x-p1.x,b1=p2.y-p1.y,c1=(a1*a1+b1*b1)/2;
	long double a2=p3.x-p1.x,b2=p3.y-p1.y,c2=(a2*a2+b2*b2)/2;
	long double d=a1*b2-a2*b1;
	return {p1.x+(c1*b2-c2*b1)/d,p1.y+(a1*c2-a2*c1)/d};
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

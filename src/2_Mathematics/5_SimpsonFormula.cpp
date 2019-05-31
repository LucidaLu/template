typedef std::pair<double,double> Point;
double Simpson(Point const &l,Point const &r,Point const &mid) {
	return (r.first-l.first)/6*(l.second+r.second+4*mid.second);
}

double Int(Point const &l,Point const &r,Point const &mid,double const &s,double const &eps) {
	Point m1={(l.first+mid.first)/2,Fun((l.first+mid.first)/2)},
		  m2={(mid.first+r.first)/2,Fun((mid.first+r.first)/2)};
	double s1=Simpson(l,mid,m1),s2=Simpson(mid,r,m2);
	if(eps<1e-8 && fabs(s1+s2-s)<15*eps)
		return s1+s2+(s1+s2-s)/15;
	else
		return Int(l,mid,m1,s1,eps/2)+Int(mid,r,m2,s2,eps/2);
}

double Int(Point const &l,Point const &r) {
	Point mid={(l.first+r.first)/2,Fun((l.first+r.first)/2)};
	return Int(l,r,mid,Simpson(l,r,mid),1e-4);
}

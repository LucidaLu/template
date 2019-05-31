const double eps=1e-10;

int sgn(double const &x) {
	return (x>-eps)-(x<eps);
}

double p2(double const &x) { 
	return x*x;
}

struct Point {
	double x,y;
	
	double Length() const {
		return sqrt(x*x+y*y);
	}
	
	Point Normal() const {
		return {-y,x};
	}

	Point Unit() const {
		double len=Length();
		return Point{x/len,y/len};
	}

	friend Point operator +(const Point &a,const Point &b) {
		return {a.x+b.x,a.y+b.y};
	}

	friend Point operator -(const Point &a,const Point &b) {
		return {a.x-b.x,a.y-b.y};
	}

	friend Point operator *(const Point &a,const double &k) {
		return Point{a.x*k,a.y*k};
	}

	friend Point operator /(const Point &a,const double &k) {
		return Point{a.x/k,a.y/k};
	}

	friend double Inner(const Point &a,const Point &b) {
		return a.x*b.x+a.y*b.y;
	}

	friend double Outer(const Point &a,const Point &b) {
		return a.x*b.y-a.y*b.x;
	}
};

struct Line {
	Point p,v;
	double ang;
};

double Dist(const Point &a,const Point &b) {
	return (a-b).Length();
}

double Dist(const Point &a,Line const &l) {
	return fabs(Outer(a-l.p,l.v))/l.v.Length();
}

Point Cross(Line const &l1,Line const &l2) {
	double t=Outer(l2.v,l1.p-l2.p)/Outer(l1.v,l2.v);
	return l1.p+l1.v*t;
}

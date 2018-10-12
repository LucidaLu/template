const double eps=1e-10;

int sgn(double const &x) {
	return (x>-eps)-(x<eps);
}

double sqr(double const &x) { 
	return x*x;
}

struct Point {
	double x,y;
	
	Point() {}
	
	Point(double const &x,double const &y):x(x),y(y) {}

	double Length() const {
		return sqrt(x*x+y*y);
	}
	
	Point Normal() const {
		return Point(-y,x);
	}

	Point Unit() const {
		double len=Length();
		return Point(x/len,y/len);
	}

	friend Point operator +(const Point &a,const Point &b) {
		return Point(a.x+b.x,a.y+b.y);
	}

	friend Point operator -(const Point &a,const Point &b) {
		return Point(a.x-b.x,a.y-b.y);
	}

	friend Point operator *(const Point &a,const double &k) {
		return Point(a.x*k,a.y*k);
	}

	friend Point operator /(const Point &a,const double &k) {
		return Point(a.x/k,a.y/k);
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
	Line() {}
	Line(Point p,Point v):p(p),v(v) {
		ang=atan2(v.y,v.x);
	}
};

double Dist(const Point &a,const Point &b) {
	return (a-b).Length();
}

double Dist(const Point &a,const Line &l) {
	return fabs(Outer(a-l.p,l.v))/l.v.Length();
}

Point Cross(const Line &ln1,const Line &ln2) {
	double t=Outer(ln2.v,ln1.p-ln2.p)/Outer(ln1.v,ln2.v);
	return ln1.p+ln1.v*t;
}


int ConvexHull(Point p[],int n,Point hull[]) {
	static Point stack[XN*2];
	int top=0;
	std::sort(p+1,p+1+n,[](Point const &a,Point const &b) { return a.x<b.x || (a.x==b.x && a.y<b.y); });
	for(int i=1;i<=n;++i) {
		while(top>=2 && sgn(Outer(stack[top]-stack[top-1],p[i]-stack[top]))<=0)
			top--;
		stack[++top]=p[i];
	}
	int k=top+1;
	for(int i=n-1;i;--i) {
		while(top>=k && sgn(Outer(stack[top]-stack[top-1],p[i]-stack[top]))<=0)
			top--;
		stack[++top]=p[i];
	}
	if(top!=1)
		top--;
	std::copy(stack+1,stack+1+top,hull+1);
	return top;
}

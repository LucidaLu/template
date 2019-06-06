template<class T>
void FWT(int a[], int n, T F) {
	for(int len=2;len<=n;len*=2)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+len/2;++j)	 
				F(a[j],a[j+len/2]);
}

void Tand(int &x,int &y) {
	x+=y;
}

void Iand(int &x,int &y) {
	x-=y;
}

void Tor(int &x,int &y) {
	y+=x;
}

void Ior(int &x,int &y) {
	y-=x;
}

void Ixor(int &x,int &y) {
	std::tie(x,y)=std::make_tuple(x+y,x-y);
}

void Txor(int &x,int &y) {
	std::tie(x,y)=std::make_tuple((x+y)/2,(x-y)/2);
}

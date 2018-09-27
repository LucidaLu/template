int Lucas(int n,int m) {
	int res=1;
	while(n && m) {
		(res*=C(n%P,m%P))%=P;
		n/=P,m/=P;
	}
	return res;
}

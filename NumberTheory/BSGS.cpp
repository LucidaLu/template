int BSGS(int y,int z,int P) {
	if(y%P) {
		std::unordered_map<int,int> S;
		int B=sqrt(P)+0.5;
		long long zyi=z;
		for(int i=0;i<=B;i++,(zyi*=y)%=P)
			if(!S.count(zyi))
				S[zyi]=i;
		int yb=Pow(y,B,P);
		long long ybi=yb;
		for(int i=1;i<=B;i++) {
			if(S.count(ybi))
				return B*i-S[ybi];
			(ybi*=yb)%=P;
		}
	}
	return -1;
}

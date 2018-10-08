int MinimumRepresentation(int *a,int n) {
	++a;
	int p1=0,p2=1,len=0;
	while(p1<n && p2<n && len<n) {
		if(a[(p1+len)%n]==a[(p2+len)%n])
			len++;
		else {
			(a[(p1+len)%n]>a[(p2+len)%n]?p1:p2)+=len+1;
			if(p1==p2)
				p2++;
			len=0;
		}
	}
	return std::min(p1,p2)+1;
}

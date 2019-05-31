double DC(int L,int R) {
    if(L==R)
        return inf;
    else {
        int M=(L+R)/2;double x0=p[M].x;
        double h=std::min(DC(L,M),DC(M+1,R));
        static Point s1[XN],s2[XN],t[XN];
        int c1=0,c2=0;
        for(int i=L;i<=M;++i)
            if(x0-p[i].x<=h)
                s1[++c1]=p[i];
        for(int i=M+1;i<=R;++i)
            if(p[i].x-x0<=h)
                s2[++c2]=p[i];
        for(int p1=1,p2=1;p1<=c1;++p1) {
            while(p2<=c2 && s1[p1].y-s2[p2].y>h)
                ++p2;
            for(int i=p2;i<=c2 && s2[i].y<=s1[p1].y+h;++i)
                Reduce(h,Dist(s2[i],s1[p1]));
        }
        std::merge(p+L,p+M+1,p+M+1,p+R+1,t+L,[&](auto const &a,auto const &b)->bool {
            return a.y!=b.y?a.y<b.y:a.x<b.x;
        });
        std::copy(t+L,t+R+1,p+L);
        return h;
    }
}

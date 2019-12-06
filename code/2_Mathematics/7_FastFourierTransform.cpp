const int N=1<<22;
const double PI=acos(-1);

struct X {
    double x,y;

    X operator +(X const &z) const { return {x + z.x, y + z.y}; }
    X operator -(X const &z) const { return {x - z.x, y - z.y}; }
    X operator *(X const &z) const { return {x * z.x - y * z.y, x * z.y + y * z.x}; }
}w[N];

void FFT(X a[],int n,int op) {
    for (int i=0,j=0;i<n;i++) {
        if (i<j)
            std::swap(a[i],a[j]);
        for(int l=n>>1; (j^=l)<l;l>>=1);
    }

    for (int l=2;l<=n;l*=2) {
        int h=l/2,d=N/l;
        for (int i=0;i<n;i+=l)
            for (int j=0;j<h;++j) {
                X &x=a[i+j],&y=a[i+j+h],t=w[d*j]*y;
                y=x-t,x=x+t;
            }
    }
    if(op==-1) {
        std::reverse(a+1,a+n);
        for (int i=0;i<n;++i)
            a[i].x/=n,a[i].y/=n;
    }
}

int main() {
    for(int i=0;i<N;++i)
        w[i]={cos(PI*2*i/N),sin(PI*2*i/N)};


    return 0;
}

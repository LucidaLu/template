//By SiriusRen
//The Union of Triangles
using namespace std;
#define pr pair<double,double>
const int N=105;
int n;
double inf=10000000,eps=1e-8,l=inf,r=-inf;
pr p[N];
struct Triangle{double x1,y1,x2,y2,x3,y3;}tr[N];
double jd(double x1,double y1,double x2,double y2,double x){
    if(abs(x1-x2)<eps)return y2-y1;
    return y1+(y2-y1)/(x2-x1)*(x-x1);
}
double Cut(double x){
    int top=0;
    double t1,t2,last=-inf,tt=0;
    for(int i=1;i<=n;i++){
        if(tr[i].x1<x&&tr[i].x2<x&&tr[i].x3<x)continue;
        if(tr[i].x1>x&&tr[i].x2>x&&tr[i].x3>x)continue;
        if(tr[i].x2<x&&tr[i].x1<x)
            t1=jd(tr[i].x1,tr[i].y1,tr[i].x3,tr[i].y3,x),t2=jd(tr[i].x2,tr[i].y2,tr[i].x3,tr[i].y3,x);
        else t1=jd(tr[i].x1,tr[i].y1,tr[i].x3,tr[i].y3,x),t2=jd(tr[i].x1,tr[i].y1,tr[i].x2,tr[i].y2,x);
        p[++top]=make_pair(min(t1,t2),max(t1,t2));
    }
    sort(p+1,p+1+top);
    for(int i=1;i<=top;i++){
        if(p[i].first>last)last=p[i].second,tt+=p[i].second-p[i].first;
        else if(p[i].second>last)tt+=p[i].second-last,last=p[i].second;
    }return tt;
}
double Simpson(double l,double mid,double r,double Cl,double Cmid,double Cr,int deep){
    double Clmid=Cut((l+mid)/2),Crmid=Cut((mid+r)/2);
    double Ansl=(mid-l)*(Cl+4*Clmid+Cmid)/6,Ansr=(r-mid)*(Cr+4*Crmid+Cmid)/6,Ans=(r-l)*(Cl+4*Cmid+Cr)/6;
    if(deep>13&&abs(Ansl+Ansr-Ans)<1e-13)return Ans;
    else return Simpson(l,(l+mid)/2,mid,Cl,Clmid,Cmid,deep+1)+Simpson(mid,(mid+r)/2,r,Cmid,Crmid,Cr,deep+1);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf%lf%lf%lf",&tr[i].x1,&tr[i].y1,&tr[i].x2,&tr[i].y2,&tr[i].x3,&tr[i].y3);
        l=min(l,min(tr[i].x1,min(tr[i].x2,tr[i].x3)));
        r=max(r,max(tr[i].x1,max(tr[i].x2,tr[i].x3)));
    }
    for(int i=1;i<=n;i++){
        if(tr[i].x3<tr[i].x2)swap(tr[i].x2,tr[i].x3),swap(tr[i].y2,tr[i].y3);
        if(tr[i].x2<tr[i].x1)swap(tr[i].x2,tr[i].x1),swap(tr[i].y2,tr[i].y1);
        if(tr[i].x3<tr[i].x2)swap(tr[i].x2,tr[i].x3),swap(tr[i].y2,tr[i].y3);
    }
    printf("%.2f\n",Simpson(l,(l+r)/2,r,0,Cut((l+r)/2),0,0));
    
}

#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long double ldb;
struct Object{
    int x,y,w;
}ob[1005];
int n;
ldb ansx,ansy,ans=1e18+7;
struct SimulateAnneal{
    ldb delta,T,nowx,nowy,nowans;
    void init(){T=5000;delta=0.993;nowx=rand()*2-RAND_MAX;nowy=rand()*2-RAND_MAX;nowans=1e18+7;}
    ldb getStatus(ldb x,ldb y){
        ldb sum=0;
        for(int i=1;i<=n;i++){
            ldb dltx=x-ob[i].x;
            ldb dlty=y-ob[i].y;
            sum+=sqrt(dltx*dltx+dlty*dlty)*ob[i].w;
        }
        return sum;
    }
    int main(){
        while(T>1e-14){
            ldb tmpx=nowx+(rand()*2-RAND_MAX)*T;
            ldb tmpy=nowy+(rand()*2-RAND_MAX)*T;
            ldb tmpans=getStatus(tmpx,tmpy);
            ldb dltans=tmpans-nowans;
            if(dltans<0){
                nowx=tmpx;
                nowy=tmpy;
                nowans=tmpans;
            }else if(exp(-dltans/T)>rand()/RAND_MAX){
                nowx=tmpx;
                nowy=tmpy;
            }
            if(nowans<ans){
                ans=nowans;
                ansx=nowx;
                ansy=nowy;
            }
            T*=delta;
        }
    }
}S;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d%d",&ob[i].x,&ob[i].y,&ob[i].w);
    for(int i=1;i<=5;i++)srand(time(0)),S.init(),S.main();
    printf("%.3lf %.3lf",(double)ansx,(double)ansy);
}

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<tr1/cmath>
#include<climits>
#include<tr1/unordered_map>
using namespace std;
using namespace std::tr1;
typedef long long LL;
const int MX=5e6;
int n,p[MX+10],top;
LL mu[MX+10],phi[MX+10];
bool vis[MX+10];
unordered_map<int,LL>Su,Sp;
void pre(){
    mu[1]=phi[1]=1;
    for(register int i=2,j,w;i<=MX;++i){
        if(!vis[i]){
            p[++top]=i;phi[i]=i-1;mu[i]=-1;
        }
        for(j=1;j<=top&&i*p[j]<=MX;++j){
            w=i*p[j];
            vis[w]=1;
            if(i%p[j]==0){
                phi[w]=phi[i]*p[j];
                break;
            }else{
                mu[w]=-mu[i];
                phi[w]=phi[i]*phi[p[j]];
            }
        }
    }
    for(register int i=1;i<=MX;++i)mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
LL getMu(int x){
    if(x<=MX)return mu[x];
    if(Su.count(x))return Su[x];
    LL res=1ll;
    for(int l=2,r;r<INT_MAX&&l<=x;l=r+1)
        r=x/(x/l),res-=1ll*(r-l+1)*getMu(x/l);
    return Su[x]=res;
}
LL getPhi(int x){
    if(x<=MX)return phi[x];
    if(Sp.count(x))return Sp[x];
    LL res=1ll*(x+1)*x/2;
    for(int l=2,r;r<INT_MAX&&l<=x;l=r+1)
        r=x/(x/l),res-=1ll*(r-l+1)*getPhi(x/l);
    return Sp[x]=res;
}
inline int in(){
    int ans=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans;
}
int main(){
    int T=in();
    pre();
    while(T--){
        n=in();
        printf("%lld %lld\n",getPhi(n),getMu(n));
    }
}

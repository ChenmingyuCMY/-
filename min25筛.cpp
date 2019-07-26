#include<cstdio>
#include<cstring>
#include<cmath>
#define min(a,b) ((a)>(b)?(b):(a))
#define swap(a,b) a^=b,b^=a,a^=b
using namespace std;
typedef long long LL;
const int MxN=1e6+10;
const LL mod=1e9+7,inv2=5e8+4,inv3=0x13de4358;
LL ans,sp1[MxN],sp2[MxN],n,sqn;
LL g1[MxN],g2[MxN],tot,w[MxN];
LL p[MxN],top,id1[MxN],id2[MxN];
bool vis[MxN];
inline int in(){
    int ans=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans;
}
inline void pre(LL n){
    vis[1]=1;
    for(int i=2;i<=n;++i){
        if(!vis[i]){//i为质数
            p[++top]=i;
            sp1[top]=(sp1[top-1]+i)%mod;//i的前缀和
            sp2[top]=(sp2[top-1]+1ll*i*i)%mod;//i^2的前缀和
        }
        for(int j=1;j<=top&&i*p[j]<=n;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
}
//g(n,j)=g(n,j-1)-p[j]^k(g(n/p,j)-g(p[j-1],j-1))
//                     数论分块   p[j]的k次方和
inline void getSum(LL n){//g(n,1)时的值
    for(LL l=1,r;l<=n;l=r+1){//数论分块
        r=n/(n/l);
        w[++tot]=n/l;//每一块的值
        g1[tot]=w[tot]%mod;//一次方和
        g2[tot]=g1[tot]*(g1[tot]+1)/2%mod*(2*g1[tot]+1)%mod*inv3%mod;//二次方和
        g2[tot]--;
        g1[tot]=g1[tot]*(g1[tot]+1)/2%mod-1;//减掉1的贡献
        if(n/l<=sqn)id1[n/l]=tot;
        else id2[r]=tot;
    }
}
inline void getG(LL n){//推出g(n,j)j>1的值
    for(int i=1;i<=top;++i){
        for(int j=1;j<=tot&&p[i]*p[i]<=w[j];++j){
            LL id=w[j]/p[i]<=sqn?id1[w[j]/p[i]]:id2[n/(w[j]/p[i])];//g(当前值/p,j-1)的id
            g1[j]-=p[i]*(g1[id]-sp1[i-1]+mod)%mod;//递推一次方和
            g2[j]-=p[i]*p[i]%mod*(g2[id]-sp2[i-1]+mod)%mod;//递推二次方和
            g1[j]%=mod,g2[j]%=mod;
            if(g1[j]<0)g1[j]+=mod;
            if(g2[j]<0)g2[j]+=mod;
        }
    }
}
LL getAns(LL x,int y){//s(n,x)=g(n)-sp[x]+\sigma{p[k]^e<=n&&k>k}f(p[k]^e)(s(n/p[k]^e,k)+e!=1)
    if(p[y]>=x)return 0;
    LL id=x<=sqn?id1[x]:id2[n/x];//x/p[k]^e的位置
    LL ans=(g2[id]-g1[id]+mod-(sp2[y]-sp1[y])+mod)%mod;//g(x)-sp[x]
    for(int i=y+1;i<=top&&p[i]*p[i]<=x;++i){//枚举前置状态第二维
        LL pe=p[i];
        for(int e=1;pe<=x;e++,pe*=p[i]){//枚举次方
            LL fx=pe%mod;
            ans=(ans+fx*(fx-1)%mod*(getAns(x/pe,i)+(e!=1)))%mod;//转移
        }
    }
    return ans%mod;
}
int main(){
    scanf("%lld",&n);
    sqn=sqrt(n);
    pre(sqn);
    getSum(n);
    getG(n);
    printf("%lld\n",(getAns(n,0)+1)%mod);//加回1的贡献
}

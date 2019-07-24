#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MxN=3e5+10;
inline int in(){
    int ans=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans;
}
struct LCT{
#define ls ch[x][0]
#define rs ch[x][1]
    int fa[MxN],re[MxN],va[MxN],xr[MxN],ch[MxN][2];
    void pushUp(int x){
        xr[x]=xr[ls]^xr[rs]^va[x];
    }
    void pushDown(int x){
        if(re[x])re[ls]^=1,re[rs]^=1,re[x]^=1,swap(ls,rs);
    }
    bool isRoot(int x){
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void pushAll(int x){
        if(!isRoot(x))pushAll(fa[x]);pushDown(x);
    }
    int ws(int x){
        return ch[fa[x]][1]==x;
    }
    void rotate(int x){
        int f=fa[x],ff=fa[f],h=ws(x),b=ch[x][h^1];
        if(!isRoot(f))ch[ff][ws(f)]=x;fa[x]=ff;
        ch[f][h]=b;fa[b]=f;
        ch[x][h^1]=f;fa[f]=x;
        pushUp(f);pushUp(x);
    }
    void splay(int x){
        for(pushAll(x);!isRoot(x);rotate(x))if(!isRoot(fa[x]))rotate(ws(x)^ws(fa[x])?x:fa[x]);
    }
    void access(int x){
        for(int t=0;x;t=x,x=fa[x])splay(x),rs=t,pushUp(x);
    }
    void split(int x,int y){
        makeRoot(x);access(y);splay(y);
    }
    void makeRoot(int x){
        access(x);splay(x);re[x]^=1;
    }
    int findRoot(int x){
        access(x);splay(x);while(ls)x=ls;return x;
    }
    void link(int x,int y){
        makeRoot(x);if(findRoot(y)!=x)fa[x]=y;
    }
    void cut(int x,int y){
        split(x,y);if(findRoot(y)==x&&fa[x]==y&&!rs)ch[y][0]=0,fa[x]=0;
    }
#undef ls
#undef rs
}T;
int n,m;
#define I in()
int main(){
    n=I,m=I;
    for(int i=1;i<=n;i++)T.va[i]=I;
    for(int i=1;i<=m;i++){
        int op=I,x=I,y=I;
        switch(op){
            case(0):T.split(x,y);printf("%d\n",T.xr[y]);break;
            case(1):T.link(x,y);break;
            case(2):T.cut(x,y);break;
            case(3):T.access(x);T.splay(x);T.va[x]=y;T.pushUp(x);break;
        }
    }
}
#undef I

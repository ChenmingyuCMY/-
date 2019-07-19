#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
typedef long long LL;
const int MxN=1e5+10;
using namespace std;
template<typename T>
inline T in(){
    T ans=0,b=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')b=-1;else b=1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
    return ans*b;
}
int n,m,R,mod;
class Graph{
public:
    void addEdge(int x,int y){
        nex[++tot]=fir[x];fir[x]=tot;to[tot]=y;
        nex[++tot]=fir[y];fir[y]=tot;to[tot]=x;
    }
    int fir[MxN],nex[MxN<<1],to[MxN<<1],va[MxN];
private:
    int tot;
}G;
class Tree{
public:
    void buildTree(int x,int f){
        int Mx=-1;
        node[x].sz=1;
        node[x].fa=f;
        node[x].de=node[f].de+1;
        for(int i=G.fir[x];i;i=G.nex[i]){
            int v=G.to[i];
            if(v==f)continue;
            buildTree(v,x);
            if(node[v].sz>Mx)node[x].sn=v,Mx=node[v].sz;
            node[x].sz+=node[v].sz;
        }
    }
protected:
    struct Node{
        int sz,fa,tp,sn,de,id;
    }node[MxN];
};
class CutTree:public Tree{
public:
    void buildCutTree(int x,int top){
        node[x].id=++sz;
        node[x].tp=top;
        va[sz]=G.va[x];
        if(!node[x].sn)return;
        buildCutTree(node[x].sn,top);
        for(int i=G.fir[x];i;i=G.nex[i]){
            int v=G.to[i];
            if(v==node[x].fa||v==node[x].sn)continue;
            buildCutTree(v,v);
        }
    }
    int querySon(int x);
    int queryRange(int y,int x);
    void updateSon(int v,int x);
    void updateRange(int v,int y,int x);
protected:
    int sz,va[MxN];
};
class SegTree:public CutTree{
public:
    void buildSegTree(int k,int l,int r){
        segnode[k]=(SegNode){l,r,0,0,1};
        if(l==r)return segnode[k].sm=va[l],void();
        int mid=(l+r)>>1;
        if(l<=mid)buildSegTree(k<<1,l,mid);
        if(r>mid)buildSegTree(k<<1|1,mid+1,r);
        pushUp(k);
    }
    int querySon(int x){
        return query(1,node[x].id,node[x].id+node[x].sz-1)%mod;
    }
    int queryRange(int y,int x){
        int ans=0;
        while(node[x].tp!=node[y].tp){
            if(node[node[x].tp].de<node[node[y].tp].de)swap(x,y);
            ans+=query(1,node[node[x].tp].id,node[x].id);
            x=node[node[x].tp].fa;ans%=mod;
        }
        if(node[x].de>node[y].de)swap(x,y);
        ans+=query(1,node[x].id,node[y].id);
        return ans%mod;
    }
    void updateSon(int v,int x){
        update(1,node[x].id,node[x].id+node[x].sz-1,v,1);
    }
    void updateRange(int v,int y,int x){
        v%=mod;
        while(node[x].tp!=node[y].tp){
            if(node[node[x].tp].de<node[node[y].tp].de)swap(x,y);
            update(1,node[node[x].tp].id,node[x].id,v,1);
            x=node[node[x].tp].fa;
        }
        if(node[x].de>node[y].de)swap(x,y);
        update(1,node[x].id,node[y].id,v,1);
    }
    int exwork();
private:
    struct SegNode{
        int l,r,sm,tP,tT;
    }segnode[MxN<<2];
    void goMod(int k){
        segnode[k].tT%=mod;
        segnode[k].tP%=mod;
        segnode[k].sm%=mod;
    }
    void calc(int k,int len,int P,int T){
        if(len<=0)return;
        segnode[k].tT*=T;
        segnode[k].tP*=T;
        segnode[k].tP+=P;
        segnode[k].sm*=T;
        segnode[k].sm+=P*len;
        goMod(k);
    }
    void pushUp(int k){
        segnode[k].sm=segnode[k<<1].sm+segnode[k<<1|1].sm;
    }
    void pushDown(int k){
        int l=segnode[k].l;
        int r=segnode[k].r;
        int mid=(l+r)>>1;
        calc(k<<1,mid-l+1,segnode[k].tP,segnode[k].tT);
        calc(k<<1|1,r-mid,segnode[k].tP,segnode[k].tT);
        segnode[k].tP=0;segnode[k].tT=1;
    }
    void update(int k,int l,int r,int P,int T){
        int sl=segnode[k].l;
        int sr=segnode[k].r;
        if(l<=sl&&r>=sr)return calc(k,sr-sl+1,P,T),void();
        pushDown(k);
        int mid=(sl+sr)>>1;
        if(l<=mid)update(k<<1,l,r,P,T);
        if(r>mid)update(k<<1|1,l,r,P,T);
        pushUp(k);
    }
    int query(int k,int l,int r){
        int sl=segnode[k].l;
        int sr=segnode[k].r;
        if(l<=sl&&r>=sr)return segnode[k].sm;
        int ans=0,mid=(sl+sr)>>1;
        pushDown(k);
        if(l<=mid)ans+=query(k<<1,l,r),ans%=mod;
        if(r>mid)ans+=query(k<<1|1,l,r),ans%=mod;
        return ans;
    }
}T;
#define I in<int>()
void pre(){
    n=I;m=I;R=I;mod=I;
    for(int i=1;i<=n;i++)G.va[i]=I;
    for(int i=1;i<n;i++)G.addEdge(I,I);
    T.buildTree(R,0);
    T.buildCutTree(R,R);
    T.buildSegTree(1,1,n);
}
void work(){
    for(int i=1;i<=m;i++)
        switch(I){
            case(1):T.updateRange(I,I,I);break;
            case(2):printf("%d\n",T.queryRange(I,I));break;
            case(3):T.updateSon(I,I);break;
            case(4):printf("%d\n",T.querySon(I));break;
        }
}
int main(int argc,char** argv){
    pre();
    work();
}

#include<bits/stdc++.h>
#define I inline
using namespace std;
typedef long long LL;
const int Mx=1e5+1;
int n,q,root[Mx],va[Mx];
template<class T>
I T read(){
    T ans=0,b=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')b=-1;else b=1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans*b;
}
struct Node{
    int id,rk,v;
}node[Mx];
bool cmpId(Node a,Node b){return a.id<b.id;}
bool cmpV(Node a,Node b){return a.v<b.v;}

class CSegTree{
#define s segnode
public:
    void init(){
        while(size){
            s[size].ls=s[size].rs=s[size].sum=0;size--;
        }
    }
    void build(int &k,int l,int r){
        k=++size;
        if(l==r)return;
        int mid=(l+r)>>1;
        build(s[k].ls,l,mid);build(s[k].rs,mid+1,r);
    }
    void update(int &k,int pk,int id,int l,int r){
        k=++size;
        if(l==r){s[k].sum=s[pk].sum+1;return;}
        int mid=(l+r)>>1;
        if(mid>=id){s[k].rs=s[pk].rs;update(s[k].ls,s[pk].ls,id,l,mid);}
        if(mid<id){s[k].ls=s[pk].ls;update(s[k].rs,s[pk].rs,id,mid+1,r);}
        pushUp(k);
    }
    int query(int k,int pk,int rk,int l,int r){
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(s[s[k].ls].sum-s[s[pk].ls].sum<rk)return query(s[k].rs,s[pk].rs,rk-(s[s[k].ls].sum-s[s[pk].ls].sum),mid+1,r);
        else return query(s[k].ls,s[pk].ls,rk,l,mid);
    }
private:
    struct SegNode{
        int ls,rs,sum;
    }segnode[Mx*50];
    int size;
    void pushUp(int k){
        s[k].sum=s[s[k].ls].sum+s[s[k].rs].sum;
    }
#undef s
}T;
int top;
void init(){
    T.init();
    memset(node,0,sizeof node);
    n=read<int>(),q=read<int>();
    for(int i=1;i<=n;i++)node[i]=(Node){i,0,read<int>()};
    sort(node+1,node+1+n,cmpV);
    top=0;
    for(int i=1;i<=n;i++){
        if(i==1||node[i].v!=node[i-1].v)node[i].rk=++top,va[top]=node[i].v;
        else node[i].rk=top;
    }
    sort(node+1,node+1+n,cmpId);
    T.build(root[0],1,top);
    for(int i=1;i<=n;i++)T.update(root[i],root[i-1],node[i].rk,1,top);
}
void work(){
    int l,r,rk;
    for(int i=1;i<=q;i++){
        l=read<int>(),r=read<int>(),rk=read<int>();
        printf("%d\n",va[T.query(root[r],root[l-1],rk,1,top)]);
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        init();
        work();
    }
} 

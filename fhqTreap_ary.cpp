#include<bits/stdc++.h>
using namespace std;
const int Mx=1e6+5;
int n,m;
class Treap{
#define so(x,k) node[(x)].ch[(k)]
#define si(x) node[(x)].size
#define va(x) node[(x)].val
#define ky(x) node[(x)].key
#define tg(x) node[(x)].tag
public:
    void init(){
        for(int i=1;i<=n;i++)root=merge(root,newNode(i));
    }
    void reverse(int x,int y){
        int l=0,r=0,p=0;
        split(root,y,l,r);
        split(l,x-1,l,p);
        tg(p)^=1;
        root=merge(merge(l,p),r);
    }
    void split(int x,int v,int &l,int &r){
        if(!x){l=r=0;return;}
        pushDown(x);
        if(si(so(x,0))+1<=v){
            l=x;
            split(so(x,1),v-si(so(x,0))-1,so(x,1),r);
        }else{
            r=x;
            split(so(x,0),v,l,so(x,0));
        }
        pushUp(x);
    }
    int merge(int l,int r){
        if(!l||!r)return l+r;
        if(ky(l)<ky(r)){
            pushDown(l);
            so(l,1)=merge(so(l,1),r);
            pushUp(l);return l;
        }else{
            pushDown(r);
            so(r,0)=merge(l,so(r,0));
            pushUp(r);return r;
        }
    }
    void ans(){
        print(root);
    }
private:
    struct Node{
        int ch[2],size,val,tag,key;
    }node[Mx];
    int size,root;
    void pushUp(int x){
        si(x)=si(so(x,0))+si(so(x,1))+1;
    }
    void pushDown(int x){
        if(!tg(x))return;
        swap(so(x,0),so(x,1));
        tg(so(x,0))^=1;
        tg(so(x,1))^=1;
        tg(x)=0;
    }
    int newNode(int x){
        ++size;
        si(size)=1;
        va(size)=x;
        ky(size)=rand();
        return size;
    }
    void print(int x){
        pushDown(x);
        if(so(x,0))print(so(x,0));
        printf("%d ",va(x));
        if(so(x,1))print(so(x,1));
    }
#undef so
#undef si
#undef va
#undef ky
#undef tg
}T;
int main(){
    scanf("%d%d",&n,&m);
    T.init();
    for(int i=1,x,y;i<=m;i++){
        scanf("%d%d",&x,&y);
        T.reverse(x,y);
    }
    T.ans();
}

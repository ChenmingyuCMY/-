#include<bits/stdc++.h>
using namespace std;
const int Mx=1e5+5;
int n;
class Treap{
#define so(x,k) node[(x)].ch[(k)]
#define si(x) node[(x)].size
#define su(x) node[(x)].sum
#define va(x) node[(x)].val
#define ky(x) node[(x)].key
public:
    Treap(){
        newNode(INT_MIN);
        newNode(INT_MAX);
        root=1;
        so(1,1)=2;
        pushUp(1);
    }
    void insert(int &x,int v){
        if(x==0){
            x=newNode(v);
            return;
        }
        if(v==va(x)){
            su(x)++;
            pushUp(x);
            return;
        }
        if(v<va(x)){
            insert(so(x,0),v);
            if(ky(x)<ky(so(x,0)))rotate(x,0);
        }else{
            insert(so(x,1),v);
            if(ky(x)<ky(so(x,1)))rotate(x,1);
        }
        pushUp(x);
    }
    void remove(int &x,int v){
        if(!x)return;
        if(v==va(x)){
            if(su(x)>1){
                su(x)--;
                pushUp(x);
                return;
            }
            if(so(x,0)||so(x,1)){
                if(!so(x,1)||ky(so(x,0))>ky(so(x,1)))rotate(x,0),remove(so(x,1),v);
                else rotate(x,1),remove(so(x,0),v);
                pushUp(x);
            }else x=0;
            return;
        }
        v<va(x)?remove(so(x,0),v):remove(so(x,1),v);
        pushUp(x);
    }
    int rnk(int x,int v){
        if(!x)return 0;
        if(va(x)==v)return si(so(x,0))+1;
        if(va(x)>v)return rnk(so(x,0),v);
        return rnk(so(x,1),v)+si(so(x,0))+su(x);
    }
    int fnd(int x,int rk){
        if(!x)return INT_MAX;
        if(si(so(x,0))>=rk)return fnd(so(x,0),rk);
        if(si(so(x,0))+su(x)>=rk)return va(x);
        return fnd(so(x,1),rk-si(so(x,0))-su(x));
    }
    int bes(int v,int k){
        int ans=k+1,x=root;
        while(x){
            if(v==va(x)){
                if(so(x,k)>0){
                    x=so(x,k);
                    while(so(x,k^1)>0)x=so(x,k^1);
                    ans=x;
                }
                break;
            }
            if((va(x)<v)^k&&va(x)>va(ans)^k)ans=x;
            x=v<va(x)?so(x,0):so(x,1);
        }
        return va(ans);
    }
    int root;
private:
    struct Node{
        int ch[2],sum,size,val,key;
    }node[Mx];
    void pushUp(int x){
        si(x)=si(so(x,0))+si(so(x,1))+su(x);
    }
    void rotate(int &x,int k){
        int tmp=so(x,k);
        so(x,k)=so(tmp,k^1);so(tmp,k^1)=x;x=tmp;
        pushUp(so(x,k^1)),pushUp(x);
    }
    int newNode(int x){
        ++size;
        va(size)=x;
        ky(size)=rand();
        su(size)=si(size)=1;
        return size;
    }
    int size;
#undef ls
#undef rs
#undef su
#undef si
#undef va
#undef ky
}T;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int op,x;
        scanf("%d%d",&op,&x);
        switch(op){
            case 1:T.insert(T.root,x);break;
            case 2:T.remove(T.root,x);break;
            case 3:printf("%d\n",T.rnk(T.root,x)-1);break;
            case 4:printf("%d\n",T.fnd(T.root,x+1));break;
            case 5:printf("%d\n",T.bes(x,0));break;
            case 6:printf("%d\n",T.bes(x,1));break;
        }
    }
}

#include<bits/stdc++.h>
using namespace std;
const int Mx=2e5+5;
int n;
class Splay{
#define fa(x) node[(x)].f
#define so(x,k) node[(x)].ch[(k)]
#define si(x) node[(x)].size
#define su(x) node[(x)].sum
#define va(x) node[(x)].val
public:
    void insert(int x){
        int cur=root,p=0;
        while(cur&&va(cur)!=x){
            p=cur;
            cur=so(cur,x>va(cur));
        }
        if(cur)su(cur)++;
        else{
            cur=++size;
            if(p)so(p,x>va(p))=cur;
            so(cur,0)=so(cur,1)=0;
            fa(cur)=p;va(cur)=x;
            su(cur)=si(cur)=1;
        }
        splay(cur);
    }
    int rnk(int x){
        int cur=root;
        while(so(cur,x>va(cur))&&x!=va(cur)){
            cur=so(cur,x>va(cur));
        }
        splay(cur);
        return si(so(cur,0));
    }
    int find(int k){
        int cur=root;
        while(1){
            if(so(cur,0)&&k<=si(so(cur,0))){
                cur=so(cur,0);
            }else if(k>si(so(cur,0))+su(cur)){
                k-=si(so(cur,0))+su(cur);
                cur=so(cur,1);
            }else{
                return cur;
            }
        }
    }
    int pre(int x){
        rnk(x);
        if(va(root)<x)return root;
        int cur=so(root,0);
        while(so(cur,1))cur=so(cur,1);
        return cur;
    }
    int suc(int x){
        rnk(x);
        if(va(root)>x)return root;
        int cur=so(root,1);
        while(so(cur,0))cur=so(cur,0);
        return cur;
    }
    void remove(int x){
        int p=pre(x),s=suc(x);
        splay(p);splay(s,p);
        int del=so(s,0);
        if(su(del)>1){
            su(del)--;
            splay(del);
        }else{
            so(s,0)=0;
        }
    }
    int val(int x){return va(x);}
private:
    bool ckP(int x){
        return so(fa(x),1)==x;
    }
    void pushUp(int x){
        si(x)=si(so(x,0))+si(so(x,1))+su(x);
    }
    void rotate(int x){
        int y=fa(x),z=fa(y),k=ckP(x),w=so(x,k^1);
        so(y,k)=w;fa(w)=y;
        so(z,ckP(y))=x;fa(x)=z;
        so(x,k^1)=y;fa(y)=x;
        pushUp(y);pushUp(x);
    }
    void splay(int x,int goal=0){
        while(fa(x)!=goal){
            int y=fa(x),z=fa(y);
            if(z!=goal){
                if(ckP(x)==ckP(y))rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if(!goal)root=x;
    }
    struct Node{
        int f,ch[2],sum,size,val;
    }node[Mx];
    int size,root;
#undef fa
#undef so
#undef si
#undef su
#undef va
}T;
int main(){
    scanf("%d",&n);
    T.insert(INT_MAX);
    T.insert(INT_MIN);
    while(n--){
        int op,x;
        scanf("%d%d",&op,&x);
        switch(op){
            case 1:T.insert(x);break;
            case 2:T.remove(x);break;
            case 3:printf("%d\n",T.rnk(x));break;
            case 4:printf("%d\n",T.val(T.find(x+1)));break;
            case 5:printf("%d\n",T.val(T.pre(x)));break;
            case 6:printf("%d\n",T.val(T.suc(x)));break;
        }
    }
}

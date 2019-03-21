#include<bits/stdc++.h>
using namespace std;
const int Mx=1e5+5;
int n,m;
inline int read(){
    int ans=0,b=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')b=-1;else b=1;ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans*b;
}
struct Node{
    Node *ch[2],*f;
    int size,tagRev,tagCov,val,sum,mxlis[3];
};
class Splay{
#define mx(x,k) (x)->mxlis[(k)]
#define so(x,k) (x)->ch[(k)]
#define si(x) (x)->size
#define tr(x) (x)->tagRev
#define tc(x) (x)->tagCov
#define va(x) (x)->val
#define su(x) (x)->sum
#define fa(x) (x)->f
public:
    Splay(){
        blk=new Node();
        fa(blk)=so(blk,0)=so(blk,1)=blk;
        si(blk)=mx(blk,0)=mx(blk,1)=su(blk)=0;
        va(blk)=mx(blk,2)=INT_MIN/4;
        root=trash=blk;
        root=newNode(blk,INT_MIN/4);
        so(root,1)=newNode(root,INT_MIN/4);
    }
    void insert(int tot,int pos){
        size+=tot;
        while(size>500000){
            Node *tmp=fa(trash);
            release(trash);
            trash=tmp;
        }
        Node *x=find(pos+1),*y=find(pos+2);
        splay(x);splay(y,x);
        tot--;
        so(y,0)=newNode(y,read());
        y=so(y,0);
        while(tot){
            so(y,1)=newNode(y,read());
            y=so(y,1);
            tot--;
        }
        splay(y);
    }
    void remove(int tot,int pos){
        Node *x=find(pos),*y=find(pos+tot+1);
        splay(x);splay(y,x);
        Node *tmp=so(y,0);
        so(y,0)=blk;
        fa(tmp)=trash;
        trash=tmp;
        pushUp(y);pushUp(x);
    }
    void cover(int v,int tot,int pos){
        Node *x=find(pos),*y=find(pos+tot+1);
        splay(x);splay(y,x);
        tc(so(y,0))=1;
        va(so(y,0))=v;
        change(so(y,0));
        pushUp(y);pushUp(x);
    }
    void reverse(int tot,int pos){
        Node *x=find(pos),*y=find(pos+tot+1);
        splay(x);splay(y,x);
        Node *tmp=so(y,0);
        swap(mx(tmp,0),mx(tmp,1));
        swap(so(tmp,0),so(tmp,1));
        pushUp(y);pushUp(x);
        tr(tmp)^=1;
    }
    int getSum(int tot,int pos){
        Node *x=find(pos),*y=find(pos+tot+1);
        splay(x);splay(y,x);
        return su(so(y,0));
    }
    int getMax(){
        return mx(root,2);
    }
    Node *root,*blk,*trash;
private:
    int size;
    Node* find(int k){
        Node *cur=root;
        while(1){
            pushDown(cur);
            if(!bl(so(cur,0))&&k<=si(so(cur,0))){
                cur=so(cur,0);
            }else if(k>si(so(cur,0))+1){
                k-=si(so(cur,0))+1;
                cur=so(cur,1);
            }else{
                return cur;
            }
        }
    }
    void release(Node *x){
        if(bl(x))return;
        release(so(x,0));
        release(so(x,1));
        delNode(x);
        size--;
    }
    void change(Node *x){
        su(x)=si(x)*va(x);
        if(va(x)>0)mx(x,0)=mx(x,1)=mx(x,2)=su(x);
        else mx(x,0)=mx(x,1)=0,mx(x,2)=va(x);
    }
    bool ckP(Node* x){
        return so(fa(x),1)==x;
    }
    void pushUp(Node* x){
        #define ls so(x,0)
        #define rs so(x,1)
        si(x)=si(ls)+si(rs)+1;
        su(x)=su(ls)+su(rs)+va(x);
        mx(x,0)=max(su(ls)+va(x)+mx(rs,0),mx(ls,0));
        mx(x,1)=max(su(rs)+va(x)+mx(ls,1),mx(rs,1));
        mx(x,2)=max(max(mx(ls,2),mx(rs,2)),mx(ls,1)+va(x)+mx(rs,0));
    }
    void pushDown(Node* x){
        if(tc(x)){
            if(!bl(ls)){
                va(ls)=va(x);
                tc(ls)=1;
                change(ls);
            }
            if(!bl(rs)){
                va(rs)=va(x);
                tc(rs)=1;
                change(rs);
            }
            tc(x)=tr(x)=0;
        }
        if(tr(x)){
            swap(mx(ls,0),mx(ls,1));
            swap(mx(rs,0),mx(rs,1));
            swap(so(ls,0),so(ls,1));
            swap(so(rs,0),so(rs,1));
            tr(ls)^=1;
            tr(rs)^=1;
            tr(x)=0;
        }
        #undef ls
        #undef rs
    }
    void rotate(Node* x){
        int k=ckP(x);
        Node *y=fa(x),*z=fa(y),*w=so(x,k^1);
        so(y,k)=w;fa(w)=y;
        so(z,ckP(y))=x;fa(x)=z;
        so(x,k^1)=y;fa(y)=x;
        pushUp(y);pushUp(x);
    }
    void splay(Node *x,Node *goal=NULL){
        ck(goal);
        while(fa(x)!=goal){
            Node *y=fa(x),*z=fa(y);
            if(z!=goal){
                if(ckP(x)==ckP(y))rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if(bl(goal))root=x;
    }
    Node* newNode(Node* f,int v){
        Node* p=new Node();
        fa(p)=f;va(p)=v;si(p)=1;
        so(p,1)=so(p,0)=blk;
        mx(p,0)=mx(p,1)=max(v,0);
        mx(p,2)=su(p)=v;
        tc(p)=tr(p)=0;
        return p;
    }
    void delNode(Node *&p){
        if(bl(p))return;
        Node *x=p;
        delete(x);
        p=blk;
    }
    void ck(Node* &p){
        if(p==NULL)p=blk;
    }
    bool bl(Node* p){
        return p==blk;
    }
#undef so
#undef si
#undef va
#undef tr
#undef tc
#undef su
#undef mx
#undef fa
}T;
char op[10];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)T.insert(1,i-1);
    for(int i=1;i<=m;i++){
        scanf("%s",op);
        switch(op[2]){
            case 'S':T.insert(read(),read());break;
            case 'L':T.remove(read(),read());break;
            case 'K':T.cover(read(),read(),read());break;
            case 'V':T.reverse(read(),read());break;
            case 'T':printf("%d\n",T.getSum(read(),read()));break;
            case 'X':printf("%d\n",T.getMax());break;
        }
    }
}

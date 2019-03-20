#include<bits/stdc++.h>
using namespace std;
const int Mx=1e5+5;
int n,m,ary[Mx];
struct Node{
    Node *ch[2],*f;
    int size,tag,val;
};
class Splay{
#define so(x,k) (x)->ch[(k)]
#define si(x) (x)->size
#define tg(x) (x)->tag
#define fa(x) (x)->f
#define va(x) (x)->val
public:
    Splay(){
        blk=new Node();
        fa(blk)=so(blk,0)=so(blk,1)=blk;
        si(blk)=va(blk)=0;
        root=blk;
    }
    void buildSplay(Node* &x,Node* f,int l,int r){
        if(l>r)return;
        int mid=(l+r)>>1;
        x=newNode(f,ary[mid]);
        buildSplay(so(x,0),x,l,mid-1);
        buildSplay(so(x,1),x,mid+1,r);
        pushUp(x);
    }
    void reverse(int l,int r){
        Node *x=find(root,l),*y=find(root,r+2);
        splay(x);splay(y,x);
        tg(so(y,0))^=1;
    }
    void print(Node* x){
        pushDown(x);
        if(!bl(so(x,0)))
            print(so(x,0));
        if(va(x)!=INT_MAX&&va(x)!=INT_MIN)
            printf("%d ",va(x));
        if(!bl(so(x,1)))
            print(so(x,1));
    }
    Node *root,*blk;
private:
    Node* find(Node *x,int k){
        pushDown(x);
        if(k==si(so(x,0))+1)return x;
        if(k<=si(so(x,0)))return find(so(x,0),k);
        return find(so(x,1),k-si(so(x,0))-1);   
    }
    bool ckP(Node* x){
        return so(fa(x),1)==x;
    }
    void pushUp(Node* x){
        si(x)=si(so(x,0))+si(so(x,1))+1;
    }
    void pushDown(Node* x){
        if(!tg(x))return;
        swap(so(x,0),so(x,1));
        tg(so(x,0))^=1;
        tg(so(x,1))^=1;
        tg(x)=0;
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
        return p;
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
#undef tg
#undef fa
}T;
int main(){
    scanf("%d%d",&n,&m);
    ary[1]=INT_MIN;
    for(int i=1;i<=n;i++)ary[i+1]=i;
    ary[n+2]=INT_MAX;
    T.buildSplay(T.root,T.blk,1,n+2);
    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        T.reverse(l,r);
    }
    T.print(T.root);
}

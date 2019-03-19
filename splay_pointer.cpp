#include<bits/stdc++.h>
using namespace std;
const int Mx=2e5+5;
int n;
class Splay{
#define fa(x) (x)->f
#define so(x,k) (x)->ch[(k)]
#define si(x) (x)->size
#define su(x) (x)->sum
#define va(x) (x)->val
public:
    Splay(){
        blank=new Node();
        fa(blank)=so(blank,0)=so(blank,1)=blank;
        si(blank)=su(blank)=0;
        root=blank;
    }
    void work(int op,int x){
        switch(op){
            case 1:insert(x);break;
            case 2:remove(x);break;
            case 3:printf("%d\n",rnk(x));break;
            case 4:printf("%d\n",va(find(x+1)));break;
            case 5:printf("%d\n",va(pre(x)));break;
            case 6:printf("%d\n",va(suc(x)));break;
        }
    }
private:
    struct Node{
        Node(int _val=0,Node* _f=NULL,int _sum=1,int _size=1):val(_val),f(_f),sum(_sum),size(_size){}
        Node *ch[2],*f;
        int sum,size,val;
    };
    void insert(int x){
        Node *cur=root,*p=blank;
        while(!bl(cur)&&va(cur)!=x){
            p=cur;
            cur=so(cur,x>va(cur));
        }
        if(!bl(cur))su(cur)++;
        else{
            cur=NULL;
            newNode(cur,x,p);
            if(!bl(p))so(p,x>va(p))=cur;
        }
        splay(cur);
    }
    void remove(int x){
        Node *p=pre(x),*s=suc(x);
        splay(p);splay(s,p);
        Node* del=so(s,0);
        if(su(del)>1){
            su(del)--;
            splay(del);
        }else{
            delNode(so(s,0));
        }
    }
    int rnk(int x){
        Node *cur=root;
        while(!bl(so(cur,x>va(cur)))&&x!=va(cur)){
            cur=so(cur,x>va(cur));
        }
        splay(cur);
        return si(so(cur,0));
    }
    Node* find(int k){
        Node *cur=root;
        while(1){
            if(!bl(so(cur,0))&&k<=si(so(cur,0))){
                cur=so(cur,0);
            }else if(k>si(so(cur,0))+su(cur)){
                k-=si(so(cur,0))+su(cur);
                cur=so(cur,1);
            }else{
                return cur;
            }
        }
    }
    Node* pre(int x){
        rnk(x);
        if(va(root)<x)return root;
        Node* cur=so(root,0);
        while(!bl(so(cur,1)))cur=so(cur,1);
        return cur;
    }
    Node* suc(int x){
        rnk(x);
        if(va(root)>x)return root;
        Node* cur=so(root,1);
        while(!bl(so(cur,0)))cur=so(cur,0);
        return cur;
    }
    bool ckP(Node* x){
        return so(fa(x),1)==x;
    }
    void pushUp(Node* x){
        si(x)=si(so(x,0))+si(so(x,1))+su(x);
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
    void ck(Node* &p){
        if(p==NULL)p=blank;
    }
    bool bl(Node* p){
        return p==blank;
    }
    void newNode(Node *&p,int v,Node *f){
        p=new Node(v,f);
        so(p,0)=so(p,1)=blank;
    }
    void delNode(Node *&p){
        delete(p);
        p=blank;
    }
    Node *root,*blank;
#undef fa
#undef so
#undef si
#undef su
#undef va
}T;
int main(){
    scanf("%d",&n);
    T.work(1,INT_MAX);
    T.work(1,INT_MIN);
    while(n--){
        int op,x;
        scanf("%d%d",&op,&x);
        T.work(op,x);
    }
}

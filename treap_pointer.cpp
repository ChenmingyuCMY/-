#include<bits/stdc++.h>
using namespace std;
const int Mx=1e5+5;
int n;
struct Node{
    Node *ch[2];
    int key,val,size,sum;
};
class Treap{
#define so(x,k) (x)->ch[(k)]
#define si(x) (x)->size
#define su(x) (x)->sum
#define ky(x) (x)->key
#define va(x) (x)->val
public:
    Treap(){
        blk=new Node();
        so(blk,0)=so(blk,1)=blk;
        si(blk)=0;
        root=newNode(INT_MIN);
        so(root,1)=newNode(INT_MAX);
        Min=root;Max=so(root,1);
        pushUp(root);
    }
    void insert(Node *&x,int v){
        if(bl(x)){
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
    void remove(Node *&x,int v){
        if(bl(x))return;
        if(v==va(x)){
            if(su(x)>1){
                su(x)--;
                pushUp(x);
                return;
            }
            if(!bl(so(x,0))||!bl(so(x,1))){
                if(bl(so(x,1))||ky(so(x,0))>ky(so(x,1)))rotate(x,0),remove(so(x,1),v);
                else rotate(x,1),remove(so(x,0),v);
                pushUp(x);
            }else del(x);
            return;
        }
        if(v<va(x))remove(so(x,0),v);
        else remove(so(x,1),v);
        pushUp(x);
    }
    int rnk(Node *x,int v){
        if(x==blk)return 0;
        if(va(x)==v)return si(so(x,0))+1;
        if(va(x)>v)return rnk(so(x,0),v);
        return rnk(so(x,1),v)+si(so(x,0))+su(x);
    }
    int fnd(Node *x,int rk){
        if(x==blk)return INT_MAX;
        if(si(so(x,0))>=rk)return fnd(so(x,0),rk);
        if(si(so(x,0))+su(x)>=rk)return va(x);
        return fnd(so(x,1),rk-si(so(x,0))-su(x));
    }
    int bes(int v,int k){
        Node *ans=k?Max:Min,*x=root;
        while(!bl(x)){
            if(v==va(x)){
                if(!bl(so(x,k))){
                    x=so(x,k);
                    while(!bl(so(x,k^1)))x=so(x,k^1);
                    ans=x;
                }
                break;
            }
            if((va(x)<v)^k&&(va(x)>va(ans))^k)ans=x;
            x=v<va(x)?so(x,0):so(x,1);
        }
        return va(ans);
    }
    Node *root,*blk,*Min,*Max,*f;
    int s;
private:
    void pushUp(Node *x){
        si(x)=si(so(x,0))+si(so(x,1))+su(x);
    }
    void rotate(Node *&x,int k){
        Node *tmp=so(x,k);
        so(x,k)=so(tmp,k^1);so(tmp,k^1)=x;x=tmp;
        pushUp(so(x,k^1)),pushUp(x);
    }
    Node* newNode(int x){
        Node* p=new Node();
        so(p,0)=so(p,1)=blk;
        si(p)=su(p)=1;
        ky(p)=rand();
        va(p)=x;
        return p;
    }
    void del(Node *&x){
        Node *p=x;
        delete(p);
        x=blk;
    }
    bool bl(Node *x){
        return x==blk;
    }
#undef so
#undef si
#undef su
#undef ky
#undef va
}T;
int main(){
    scanf("%d",&n);
    while(n--){
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

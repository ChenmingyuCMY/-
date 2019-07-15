#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long LL;
const int MxN=1e5+10086,inf=192608170;
class Splay{
#define sz(x) node[x].sz
#define vl(x) node[x].vl
#define sm(x) node[x].sm
#define ft(x) node[x].ft
#define sn(x,i) node[x].ch[i] 
#define ls sn(x,0)
#define rs sn(x,1)
public:
    Splay(){
        root=size=top=1;vl(1)=inf;
        newNode(sn(1,0),1,-inf);
        sz(1)=sm(1)=1;
        pushUp(1);
        size++;
    }
    int ask(int k){
        return vl(fnd(k));
    }
    int insert(int k){
        int p=pre(k),s=suc(k);
        splay(s),splay(p,s);
        if(sn(p,1))sm(sn(p,1))++;
        else newNode(sn(p,1),p,k);
        pushUp(p);pushUp(s);
        splay(sn(p,1));
        size++;
    }
    int remove(int k){
        int p=pre(k),s=suc(k);
        splay(p);splay(s,p);
        int x=sn(s,0);
        if(sm(x)>1)sm(x)--,splay(x);
        else th.push(sn(s,0)),sn(s,0)=0;
    }
    int rnk(int k){
        int x=root;
        while(sn(x,vl(x)<k)&&k!=vl(x))x=sn(x,vl(x)<k);
        splay(x);
        return sz(ls);
    }
    int fnd(int k){
        int x=root;
        for(;;){
            if(ls&&sz(ls)>=k)x=ls;
            else if(rs&&sz(ls)+sm(x)<k)k-=sz(ls)+sm(x),x=rs;
            else return x;
        }
    }
    int pre(int k){
        rnk(k);
        if(vl(root)<k)return root;
        int x=sn(root,0);
        while(rs)x=rs;
        return x;
    }
    int suc(int k){
        rnk(k);
        if(vl(root)>k)return root;
        int x=sn(root,1);
        while(ls)x=ls;
        return x;
    }
    int _sz(){
        return size;
    }
    int _lv(){
        return leave;
    }
    int _rt(){
        return root;
    }
    int _vl(int x){
        return vl(x);
    }
private:
    int leave,root,size,top;
    struct Node{
        int ch[2],ft,sz,vl,sm;
    }node[MxN];
    queue<int>th;
    int pushUp(int x){
        sz(x)=sz(ls)+sz(rs)+sm(x);
    }
    int rotate(int x){
        int f=ft(x),ff=ft(f),h=ws(x),w=sn(x,h^1);
        sn(f,h)=w;ft(w)=f;
        sn(ff,ws(f))=x;ft(x)=ff;
        sn(x,h^1)=f;ft(f)=x;
        pushUp(f);pushUp(x);
    }
    int splay(int x,int pos=0){
        for(;ft(x)!=pos;rotate(x))if(ft(ft(x))!=pos)rotate(ws(ft(x))==ws(x)?ft(x):x);
        if(pos==0)root=x;
    }
    int ws(int x){
        return sn(ft(x),1)==x;
    }
    int delNode(){
        int x;
        if(th.empty())x=++top;
        else x=th.front(),th.pop();
        ls=rs=0;
        return x;
    }
    int newNode(int &x,int f,int v){
        x=delNode();
        ft(x)=f;vl(x)=v;
        sz(x)=sm(x)=1;
        return x;
    }
#undef sz
#undef vl
#undef sm
#undef ft
#undef sn
#undef ls
#undef rs
}T;
int n,m,k;
char op[10];
int main(int argc,char **argv){
    scanf("%d",&n);
    for(int op,x;n;n--){
        scanf("%d%d",&op,&x);
        switch(op){
            case 1:T.insert(x);break;
            case 2:T.remove(x);break;
            case 3:printf("%d\n",T.rnk(x));break;
            case 4:printf("%d\n",T._vl(T.fnd(x+1)));break;
            case 5:printf("%d\n",T._vl(T.pre(x)));break;
            case 6:printf("%d\n",T._vl(T.suc(x)));break;
        }
    }

}

#include<bits/stdc++.h>
using namespace std;
typedef double db;
const db eps=1e-9;
const int MxN=2005;
int n;
struct Hull{
    Hull(){O=(Point){0,0,0};}
    struct Point{
        db x,y,z;
        friend Point operator+(const Point a,const Point b){
            return (Point){a.x+b.x,a.y+b.y,a.z+b.z};
        }
        friend Point operator-(const Point a,const Point b){
            return (Point){a.x-b.x,a.y-b.y,a.z-b.z};
        }
        friend Point operator*(const Point a,const Point b){
            return (Point){a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
        }//叉乘
        friend db operator^(const Point a,const Point b){
            return a.x*b.x+a.y*b.y+a.z*b.z;
        }//点积
        void print(){
            printf("Point: x=%.2f y=%.2f z=%.2f\n",x,y,z);
        }
    }p[MxN],O;
    struct Surface{
        Point *a,*b,*c;
        int p[3];
        void print(){
            puts("Surface:{");
            printf("    ");a->print();
            printf("    ");b->print();
            printf("    ");c->print();
            puts("}");
        }
    };
    vector<Point>ph;
    vector<Surface>s;
    int ptop,stop,top;
    db _rand(db x){
        return x+(1.0*rand()/RAND_MAX-0.5)*eps*10;
    }
    Point _shake(Point a){
        return (Point){_rand(a.x),_rand(a.y),_rand(a.z)};
    }
    db _norm(Point a){
        return sqrt(a^a);
    }
    db _distance(Point a,Point b){
        return _norm(a-b);
    }
    db _area(Point a,Point b,Point c){
        return _norm((a-c)*(b-c))/2;
    }
    db _volume(Point a,Point b,Point c,Point d){
        return (((a-d)*(b-d))^(c-d))/6;
    }
    db point_to_surface(Point p,Surface s){
        return ((*s.b-*s.a)*(*s.c-*s.a))^(p-*s.a);
    }
    void init(){
        Point tmp;
        while(~scanf("%lf%lf%lf",&tmp.x,&tmp.y,&tmp.z)){
            bool conflict=0;
            for(int j=1;j<=top;j++)
                if(_norm(tmp-p[j])<=eps){conflict=1;break;}
            if(!conflict)p[++top]=tmp;
        }
        for(int i=1;i<=top;i++)p[i]=_shake(p[i]);
        n=top;
    }
    bool vis[MxN][MxN];
    bool isin[MxN];
    db hullSurface(){
        db ans=0;
        for(int i=0;i<(int)s.size();i++)ans+=_area(*s[i].a,*s[i].b,*s[i].c);
        return ans;
    }
    db hullVolume(){
        db ans=0;
        for(int i=0;i<(int)s.size();i++)ans+=_volume(*s[i].a,*s[i].b,*s[i].c,O);
        return ans;
    }
    db getHull(){
        s.push_back((Surface){&p[1],&p[2],&p[3],1,2,3});
        s.push_back((Surface){&p[3],&p[2],&p[1],3,2,1});
        for(int i=4;i<=n;i++){
            vector<Surface>now;
            for(int j=0;j<(int)s.size();j++){
                Surface f=s[j];
                bool see=point_to_surface(p[i],f)>eps;
                if(!see)now.push_back(f);
                for(int k=0;k<3;k++)
                    vis[f.p[k]][f.p[(k+1)%3]]=see;
            }
            for(int j=0;j<(int)s.size();j++)
                for(int k=0;k<3;k++){
                    int a=s[j].p[k];
                    int b=s[j].p[(k+1)%3];
                    if(vis[a][b]!=vis[b][a]&&vis[a][b])
                        now.push_back((Surface){&p[a],&p[b],&p[i],a,b,i});
                }
            s=now;
        }
        for(int i=0;i<(int)s.size();i++)isin[s[i].p[0]]=isin[s[i].p[1]]=isin[s[i].p[2]]=1;
        for(int i=1;i<=n;i++)if(vis[i])ph.push_back(p[i]);
        return hullVolume();
    }
}H;
int main(){
    H.init();
    printf("%.2lf",H.getHull());
}

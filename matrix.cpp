
34 lines (33 sloc) 934 Bytes
#include<bits/stdc++.h>
using namespace std;
template<typename T,int N,int M>
class Matrix{
public:
    T n,m,A[N][M];
    Matrix(int _n=0,int _m=0):n(_n),m(_m){memset(A,0,sizeof A);}
    friend Matrix<T,N,M> operator* (Matrix<T,N,M> a,Matrix<T,N,M> b){
        int _i=a.n,_j=b.m,_k=a.m;
        Matrix<T,N,M> ans(_i,_j);
        for(int i=0;i<_i;i++)
            for(int j=0;j<_j;j++)
                for(int k=0;k<_k;k++)
                    ans.A[i][j]+=a.A[i][k]*b.A[k][j];
        return ans;
    }
    void print(){
        char ch[10];
        if(typeid(T).name()==typeid(int).name())sprintf(ch,"%%d ");
        if(typeid(T).name()==typeid(long long).name())sprintf(ch,"%%lld ");
        printf("n:%d m:%d\n",n,m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf(ch,A[i][j]);
            }
            puts("");
        }
    }
};
int main(){
    Matrix<int,2,2> a(2,2);
    a.print();
}

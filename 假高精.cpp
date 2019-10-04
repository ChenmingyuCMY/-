#include<bits/stdc++.h>
using namespace std;
const int Mx=55;
int N,K;
char ch[Mx];
struct BigInt{
    short len,dig[Mx];
    BigInt(){len=1;dig[1]=0;}
    BigInt(int a){len=1;dig[1]=a;ck();}
    void ck(){
        for(int i=this->len+1;i<Mx;i++)this->dig[i]=0;
        for(int i=1;i<=this->len;i++){
            this->dig[i+1]+=this->dig[i]/10;
            this->dig[i]%=10;
            if(this->dig[this->len+1])this->len++;
        }
        while(this->dig[this->len]==0&&this->len)this->len--;
        if(this->len==0)this->len++;
    }
    friend BigInt operator+(const BigInt &a,int x){
        BigInt tmp=a;
        tmp.dig[1]+=x;
        tmp.ck();
        return tmp;
    }
    friend BigInt operator*(const BigInt &a,int x){
        BigInt tmp=a;
        for(int i=1;i<=tmp.len;i++)tmp.dig[i]*=x;
        tmp.ck();
        return tmp;
    }
    friend BigInt operator+(const BigInt &a,const BigInt &b){
        BigInt tmp;tmp.ck();
        tmp.len=a.len>b.len?a.len:b.len;
        for(int i=1;i<=a.len;i++)tmp.dig[i]+=a.dig[i];
        for(int i=1;i<=b.len;i++)tmp.dig[i]+=b.dig[i];
        tmp.ck();
        return tmp;
    }
    friend BigInt operator*(const BigInt &a,const BigInt &b){
        BigInt tmp;tmp.ck();
        tmp.len=a.len+b.len-1;
        for(int i=1;i<=a.len;i++)
            for(int j=1;j<=b.len;j++)
                tmp.dig[i+j-1]+=a.dig[i]*b.dig[j];    
        tmp.ck();
        return tmp;
    }
    friend bool operator==(const BigInt &a,const BigInt &b){
        if(a.len!=b.len)return 0;
        for(int i=1;i<=a.len;i++)if(a.dig[i]!=b.dig[i])return 0;
        return 1;
    }
    friend bool operator!=(const BigInt &a,const BigInt &b){
        return !(a==b);
    }
    friend bool operator<(const BigInt &a,const BigInt &b){
        if(a.len!=b.len)return a.len<b.len;
        for(int i=a.len;i>=1;i--)if(a.dig[i]!=b.dig[i])return a.dig[i]<b.dig[i];
        return 0;
    }
    friend bool operator>(const BigInt &a,const BigInt &b){
        return !(a<b)&&!(a==b);
    }
    friend bool operator>=(const BigInt &a,const BigInt &b){
        return !(a<b);
    }
    friend bool operator<=(const BigInt &a,const BigInt &b){
        return !(a>b);
    }
    friend ostream& operator<<(ostream&os,const BigInt &a){
        for(int i=a.len;i>=1;i--)os<<a.dig[i];return os;
    }
};
BigInt max(BigInt a,BigInt b){
    return (a>b)?a:b;
}
BigInt num[Mx][Mx],dp[Mx][Mx];
int main(){
    scanf("%d%d%s",&N,&K,ch+1);
    for(int i=1;i<=N;i++)
        for(int j=i;j<=N;j++)
            num[i][j]=num[i][j-1]*10+(ch[j]-'0');
    for(int i=1;i<=N;i++)
        dp[i][0]=num[1][i];
    for(int i=1;i<=N;i++)
        for(int j=1;j<i;j++)
            for(int k=1;k<=j;k++)
                dp[i][k]=(max(dp[i][k],dp[j][k-1]*num[j+1][i]));
    cout<<dp[N][K];
}

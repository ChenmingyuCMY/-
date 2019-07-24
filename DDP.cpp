#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
const int MxN = 1e5 + 10, inf = 192608170;
using namespace std;
int n, m;

inline int in() {
    int ans = 0, b = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') b = -1; else b = 1; ch = getchar();}
    while(ch >= '0' && ch <= '9') {ans = ans * 10 + ch - '0'; ch = getchar();}
    return ans * b;
}

class Graph {
public:
    void addEdge(int x, int y) {
        nex[++tot] = fir[x]; fir[x] = tot; to[tot] = y;
        nex[++tot] = fir[y]; fir[y] = tot; to[tot] = x;
    }

    int fir[MxN], nex[MxN << 1], to[MxN << 1], va[MxN];
private:
    int tot;
}G;

class Matrix {
public:
    int A[2][2];

    void init() {A[0][0] = A[1][0] = A[0][1] = A[1][1] = -inf;}
    
    friend Matrix operator* (Matrix a, Matrix b) {
        Matrix ans; ans.init();
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    ans.A[i][j] = max(ans.A[i][j], a.A[i][k] + b.A[k][j]);
        return ans;
    }

    void print() {
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++)
                printf("%d ", A[i][j]);
            puts("");
        }
        puts("--------------------");
    }
};

class Tree {
protected:
    struct Node {
        int fa, sz, sn, de, tp, id, dn;
    }nd[MxN];
public:
    void buildTree(int x, int f){
        int Mx = -1;
        nd[x].fa = f;
        nd[x].sz = 1;
        nd[x].de = nd[f].de + 1;
        for (int i = G.fir[x]; i; i = G.nex[i]) {
            int v = G.to[i];
            if (v == f) continue;
            buildTree(v, x);
            nd[x].sz += nd[v].sz;
            if (nd[v].sz > Mx) nd[x].sn = v, Mx = nd[v].sz;
        }
    }
};

class CutTree: public Tree {
protected:
    struct NewNode {
        int G[2], F[2];
        Matrix mat; 
    }nnd[MxN];

    int sz;
public:
    void buildCutTree(int x, int top) {
        int id = ++sz, vid;
        nd[x].id = id;
        nd[x].tp = top;
        nd[top].dn = id;
        nnd[id].G[1] = nnd[id].F[1] = G.va[x];
        if (!nd[x].sn)
            return;
        buildCutTree(nd[x].sn, top);
        vid = nd[nd[x].sn].id;
        nnd[id].F[0] += max(nnd[vid].F[1], nnd[vid].F[0]);
        nnd[id].F[1] += nnd[vid].F[0];
        for (int i = G.fir[x]; i; i = G.nex[i]) {
            int v = G.to[i];
            if (v == nd[x].fa || v == nd[x].sn)
                continue;
            buildCutTree(v, v);
            vid = nd[v].id;
            nnd[id].G[0] += max(nnd[vid].F[0], nnd[vid].F[1]);
            nnd[id].G[1] += nnd[vid].F[0];
            nnd[id].F[0] += max(nnd[vid].F[0], nnd[vid].F[1]);
            nnd[id].F[1] += nnd[vid].F[0];
        }
    }
};

class SegTree: public CutTree {
private:
    Matrix ans, lst, now;

    struct SegNode {
        int l, r;
        Matrix s;
    }snd[MxN << 2];

    void update(int k, int id){
        if (snd[k].l == snd[k].r && snd[k].l == id)
            return snd[k].s = nnd[id].mat, void();
        int mid = (snd[k].l + snd[k].r) >> 1;
        if (id <= mid)
            update(k << 1, id);
        if (id > mid)
            update(k << 1 | 1, id);
        pushUp(k);
    }

    Matrix query(int k, int l, int r){
        if (snd[k].l >= l && r >= snd[k].r)
            return snd[k].s;
        int mid = (snd[k].l + snd[k].r) >> 1;
        if (r <= mid)
            return query(k << 1, l, r);
        if (l > mid)
            return query(k << 1 | 1, l, r);
        return query(k << 1, l, r) * query(k << 1 | 1, l, r);	
    }
    
    void pushUp(int k) {
        snd[k].s = snd[k << 1].s * snd[k << 1 | 1].s;
    }
public:
    void buildSegTree(int k, int l, int r){
        snd[k].l = l, snd[k].r = r;
        if (l == r) {
            nnd[l].mat.A[0][0] = nnd[l].G[0];
            nnd[l].mat.A[0][1] = nnd[l].G[0];
            nnd[l].mat.A[1][0] = nnd[l].G[1];
            nnd[l].mat.A[1][1] = -inf;
            snd[k].s = nnd[l].mat;
            return;
        }
        int mid = (l + r) >> 1;
        buildSegTree(k << 1, l, mid);
        buildSegTree(k << 1 | 1, mid + 1, r);
        pushUp(k);
    }

    int modify(int v, int x) {
        int id = nd[x].id, top;
        nnd[id].mat.A[1][0] += v - G.va[x];
        G.va[x] = v;
        while (x) {
            top = nd[x].tp;
            lst = query(1, nd[top].id, nd[top].dn);
            update(1, id);
            now = query(1, nd[top].id, nd[top].dn);
            x = nd[top].fa, id = nd[x].id;
            nnd[id].mat.A[0][0] += max(now.A[0][0], now.A[1][0]) - max(lst.A[0][0], lst.A[1][0]);
            nnd[id].mat.A[0][1] = nnd[id].mat.A[0][0];
            nnd[id].mat.A[1][0] += now.A[0][0] - lst.A[0][0];
        }
        ans = query(1, nd[1].id, nd[1].dn);
        return max(ans.A[0][0], ans.A[1][0]);
    }
}T;

#define I in()
void pre() {
    n = I, m = I;
    for (int i = 1; i <= n; i++) G.va[i] = I;
    for (int i = 1; i < n; i++) G.addEdge(I, I);
    T.buildTree(1, 0);
    T.buildCutTree(1, 1);
    T.buildSegTree(1, 1, n);
}

void work() {
    for (int i = 1; i <= m; i++) printf("%d\n", T.modify(I, I));
}
#undef I

int main() {
    pre();
    work();
}

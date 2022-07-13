#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

using i64 = long long;
using namespace std;

namespace IO
{
    int f, c;

    template<typename T> inline void _Read(T &k)
    {
        k = 0, f = 1, c = getchar();
        while(!isdigit(c))
        {
            if(c == '-') f = -1;
            c = getchar();
        }
        while(isdigit(c))
        {
            k = (k << 3) + (k << 1) + c - '0';
            c = getchar();
        }
        return k *= f, void();
    }

    template<typename T> inline void _Write(T k)
    {
        if(k < 0) putchar('-'), k = -k;
        if(k > 9) _Write(k / 10);
        return putchar(k % 10 + '0'), void();
    }

    inline int Read32() { int k; _Read(k); return k; }
    inline i64 Read64() { i64 k; _Read(k); return k; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Read64;
using IO :: Write32;
using IO :: Write64;

namespace Program
{
    const int MAXN = 105;
    const int MAXM = 2505;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, m, t;
    i64 dis[MAXN][MAXN];

    struct Edge { int u, v; i64 w; Edge(int _u = 0, int _v = 0, i64 _w = 0) : u(_u), v(_v), w(_w) {} } ed[MAXM];

    struct Matrix
    {
        int n, m; i64 v[MAXN][MAXN];
        Matrix(int _n, int _m) : n(_n), m(_m) { memset(v, 0x3F, sizeof v); }
        Matrix(int _n) : n(_n), m(_n) { memset(v, 0x3F, sizeof v); for(register int i = 1; i <= _n; i++) v[i][i] = 0; }
    };

    Matrix operator * (Matrix a, Matrix b)
    {
        Matrix res(a.n, b.m); int p = a.m;
        for(register int i = 1; i <= res.n; i++) for(register int j = 1; j <= res.m; j++) for(register int k = 1; k <= p; k++) res.v[i][j] = min(res.v[i][j], a.v[i][k] + b.v[k][j]);
        return res;
    }

    Matrix operator ^ (Matrix a, int t)
    {
        Matrix res(n);
        while(t)
        {
            if(t & 1) res = res * a;
            a = a * a;
            t >>= 1;
        }
        return res;
    }

    inline void Floyd()
    {
        for(register int k = 1; k <= n; k++) for(register int i = 1; i <= n; i++) for(register int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), t = Read32();
        memset(dis, 0x3F, sizeof dis);
        for(register int i = 1; i <= n; i++) dis[i][i] = 0;
        int c = 0;
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32(); i64 w = Read64();
            dis[u][v] = min(dis[u][v], w), ed[++c] = Edge(u, v, w);
        }
        Floyd();
        if(t == 0) return Write32(dis[1][n]), 0;
        Matrix u(n, n);
        for(register int i = 1; i <= n; i++) for(register int j = 1; j <= n; j++)
        {
            u.v[i][j] = dis[i][j];
            for(register int k = 1; k <= m; k++) u.v[i][j] = min(u.v[i][j], dis[i][ed[k].u] + dis[ed[k].v][j] - ed[k].w);
        }
        u = u ^ t, Write64(u.v[1][n]);
        return 0;
    }
}

int main() { return Program :: Run(); }
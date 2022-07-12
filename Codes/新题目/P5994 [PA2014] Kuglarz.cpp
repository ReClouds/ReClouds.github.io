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
    const int MAXN = 2005;

    int n, m, fa[MAXN];
    i64 c[MAXN][MAXN];

    struct Edge { int u, v; i64 w; Edge(int _u = 0, int _v = 0, i64 _w = 0) : u(_u), v(_v), w(_w) {} bool operator < (const Edge &t) const { return w < t.w; } } ed[MAXN * MAXN];

    inline int Find(int u)
    {
        while(u != fa[u]) u = fa[u] = fa[fa[u]];
        return u;
    }

    inline i64 Kruskal()
    {
        i64 res = 0, tot = 0;
        for(register int i = 1; i <= m; i++)
        {
            int u = ed[i].u, v = ed[i].v, fu = Find(u), fv = Find(v);
            if(fu == fv) continue;
            ++tot, fa[fv] = fu, res += ed[i].w;
            if(tot == n) break;
        }
        return res;
    }

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i <= n; i++) for(register int j = i; j <= n; j++)
        {
            i64 w = Read64();
            ed[++m] = Edge(i - 1, j, w);
        }
        sort(ed + 1, ed + m + 1);
        for(register int i = 0; i <= n; i++) fa[i] = i;
        Write64(Kruskal());
        return 0;
    }
}

int main() { return Program :: Run(); }
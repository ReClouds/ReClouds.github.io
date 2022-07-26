#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>

#define i64 long long

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
    const int MAXN = 300005;

    int n, t, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], si[MAXN], dep[MAXN], mxdep[MAXN], hs[MAXN], dfn[MAXN];
    i64 *f[MAXN], g[MAXN], tag[MAXN], ans[MAXN];
    vector<int> vec[MAXN];

    struct Query { int p, k; } q[MAXN];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void DFS1(int u, int fa)
    {
        si[u] = 1, dep[u] = dep[fa] + 1, mxdep[u] = hs[u] = 0;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            DFS1(v, u), si[u] += si[v];
            if(mxdep[v] + 1 > mxdep[u]) mxdep[u] = mxdep[v] + 1, hs[u] = v;
        }
        return;
    }

    inline void DFS2(int u, int fa)
    {
        dfn[u] = ++*dfn, f[u] = g + dfn[u];
        if(hs[u]) DFS2(hs[u], u);
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa || v == hs[u]) continue;
            DFS2(v, u);
        }
        return;
    }

    inline void Solve(int u, int fa)
    {
        tag[u] = 0;
        if(hs[u])
        {
            Solve(hs[u], u);
            tag[u] += tag[hs[u]] + si[hs[u]] - 1;
        }
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa || v == hs[u]) continue;
            Solve(v, u), tag[u] += tag[v] + si[v] - 1;
            for(register int j = 0; j <= mxdep[v]; j++) f[u][j + 1] += f[v][j];
        }
        f[u][0] -= tag[u];
        for(register vector<int> :: iterator it = vec[u].begin(); it != vec[u].end(); it++) ans[*it] += f[u][min(q[*it].k, mxdep[u])] + tag[u];
        return;
    }

    inline int Run()
    {
        n = Read32(), t = Read32();
        for(register int i = 1; i < n; i++)
        {
            int u = Read32(), v = Read32();
            Link(u, v), Link(v, u);
        }
        DFS1(1, 0), DFS2(1, 0);
        for(register int i = 1; i <= t; i++)
        {
            q[i].p = Read32(), q[i].k = Read32();
            ans[i] = 1LL * (si[q[i].p] - 1) * min(q[i].k, dep[q[i].p] - 1);
            vec[q[i].p].push_back(i);
        }
        Solve(1, 0);
        for(register int i = 1; i <= t; i++) Write64(ans[i]);
        return 0;
    }
}

int main() { return Program :: Run(); }
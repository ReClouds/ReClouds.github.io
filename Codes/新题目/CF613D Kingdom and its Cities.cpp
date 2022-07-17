#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>

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
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write32;

namespace Program
{
    const int MAXN = 100005;
    const int MAXLOG = 18;
    const int INF = 0x3F3F3F3F;

    int n, q, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], dfncnt, dfn[MAXN], g[MAXN][MAXLOG], dep[MAXN], len, seq[MAXN << 1], f[MAXN];
    bool t[MAXN], d[MAXN];
    vector<int> vec[MAXN];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }
    inline bool Compare(int u, int v) { return dfn[u] < dfn[v]; }

    inline int LCA(int u, int v)
    {
        if(dep[u] < dep[v]) swap(u, v);
        for(register int i = MAXLOG - 1; i >= 0; i--) if(dep[g[u][i]] >= dep[v]) u = g[u][i];
        if(u == v) return u;
        for(register int i = MAXLOG - 1; i >= 0; i--) if(g[u][i] != g[v][i]) u = g[u][i], v = g[v][i];
        return g[u][0];
    }

    inline void DFS(int u, int fa)
    {
        dfn[u] = ++dfncnt, g[u][0] = fa, dep[u] = dep[fa] + 1;
        for(register int i = 1; i < MAXLOG && g[u][i - 1]; i++) g[u][i] = g[g[u][i - 1]][i - 1];
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            DFS(v, u);
        }
        return;
    }

    inline void Solve(int u)
    {
        int c = 0;
        for(auto v : vec[u])
        {
            Solve(v);
            f[u] += f[v], c += d[v];
        }
        if(t[u]) f[u] += c, d[u] = true;
        else if(c > 1) ++f[u], d[u] = false;
        else d[u] = (c == 1);
        return;
    }

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i < n; i++)
        {
            int u = Read32(), v = Read32();
            Link(u, v), Link(v, u);
        }
        DFS(1, 0);
        q = Read32();
        while(q--)
        {
            int k = Read32(); len = 0;
            for(register int i = 1; i <= k; i++) seq[++len] = Read32(), t[seq[len]] = true;
            sort(seq + 1, seq + k + 1, Compare);
            for(register int i = 2; i <= k; i++) seq[++len] = LCA(seq[i - 1], seq[i]);
            sort(seq + 1, seq + len + 1, Compare), len = unique(seq + 1, seq + len + 1) - seq - 1;
            bool OK = true;
            for(register int i = 2; i <= len; i++)
            {
                int anc = LCA(seq[i - 1], seq[i]);
                if(t[seq[i]] && t[anc] && dep[seq[i]] - dep[anc] == 1) { OK = false; break; }
                vec[anc].push_back(seq[i]);
            }
            if(!OK) puts("-1"); else Solve(seq[1]), Write32(f[seq[1]]);
            for(register int i = 1; i <= len; i++) f[seq[i]] = 0, t[seq[i]] = d[seq[i]] = false, vec[seq[i]].clear();
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
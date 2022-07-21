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
    const int MAXM = 305;
    const int MAXLOG = 18;
    const int MOD = 1000000007;

    int n, q, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], dfncnt, dfn[MAXN], dep[MAXN], len, seq[MAXN], f[MAXN][MAXLOG], g[MAXN][MAXM], dfnrcnt, dfnr[MAXN], val[MAXN];
    bool vis[MAXN];
    vector<int> vec[MAXN];

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }
    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline int LCA(int u, int v)
    {
        if(dep[u] < dep[v]) swap(u, v);
        for(register int i = MAXLOG - 1; i >= 0; i--) if(dep[f[u][i]] >= dep[v]) u = f[u][i];
        if(u == v) return u;
        for(register int i = MAXLOG - 1; i >= 0; i--) if(f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
        return f[u][0];
    }

    inline void DFS(int u, int fa)
    {
        dfn[u] = ++dfncnt, dep[u] = dep[fa] + 1, f[u][0] = fa;
        for(register int i = 1; i < MAXLOG && f[u][i - 1]; i++) f[u][i] = f[f[u][i - 1]][i - 1];
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            DFS(v, u);
        }
        return;
    }

    inline void DFSr(int u, int fa)
    {
        dfnr[u] = ++dfnrcnt, val[u] = val[fa] + vis[u];
        for(auto v : vec[u]) if(v != fa) DFSr(v, u);
        return;
    }

    inline int Run()
    {
        n = Read32(), q = Read32();
        for(register int i = 1; i < n; i++)
        {
            int u = Read32(), v = Read32();
            Link(u, v), Link(v, u);
        }
        DFS(1, 0);
        while(q--)
        {
            int k = Read32() + 1, m = Read32(), r = Read32(); seq[len = 1] = r;
            for(register int i = 1; i < k; i++) seq[++len] = Read32(), vis[seq[len]] = true;
            sort(seq + 1, seq + k + 1, [&](int a, int b) -> bool { return dfn[a] < dfn[b]; } );
            for(register int i = 1; i < k; i++) seq[++len] = LCA(seq[i], seq[i + 1]);
            sort(seq + 1, seq + len + 1, [&](int a, int b) -> bool { return dfn[a] < dfn[b]; } ), len = unique(seq + 1, seq + len + 1) - seq - 1;
            for(register int i = 2; i <= len; i++)
            {
                int t = LCA(seq[i - 1], seq[i]);
                vec[t].push_back(seq[i]), vec[seq[i]].push_back(t);
            }
            dfnrcnt = 0, DFSr(r, 0), sort(seq + 1, seq + len + 1, [&](int a, int b) -> bool { return dfnr[a] < dfnr[b]; });
            for(register int i = 1; i <= len; i++) vec[seq[i]].clear();
            int tmp = 0;
            for(register int i = 1; i <= len; i++) if(vis[seq[i]]) seq[++tmp] = seq[i], val[seq[i]] -= vis[seq[i]], vis[seq[i]] = false;
            len = tmp, g[1][1] = 1;
            for(register int i = 2; i <= len; i++) for(register int j = 1; j <= min(i, m); j++)
            {
                if(j - val[seq[i]] > 0) g[i][j] = Get_MOD(g[i - 1][j - 1] + 1LL * (j - val[seq[i]]) * g[i - 1][j] % MOD);
                else g[i][j] = g[i - 1][j - 1];
            }
            int ans = 0;
            for(register int i = 1; i <= m; i++) ans = Get_MOD(ans + g[len][i]);
            Write32(ans);
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
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
    const int MAXM = 200005;
    const int MAXLOG = 21;

    int t, n, m, q, tot = 1, hd[MAXN], nxt[MAXM << 1], to[MAXM << 1], dfncnt, dfn[MAXN << 1], low[MAXN], top, stk[MAXN], cnt, dep[MAXN << 1], f[MAXN << 1][MAXLOG], val[MAXN << 1], seq[MAXN];
    vector<int> vec[MAXN << 1];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }
    inline bool Compare(int a, int b) { return dfn[a] < dfn[b]; }

    inline void Clear()
    {
        tot = 1, dfncnt = top = 0;
        for(register int i = 1; i <= n + cnt; i++)
        {
            if(i <= n) hd[i] = 0;
            dfn[i] = 0, vec[i].clear();
            for(register int j = 0; j < MAXLOG; j++) f[i][j] = 0;
        }
        return cnt = 0, void();
    }

    inline void Tarjan(int u)
    {
        dfn[u] = low[u] = ++dfncnt, stk[++top] = u;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(!dfn[v])
            {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if(dfn[u] == low[v])
                {
                    ++cnt;
                    int k = 0;
                    do
                    {
                        k = stk[top--];
                        vec[k].push_back(n + cnt);
                        vec[n + cnt].push_back(k);
                    }
                    while(k != v);
                    vec[u].push_back(n + cnt);
                    vec[n + cnt].push_back(u);
                }
            }
            else low[u] = min(low[u], dfn[v]);
        }
        return;
    }

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
        dfn[u] = ++dfncnt, dep[u] = dep[fa] + 1, f[u][0] = fa, val[u] = val[fa] + (u <= n);
        for(register int i = 1; i < MAXLOG; i++) f[u][i] = f[f[u][i - 1]][i - 1];
        for(auto v : vec[u]) if(v != fa) DFS(v, u);
        return;
    }

    inline int Run()
    {
        t = Read32();
        while(t--)
        {
            n = Read32(), m = Read32();
            for(register int i = 1; i <= m; i++)
            {
                int u = Read32(), v = Read32();
                Link(u, v), Link(v, u);
            }
            Tarjan(1);
            dfncnt = 0, memset(dfn, 0, sizeof dfn);
            DFS(1, 0);
            q = Read32();
            while(q--)
            {
                int si = Read32();
                for(register int i = 1; i <= si; i++) seq[i] = Read32();
                sort(seq + 1, seq + si + 1, Compare), seq[si + 1] = seq[1];
                int ans = 0;
                for(register int i = 1; i <= si; i++)
                {
                    int t = LCA(seq[i], seq[i + 1]);
                    ans += val[seq[i]] + val[seq[i + 1]] - val[t] * 2;
                }
                ans >>= 1, ans -= si, ans += (LCA(seq[1], seq[si]) <= n);
                Write32(ans);
            }
            Clear();
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
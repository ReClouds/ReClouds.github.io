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
    const int MAXN = 2005;
    const int MAXM = 100005;

    int n, m, tot = 1, hd[MAXN], nxt[MAXM << 1], to[MAXM << 1], dfncnt, dfn[MAXN], low[MAXN], cnt, in[MAXN], deg[MAXN], mx[MAXN], res, ans;
    bool f[MAXM];
    vector<int> vec[MAXN];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void Tarjan(int u, int fa)
    {
        dfn[u] = low[u] = ++dfncnt;
        for(register int i = hd[u]; i; i = nxt[i]) if(i != (fa ^ 1))
        {
            int v = to[i];
            if(!dfn[v])
            {
                Tarjan(v, i);
                low[u] = min(low[u], low[v]);
                if(dfn[u] < low[v]) f[i >> 1] = true;
            }
            else low[u] = min(low[u], dfn[v]);
        }
        return;

    }

    inline void DFS(int u, int fa)
    {
        in[u] = cnt;
        for(register int i = hd[u]; i; i = nxt[i]) if(!f[i >> 1])
        {
            int v = to[i];
            if(v == fa || in[v]) continue;
            DFS(v, u);
        }
        return;
    }

    inline void Solve(int u, int fa)
    {
        mx[u] = 1;
        if(deg[u] <= 1) ++ans;
        for(auto v : vec[u]) if(v != fa)
        {
            Solve(v, u);
            res = max(res, mx[u] + mx[v]);
            mx[u] = max(mx[u], mx[v] + 1);
        }
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32();
            Link(u, v), Link(v, u);
        }
        for(register int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i, 0);
        for(register int i = 1; i <= n; i++) if(!in[i]) ++cnt, DFS(i, 0);
        for(register int i = 2; i <= tot; i += 2)
        {
            int u = to[i], v = to[i ^ 1];
            if(in[u] != in[v]) vec[in[u]].push_back(in[v]), vec[in[v]].push_back(in[u]), ++deg[in[u]], ++deg[in[v]];
        }
        int c = 0;
        for(register int i = 1; i <= cnt; i++) if(!mx[i])
        {
            ++c, res = 0, Solve(i, 0);
            if(res > 2) ans += res - 2;
        }
        ans = n - ans + c - 1;
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
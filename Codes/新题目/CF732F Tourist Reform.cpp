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
    const int MAXN = 400005;

    int n, m, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], dfncnt, dfn[MAXN], low[MAXN], ed[MAXN][2], cnt, si[MAXN], in[MAXN], mx, pos;
    bool f[MAXN], vis[MAXN];
    vector<pair<int, int> > vec[MAXN];

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
        ++si[cnt], in[u] = cnt;
        for(register int i = hd[u]; i; i = nxt[i]) if(!f[i >> 1])
        {
            int v = to[i];
            if(v == fa) continue;
            if(!in[v])
            {
                DFS(v, u);
                if(!vis[i >> 1]) vis[i >> 1] = true, ed[i >> 1][0] = u, ed[i >> 1][1] = v;
            }
            else if(!vis[i >> 1]) vis[i >> 1] = true, ed[i >> 1][0] = u, ed[i >> 1][1] = v;
        }
        return;
    }

    inline void Solve(int u, int fa)
    {
        for(auto v : vec[u]) if(v.first != fa)
        {
            int i = v.second, a = to[i << 1], b = to[i << 1 | 1];
            if(in[a] == u) ed[i][0] = b, ed[i][1] = a;
            else ed[i][0] = a, ed[i][1] = b;
            Solve(v.first, u);
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
        Tarjan(1, 0);
        for(register int i = 1; i <= n; i++)
        {
            if(!in[i])
            {
                ++cnt, DFS(i, 0);
                if(si[cnt] > mx)
                {
                    mx = si[cnt];
                    pos = cnt;
                }
            }
        }
        for(register int i = 2; i <= tot; i += 2)
        {
            if(f[i >> 1])
            {
                vec[in[to[i | 1]]].push_back(make_pair(in[to[i]], i >> 1));
                vec[in[to[i]]].push_back(make_pair(in[to[i | 1]], i >> 1));
            }
        }
        Solve(pos, 0);
        Write32(mx);
        for(register int i = 1; i <= m; i++) Write32(ed[i][0], ' '), Write32(ed[i][1]);
        return 0;
    }
}

int main() { return Program :: Run(); }
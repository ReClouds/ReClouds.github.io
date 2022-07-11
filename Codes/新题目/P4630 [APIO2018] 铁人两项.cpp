#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>

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
    const int MAXN = 100005;
    const int MAXM = 200005;

    int n, cnt, m, tot = 1, hd[MAXN], nxt[MAXM << 1], to[MAXM << 1], dfncnt, dfn[MAXN], low[MAXN], top, stk[MAXN], si[MAXN << 1], incnt, in[MAXN << 1], sum[MAXN << 1];
    i64 ans;
    bool vis[MAXN << 1];
    vector<int> vec[MAXN << 1];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void Tarjan(int u)
    {
        dfn[u] = low[u] = ++dfncnt, stk[++top] = u, in[u] = incnt, ++sum[incnt];
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(!dfn[v])
            {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if(dfn[u] == low[v])
                {
                    ++cnt, in[n + cnt] = incnt;
                    int k = 0;
                    do
                    {
                        k = stk[top--];
                        vec[k].push_back(n + cnt), vec[n + cnt].push_back(k);
                    }
                    while(k != v);
                    vec[u].push_back(n + cnt), vec[n + cnt].push_back(u); 
                }
            }
            else low[u] = min(low[u], dfn[v]);
        }
        return;
    }

    inline void Solve(int u, int fa)
    {
        si[u] = (u <= n), vis[u] = true;
        for(auto v : vec[u]) if(v != fa)
        {
            Solve(v, u);
            si[u] += si[v];
        }
        if(u > n)
        {
            int cnt = (int)(vec[u].size());
            ans += 1LL * (sum[in[u]] - si[u]) * (1LL * si[u] * (cnt - 1) - (cnt - 1));
            for(auto v : vec[u]) if(v != fa) ans += 1LL * si[v] * (1LL * (sum[in[u]] - si[v]) * (cnt - 1) - (cnt - 1));
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
        for(register int i = 1; i <= n; i++) if(!dfn[i]) top = 0, ++incnt, Tarjan(i);
        for(register int i = 1; i <= n; i++) if(!vis[i]) Solve(i, 0);
        Write64(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

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
    const int MAXN = 10005;
    const int TIME = 36;
    const int INF = 0x3F3F3F3F;

    int n, k, col[MAXN], tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], mp[MAXN], f[MAXN][1 << 5], g[1 << 5], ans;

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void Map()
    {
        for(register int i = 1; i <= n; i++) mp[i] = rand() % k;
        return;
    }

    inline void Solve(int u, int fa)
    {
        f[u][1 << mp[col[u]]] = 1;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            Solve(v, u), memset(g, 0x3F, sizeof g);
            for(register int S = 1; S < (1 << k); S++)
                for(register int T = 1; T < (1 << k); T++)
                    g[S | T] = min(g[S | T], f[u][S] + f[v][T]);
            for(register int S = 1; S < (1 << k); S++) f[u][S] = min(f[u][S], g[S]);
        }
        return;
    }

    inline int Run()
    {
        srand((unsigned)(time(NULL)));
        n = Read32(), k = Read32();
        for(register int i = 1; i <= n; i++) col[i] = Read32();
        for(register int i = 1; i < n; i++)
        {
            int u = Read32(), v = Read32();
            Link(u, v), Link(v, u);
        }
        if(k <= 1) return Write32(k), 0;
        ans = INF;
        for(register int i = 1; i <= TIME; i++)
        {
            Map(), memset(f, 0x3F, sizeof f), Solve(1, 0);
            int res = INF;
            for(register int S = 1; S < (1 << k); S++) if(__builtin_popcount(S) == k)
                for(register int u = 1; u <= n; u++) res = min(res, f[u][S]);
            ans = min(ans, res);
        }
        if(ans != INF) Write32(ans); else puts("-1");
        return 0;
    }
}

int main() { return Program :: Run(); }
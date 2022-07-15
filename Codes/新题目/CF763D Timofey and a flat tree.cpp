#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<unordered_map>

using ui64 = unsigned long long;
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
    const int BASE = 13331;

    int n, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], si[MAXN], now, ans, pos;
    ui64 pw[MAXN], hs[MAXN];
    unordered_map<ui64, int> cnt;

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void Add(ui64 val)
    {
        if(!cnt.count(val)) cnt.insert(make_pair(val, 0));
        if(++cnt[val] == 1) ++now;
        return;
    }

    inline void Del(ui64 val)
    {
        if(--cnt[val] == 0) --now;
        return;
    }

    inline void DFS(int u, int fa)
    {
        si[u] = 1;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            DFS(v, u);
            hs[u] += hs[v] * pw[si[v]] * pw[si[v]];
            si[u] += si[v];
        }
        hs[u] += pw[si[u]] * pw[si[u]];
        return;
    }

    inline void Solve(int u, int fa)
    {
        if(now > ans) ans = now, pos = u;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            ui64 tmp = hs[v];
            Del(hs[u]); ui64 k1 = hs[u] - pw[n] * pw[n] - hs[v] * pw[si[v]] * pw[si[v]] + pw[n - si[v]] * pw[n - si[v]]; Add(k1);
            Del(hs[v]); ui64 k2 = hs[v] - pw[si[v]] * pw[si[v]] + k1 * pw[n - si[v]] * pw[n - si[v]] + pw[n] * pw[n]; Add(hs[v] = k2);
            Solve(v, u);
            Del(k1), Add(hs[u]);
            Del(k2), Add(hs[v] = tmp);
        }
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
        pw[0] = 1; for(register int i = 1; i <= n; i++) pw[i] = pw[i - 1] * BASE;
        DFS(1, 0);
        for(register int i = 1; i <= n; i++) Add(hs[i]);
        Solve(1, 0);
        return Write32(pos), 0;
    }
}

int main() { return Program :: Run(); }
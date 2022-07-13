#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<queue>

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
    inline i64 Read64() { int k; _Read(k); return k; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Read64;
using IO :: Write32;
using IO :: Write64;

namespace Program
{
    const int MAXN = 5005;
    const int MAXM = 200005;
    const int INF = 0x3F3F3F3F;

    int n, m, k, tot = 1, hd[MAXN], nxt[MAXM << 1], to[MAXM << 1], val[MAXM << 1], disst[MAXN], dised[MAXN];
    bool ban[MAXN], vis[MAXN], g[MAXN][MAXN];

    struct Node { int u; i64 d; Node(int _u = 0, i64 _d = 0) : u(_u), d(_d) {} bool operator < (const Node &t) const { return d > t.d; } };
    priority_queue<Node> pq;

    inline void Link(int u, int v, i64 w) { return ++tot, nxt[tot] = hd[u], to[tot] = v, val[tot] = w, hd[u] = tot, void(); }

    inline void Dijkstra()
    {
        memset(disst, 0x3F, sizeof disst), memset(vis, false, sizeof vis);
        while(!pq.empty()) pq.pop();
        pq.push(Node(1, 0)), disst[1] = 0;
        while(!pq.empty())
        {
            int u = pq.top().u; pq.pop(), vis[u] = true;
            for(register int i = hd[u]; i; i = nxt[i])
            {
                int v = to[i];
                if(ban[v] || vis[v]) continue;
                if(disst[u] + val[i] < disst[v])
                {
                    disst[v] = disst[u] + val[i];
                    pq.push(Node(v, disst[v]));
                }
            }
        }
        memset(dised, 0x3F, sizeof dised), memset(vis, false, sizeof vis);
        while(!pq.empty()) pq.pop();
        pq.push(Node(n, 0)), dised[n] = 0;
        while(!pq.empty())
        {
            int u = pq.top().u; pq.pop(), vis[u] = true;
            for(register int i = hd[u]; i; i = nxt[i])
            {
                int v = to[i];
                if(ban[v] || vis[v]) continue;
                if(dised[u] + val[i] < dised[v])
                {
                    dised[v] = dised[u] + val[i];
                    pq.push(Node(v, dised[v]));
                }
            }
        }
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), k = Read32();
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32(); i64 w = Read64();
            Link(u, v, w), Link(v, u, w), g[u][v] = g[v][u] = true;
        }
        for(register int i = 2; i < n; i++)
        {
            int t = 0;
            for(register int j = 1; j <= n; j++) if(i != j && g[i][j]) ++t;
            if(t < k) ban[i] = true;
        }
        Dijkstra();
        int mi = disst[n], cmi = INF;
        for(register int i = 2; i <= tot; i++) if(!ban[to[i ^ 1]] || !ban[to[i]])
        {
            int u = to[i ^ 1], v = to[i], w = disst[u] + val[i] + dised[v];
            if(w == mi) continue;
            cmi = min(cmi, w);
        }
        if(cmi == INF) puts("-1");
        else Write32(cmi);
        return 0;
    }
}

int main() { return Program :: Run(); }
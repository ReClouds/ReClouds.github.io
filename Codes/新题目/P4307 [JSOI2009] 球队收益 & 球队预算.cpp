#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<queue>

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
    const int MAXN = 50005;
    const int MAXM = 1000005;
    const int INF = 0x3F3F3F3F;

    int n, m, a[MAXN], b[MAXN], c[MAXN], d[MAXN], g[MAXN][2], r[MAXN], ans;

    namespace Network_Flow
    {
        int S, T, tot = 1, hd[MAXN], nw[MAXN], nxt[MAXM], to[MAXM], dep[MAXN], cap[MAXM], val[MAXM], dis[MAXN], mxf, mic;
        bool in[MAXN];

        inline void Link(int u, int v, int w, int c)
        {
            ++tot, nxt[tot] = hd[u], to[tot] = v, cap[tot] = w, val[tot] = c, hd[u] = tot;
            ++tot, nxt[tot] = hd[v], to[tot] = u, cap[tot] = 0, val[tot] = -c, hd[v] = tot;
            return;
        }

        inline void Init()
        {
            S = m + n + 1, T = m + n + 2;
            for(register int i = 1; i <= m; i++) Link(S, i, 1, 0), Link(i, g[i][0] + m, 1, 0), Link(i, g[i][1] + m, 1, 0);
            for(register int i = 1; i <= n; i++)
                for(register int j = 1; j <= r[i]; j++)
                    Link(i + m, T, 1, c[i] + d[i] + c[i] * a[i] * 2 - d[i] * b[i] * 2),  ++a[i], --b[i];
            return;
        }

        inline bool SPFA()
        {
            memset(dep, 0, sizeof dep), memset(dis, 0x3F, sizeof dis), memset(in, false, sizeof in);
            for(register int i = 1; i <= T; i++) nw[i] = hd[i];
            queue<int> q; q.push(S);
            dep[S] = 0, dis[S] = 0, in[S] = true;
            while(!q.empty())
            {
                int u = q.front(); q.pop(), in[u] = false;
                for(register int i = hd[u]; i; i = nxt[i]) if(cap[i])
                {
                    int v = to[i];
                    if(dis[u] + val[i] < dis[v])
                    {
                        dis[v] = dis[u] + val[i], dep[v] = dep[u] + 1;
                        if(!in[v]) q.push(v), in[v] = true;
                    }
                }
            }
            return (dis[T] != INF);
        }

        inline int DFS(int u, int rem)
        {
            if(u == T) return rem;
            int now = rem;
            for(register int &i = nw[u]; i; i = nxt[i]) if(cap[i])
            {
                int v = to[i];
                if(dep[u] + 1 != dep[v] || dis[u] + val[i] != dis[v]) continue;
                int k = DFS(v, min(rem, cap[i]));
                rem -= k, cap[i] -= k, cap[i ^ 1] += k;
                if(!k) dep[v] = 0;
                if(!rem) break;
            }
            return (now - rem);
        }

        inline void Dinic()
        {
            while(SPFA())
            {
                int k = DFS(S, INF);
                while(k) mxf += k, mic += k * dis[T], k = DFS(S, INF);
            }
            return;
        }
    }

    namespace nf = Network_Flow;

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32(), b[i] = Read32(), c[i] = Read32(), d[i] = Read32();
        for(register int i = 1; i <= m; i++)
        {
            g[i][0] = Read32(), g[i][1] = Read32();
            ++r[g[i][0]], ++b[g[i][0]], ++r[g[i][1]], ++b[g[i][1]];
        }
        for(register int i = 1; i <= n; i++) ans += c[i] * a[i] * a[i] + d[i] * b[i] * b[i];
        nf :: Init(), nf :: Dinic();
        Write32(ans + nf :: mic);
        return 0;
    }
}

int main() { return Program :: Run(); }
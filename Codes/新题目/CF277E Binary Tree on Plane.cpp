#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<cmath>
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
    const int MAXN = 1005;
    const int MAXM = 500005;
    const double INF = 0x3F3F3F3F;
    const double EPS = 1e-8;

    int n, xi[MAXN], yi[MAXN];
    char s[MAXN];

    inline double Dist(int a, int b) { return sqrt(pow(xi[a] - xi[b], 2) + pow(yi[a] - yi[b], 2)); }

    inline int Sign(double a)
    {
        if(a > EPS) return 1;
        if(fabs(a) <= EPS) return 0;
        return -1;
    }

    namespace Network_Flow
    {
        int S, T, tot = 1, hd[MAXN], nw[MAXN], nxt[MAXM], to[MAXM], cap[MAXM], dep[MAXN], maxflow;
        double mincost, val[MAXM], dis[MAXM];
        bool in[MAXN];

        inline void Link(int u, int v, int c, double w)
        {
            ++tot, nxt[tot] = hd[u], to[tot] = v, cap[tot] = c, val[tot] = w, hd[u] = tot;
            ++tot, nxt[tot] = hd[v], to[tot] = u, cap[tot] = 0, val[tot] = -w, hd[v] = tot;
            return;
        }

        inline bool SPFA()
        {
            for(register int i = 1; i <= T; i++) nw[i] = hd[i], dis[i] = INF;
            memset(dep, 0, sizeof dep), memset(in, false, sizeof in);
            dep[S] = 1, dis[S] = 0;
            queue<int> q; q.push(S), in[S] = true;
            while(!q.empty())
            {
                int u = q.front(); q.pop(), in[u] = false;
                for(register int i = hd[u]; i; i = nxt[i]) if(cap[i])
                {
                    int v = to[i];
                    if(Sign(dis[v] - (dis[u] + val[i])) > 0)
                    {
                        dep[v] = dep[u] + 1;
                        dis[v] = dis[u] + val[i];
                        if(!in[v]) q.push(v), in[v] = true;
                    }
                }
            }
            return dis[T] != INF;
        }

        inline int DFS(int u, int rem)
        {
            if(u == T || !rem) return rem;
            int st = rem;
            for(register int &i = nw[u]; i; i = nxt[i]) if(cap[i])
            {
                int v = to[i];
                if(dep[v] != dep[u] + 1 || fabs(dis[u] + val[i] - dis[v]) > EPS) continue;
                int k = DFS(v, min(rem, cap[i]));
                rem -= k, cap[i] -= k, cap[i ^ 1] += k;
                if(!rem) break;
            }
            if(st - rem == 0) dep[u] = 0;
            return st - rem;
        }

        inline void Dinic()
        {
            maxflow = mincost = 0;
            while(SPFA())
            {
                int k = DFS(S, INF);
                while(k) maxflow += k, mincost += dis[T] * k, k = DFS(S, INF);
            }
            return;
        }
    }

    namespace nf = Network_Flow;

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i <= n; i++) xi[i] = Read32(), yi[i] = Read32();
        nf :: S = (n << 1 | 1), nf :: T = nf :: S + 1;
        for(register int i = 1; i <= n; i++)
        {
            nf :: Link(nf :: S, i, 2, 0);
            nf :: Link(i + n, nf :: T, 1, 0);
        }
        for(register int i = 1; i <= n; i++) for(register int j = 1; j <= n; j++) if(i != j && yi[j] < yi[i]) nf :: Link(i, j + n, 1, Dist(i, j));
        nf :: Dinic();
        if(nf :: maxflow != n - 1) return puts("-1"), 0;
        return printf("%.15lf\n", nf :: mincost), 0;
    }
}

int main() { return Program :: Run(); }
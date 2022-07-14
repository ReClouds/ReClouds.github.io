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
    const int MAXN = 805;
    const i64 LIM = 0x3F3F3F3F;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;
    const i64 MAX = 0x7FFFFFFFFFFFFFFF;

    int n;
    i64 sum;

    namespace Network_Flow
    {
        int S, T, tot = 1, hd[MAXN], nxt[MAXN * MAXN], to[MAXN * MAXN], dep[MAXN], nw[MAXN];
        i64 cap[MAXN * MAXN], maxflow;
        queue<int> q;

        inline void Link(int u, int v, i64 c)
        {
            ++tot, nxt[tot] = hd[u], to[tot] = v, cap[tot] = c, hd[u] = tot;
            ++tot, nxt[tot] = hd[v], to[tot] = u, cap[tot] = 0, hd[v] = tot;
            return;
        }

        inline bool BFS()
        {
            for(register int i = 1; i <= T; i++) nw[i] = hd[i];
            memset(dep, 0, sizeof dep);
            while(!q.empty()) q.pop();
            q.push(S), dep[S] = 1;
            while(!q.empty())
            {
                int u = q.front(); q.pop();
                for(register int i = hd[u]; i; i = nxt[i]) if(cap[i])
                {
                    int v = to[i];
                    if(dep[v]) continue;
                    dep[v] = dep[u] + 1, q.push(v);
                }
            }
            return dep[T] != 0;
        }

        inline i64 DFS(int u, i64 rem)
        {
            if(u == T || !rem) return rem;
            i64 st = rem;
            for(register int &i = nw[u]; i; i = nxt[i]) if(cap[i])
            {
                int v = to[i];
                if(dep[u] + 1 != dep[v]) continue;
                i64 k = DFS(v, min(rem, cap[i]));
                rem -= k, cap[i] -= k, cap[i ^ 1] += k;
                if(!k) dep[v] = 0;
                if(!rem) break;
            }
            return st - rem;
        }

        inline i64 Dinic()
        {
            i64 k = 0; maxflow = 0;
            while(BFS())
            {
                k = DFS(S, MAX);
                while(k) maxflow += k, k = DFS(S, MAX);
            }
            return maxflow;
        }
    }

    namespace nf = Network_Flow;

    inline int Run()
    {
        n = Read32();
        nf :: S = (n << 1 | 1), nf :: T = nf :: S + 1;
        for(register int i = 1; i <= n; i++)
        {
            int t = Read32();
            for(register int j = 1; j <= t; j++)
            {
                int v = Read32();
                nf :: Link(i, v + n, INF);
            }
        }
        for(register int i = 1; i <= n; i++)
        {
            i64 val = Read64();
            sum += LIM - val, nf :: Link(nf :: S, i, LIM - val);
        }
        for(register int i = 1; i <= n; i++) nf :: Link(i + n, nf :: T, LIM);
        int ans = nf :: Dinic() - sum;
        Write32(min(0, ans));
        return 0;
    }
}

int main() { return Program :: Run(); }
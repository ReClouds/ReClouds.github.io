#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

#define i64 long long

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
    const int MAXN = 1005;
    const int MAXM = 50005;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, m, a[MAXN], pre[MAXN];

    namespace Network_Flow
    {
        int n, S, T, tot = 1, hd[MAXM], nw[MAXM], nxt[MAXM << 1], to[MAXM << 1], dep[MAXM];
        i64 cap[MAXM << 1], mxf;

        inline void Link(int u, int v, i64 w)
        {
            ++tot, nxt[tot] = hd[u], to[tot] = v, cap[tot] = w, hd[u] = tot;
            ++tot, nxt[tot] = hd[v], to[tot] = u, cap[tot] = 0, hd[v] = tot;
            return;
        }

        inline void Init()
        {
            S = m + 1, T = m + 2;
            for(register int i = 1; i <= m; i++)
            {
                int p = Read32();
                while(p--)
                {
                    int j = Read32();
                    if(pre[j] == 0) Link(S, i, a[j]);
                    else Link(pre[j], i, INF);
                    pre[j] = i;
                }
                int b = Read32();
                Link(i, T, b);
            }
            return;
        }

        inline bool BFS()
        {
            for(register int i = 1; i <= T; i++) nw[i] = hd[i];
            memset(dep, 0, sizeof dep), dep[S] = 1;
            queue<int> q; q.push(S);
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
            return dep[T];
        }

        inline i64 DFS(int u, i64 rem)
        {
            if(u == T) return rem;
            i64 now = rem;
            for(register int &i = nw[u]; i; i = nxt[i]) if(cap[i])
            {
                int v = to[i];
                if(dep[u] + 1 != dep[v]) continue;
                i64 k = DFS(v, min(rem, cap[i]));
                rem -= k, cap[i] -= k, cap[i ^ 1] += k;
                if(!k) dep[v] = 0;
                if(!rem) break;
            }
            return (now - rem);
        }

        inline void Dinic()
        {
            while(BFS())
            {
                i64 k = DFS(S, INF);
                while(k) mxf += k, k = DFS(S, INF);
            }
            return;
        }
    }

    namespace nf = Network_Flow;

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32();
        nf :: Init(), nf :: Dinic();
        Write64(nf :: mxf);
        return 0;
    }
}

int main() { return Program :: Run(); }
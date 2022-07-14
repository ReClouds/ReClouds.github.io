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
    const int MAXN = 505;
    const int MAXM = 500005;
    const int INF = 0x3F3F3F3F;

    int n, ct[26], cs[26], mp[26];
    char s[MAXN];

    namespace Network_Flow
    {
        int S, T, tot = 1, hd[MAXN], nw[MAXN], nxt[MAXM], to[MAXM], cap[MAXM], val[MAXM], dep[MAXN], dis[MAXN], maxflow, mincost;
        bool in[MAXN];

        inline void Link(int u, int v, int c, int w)
        {
            ++tot, nxt[tot] = hd[u], to[tot] = v, cap[tot] = c, val[tot] = w, hd[u] = tot;
            ++tot, nxt[tot] = hd[v], to[tot] = u, cap[tot] = 0, val[tot] = -w, hd[v] = tot;
            return;
        }

        inline bool SPFA()
        {
            for(register int i = 1; i <= T; i++) nw[i] = hd[i];
            memset(dep, 0, sizeof dep), memset(dis, 0x3F, sizeof dis), memset(in, false, sizeof in);
            dep[S] = 1, dis[S] = 0;
            queue<int> q; q.push(S), in[S] = true;
            while(!q.empty())
            {
                int u = q.front(); q.pop(), in[u] = false;
                for(register int i = hd[u]; i; i = nxt[i]) if(cap[i])
                {
                    int v = to[i];
                    if(dis[u] + val[i] < dis[v])
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
                if(dep[v] != dep[u] + 1 || dis[v] != dis[u] + val[i]) continue;
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
        scanf("%s", s + 1);
        n = Read32(), nf :: S = n + 26 + 1, nf :: T = n + 26 + 2;
        for(register int i = 1, len = strlen(s + 1); i <= len; i++) ++ct[(int)(s[i] - 'a')];
        for(register int i = 0; i < 26; i++) if(ct[i]) nf :: Link(n + i + 1, nf :: T, ct[i], 0), mp[i] = (nf :: tot ^ 1);
        for(register int i = 1; i <= n; i++)
        {
            scanf("%s", s + 1); int lim = Read32();
            for(register int j = 1, len = strlen(s + 1); j <= len; j++) ++cs[(int)(s[j] - 'a')];
            nf :: Link(nf :: S, i, lim, i);
            for(register int j = 0; j < 26; j++) if(cs[j]) nf :: Link(i, n + j + 1, cs[j], 0), cs[j] = 0;
        }
        nf :: Dinic();
        for(register int i = 0; i < 26; i++) if(ct[i] && nf :: cap[mp[i]]) return puts("-1"), 0;
        return Write32(nf :: mincost), 0;
    }
}

int main() { return Program :: Run(); }
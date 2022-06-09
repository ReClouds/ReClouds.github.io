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
    const int MAXN = 1005;
    const int MAXM = 5005;
    const int INF = 0x3F3F3F3F;

    int n, k, len, seq[MAXN], ran[MAXN][2], w[MAXN];

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
            S = len + 1, T = len + 2;
            Link(S, 1, INF, 0);
            for(register int i = 1; i < len; i++) Link(i, i + 1, k, 0);
            Link(len, T, k, 0);
            for(register int i = 1; i <= n; i++) Link(ran[i][0], ran[i][1], 1, -w[i]);
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

    inline void Discretization()
    {
        sort(seq + 1, seq + len + 1);
        len = unique(seq + 1, seq + len + 1) - seq - 1;
        for(register int i = 1; i <= n; i++) ran[i][0] = lower_bound(seq + 1, seq + len + 1, ran[i][0]) - seq, ran[i][1] = lower_bound(seq + 1, seq + len + 1, ran[i][1]) - seq;
        return;
    }

    inline int Run()
    {
        n = Read32(), k = Read32();
        for(register int i = 1; i <= n; i++) seq[++len] = ran[i][0] = Read32(), seq[++len] = ran[i][1] = Read32(), w[i] = ran[i][1] - ran[i][0];
        Discretization();
        nf :: Init(), nf :: Dinic();
        Write32(-nf :: mic);
        return 0;
    }
}

int main() { return Program :: Run(); }
/*

                                                                 /@@@O
                                                              =@@@@@@@@@
                                                           ]/@@@@@@@@@@@
                                             ]]]]]/@@@@@@@@@@@@@@@@@@@@@
                       @@@@@\]]]]]]]]@@@@@@@@@@OO/          /@@@@@@@@@@@@
                      =@@@@@@@@@@O/[[                    [ @@@O[     O@@@\
                      =@@@@@@@@@@@]                     /@@/            \@\
                      =@@@@@      O@@@@\]]           /@@@[               \@@\
                      @@@@@             /@@@@@\    /@@[                    O@O
                     =@@ =@                  [\@@@@@\]                       @@O
                     @@/ O@                   /@@   [O@@@@\]                  =@@
                    /@   =@@               /@@/            @@@@@OO [            @@]
                   /@@    @@             @@@                     \@@@@O]         \@@
                   @@     @@         =O@@/                             \@@@@O/O    @@@\
                  @@      =@       /@@/                                      \@@@@@@@@@@@@
                =/@@      =@     @@@/                                             \@@@@@@@
                =@@       =@@ O@@O                                                  =@@@@@
                @@         @@@@[
              =/@O       O@@@
              =@@     \@@@ \@
              @@    @@@/   =@\
            =@@/[]@@@[     =@@
           /@@@@@@          @@
         /@@@@@@@           @@
         @@@@@@@            =@
          \@@@@@@\          =@
             @@@@@@@\       =@@
               @@\[@@@       @@
                =@@  \@@\    @@
                 =@@/  [@@@  @@
                  =@@\    =@@@@O
                    \@@     =@@@]                                                    /@@@O
                     \@@     =@@@@\                                                @@@@@@@
                      =@@     @@ [@@@                                        ]]@@@@@@@@@@@
                        @@    =@     @@\                              ]]@@@@@/[ /O@@@@[
                         \@@  =@\      \@@\                   \]@@@@@@O[       O@@[
                          =@@ /@@         @@O          ]/@@@@@@/[           /@@/
                           \@@@@@@          O@@]/O@@@@@/[                ]O@@/
                           =@@@@@@@@\]]]]\@@@@@@@O                     O@@
                           =@@@@@@@@@@@@@/       O@@\                @@@
                           =@@@@@@@@@@@@]          [@@\           /@@O
                            @@@@@@@@@@@@@@@@@@@O\]    \@@@O  ]]/@@@[
                              [@@/             [O@@@@@@@@@@@@@@@@/
                                                       \@@@@@@@@
                                                          \@@@@
*/
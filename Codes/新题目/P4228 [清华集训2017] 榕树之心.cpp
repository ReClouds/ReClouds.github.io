#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>

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

    int w, t, n, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], dep[MAXN], si[MAXN], hs[MAXN], chs[MAXN], f[MAXN];
    bool ans[MAXN];

    inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

    inline void DFS(int u, int fa)
    {
        dep[u] = dep[fa] + 1, si[u] = 1, hs[u] = chs[u] = 0;
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            DFS(v, u);
            si[u] += si[v];
            if(si[v] > si[hs[u]])
            {
                chs[u] = hs[u];
                hs[u] = v;
            }
            else if(si[v] > si[chs[u]]) chs[u] = v;
        }
        if(hs[u])
        {
            if(si[hs[u]] - f[hs[u]] * 2 <= si[u] - 1 - si[hs[u]]) f[u] = ((si[u] - 1) >> 1);
            else f[u] = f[hs[u]] + si[u] - 1 - si[hs[u]];
        }
        else f[u] = 0;
        return;
    }

    inline int Compare(int u, int v) { return (si[u] > si[v] ? u : v); }

    inline void Solve(int u, int fa, int nw)
    {
        for(register int i = hd[u]; i; i = nxt[i])
        {
            int v = to[i];
            if(v == fa) continue;
            if(v == hs[u]) Solve(v, u, Compare(chs[u], nw));
            else Solve(v, u, Compare(hs[u], nw));
        }
        int v = Compare(hs[u], nw);
        if(si[v] - f[v] * 2 <= n - dep[u] - si[v])
        {
            int tf = ((n - dep[u]) >> 1);
            if(tf * 2 == n - dep[u]) ans[u] = true;
        }
        return;
    }

    inline int Run()
    {
        w = Read32(), t = Read32();
        while(t--)
        {
            n = Read32();
            tot = 1, memset(hd, 0, sizeof hd);
            for(register int i = 1; i < n; i++)
            {
                int u = Read32(), v = Read32();
                Link(u, v), Link(v, u);
            }
            memset(ans, false, sizeof ans);
            DFS(1, 0), Solve(1, 0, 0);
            if(w == 3) printf("%d", ans[1]);
            else for(register int i = 1; i <= n; i++) printf("%d", ans[i]);
            putchar('\n');
        }
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
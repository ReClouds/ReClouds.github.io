#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

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
    const int MAXN = 10005;
    const int MAXM = 6000005;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, a[MAXN], d[MAXN], s[MAXN];
    bool vis[2][MAXM];
    i64 f[2][MAXM];

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32();
        for(register int i = 1; i < n; i++) d[i] = a[i + 1] - a[i];
        sort(d + 1, d + n);
        for(register int i = 1; i < n; i++) s[i] = s[i - 1] + d[i];
        int u = 0, v = 1, mx = 0; f[u][0] = 0, vis[u][0] = true;
        for(register int i = 1; i < n; i++)
        {
            if(d[i] == 0) continue;
            memset(vis[v], false, sizeof vis[v]);
            int tmx = 0;
            for(register int j = 0; j <= mx; j++) if(vis[u][j])
            {
                if(j + s[i] < MAXM)
                {
                    tmx = max(tmx, j + s[i]);
                    i64 val = f[u][j] + s[i] * s[i];
                    if(!vis[v][j + s[i]] || val < f[v][j + s[i]]) f[v][j + s[i]] = val;
                    vis[v][j + s[i]] = true;
                }
                if(j + d[i] * i < MAXM)
                {
                    tmx = max(tmx, j + d[i] * i);
                    i64 val = f[u][j] + d[i] * j * 2 + d[i] * d[i] * i;
                    if(!vis[v][j + d[i] * i] || val < f[v][j + d[i] * i]) f[v][j + d[i] * i] = val;
                    vis[v][j + d[i] * i] = true;
                }
            }
            mx = tmx, swap(u, v);
        }
        i64 ans = INF;
        for(register int i = 0; i <= mx; i++) if(vis[u][i]) ans = min(ans, f[u][i] * n - 1LL * i * i);
        return Write64(ans), 0;
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
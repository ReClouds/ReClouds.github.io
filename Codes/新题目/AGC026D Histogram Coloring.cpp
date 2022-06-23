#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<vector>

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
    const int MAXN = 105;
    const int MOD = 1000000007;

    int n, rt, tot, h[MAXN], si[MAXN], f[MAXN << 1][2];

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }

    inline int Pow(int a, int b)
    {
        int res = 1;
        while(b)
        {
            if(b & 1) res = 1LL * res * a % MOD;
            a = 1LL * a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    inline void Solve(int &u, int l, int r, int lst)
    {
        u = ++tot, f[u][0] = f[u][1] = 1;
        int mi = 0x3F3F3F3F;
        for(register int i = l; i <= r; i++) mi = min(mi, h[i]);
        vector<int> pos;
        for(register int i = l; i <= r; i++) if(h[i] == mi) pos.push_back(i);
        int cnt = (int)(pos.size()), pre = l - 1;
        si[u] = cnt, pos.push_back(r + 1);
        for(auto it : pos)
        {
            if(pre + 1 <= it - 1)
            {
                int v = 0;
                Solve(v, pre + 1, it - 1, mi), si[u] += si[v];
                f[u][0] = 1LL * f[u][0] * Get_MOD(f[v][0] + f[v][1]) % MOD;
                f[u][1] = 1LL * f[u][1] * f[v][1] % MOD;
            }
            pre = it;
        }
        f[u][0] = Get_MOD(1LL * f[u][0] * Pow(2, cnt) % MOD + 1LL * Get_MOD(Pow(2, mi - lst) - 2 + MOD) * f[u][1] % MOD);
        f[u][1] = 1LL * f[u][1] * Pow(2, mi - lst) % MOD;
        return;
    }

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i <= n; i++) h[i] = Read32();
        return Solve(rt, 1, n, 0), Write32(f[rt][0]), 0;
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
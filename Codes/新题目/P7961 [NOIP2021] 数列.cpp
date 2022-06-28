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
    const int MOD = 998244353;
    const int MAXN = 35;
    const int MAXM = 105;

    int n, m, k, v[MAXM], fac[MAXN << 1], invf[MAXN << 1], f[MAXN][MAXN][MAXN], g[MAXN][MAXN][MAXN];

    inline int Get_MOD(int t) { return t - (t >= MOD) * MOD; }
    inline int Bit_Cnt(int t) { return __builtin_popcount(t); }

    inline int C(int n, int m)
    {
        if(n < m) return 0;
        return 1LL * fac[n] * invf[m] % MOD * invf[n - m] % MOD;
    }

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

    inline int Run()
    {
        n = Read32(), m = Read32(), k = Read32();
        for(register int i = 0; i <= m; i++) v[i] = Read32();
        fac[0] = 1; for(register int i = 1; i <= (n << 1); i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
        invf[n << 1] = Pow(fac[n << 1], MOD - 2); for(register int i = (n << 1) - 1; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
        f[0][0][0] = 1;
        for(register int nw = 0; nw <= m; nw++)
        {
            memset(g, 0, sizeof g);
            for(register int i = 0; i <= n; i++) for(register int j = 0; j <= k; j++) for(register int S = 0; S <= n; S++) if(j + (S & 1) <= k) g[i][j + (S & 1)][S >> 1] = Get_MOD(g[i][j + (S & 1)][S >> 1] + f[i][j][S]);
            swap(f, g), memset(g, 0, sizeof g);
            int pw = 1;
            for(register int c = 0; c <= n; c++)
            {
                for(register int i = 0; i <= n - c; i++) for(register int j = 0; j <= k; j++) for(register int S = 0; S <= n; S++) if(f[i][j][S]) g[i + c][j][S + c] = Get_MOD(g[i + c][j][S + c] + 1LL * f[i][j][S] * pw % MOD * C(c + i, i) % MOD);
                pw = 1LL * pw * v[nw] % MOD;
            }
            swap(f, g);
        }
        memset(g, 0, sizeof g);
        for(register int j = 0; j <= k; j++) for(register int S = 0; S <= n; S++) if(j + Bit_Cnt(S) <= k && f[n][j][S]) g[n][j + Bit_Cnt(S)][0] = Get_MOD(g[n][j + Bit_Cnt(S)][0] + f[n][j][S]);
        int ans = 0;
        for(register int i = 0; i <= k; i++) ans = Get_MOD(ans + g[n][i][0]);
        return Write32(ans), 0;
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
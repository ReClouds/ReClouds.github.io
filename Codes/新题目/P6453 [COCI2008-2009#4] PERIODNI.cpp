#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>

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
    const int MAXM = 1000005;
    const int MOD = 1000000007;

    int n, k, h[MAXN], fac[MAXM], invf[MAXM], top, stk[MAXN], ls[MAXN], rs[MAXN], si[MAXN], f[MAXN][MAXN];

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

    inline int C(int n, int m)
    { 
        if(n < m) return 0;
        return 1LL * fac[n] * invf[m] % MOD * invf[n - m] % MOD; 
    }

    inline int W(int n, int m, int k) { return 1LL * C(n, k) * C(m, k) % MOD * fac[k] % MOD; }

    inline void Solve(int u, int fa)
    {
        si[u] = f[u][0] = 1;
        if(ls[u])
        {
            if(u == 1) return;
            Solve(ls[u], u), si[u] += si[ls[u]];
            for(register int i = k; i >= 0; i--)
            {
                int val = 0;
                for(register int j = 0; j <= i; j++) val = Get_MOD(val + 1LL * f[u][j] * f[ls[u]][i - j] % MOD);
                f[u][i] = val;
            }
        }
        if(rs[u])
        {
            Solve(rs[u], u), si[u] += si[rs[u]];
            for(register int i = k; i >= 0; i--)
            {
                int val = 0;
                for(register int j = 0; j <= i; j++) val = Get_MOD(val + 1LL * f[u][j] * f[rs[u]][i - j] % MOD);
                f[u][i] = val;
            }
        }
        for(register int i = k; i >= 0; i--)
        {
            int val = 0;
            for(register int j = 0; j <= i; j++) val = Get_MOD(val + 1LL * f[u][j] * W(si[u] - j, h[u] - h[fa], i - j) % MOD);
            f[u][i] = val;
        }
        return;
    }

    inline int Run()
    {
        n = Read32(), k = Read32();
        for(register int i = 1; i <= n; i++) h[i] = Read32();
        fac[0] = 1; for(register int i = 1; i <= MAXM - 5; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
        invf[MAXM - 5] = Pow(fac[MAXM - 5], MOD - 2); for(register int i = MAXM - 6; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
        top = 0;
        for(register int i = 1; i <= n; i++)
        {
            int t = top;
            while(t && h[i] < h[stk[t]]) t--;
            if(t) rs[stk[t]] = i;
            if(t < top) ls[i] = stk[t + 1];
            stk[top = ++t] = i;
        }
        int rt = stk[1];
        return Solve(rt, 0), Write32(f[rt][k]), 0;
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
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
    const int MAXN = 500005;
    const int MOD = 998244353;
    const int G = 3;

    int n, p, q, fac[MAXN], invf[MAXN], r[MAXN], f[MAXN], g[MAXN], ans;

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

    inline void Init(int n)
    {
        p = 1, q = -1;
        while(p <= n) p <<= 1, ++q;
        for(register int i = 1; i < p; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << q);
        return;
    }

    inline void NTT(int *f, int n, bool inv = false)
    {
        if(inv) for(register int i  = 1; i < n; i++) if(i < n - i) swap(f[i], f[n - i]);
        for(register int i = 1; i < n; i++) if(i < r[i]) swap(f[i], f[r[i]]);
        for(register int len = 2; len <= n; len <<= 1)
        {
            int k = (len >> 1), _w = Pow(G, (MOD - 1) / len);
            for(register int i = 0; i < n; i += len)
            {
                int w = 1;
                for(register int j = 0; j < k; j++)
                {
                    int u = f[i + j], v = 1LL * w * f[i + j + k] % MOD;
                    f[i + j] = Get_MOD(u + v);
                    f[i + j + k] = Get_MOD(u - v + MOD);
                    w = 1LL * w * _w % MOD;
                }
            }
        }
        if(inv)
        {
            int invn = Pow(n, MOD - 2);
            for(register int i = 0; i < n; i++) f[i] = 1LL * f[i] * invn % MOD;
        }
        return;
    }

    inline int Run()
    {
        n = Read32() + 1;
        fac[0] = 1; for(register int i = 1; i < n; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
        invf[n - 1] = Pow(fac[n - 1], MOD - 2); for(register int i = n - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
        for(register int i = 0, w = 1; i < n; i++) f[i] = 1LL * w * invf[i] % MOD, w = 1LL * w * (MOD - 1) % MOD;
        for(register int i = 0; i < n; i++) g[i] = 1LL * Get_MOD(Pow(i, n) - 1 + MOD) * invf[i] % MOD * Pow(Get_MOD(i - 1 + MOD), MOD - 2) % MOD;
        g[1] = n;
        Init((n - 1) << 1);
        NTT(f, p), NTT(g, p);
        for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * g[i] % MOD;
        NTT(f, p, true);
        for(register int i = 0; i < n; i++) ans = Get_MOD(ans + 1LL * Pow(2, i) * fac[i] % MOD * f[i] % MOD);
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

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
    const int MAXN = 1000005;
    const int MOD = 1000000007;

    int n, m, a, b, fac[MAXN], invf[MAXN], ans;

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
        if(n < 0 || m < 0 || n < m) return 0;
        return 1LL * fac[n] * invf[m] % MOD * invf[n - m] % MOD;
    }

    inline int Count(int t)
    {
        if(t == 1) return 1;
        if(t == 2) return n - 1;
        return 1LL * (n - t + 1) * Pow(n, t - 2) % MOD;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), a = Read32(), b = Read32();
        fac[0] = 1; for(register int i = 1; i < MAXN; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
        invf[MAXN - 1] = Pow(fac[MAXN - 1], MOD - 2); for(register int i = MAXN - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
        for(register int i = 1; i <= n - 1; i++)
        {
            int coef = 1LL * C(m - 1, i - 1) * C(n - 2, i - 1) % MOD * fac[i - 1] % MOD;
            ans = Get_MOD(ans + 1LL * coef * Count(n - i) % MOD * Pow(m, n - i - 1) % MOD);
        }
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
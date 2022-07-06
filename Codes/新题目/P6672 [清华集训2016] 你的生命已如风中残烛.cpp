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
    const int MAXN = 45;
    const int MOD = 998244353;

    int n, m, w[MAXN], fac, ans;

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
        n = Read32();
        for(register int i = 1; i <= n; i++) w[i] = Read32(), m += w[i];
        fac = 1;
        for(register int i = 2; i <= m; i++) fac = 1LL * fac * i % MOD;
        ans = 1LL * fac * Pow(m - n + 1, MOD - 2) % MOD;
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
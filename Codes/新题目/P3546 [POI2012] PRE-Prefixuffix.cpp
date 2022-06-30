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
    const int MAXN = 1000005;
    const int BASE = 131;
    const int MOD = 998244353;

    int n, f[MAXN], ans, pw[MAXN], hs[MAXN];
    char s[MAXN];

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }
    inline int Hash(int l, int r) { return Get_MOD(hs[r] - 1LL * hs[l - 1] * pw[r - l + 1] % MOD + MOD); }
    inline bool Equal(int l1, int r1, int l2, int r2) { return Hash(l1, r1) == Hash(l2, r2); }

    inline int Run()
    {
        n = Read32(), scanf("%s", s + 1);
        pw[0] = 1;
        for(register int i = 1; i <= n; i++)
        {
            pw[i] = 1LL * pw[i - 1] * BASE % MOD;
            hs[i] = Get_MOD(1LL * hs[i - 1] * BASE % MOD + s[i]);
        }
        for(register int i = (n >> 1); i >= 1; i--)
        {
            int k = min(f[i + 1] + 2, (n >> 1) - i + 1);
            while(!Equal(i, i + k - 1, n - i - k + 2, n - i + 1)) --k;
            f[i] = k;
        }
        for(register int i = 1; i <= (n >> 1); i++)
        {
            if(!Equal(1, i, n - i + 1, n)) continue;
            ans = max(ans, i + f[i + 1]);
        }
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
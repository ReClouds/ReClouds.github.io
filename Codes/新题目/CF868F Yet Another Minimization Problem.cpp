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
    const int MAXN = 100005;
    const int MAXM = 25;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, k, u, v, a[MAXN], l, r, cnt[MAXN];
    i64 val, f[MAXM][MAXN];

    inline void Count(int ql, int qr)
    {
        while(r < qr) val += (cnt[a[++r]]++);
        while(l > ql) val += (cnt[a[--l]]++);
        while(r > qr) val -= (--cnt[a[r--]]);
        while(l < ql) val -= (--cnt[a[l++]]);
        return;
    }

    inline void Solve(int L, int R, int ll, int lr)
    {
        if(L > R || ll > lr) return;
        int mid = (L + R) >> 1, lmid = -1;
        for(register int i = ll; i <= min(mid - 1, lr); i++) if(f[u][i] != INF)
        {
            Count(i + 1, mid);
            if(f[u][i] + val < f[v][mid]) f[v][mid] = f[u][i] + val, lmid = i;
        }
        if(L == R) return;
        int tl = lmid + 1, tr = mid;
        Solve(L, mid - 1, ll, lmid), Count(tl, tr);
        Solve(mid + 1, R, lmid, lr), Count(tl, tr);
        return;
    }

    inline int Run()
    {
        n = Read32(), k = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32();
        u = 0, v = 1;
        memset(f, 0x3F, sizeof f), f[u][0] = 0;
        for(register int i = 1; i <= k; i++)
        {
            memset(cnt, 0, sizeof cnt), memset(f[v], 0x3F, sizeof f[v]);
            l = 1, r = 0, val = 0;
            Solve(i, n, 0, n - 1), swap(u, v);
        }
        Write64(f[u][n]);
        return 0;
    }
}

int main() { return Program :: Run(); }
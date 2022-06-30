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
    const int MAXN = 1005;

    int t, n, m;
    i64 w[MAXN][MAXN], f[MAXN][MAXN];

    inline int Run()
    {
        t = Read32();
        while(t--)
        {
            n = Read32(), m = Read32();
            for(register int i = 1; i <= n; i++) for(register int j = 1; j <= m; j++) w[i][j] = Read32();
            memset(f, 0, sizeof f);
            for(register int i = n; i >= 1; i--)
                for(register int j = 1; j <= m; j++)
                    f[i][j] = max(max(f[i + 1][j], f[i][j - 1]), f[i + 1][j - 1] + w[i][j]);
            Write64(f[1][m]);
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
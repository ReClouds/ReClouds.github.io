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
    const int MAXN = 105;
    const int MAXM = 1005;
    const int MOD = 1000000007;

    int n, l, a[MAXN], f[2][MAXN][3][MAXM];

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }

    inline int Run()
    {
        n = Read32(), l = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32();
        if(n == 1) return puts("1"), 0;
        sort(a + 1, a + n + 1);
        int u = 0, v = 1;
        f[u][1][2][0] = 1, f[u][1][1][0] = 2;
        for(register int i = 2; i <= n; i++)
        {
            memset(f[v], 0, sizeof f[v]);
            for(register int j = 1; j <= i; j++)
            {
                for(register int k = 0; k <= 2; k++)
                {
                    for(register int t = 0; t <= l; t++) if(f[u][j][k][t] && t + (a[i] - a[i - 1]) * ((j - 1) * 2 + k) <= l)
                    {
                        int w = t + (a[i] - a[i - 1]) * ((j - 1) * 2 + k);
                        f[v][j + 1][k][w] = Get_MOD(f[v][j + 1][k][w] + 1LL * f[u][j][k][t] * (j - 1 + k) % MOD);
                        if(k) f[v][j + 1][k - 1][w] = Get_MOD(f[v][j + 1][k - 1][w] + 1LL * f[u][j][k][t] * k % MOD);
                        f[v][j][k][w] = Get_MOD(f[v][j][k][w] + 1LL * f[u][j][k][t] * ((j - 1) * 2 + k) % MOD);
                        if(k) f[v][j][k - 1][w] = Get_MOD(f[v][j][k - 1][w] + 1LL * f[u][j][k][t] * k % MOD);
                        f[v][j - 1][k][w] = Get_MOD(f[v][j - 1][k][w] + 1LL * f[u][j][k][t] * (j - 1) % MOD);
                    }
                }
            }
            swap(u, v);
        }
        int ans = 0;
        for(register int i = 0; i <= l; i++) ans = Get_MOD(ans + f[u][1][0][i]);
        return Write32(ans), 0;
    }
}

int main() { return Program :: Run(); }
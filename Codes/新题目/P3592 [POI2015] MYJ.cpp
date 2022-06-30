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
    const int MAXN = 55;
    const int MAXM = 4005;

    int n, m, ai[MAXM], bi[MAXM], ci[MAXM], len, seq[MAXM], g[MAXN][MAXN][MAXM], f[MAXN][MAXN][MAXM], mx[MAXN][MAXN][MAXM][2], tr[MAXN][MAXN][MAXM][3];

    inline void Discretization()
    {
        sort(seq + 1, seq + len + 1), len = unique(seq + 1, seq + len + 1) - seq - 1;
        for(register int i = 1; i <= m; i++) ci[i] = lower_bound(seq + 1, seq + len + 1, ci[i]) - seq;
        return;
    }

    inline int W(int l, int r, int i, int k) { return g[l][r][k] - g[l][i - 1][k] - g[i + 1][r][k]; }

    inline void DFS(int l, int r, int k)
    {
        if(l > r) return;
        int i = tr[l][r][k][0], a = tr[l][r][k][1], b = tr[l][r][k][2];
        return DFS(l, i - 1, a), Write32(seq[k], " \n"[i == n]), DFS(i + 1, r, b);
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= m; i++) ai[i] = Read32(), bi[i] = Read32(), seq[++len] = ci[i] = Read32();
        Discretization();
        for(register int i = 1; i <= m; i++) for(register int j = 1; j <= ci[i]; j++) ++g[ai[i]][bi[i]][j];
        for(register int l = n - 1; l >= 1; l--) for(register int r = l + 1; r <= n; r++) for(register int k = 1; k <= len; k++) g[l][r][k] += g[l + 1][r][k] + g[l][r - 1][k] - g[l + 1][r - 1][k];
        memset(f, -1, sizeof f);
        for(register int i = 1; i <= n; i++) for(register int l = 1, r = i; r <= n; ++l, ++r)
        {
            mx[l][r][len + 1][0] = -1;
            for(register int k = len; k >= 1; k--)
            {
                for(register int t = l; t <= r; t++) if(mx[l][t - 1][k][0] + mx[t + 1][r][k][0] + seq[k] * W(l, r, t, k) > f[l][r][k])
                {
                    f[l][r][k] = mx[l][t - 1][k][0] + mx[t + 1][r][k][0] + seq[k] * W(l, r, t, k);
                    tr[l][r][k][0] = t, tr[l][r][k][1] = mx[l][t - 1][k][1], tr[l][r][k][2] = mx[t + 1][r][k][1];
                }
                mx[l][r][k][0] = mx[l][r][k + 1][0], mx[l][r][k][1] = mx[l][r][k + 1][1];
                if(f[l][r][k] > mx[l][r][k][0])
                {
                    mx[l][r][k][0] = f[l][r][k];
                    mx[l][r][k][1] = k;
                }
            }
        }
        int ans = 0, k = 0;
        for(register int i = 1; i <= len; i++) if(f[1][n][i] > ans) ans = f[1][n][i], k = i;
        return Write32(ans), DFS(1, n, k), 0;
    }
}

int main() { return Program :: Run(); }
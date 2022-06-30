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
    const int MAXN = 15;
    const int MAXM = 1005;
    const int MOD = 1000000007;
    const char DNA[4] = {'A', 'G', 'C', 'T'};

    int t, n, m, f[2][1 << MAXN], g[MAXM], h[MAXM], tr[1 << MAXN][4], ans[MAXM];
    char s[MAXM];

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }

    inline int Run()
    {
        t = Read32();
        while(t--)
        {
            scanf("%s%d", s + 1, &m), n = strlen(s + 1);
            for(register int S = 0; S < (1 << n); S++)
            {
                g[0] = 0; for(register int i = 1; i <= n; i++) g[i] = g[i - 1] + (S >> (i - 1) & 1);
                for(register int c = 0; c < 4; c++)
                {
                    for(register int i = 0; i <= n; i++) h[i] = 0;
                    for(register int i = 1; i <= n; i++) h[i] = max(max(g[i], h[i - 1]), g[i - 1] + (s[i] == DNA[c]));
                    tr[S][c] = 0;
                    for(register int i = 0; i < n; i++) tr[S][c] |= ((h[i + 1] - h[i]) << i);
                }
            }
            int u = 0, v = 1;
            memset(f[u], 0, sizeof f[u]), f[u][0] = 1;
            for(register int i = 1; i <= m; i++)
            {
                memset(f[v], 0, sizeof f[v]);
                for(register int S = 0; S < (1 << n); S++) 
                {
                    if(!f[u][S]) continue;
                    for(register int c = 0; c < 4; c++) f[v][tr[S][c]] = Get_MOD(f[v][tr[S][c]] + f[u][S]);
                }
                swap(u, v);
            }
            for(register int i = 0; i <= n; i++) ans[i] = 0;
            for(register int S = 0; S < (1 << n); S++)
            {
                int k = __builtin_popcount(S);
                ans[k] = Get_MOD(ans[k] + f[u][S]);
            }
            for(register int i = 0; i <= n; i++) Write32(ans[i]);
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
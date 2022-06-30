#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
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
    const int MAXN = 21;

    int n, m, t, v[MAXN], w[MAXN], s[2][MAXN], si[2][1 << MAXN], sum[2][1 << MAXN], len[2], seq[2][1 << MAXN];
    bool g[MAXN][MAXN], h[2][1 << MAXN], f[2][1 << MAXN];

    inline int Lowbit(int k) { return k & (-k); }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) for(register int j = 1; j <= m; j++) scanf("%1d", &g[i][j]);
        for(register int i = 1; i <= n; i++) v[i] = Read32();
        for(register int i = 1; i <= m; i++) w[i] = Read32();
        for(register int i = 1; i <= n; i++) for(register int j = 1; j <= m; j++) s[0][i] |= g[i][j] << (j - 1);
        for(register int i = 1; i <= m; i++) for(register int j = 1; j <= n; j++) s[1][i] |= g[j][i] << (j - 1);
        for(register int i = 1; i < (1 << n); i++)
        {
            for(register int j = 1; j <= n; j++) if(i >> (j - 1) & 1) si[0][i] |= s[0][j];
            for(register int j = 1; j <= n; j++) if(i >> (j - 1) & 1) sum[0][i] += v[j];
            if(__builtin_popcount(si[0][i]) >= __builtin_popcount(i)) h[0][i] = true;
        }
        for(register int i = 1; i < (1 << m); i++)
        {
            for(register int j = 1; j <= m; j++) if(i >> (j - 1) & 1) si[1][i] |= s[1][j];
            for(register int j = 1; j <= m; j++) if(i >> (j - 1) & 1) sum[1][i] += w[j];
            if(__builtin_popcount(si[1][i]) >= __builtin_popcount(i)) h[1][i] = true;
        }
        f[0][0] = true;
        for(register int i = 1; i < (1 << n); i++)
        {
            f[0][i] = h[0][i];
            for(register int j = i; j; j -= Lowbit(j)) f[0][i] &= f[0][i ^ Lowbit(j)];
            if(f[0][i]) seq[0][++len[0]] = sum[0][i];
        }
        f[1][0] = true;
        for(register int i = 1; i < (1 << m); i++)
        {
            f[1][i] = h[1][i];
            for(register int j = i; j; j -= Lowbit(j)) f[1][i] &= f[1][i ^ Lowbit(j)];
            if(f[1][i]) seq[1][++len[1]] = sum[1][i];
        }
        t = Read32();
        sort(seq[0] + 1, seq[0] + len[0] + 1), sort(seq[1] + 1, seq[1] + len[1] + 1);
        long long ans = 0;
        for(register int i = 1; i <= len[0]; i++) ans += (seq[0][i] >= t);
        for(register int i = 1; i <= len[1]; i++) ans += (seq[1][i] >= t);
        int j = len[1];
        for(register int i = 1; i <= len[0]; i++)
        {
            while(j && seq[0][i] + seq[1][j] >= t) j--;
            ans += len[1] - j;
        }
        printf("%lld\n", ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
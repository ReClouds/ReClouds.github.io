#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>

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
    const int MAXM = 405;

    int n, m, s, cnt, tot, a[MAXN], b[MAXN], pos[MAXN];
    i64 ans;

    namespace Fenwick_Tree
    {
        #define Lowbit(k) (k & (-k))

        int sum[MAXN];

        inline void Modify(int pos, int k)
        {
            while(pos <= n)
            {
                sum[pos] += k;
                pos += Lowbit(pos);
            }
            return;
        }

        inline int Get(int pos)
        {
            int res = 0;
            while(pos)
            {
                res += sum[pos];
                pos -= Lowbit(pos);
            }
            return res;
        }

        #undef Lowbit
    }

    using namespace Fenwick_Tree;

    const int BIT = 8;
    const int BASE = 256;

    int seq[BASE][MAXN], lens[BASE];

    inline void Radix_Sort(vector<int> &a)
    {
        for(register int t = 0; t < 3; t++)
        {
            for(auto it : a)
            {
                int d = ((it >> (BIT * t)) & (BASE - 1));
                seq[d][++lens[d]] = it;
            }
            a.clear();
            for(register int i = 0; i < BASE; i++)
            {
                for(register int j = 1; j <= lens[i]; j++) a.push_back(seq[i][j]);
                lens[i] = 0;
            }
        }
        return;
    }

    namespace Block
    {
        int in[MAXN], len[MAXM], bl[MAXM], br[MAXM], ta[MAXM], pre[MAXN], suf[MAXN];
        i64 f[MAXM][MAXN], g[MAXM][MAXM];
        vector<int> bk[MAXM];

        inline void Build()
        {
            cnt = (n - 1) / s + 1;
            for(register int i = 1; i <= n; i++)
            {
                in[i] = (i - 1) / s + 1;
                ++len[in[i]];
                bk[in[i]].push_back(a[i]);
            }
            for(register int i = 1; i <= cnt; i++)
            {
                bl[i] = s * (i - 1) + 1, br[i] = min(n, s * i);
                Radix_Sort(bk[i]);
                tot = 0;
                for(register int j = 1; j <= n; j++) if(in[pos[j]] != i) b[++tot] = j;
                int p = 1, q = 1; 
                auto it = bk[i].begin();
                while(p <= tot)
                {
                    while(q <= len[i] && b[p] > *it) ++q, ++it;
                    if(pos[b[p]] < bl[i]) f[i][pos[b[p]]] += q - 1;
                    else f[i][pos[b[p]]] += len[i] - q + 1;
                    ++p;
                }
                for(register int j = 1; j <= n; j++) f[i][j] += f[i][j - 1];
                pre[bl[i]] = 0, Modify(a[bl[i]], 1);
                for(register int j = bl[i] + 1; j <= br[i]; j++)
                {
                    pre[j] = pre[j - 1] + (Get(n) - Get(a[j]));
                    Modify(a[j], 1);
                }
                for(register int j = bl[i]; j <= br[i]; j++) Modify(a[j], -1);
                suf[br[i]] = 0, Modify(a[br[i]], 1);
                for(register int j = br[i] - 1; j >= bl[i]; j--)
                {
                    suf[j] = suf[j + 1] + Get(a[j] - 1);
                    Modify(a[j], 1);
                }
                for(register int j = bl[i]; j <= br[i]; j++) Modify(a[j], -1);
            }
            for(register int i = cnt; i >= 1; i--)
            {
                g[i][i] = pre[br[i]];
                for(register int j = i + 1; j <= cnt; j++) g[i][j] = g[i][j - 1] + g[i + 1][j] - g[i + 1][j - 1] + (f[j][br[i]] - f[j][bl[i] - 1]);
            }
            for(register int i = 1; i <= cnt; i++) for(register int j = 1; j <= n; j++) f[i][j] += f[i - 1][j];
            return;
        }

        inline i64 Weight(int a, int b, int c, int d) { return f[b][d] - f[a - 1][d] - f[b][c - 1] + f[a - 1][c - 1]; }

        inline i64 Query(int l, int r)
        {
            int t = in[l], s = in[r];
            i64 res = 0;
            if(t == s)
            {
                if(l == bl[t]) return pre[r];
                if(r == br[s]) return suf[l];
                res = suf[l] - suf[r + 1];
                ta[0] = 0;
                auto it = bk[t].begin();
                for(register int i = 1; i <= len[t]; ++i, ++it) if(l <= pos[*it] && pos[*it] <= r) ta[++ta[0]] = *it;
                int p = 1;
                it = bk[t].begin();
                for(register int i = 1; i <= len[t]; ++i, ++it) if(pos[*it] > r)
                {
                    while(p <= ta[0] && ta[p] < *it) ++p;
                    res -= ta[0] - p + 1;
                }
                return res;
            }
            res = suf[l] + pre[r] + g[t + 1][s - 1] + Weight(t + 1, s - 1, l, br[t]) + Weight(t + 1, s - 1, bl[s], r);
            ta[0] = 0;
            auto it = bk[t].begin();
            for(register int i = 1; i <= len[t]; ++i, ++it) if(pos[*it] >= l) ta[++ta[0]] = *it;
            int p = 1;
            it = bk[s].begin();
            for(register int i = 1; i <= len[s]; ++i, ++it) if(pos[*it] <= r)
            {
                while(p <= ta[0] && ta[p] < *it) ++p;
                res += ta[0] - p + 1;
            }
            return res;
        }
    }

    using namespace Block;

    inline int Run()
    {
        n = Read32(), m = Read32(), s = MAXM - 5;
        for(register int i = 1; i <= n; i++) a[i] = Read32(), pos[a[i]] = i;
        Build();
        while(m--)
        {
            i64 l = Read64() ^ ans, r = Read64() ^ ans;
            Write64(ans = Query(l, r));
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
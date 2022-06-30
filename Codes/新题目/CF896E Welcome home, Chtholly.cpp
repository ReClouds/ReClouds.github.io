#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>

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
    const int MAXN = 100005;
    const int MAXM = 405;

    int n, m, a[MAXN];

    namespace Block
    {
        #define BL(i) (s * (i - 1) + 1)
        #define BR(i) (min(n, s * i))

        int s, in[MAXN], cnt[MAXM][MAXN], mx[MAXM], tag[MAXM], hd[MAXM][MAXN], fa[MAXN], val[MAXN];

        inline int Find(int u, int k)
        {
            while(u != fa[u]) u = fa[u] = fa[fa[u]];
            return u;
        }

        inline int Get(int pos) { return val[Find(pos, in[pos])] - tag[in[pos]]; }

        inline void Build(int k)
        {
            mx[k] = tag[k] = 0;
            for(register int i = BL(k); i <= BR(k); i++) hd[k][a[i]] = cnt[k][a[i]] = fa[i] = 0;
            for(register int i = BL(k); i <= BR(k); i++)
            {
                ++cnt[k][a[i]], mx[k] = max(mx[k], a[i]);
                if(!hd[k][a[i]]) hd[k][a[i]] = i, val[i] = a[i];
                fa[i] = hd[k][a[i]];
            }
            return;
        }

        inline void Merge(int u, int v, int k)
        {
            int &fu = hd[k][u], &fv = hd[k][v];
            if(!fu)
            {
                cnt[k][u] = cnt[k][v], cnt[k][v] = 0;
                fu = fv, fv = 0;
                val[fu] = u;
            }
            else
            {
                cnt[k][u] = cnt[k][u] + cnt[k][v], cnt[k][v] = 0;
                fa[fv] = fu, fv = 0;
            }
            return;
        }

        inline void Modify(int l, int r, int x)
        {
            if(in[l] == in[r])
            {
                for(register int i = BL(in[l]); i <= BR(in[l]); i++) a[i] = Get(i), cnt[in[l]][a[i] + tag[in[l]]] = hd[in[l]][a[i] + tag[in[l]]] = 0;
                for(register int i = l; i <= r; i++) if(a[i] > x) a[i] -= x;
                Build(in[l]);
                return;
            }
            for(register int i = BL(in[l]); i <= BR(in[l]); i++) a[i] = Get(i), cnt[in[l]][a[i] + tag[in[l]]] = hd[in[l]][a[i] + tag[in[l]]] = 0;
            for(register int i = l; i <= BR(in[l]); i++) if(a[i] > x) a[i] -= x;
            Build(in[l]);
            for(register int i = BL(in[r]); i <= BR(in[r]); i++) a[i] = Get(i), cnt[in[r]][a[i] + tag[in[r]]] = hd[in[r]][a[i] + tag[in[r]]] = 0;
            for(register int i = BL(in[r]); i <= r; i++) if(a[i] > x) a[i] -= x;
            Build(in[r]);
            for(register int i = in[l] + 1; i <= in[r] - 1; i++)
            {
                if(mx[i] - tag[i] <= x * 2)
                {
                    for(register int j = x + 1 + tag[i]; j <= mx[i]; j++) Merge(j - x, j, i);
                    mx[i] = min(mx[i], x + tag[i]);
                }
                else
                {
                    for(register int j = 1 + tag[i]; j <= x + tag[i]; j++) Merge(j + x, j, i);
                    tag[i] += x;
                }
            }
            return;
        }

        inline int Query(int l, int r, int x)
        {
            int res = 0;
            if(in[l] == in[r])
            {
                for(register int i = l; i <= r; i++) if(Get(i) == x) ++res;
                return res;
            }
            for(register int i = l; i <= BR(in[l]); i++) if(Get(i) == x) ++res;
            for(register int i = BL(in[r]); i <= r; i++) if(Get(i) == x) ++res;
            for(register int i = in[l] + 1; i <= in[r] - 1; i++) if(x + tag[i] < MAXN) res += cnt[i][x + tag[i]];
            return res;
        }

        #undef BL
        #undef BR
    }

    using namespace Block;

    inline int Run()
    {
        n = Read32(), s = (int)sqrt(n), m = Read32();
        for(register int i = 1; i <= n; i++) a[i] = Read32(), in[i] = (i - 1) / s + 1;
        for(register int i = 1; i <= in[n]; i++) Build(i);
        while(m--)
        {
            int op = Read32(), l = Read32(), r = Read32(), x = Read32();
            if(op & 1)
            {
                Modify(l, r, x);
                continue;
            }
            else
            {
                Write32(Query(l, r, x));
                continue;
            }
        }
        return 0;
    }
}

int main() { return Program :: Run(); }

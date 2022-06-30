#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
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
    const int MAXN = 50005;
    const int MAXM = 305;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, m, s;
    i64 a[MAXN];

    namespace Block
    {
        #define BL(i) (s * (i - 1) + 1)
        #define BR(i) (min(n, s * i))
        #define LEN(i) (BR(i) - BL(i) + 1)

        int top, in[MAXN], len[MAXM];
        i64 tag[MAXM], sum[MAXM], val[MAXM][2];
        double sp[MAXM][MAXM];

        struct Line { i64 k, b; } stk[MAXM], li[MAXM][MAXM];

        inline double Intersection(Line a, Line b) { return (double)(b.b - a.b) / (a.k - b.k); }

        inline void Build(int k)
        {
            sum[k] = 0;
            for(register int i = BL(k); i <= BR(k); i++) a[i] += tag[k], sum[k] += a[i];
            tag[k] = 0;
            i64 now = 0;
            top = 0;
            for(register int i = BL(k); i <= BR(k); i++)
            {
                now += a[i];
                Line t = (Line){(i - BL(k) + 1), now};
                while(top > 1)
                {
                    double x = Intersection(stk[top - 1], stk[top]);
                    if(t.k * x + t.b >= stk[top].k * x + stk[top].b) --top;
                    else break;
                }
                stk[++top] = t;
            }
            len[k] = top - 1;
            for(register int i = 1; i <= top; i++)
            {
                li[k][i - 1] = stk[i];
                sp[k][i] = Intersection(stk[i], stk[i + 1]);                
            }
            return;
        }

        inline void Construct()
        {
            for(register int i = 1; i <= n; i++) in[i] = (i - 1) / s + 1;
            for(register int i = 1; i <= in[n]; i++) Build(i);
            return;
        }

        inline void Modify(int l, int r, i64 k)
        {
            if(in[l] == in[r])
            {
                for(register int i = l; i <= r; i++) a[i] += k;
                return Build(in[l]);
            }
            for(register int i = l; i <= BR(in[l]); i++) a[i] += k;
            Build(in[l]);
            for(register int i = BL(in[r]); i <= r; i++) a[i] += k;
            Build(in[r]);
            for(register int i = in[l] + 1; i <= in[r] - 1; i++) sum[i] += k * LEN(i), tag[i] += k;
            return;
        }

        inline int Find(int k)
        {
            if(tag[k] < sp[k][1]) return li[k][0].k * tag[k] + li[k][0].b;
            int l = 1, r = len[k], ans = 0;
            while(l <= r)
            {
                int mid = (l + r) >> 1;
                if(tag[k] >= sp[k][mid]) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            return li[k][ans].k * tag[k] + li[k][ans].b;
        }

        inline i64 Query(int l, int r)
        {
            i64 now = 0, res = -INF, pre = 0;
            for(register int i = 1; i < in[l]; i++) pre += sum[i];
            for(register int i = BL(in[l]); i < l; i++) pre += a[i] + tag[in[l]];
            if(in[l] == in[r])
            {
                now = 0, res = -INF;
                for(register int i = l; i <= r; i++) now += a[i] + tag[in[l]], res = max(res, now);
                return pre + res;
            }
            now = 0, val[in[l]][0] = -INF;
            for(register int i = l; i <= BR(in[l]); i++) now += a[i] + tag[in[l]], val[in[l]][0] = max(val[in[l]][0], now);
            val[in[l]][1] = now;
            now = 0, val[in[r]][0] = -INF;
            for(register int i = BL(in[r]); i <= r; i++) now += a[i] + tag[in[r]], val[in[r]][0] = max(val[in[r]][0], now);
            val[in[r]][1] = now;
            for(register int i = in[l] + 1; i <= in[r] - 1; i++)
            {
                val[i][0] = Find(i);
                val[i][1] = sum[i];
            }
            now = 0, res = -INF;
            for(register int i = in[l]; i <= in[r]; i++)
            {
                res = max(res, now + val[i][0]);
                now += val[i][1];
            }
            return pre + res;
        }

        #undef BL
        #undef BR
    }

    using namespace Block;

    inline int Run()
    {
        n = Read32(), s = (int)sqrt(n);
        for(register int i = 1; i <= n; i++) a[i] = Read64();
        Construct();
        m = Read32();
        while(m--)
        {
            int opt = Read32();
            if(opt)
            {
                int l = Read32(), r = Read32();
                Write64(Query(l, r));
                continue;
            }
            else
            {
                int l = Read32(), r = Read32(); i64 k = Read64();
                Modify(l, r, k);
                continue;
            }
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
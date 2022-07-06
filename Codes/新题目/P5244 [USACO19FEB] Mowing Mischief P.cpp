#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
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
    const int MAXN = 200005;
    const int MAXM = 1000005;
    const i64 INF = 0x3F3F3F3F3F3F3F3F;

    int n, t, mxlen;
    i64 f[MAXN], ans;
    vector<int> vec[MAXN];

    struct Point { int xi, yi, len; Point(int _xi = 0, int _yi = 0) : xi(_xi), yi(_yi) {} bool operator < (const Point &t) const { return xi == t.xi ? yi < t.yi : xi < t.xi; } } p[MAXN];

    namespace Fenwick_Tree
    {
        #define Lowbit(k) (k & (-k))

        int mx[MAXM];

        inline void Modify(int pos, int val)
        {
            while(pos <= t)
            {
                mx[pos] = max(mx[pos], val);
                pos += Lowbit(pos);
            }
            return;
        }

        inline int Query(int pos)
        {
            int res = 0;
            while(pos)
            {
                res = max(res, mx[pos]);
                pos -= Lowbit(pos);
            }
            return res;
        }

        #undef Lowbit
    }

    using namespace Fenwick_Tree;

    namespace Segment_Tree
    {
        #define ls (now << 1)
        #define rs (now << 1 | 1)
        #define mid ((l + r) >> 1)

        

        #undef ls
        #undef rs
        #undef mid
    }

    using namespace Segment_Tree;

    inline int Run()
    {
        n = Read32(), t = Read32();
        for(register int i = 1; i <= n; i++) p[i] = Point(Read32(), Read32());
        p[++n] = Point(), p[++n] = Point(t, t), sort(p + 1, p + n + 1);
        for(register int i = 1; i <= n; i++) p[i].len = Query(p[i].yi) + 1, Modify(p[i].xi, p[i].len), vec[p[i].len].push_back(i);
        for(register int i = 1; i <= n; i++) mxlen = max(mxlen, p[i].len), f[i] = (p[i].len == 1 ? 0 : INF);
        for(register int i = 2; i <= mxlen; i++)
        {
            for(auto j : vec[i]) Insert(1, 0, (int)(vec[i - 1].size() - 1));
        }
        ans = INF;
        for(register int i = 1; i <= n; i++) if(p[i].len == mxlen) ans = min(ans, f[i]);
        Write64(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
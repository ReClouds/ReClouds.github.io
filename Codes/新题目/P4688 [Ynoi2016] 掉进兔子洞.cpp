#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<bitset>

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
    const int MAXM = 40005;

    int n, m, s, tot, a[MAXN], b[MAXN], in[MAXN], cnt[MAXN], ans[MAXN];
    bool vis[MAXN];
    bitset<MAXN> nw, bt[MAXM];

    struct Query { int l, r, len, bel; bool operator < (const Query &t) const { return in[l] == in[t.l] ? r < t.r : in[l] < in[t.l]; } } q[MAXM * 3];

    inline void Discretization()
    {
        sort(b + 1, b + n + 1);
        for(register int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
        return;
    }

    inline void Modify(int val, bool k)
    {
        if(k) return nw.set(val + (++cnt[val]) - 1, k), void();
        return nw.set(val + (cnt[val]--) - 1, k), void();
    }

    inline void Solve(int len)
    {
        tot = 0;
        for(register int i = 1; i <= len; i++)
        {
            ans[i] = 0, vis[i] = false;
            q[++tot].l = Read32(), q[tot].r = Read32(), q[tot].len = q[tot].r - q[tot].l + 1, q[tot].bel = i, ans[i] += q[tot].len;
            q[++tot].l = Read32(), q[tot].r = Read32(), q[tot].len = q[tot].r - q[tot].l + 1, q[tot].bel = i, ans[i] += q[tot].len;
            q[++tot].l = Read32(), q[tot].r = Read32(), q[tot].len = q[tot].r - q[tot].l + 1, q[tot].bel = i, ans[i] += q[tot].len;
            bt[i].reset();
        }
        sort(q + 1, q + tot + 1), nw.reset();
        memset(cnt, 0, sizeof cnt);
        int l = 1, r = 0;
        for(register int i = 1; i <= tot; i++)
        {
            while(r < q[i].r) Modify(a[++r], true);
            while(l > q[i].l) Modify(a[--l], true);
            while(r > q[i].r) Modify(a[r--], false);
            while(l < q[i].l) Modify(a[l++], false);
            if(!vis[q[i].bel]) bt[q[i].bel] = nw, vis[q[i].bel] = true;
            else bt[q[i].bel] &= nw;
        }
        for(register int i = 1; i <= len; i++) Write32(ans[i] - (int)(bt[i].count()) * 3);
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), s = (int)(sqrt(m));
        for(register int i = 1; i <= n; i++) b[i] = a[i] = Read32(), in[i] = (i - 1) / s + 1;
        Discretization();
        int k = MAXM - 5;
        for(register int i = 1; i <= m; i += k) Solve(min(m, i + k - 1) - i + 1); 
        return 0;
    }
}

int main() { return Program :: Run(); }
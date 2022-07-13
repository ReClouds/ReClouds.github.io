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
    const int MAXN = 1005;
    const int INF = 0x3F3F3F3F;

    int n, m, w[MAXN][MAXN], disst[MAXN], dised[MAXN], fast[MAXN], faed[MAXN], len, seq[MAXN], val[MAXN];
    bool vis[MAXN], in[MAXN][MAXN];

    inline int Findst(int u)
    {
        while(u != fast[u]) u = fast[u] = fast[fast[u]];
        return val[u];
    }

    inline int Finded(int u)
    {
        while(u != faed[u]) u = faed[u] = faed[faed[u]];
        return val[u];
    }

    inline void Dijkstra()
    {
        memset(disst, 0x3F, sizeof disst), memset(vis, false, sizeof vis);
        disst[1] = 0;
        for(register int i = 1; i <= n; i++)
        {
            int k = 0;
            for(register int j = 1; j <= n; j++) if(!vis[j] && (!k || disst[j] < disst[k])) k = j;
            if(!k) break;
            vis[k] = true;
            for(register int j = 1; j <= n; j++) if(disst[k] + w[k][j] < disst[j]) disst[j] = disst[k] + w[k][j], fast[j] = k;
        }
        int u = n;
        while(u) seq[++len] = u, u = fast[u];
        reverse(seq + 1, seq + len + 1);
        for(register int i = 2; i <= len; i++) in[fast[seq[i]]][seq[i]] = in[seq[i]][fast[seq[i]]] = true;
        memset(val, -1, sizeof val);
        for(register int i = 1; i <= len; i++) val[seq[i]] = i;
        memset(dised, 0x3F, sizeof dised), memset(vis, false, sizeof vis);
        dised[n] = 0;
        for(register int i = 1; i <= n; i++)
        {
            int k = 0;
            for(register int j = 1; j <= n; j++) if(!vis[j] && (!k || dised[j] < dised[k])) k = j;
            if(!k) break;
            vis[k] = true;
            for(register int j = 1; j <= n; j++) if(dised[k] + w[k][j] < dised[j]) dised[j] = dised[k] + w[k][j], faed[j] = k;
        }
        for(register int i = 1; i <= len; i++) fast[seq[i]] = faed[seq[i]] = seq[i];
        return;
    }

    namespace Segment_Tree
    {
        #define ls (now << 1)
        #define rs (now << 1 | 1)
        #define mid ((l + r) >> 1)

        int mi[MAXN << 2], tag[MAXN << 2];

        inline void Pushup(int now) { return mi[now] = min(mi[ls], mi[rs]), void(); }
        inline void Pushtag(int now, int val) { return mi[now] = min(mi[now], val), tag[now] = min(tag[now], val), void(); }
        inline void Pushdown(int now) { return Pushtag(ls, tag[now]), Pushtag(rs, tag[now]); }

        inline void Modify(int now, int l, int r, int L, int R, int val)
        {
            if(L <= l && r <= R) return Pushtag(now, val);
            Pushdown(now);
            if(L <= mid) Modify(ls, l, mid, L, R, val);
            if(R > mid) Modify(rs, mid + 1, r, L, R, val);
            return;
        }

        inline int Query(int now, int l, int r, int pos)
        {
            if(l == r) return mi[now];
            Pushdown(now);
            if(pos <= mid) return Query(ls, l, mid, pos);
            return Query(rs, mid + 1, r, pos);
        }

        #undef ls
        #undef rs
        #undef mid
    }

    using namespace Segment_Tree;

    inline int Run()
    {
        n = Read32(), m = Read32();
        memset(w, 0x3F, sizeof w);
        for(register int i = 1; i <= n; i++) w[i][i] = 0;
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32();
            w[u][v] = w[v][u] = Read32();
        }
        Dijkstra();
        memset(mi, 0x3F, sizeof mi), memset(tag, 0x3F, sizeof tag);
        for(register int i = 1; i <= n; i++) for(register int j = 1; j <= n; j++) if(i != j && !in[i][j] && w[i][j] != INF)
        {
            int a = Findst(i), b = Finded(j) - 1;
            if(a > b) continue;
            Modify(1, 1, len - 1, a, b, disst[i] + w[i][j] + dised[j]);
        }
        int ans = 0;
        for(register int i = 1; i < len; i++) ans = max(ans, Query(1, 1, len - 1, i));
        Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
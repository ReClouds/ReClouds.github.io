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
    const int MAXN = 10005;
    const int MAXM = 100;

    int n, m, s;
    bool ans[MAXN];

    struct Edge { int u, v; } ed[MAXN];

    namespace Disjoint_Set
    {
        int fa[MAXN << 1], si[MAXN << 1], top, stk[MAXN << 1];

        inline int Find(int u) { return u == fa[u] ? u : Find(fa[u]); }

        inline void Merge(int u, int v)
        {
            u = Find(u), v = Find(v);
            if(u == v) return;
            if(si[u] < si[v]) swap(u, v);
            fa[v] = u, si[u] += si[v];
            stk[++top] = v;
            return;
        }

        inline void Undo()
        {
            si[fa[stk[top]]] -= si[stk[top]], fa[stk[top]] = stk[top];
            return --top, void();
        }
    };

    using namespace Disjoint_Set;

    inline void Solve(int l, int r)
    {
        top = 0;
        for(register int i = 1; i <= (n << 1); i++) fa[i] = i, si[i] = 1;
        for(register int i = 1; i <= m; i++)
        {
            if(l <= i && i <= r) continue;
            Merge(ed[i].u, ed[i].v + n), Merge(ed[i].u + n, ed[i].v);
            if(Find(ed[i].u) == Find(ed[i].v)) return;
        }
        top = 0;
        for(register int i = l; i <= r; i++)
        {
            int nw = top;
            bool f = true;
            for(register int j = l; j <= r; j++) if(i != j)
            {
                Merge(ed[j].u, ed[j].v + n), Merge(ed[j].u + n, ed[j].v);
                if(Find(ed[j].u) == Find(ed[j].v))
                {
                    f = false;
                    break;
                }
            }
            ans[i] = f;
            while(top > nw) Undo();
        }
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), s = (int)sqrt(m);
        for(register int i = 1; i <= m; i++) ed[i].u = Read32(), ed[i].v = Read32();
        int pre = 0;
        for(register int i = 1; i <= m; i++)
        {
            if(i % s == 0 || i == m)
            {
                Solve(pre + 1, i);
                pre = i;
                continue;
            }
        }
        int cnt = 0;
        for(register int i = 1; i <= m; i++) cnt += ans[i];
        Write32(cnt);
        for(register int i = 1; i <= m; i++) if(ans[i]) Write32(i, ' ');
        return 0;
    }
}

int main() { return Program :: Run(); }
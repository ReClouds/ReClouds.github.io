#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
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
    const int MAXLOG = 18;

    int n, q, tot = 1, ndtrt, rt, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], fa[MAXN], mp[MAXN], tr[MAXN], top, stk[MAXN], si[MAXN], mx[MAXN], len, seq[MAXN << 1], pos[MAXN], lg2[MAXN << 1], mi[MAXLOG][MAXN << 1], nd[MAXLOG][MAXN << 1];
    i64 sum, val[MAXN << 1], dep[MAXN], f[MAXN], g[MAXN], h[MAXN];
    bool vis[MAXN];
    vector<int> vec[MAXN], dis[MAXN];

    namespace Tree
    {
        inline void Link(int u, int v, i64 w) { return ++tot, nxt[tot] = hd[u], to[tot] = v, val[tot] = w, hd[u] = tot, void(); }

        inline void DFS(int u, int fa)
        {
            seq[pos[u] = ++len] = u;
            for(register int i = hd[u]; i; i = nxt[i])
            {
                int v = to[i];
                if(v == fa) continue;
                dep[v] = dep[u] + val[i];
                DFS(v, u);
                seq[++len] = u;
            }
            return;
        }

        inline void Init()
        {
            lg2[1] = 0; for(register int i = 2; i <= len; i++) lg2[i] = lg2[i >> 1] + 1;
            for(register int i = 1; i <= len; i++) mi[0][i] = dep[seq[i]], nd[0][i] = seq[i];
            for(register int j = 1; j < MAXLOG; j++)
            {
                for(register int i = 1; i <= len - (1 << j) + 1; i++)
                {
                    if(mi[j - 1][i] < mi[j - 1][i + (1 << (j - 1))]) mi[j][i] = mi[j - 1][i], nd[j][i] = nd[j - 1][i];
                    else mi[j][i] = mi[j - 1][i + (1 << (j - 1))], nd[j][i] = nd[j - 1][i + (1 << (j - 1))];
                }
            }
            return;
        }

        inline int LCA(int u, int v)
        {
            int l = pos[u], r = pos[v];
            if(l > r) swap(l, r);
            int k = lg2[r - l + 1];
            if(mi[k][l] < mi[k][r - (1 << k) + 1]) return nd[k][l];
            return nd[k][r - (1 << k) + 1];
        }

        inline int Dist(int u, int v) { return dep[u] + dep[v] - dep[LCA(u, v)] * 2; }

        inline void Get_Root(int u, int fa, int sum)
        {
            si[u] = 1, mx[u] = 0;
            for(register int i = hd[u]; i; i = nxt[i])
            {
                int v = to[i];
                if(v == fa || vis[v]) continue;
                Get_Root(v, u, sum);
                si[u] += si[v], mx[u] = max(mx[u], si[v]);
            }
            mx[u] = max(mx[u], sum - si[u]);
            if(!rt || mx[u] < mx[rt]) rt = u;
            return;
        }

        inline void Build(int now, int u, int up)
        {
            vis[u] = true, mp[u] = now;
            for(register int i = hd[u]; i; i = nxt[i])
            {
                int v = to[i];
                if(v == up || vis[v]) continue;
                rt = 0, Get_Root(v, u, si[v]), vec[u].push_back(rt), fa[rt] = u, Build(v, rt, u);
            }
            return;
        }
    }

    namespace Node_Division_Tree
    {
        inline void Init(int u)
        {
            int t = u;
            while(t) dis[u].push_back(Tree :: Dist(u, t)), t = fa[t];
            for(auto v : vec[u]) Init(v);
            return;
        }

        inline void Modify(int u, i64 k)
        {
            sum += k;
            int now = u;
            while(now) h[now] += k, now = fa[now];
            int a = fa[u], b = u, cnt = 0;
            while(a)
            {
                ++cnt, f[a] += k * dis[u][cnt], g[b] += k * dis[u][cnt];
                a = fa[a], b = fa[b];
            }
            return;
        }

        inline void Temporary_Modify(int u, i64 k) { while(u) h[u] += k, u = fa[u]; return; }

        inline int Find_Root()
        {
            int now = ndtrt;
            while(true)
            {
                int k = 0;
                for(auto v : vec[now]) if(h[v] > (sum >> 1)) { k = v; break; }
                if(!k) break;
                Temporary_Modify(mp[stk[++top] = k], h[now] - h[k]), now = k;
            }
            while(top) Temporary_Modify(mp[stk[top]], h[stk[top]] - h[fa[stk[top]]]), --top;
            return now;
        }

        inline i64 Query(int u)
        {
            int a = fa[u], b = u, cnt = 0;
            i64 res = f[b];
            while(a)
            {
                res += f[a] - g[b] + (h[a] - h[b]) * dis[u][++cnt];
                a = fa[a], b = fa[b];
            }
            return res;
        }
    }

    inline int Run()
    {
        n = Read32(), q = Read32();
        for(register int i = 1; i < n; i++)
        {
            int u = Read32(), v = Read32(); i64 w = Read64();
            Tree :: Link(u, v, w), Tree :: Link(v, u, w);
        }
        Tree :: DFS(1, 0), Tree :: Init(), rt = 0, Tree :: Get_Root(1, 0, n), ndtrt = rt, Tree :: Build(ndtrt, ndtrt, 0), Node_Division_Tree :: Init(ndtrt);
        while(q--)
        {
            int u = Read32(); i64 k = Read32();
            Node_Division_Tree :: Modify(u, k);
            int t = Node_Division_Tree :: Find_Root();
            Write64(Node_Division_Tree :: Query(t));
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
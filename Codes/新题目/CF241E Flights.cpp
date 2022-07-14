#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>

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
    const int MAXM = 5005;
    const int INF = 0x3F3F3F3F;

    int n, m, tot, dis[MAXN], id[MAXN][MAXN], ans[MAXM];
    bool tag[MAXN];
    vector<int> vec[MAXN];

    struct Edge { int u, v, w; Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {} } ed[MAXM << 2];

    inline void Link(int u, int v, int w) { return ed[++tot] = Edge(u, v, w), void(); }

    inline bool DFS(int u)
    {
        if(tag[u]) return tag[u];
        for(auto v : vec[u]) tag[u] |= DFS(v);
        return tag[u];
    }

    inline bool Bellman_Ford()
    {
        memset(dis, 0x3F, sizeof dis), dis[0] = 0;
        for(register int i = 1; i <= n; i++)
        {
            for(register int j = 1; j <= tot; j++)
            {
                if(dis[ed[j].u] == INF) continue;
                dis[ed[j].v] = min(dis[ed[j].v], dis[ed[j].u] + ed[j].w);
            }
        }
        for(register int j = 1; j <= tot; j++) if(dis[ed[j].u] + ed[j].w < dis[ed[j].v]) return false;
        return true;
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32();
            id[u][v] = i, vec[u].push_back(v);
        }
        tag[n] = true, DFS(1);
        for(register int u = 1; u <= n; u++) for(register int v = 1; v <= n; v++) if(id[u][v])
        {
            if(!tag[u] || !tag[v]) { ans[id[u][v]] = 1; continue; }
            Link(u, v, 2), Link(v, u, -1);
        }
        for(register int i = 1; i <= n; i++) if(tag[i]) Link(0, i, 0);
        if(!Bellman_Ford()) return puts("No"), 0;
        puts("Yes");
        for(register int i = 1; i <= tot; i++) if(ed[i].u && ed[i].v) ans[id[ed[i].u][ed[i].v]] = dis[ed[i].v] - dis[ed[i].u];
        for(register int i = 1; i <= m; i++) Write32(ans[i]);
        return 0;
    }
}

int main() { return Program :: Run(); }
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>

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
	const int MAXN = 2005;

    int n, tot = 1, hd[MAXN], nxt[MAXN << 1], to[MAXN << 1], col[MAXN], f[MAXN], si[MAXN], dis[MAXN], ans = 0x3F3F3F3F;
	char s[MAXN];

	inline void Link(int u, int v) { return ++tot, nxt[tot] = hd[u], to[tot] = v, hd[u] = tot, void(); }

	inline void Clear() { return memset(f, 0, sizeof f), memset(si, 0, sizeof si), memset(dis, 0, sizeof dis), void(); }

	inline void Solve(int u, int fa)
	{
		si[u] = col[u], dis[u] = 0;
		int mx = 0;
		for(register int i = hd[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(v == fa) continue;
			Solve(v, u);
			si[u] += si[v];
			dis[u] += (dis[v] += si[v]);
			if(dis[v] > dis[mx]) mx = v;
		}
		if(dis[u] >= dis[mx] * 2) f[u] = (dis[u] >> 1);
		else f[u] = (dis[u] - dis[mx]) + (mx ? (min(f[mx] << 1, dis[mx] * 2 - dis[u]) >> 1) : 0);
		return;
	}

    inline int Run()
    {
        n = Read32(), scanf("%s", s + 1);
		for(register int i = 1; i <= n; i++) col[i] = (int)(s[i] - '0');
		for(register int i = 1; i < n; i++)
		{
			int u = Read32(), v = Read32();
			Link(u, v), Link(v, u);
		}
		for(register int i = 1; i <= n; i++)
		{
			Clear(), Solve(i, 0);
			if(dis[i] == f[i] * 2) ans = min(ans, f[i]);
		}
		if(ans == 0x3F3F3F3F) puts("-1"); else Write32(ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
/*

                                                                 /@@@O
                                                              =@@@@@@@@@
                                                           ]/@@@@@@@@@@@
                                             ]]]]]/@@@@@@@@@@@@@@@@@@@@@
                       @@@@@\]]]]]]]]@@@@@@@@@@OO/          /@@@@@@@@@@@@
                      =@@@@@@@@@@O/[[                    [ @@@O[     O@@@\
                      =@@@@@@@@@@@]                     /@@/            \@\
                      =@@@@@      O@@@@\]]           /@@@[               \@@\
                      @@@@@             /@@@@@\    /@@[                    O@O
                     =@@ =@                  [\@@@@@\]                       @@O
                     @@/ O@                   /@@   [O@@@@\]                  =@@
                    /@   =@@               /@@/            @@@@@OO [            @@]
                   /@@    @@             @@@                     \@@@@O]         \@@
                   @@     @@         =O@@/                             \@@@@O/O    @@@\
                  @@      =@       /@@/                                      \@@@@@@@@@@@@
                =/@@      =@     @@@/                                             \@@@@@@@
                =@@       =@@ O@@O                                                  =@@@@@
                @@         @@@@[
              =/@O       O@@@
              =@@     \@@@ \@
              @@    @@@/   =@\
            =@@/[]@@@[     =@@
           /@@@@@@          @@
         /@@@@@@@           @@
         @@@@@@@            =@
          \@@@@@@\          =@
             @@@@@@@\       =@@
               @@\[@@@       @@
                =@@  \@@\    @@
                 =@@/  [@@@  @@
                  =@@\    =@@@@O
                    \@@     =@@@]                                                    /@@@O
                     \@@     =@@@@\                                                @@@@@@@
                      =@@     @@ [@@@                                        ]]@@@@@@@@@@@
                        @@    =@     @@\                              ]]@@@@@/[ /O@@@@[
                         \@@  =@\      \@@\                   \]@@@@@@O[       O@@[
                          =@@ /@@         @@O          ]/@@@@@@/[           /@@/
                           \@@@@@@          O@@]/O@@@@@/[                ]O@@/
                           =@@@@@@@@\]]]]\@@@@@@@O                     O@@
                           =@@@@@@@@@@@@@/       O@@\                @@@
                           =@@@@@@@@@@@@]          [@@\           /@@O
                            @@@@@@@@@@@@@@@@@@@O\]    \@@@O  ]]/@@@[
                              [@@/             [O@@@@@@@@@@@@@@@@/
                                                       \@@@@@@@@
                                                          \@@@@
*/
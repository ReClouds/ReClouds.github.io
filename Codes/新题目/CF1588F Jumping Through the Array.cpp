#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>
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
	const int MAXM = 505;

	int n, q, s, c, t, tq, p[MAXN], in[MAXN], tl[MAXM << 1], pre[MAXM << 1];
	i64 a[MAXN], sum[MAXN], tag[MAXM << 1];
	bool md[MAXN];

	struct Operation { int opt, a, b; } op[MAXM];
	struct Query { int id, pos; } qr[MAXM << 1];
	struct Answer { int pre[MAXM << 1]; i64 sum, tag[MAXM << 1]; } ans[MAXM];

	inline void Construct()
	{
        t = 0;
		for(register int i = 1; i <= n; i++) if(md[i])
		{
			++t;
			int u = p[i];
			while(true)
			{
				in[u] = t;
				if(md[u]) break;
				u = p[u];
			}
			tl[t] = u;
		}
		return;
	}

	const int BIT = 8;
	const int BASE = 256;

    int len[BASE];
	Query vec[BASE][MAXM << 1];

	inline void Radix_Sort()
	{
		for(register int T = 0; T < 3; T++)
		{
			for(register int i = 1; i <= tq; i++)
            {
                int d = ((qr[i].pos >> (BIT * T)) & (BASE - 1));
                vec[d][len[d]++] = qr[i];
            }
			tq = 0;
			for(register int S = 0; S < BASE; S++)
            {
                for(register int i = 0; i < len[S]; i++) qr[++tq] = vec[S][i];
                len[S] = 0;
            }
		}
		return;
	}

	inline void Work()
	{
		for(register int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
		for(register int i = 1; i <= c; i++)
		{
			if(op[i].opt == 2) md[op[i].a] = true;
			if(op[i].opt == 3) md[op[i].a] = md[op[i].b] = true;
		}
		Construct();
        tq = 0;
		for(register int i = 1; i <= c; i++)
		{
			if(op[i].opt == 1)
			{
				if(op[i].a - 1 > 0) qr[++tq] = (Query){-i, op[i].a - 1};
				qr[++tq] = (Query){i, op[i].b};
				ans[i].sum = sum[op[i].b] - sum[op[i].a - 1];
				for(register int j = 1; j <= t; j++) ans[i].tag[j] = tag[j];
				continue;
			}
			if(op[i].opt == 2)
			{
				int u = in[op[i].a], v = u;
				do
				{
					tag[v] += op[i].b;
					v = in[p[tl[v]]];
				}
				while(v != u);
				continue;
			}
			if(op[i].opt == 3)
			{
				swap(p[op[i].a], p[op[i].b]);
				continue;
			}
		}
		Radix_Sort();
		int nw = 0;
		for(register int i = 1; i <= tq; i++)
		{
			while(nw < qr[i].pos) ++pre[in[++nw]];
			int v = (qr[i].id < 0 ? -1 : 1);
			for(register int j = 1; j <= t; j++) ans[qr[i].id * v].pre[j] += pre[j] * v;
		}
		for(register int i = 1; i <= c; i++)
		{
            if(op[i].opt == 1)
            {
			    i64 res = ans[i].sum; ans[i].sum = 0;
			    for(register int j = 1; j <= t; j++) res += ans[i].tag[j] * ans[i].pre[j], ans[i].tag[j] = ans[i].pre[j] = 0;
			    Write64(res);
                continue;
            }
            if(op[i].opt == 2) md[op[i].a] = false;
            if(op[i].opt == 3) md[op[i].a] = md[op[i].b] = false;
		}
		for(register int i = 1; i <= n; i++)
        {
            if(in[i]) a[i] += tag[in[i]];
            in[i] = 0;
        }
        for(register int i = 1; i <= t; i++) tl[i] = pre[i] = tag[i] = 0;
		return;
	}

    inline int Run()
    {
		n = Read32();
		for(register int i = 1; i <= n; i++) a[i] = Read64();
		for(register int i = 1; i <= n; i++) p[i] = Read32();
		q = Read32(), s = (int)sqrt(q);
		while(q--)
		{
			++c, op[c].opt = Read32(), op[c].a = Read32(), op[c].b = Read32();
			if(c == s || q == 0) Work(), c = 0;
		}
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


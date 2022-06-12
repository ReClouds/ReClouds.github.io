#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
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
	const int MAXN = 1005;

    int n, m, seq[MAXN];
	i64 cnt[MAXN][MAXN][2], ans;
	vector<i64> val[MAXN], sum;

	struct Vector
	{
		i64 xi, yi;
		Vector(i64 _xi = 0.0, i64 _yi = 0.0) : xi(_xi), yi(_yi) {}

		Vector operator + (const Vector &t) const { return Vector(xi + t.xi, yi + t.yi); }
		Vector operator - (const Vector &t) const { return Vector(xi - t.xi, yi - t.yi); }
		Vector operator * (const i64 &t) const { return Vector(xi * t, yi * t); }
		i64 operator * (const Vector &t) const { return xi * t.yi - yi * t.xi; }

		bool operator < (const Vector &t) const
		{
			int ain = (yi > 0 || (yi == 0 && xi > 0)), bin = (t.yi > 0 || (t.yi == 0 && t.xi > 0));
			if(ain == bin) return (*this) * t > 0;
			return ain < bin;
		}

		bool operator <= (const Vector &t) const
		{
			int ain = (yi > 0 || (yi == 0 && xi > 0)), bin = (t.yi > 0 || (t.yi == 0 && t.xi > 0));
			if(ain == bin) return (*this) * t >= 0;
			return ain < bin;
		}

		inline i64 Dist() { return xi * xi + yi * yi; }
	} p[MAXN], q[MAXN];

	struct Line
	{
		Vector pos, dir;
		Line(Vector _pos = Vector(), Vector _dir = Vector()) : pos(_pos), dir(_dir) {}
	};

	inline bool On(int a, int b, int u)
	{
		Line t(p[a], p[b] - p[a]);
		return (p[u] - t.pos) * t.dir == 0;
	}

	inline bool Right(int a, int b, int u)
	{
		Line t(p[a], p[b] - p[a]);
		return (p[u] - t.pos) * t.dir > 0;
	}

	struct Isosceles_Triangle
	{
		int lp, rp;
		i64 val;
		Vector dir;
		Isosceles_Triangle(int _lp = 0, int _rp = 0, i64 _val = 0, Vector _dir = Vector()) : lp(_lp), rp(_rp), val(_val), dir(_dir) {}
	};
	
	vector<Isosceles_Triangle> pr[MAXN];

    inline int Run()
    {
		n = Read32();
		for(register int i = 1; i <= n; i++) p[i].xi = Read64(), p[i].yi = Read64();
		for(register int u = 1; u <= n; u++)
		{
			int len = 0;
			for(register int v = 1; v <= n; v++) if(u != v) q[v] = p[v] - p[u], seq[++len] = v;
			sort(seq + 1, seq + len + 1, [&](int a, int b) { return q[a].Dist() < q[b].Dist(); } );
			for(register int i = 1; i <= len; i++)
			{
				for(register int j = i - 1; j >= 1 && q[seq[i]].Dist() == q[seq[j]].Dist(); j--)
				{
					int a = seq[i], b = seq[j];
					if(a > b) swap(a, b);
					if(On(a, b, u)) continue;
					pr[u].push_back(Isosceles_Triangle(a, b));
					++cnt[a][b][Right(a, b, u)];
				}
			}
		}
		for(register int u = 1; u <= n; u++)
		{
			for(vector<Isosceles_Triangle> :: iterator it = pr[u].begin(); it != pr[u].end(); it++)
			{
				int a = it -> lp, b = it -> rp;
				it -> val = cnt[a][b][Right(a, b, u) ^ 1];
				it -> dir = (p[a] + p[b]) - p[u] * 2;
			}
		}
		for(register int u = 1; u <= n; u++)
		{
			if(pr[u].empty()) continue;
			sort(pr[u].begin(), pr[u].end(), [&](Isosceles_Triangle ta, Isosceles_Triangle tb) {
				Vector a = ta.dir, b = tb.dir;
				int ain = (a.yi > 0 || (a.yi == 0 && a.xi > 0)), bin = (b.yi > 0 || (b.yi == 0 && b.xi > 0));
				if(ain == bin) return a * b > 0;
				return ain < bin;
			} );
			sum.clear(), sum.resize(pr[u].size());
			for(register int i = 0; i < (int)(sum.size()); i++)
			{
				sum[i] = pr[u][i].val;
				if(i > 0) sum[i] += sum[i - 1];
			}
			i64 all = sum[(int)(sum.size() - 1)];
			for(auto it : pr[u])
			{
				Vector a = p[it.lp] - p[u], b = p[it.rp] - p[u];
				if(a * b < 0) swap(a, b);
				a = Vector(a.yi, -a.xi), b = Vector(-b.yi, b.xi);
				if(a * b < 0) swap(a, b);
				i64 res = 0;
				if(b < a) res += all;
				int l = 0, r = (int)(pr[u].size() - 1), t1 = -1, t2 = -1;
				while(l <= r)
				{
					int mid = (l + r) >> 1;
					if(pr[u][mid].dir <= a) t1 = mid, l = mid + 1;
					else r = mid - 1;
				}
				res -= (t1 == -1 ? 0 : sum[t1]);
				l = 0, r = (int)(pr[u].size() - 1);
				while(l <= r)
				{
					int mid = (l + r) >> 1;
					if(pr[u][mid].dir < b) t2 = mid, l = mid + 1;
					else r = mid - 1;
				}
				res += (t2 == -1 ? 0 : sum[t2]);
				ans += res;
			}
		}
		Write64(ans * 4);
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
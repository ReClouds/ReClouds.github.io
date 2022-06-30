#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
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
	const int MAXN = 200005;

	int n, m, q, top, stk[MAXN], cnt;

	struct Vector
	{
		i64 xi, yi;
		Vector(i64 _xi = 0, i64 _yi = 0) : xi(_xi), yi(_yi) {}
		inline i64 Dist() { return xi * xi + yi * yi; }

		Vector operator + (const Vector &t) const { return Vector(xi + t.xi, yi + t.yi); }
		Vector operator - (const Vector &t) const { return Vector(xi - t.xi, yi - t.yi); }
		Vector operator * (const int &t) const { return Vector(xi * t, yi * t); }
		i64 operator * (const Vector &t) const { return xi * t.yi - t.xi * yi; }
	} a[MAXN], b[MAXN], va[MAXN], vb[MAXN], sum[MAXN], dt;

	inline bool Compare1(Vector u, Vector v) { return u.yi == v.yi ? u.xi < v.xi : u.yi < v.yi; }
	inline bool Compare2(Vector u, Vector v) { return u * v == 0 ? u.Dist() < v.Dist() : u * v > 0; }

	inline void Graham(Vector *vec, int &len)
	{
		sort(vec + 1, vec + len + 1, Compare1);
		dt = vec[1], stk[top = 1] = 1;
		for(register int i = 1; i <= len; i++) vec[i] = vec[i] - dt;
		sort(vec + 2, vec + len + 1, Compare2);
		for(register int i = 2; i <= len; i++)
		{
			while(top > 1 && (vec[i] - vec[stk[top - 1]]) * (vec[stk[top]] - vec[stk[top - 1]]) >= 0) --top;
			stk[++top] = i;
		}
		for(register int i = 1; i <= top; i++) vec[i] = vec[stk[i]] + dt;
		return len = top, vec[len + 1] = vec[1], void();
	}

	inline void Minkowski()
	{
		for(register int i = 1; i <= n; i++) va[i] = a[i + 1] - a[i];
		for(register int i = 1; i <= m; i++) vb[i] = b[i + 1] - b[i];
		sum[cnt = 1] = a[1] + b[1];
		int p = 1, q = 1;
		while(p <= n || q <= m)
		{
			++cnt;
			if(q > m || (p <= n && va[p] * vb[q] >= 0)) sum[cnt] = sum[cnt - 1] + va[p], ++p;
			else sum[cnt] = sum[cnt - 1] + vb[q], ++q;
		}
		return;
	}

	inline bool Query(Vector t)
	{
		if(t * sum[2] > 0 || t * sum[cnt] < 0) return false;
		int pos = lower_bound(sum + 1, sum + cnt + 1, t, Compare2) - sum - 1;
		return (t - sum[pos]) * (sum[pos + 1] - sum[pos]) <= 0;
	}

    inline int Run()
    {
		n = Read32(), m = Read32(), q = Read32();
		for(register int i = 1; i <= n; i++) a[i].xi = Read64(), a[i].yi = Read64();
		for(register int i = 1; i <= m; i++) b[i].xi = -Read64(), b[i].yi = -Read64();
		Graham(a, n), Graham(b, m), Minkowski(), Graham(sum, cnt);
		dt = sum[1];
		for(register int i = 1; i <= cnt; i++) sum[i] = sum[i] - dt;
		while(q--)
		{
			int dxi = Read32(), dyi = Read32();
			Write32(Query(Vector(dxi, dyi) - dt));
			continue;
		}
        return 0;
    }
}

int main() { return Program :: Run(); }

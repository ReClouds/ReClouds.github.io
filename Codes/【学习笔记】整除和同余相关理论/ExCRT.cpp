#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>

#define MAXN 100005

#define up(i, l, r) for(int i = (l); i <= (r); i = -~i)
#define down(i, l, r) for(int i = (l); i >= (r); i--)

using i64 = long long;
using namespace std;

namespace IO
{
	int f; char c;

	template<typename T> inline void _Read(T &v)
	{
		v = 0; f = 1; c = getchar();
		while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
		while(isdigit(c)) { v = (v << 3) + (v << 1) + (int)(c - '0'); c = getchar(); }
		v *= f;
		return;
	}

	template<typename T> inline void _Write(T k)
	{
		if(k < 0) { putchar('-'); k = -k; }
		if(k > 9) _Write(k / 10);
		putchar((char)(k % 10 + '0'));
		return;
	}

	inline int Read() { int v; _Read(v); return v; }
	inline i64 Read64() { i64 v; _Read(v); return v; }
	inline void Write(int v, char ed = '\n') { _Write(v); putchar(ed); return; }
	inline void Write64(i64 v, char ed = '\n') { _Write(v); putchar(ed); return; }
}

using IO :: Read;
using IO :: Read64;
using IO :: Write;
using IO :: Write64;

int n;
i64 b[MAXN], a[MAXN], mul, ans;

inline void Mul(i64 &res, i64 a, i64 b, i64 p)
{
	res = 0LL;
	while(b)
	{
		if(b & 1LL) res = (res + a) % p;
		a = (a << 1) % p;
		b >>= 1;
	}
	return;
}

inline i64 Exgcd(i64 a, i64 b, i64 &x, i64 &y)
{
	if(b == 0LL) return x = 1LL, y = 0LL, a;
	i64 c = Exgcd(b, a % b, y, x);
	return y -= (a / b) * x, c;
}

int main()
{
	n = Read();
	up(i, 1, n) a[i] = Read64(), b[i] = Read64();
	mul = a[1]; ans = b[1];
	up(i, 2, n)
	{
		i64 A = mul, B = a[i], C = ((b[i] - ans) % B + B) % B, x, y;
		i64 D = Exgcd(A, B, x, y), E = B / D;
		Mul(x, x, C / D, E);
		ans += mul * x; mul *= E;
		ans = (ans % mul + mul) % mul;
	}
	Write64(ans);
	return 0;
}
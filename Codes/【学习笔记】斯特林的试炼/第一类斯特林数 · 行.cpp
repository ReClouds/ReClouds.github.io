#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>

#define MAXN 2000005

#define MOD 167772161
#define Min_G 3
#define Inv_Min_G 55924054

using namespace std;

int n, fac[MAXN], inv[MAXN], f[MAXN], g[MAXN], s[MAXN], t[MAXN];

inline int Pow(int a, int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1LL * res * a % MOD;
		a = 1LL * a * a % MOD;
		b >>= 1;
	}
	return res;
}

namespace Polynomial
{
	int p, q, rev[MAXN];

	inline void Init(int n)
	{
		p = 1, q = -1;
		while(p < n) p <<= 1, ++q;
		for(register int i = 0; i < p; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << q);
		return;
	}

	inline void NTT(int *f, int n, bool Inverse = false)
	{
		for(register int i = 0; i < n; i++) if(i < rev[i]) swap(f[i], f[rev[i]]);
		for(register int len = 2; len <= n; len <<= 1)
		{
			int k = (len >> 1), g = Pow(Inverse ? Inv_Min_G : Min_G, (MOD - 1) / len);
			for(register int i = 0; i < n; i += len)
			{
				int w = 1;
				for(register int j = 0; j < k; j++)
				{
					int u = f[i + j], v = 1LL * w * f[i + j + k] % MOD;
					f[i + j] = (u + v) % MOD;
					f[i + j + k] = (u - v + MOD) % MOD;
					w = 1LL * w * g % MOD;
				}
			}
		}
		if(Inverse)
		{
			int Inv_N = Pow(n, MOD - 2);
			for(register int i = 0; i < n; i++) f[i] = 1LL * f[i] * Inv_N % MOD;
		}
		return;
	}
}

inline void Init(int n)
{
	fac[0] = 1;
	for(register int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
	inv[n] = Pow(fac[n], MOD - 2);
	for(register int i = n - 1; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % MOD;
	return;
}

inline void Solve(int *f, int n)
{
	if(n == 0) return f[0] = 1, void();
	if(n & 1)
	{
		Solve(f, n - 1);
		if(n & 1)
		{
			for(register int i = n; i >= 1; i--) f[i] = (1LL * f[i] * (n - 1) % MOD + f[i - 1]) % MOD;
			f[0] = 1LL * f[0] * (n - 1) % MOD;
		}
		return;
	}
	Solve(f, n >> 1);

	int m = (n >> 1), w = 1;
	Polynomial :: Init((m << 1) + 1);
	int p = Polynomial :: p;
	fill(s, s + p, 0), fill(t, t + p, 0);
	for(register int i = 0; i <= m; i++)
	{
		s[i] = 1LL * f[m - i] * fac[m - i] % MOD;
		t[i] = 1LL * w * inv[i] % MOD;
		w = 1LL * w * m % MOD;
	}
	Polynomial :: NTT(s, p), Polynomial :: NTT(t, p);
	for(register int i = 0; i < p; i++) s[i] = 1LL * s[i] * t[i] % MOD;
	Polynomial :: NTT(s, p, true);

	fill(f + n + 1, f + p, 0), fill(g, g + p, 0);
	for(register int i = 0; i <= m; i++) g[i] = 1LL * s[m - i] * inv[i] % MOD;
	Polynomial :: NTT(f, p), Polynomial :: NTT(g, p);
	for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	Polynomial :: NTT(f, p, true);
	return;
}

int main()
{
	scanf("%d", &n);
	Init(n << 1);
	Solve(f, n);
	for(register int i = 0; i <= n; i++) printf("%d ", f[i]);
	putchar('\n');
	return 0;
}

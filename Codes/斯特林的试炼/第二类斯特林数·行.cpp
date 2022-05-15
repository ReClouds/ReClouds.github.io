#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>

#define MAXN 1000005

#define MOD 167772161
#define Min_G 3
#define Inv_Min_G 55924054

using namespace std;

int n, f[MAXN], g[MAXN], fac[MAXN], invf[MAXN], p, q, rev[MAXN];

inline int Get_MOD(int k) { if(k >= MOD) k -= MOD; return k; }

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

inline void Init()
{
	fac[0] = 1;
	for(register int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
	invf[n] = Pow(fac[n], MOD - 2);
	for(register int i = n - 1; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
	p = 1, q = -1;
	while(p < (n << 1)) p <<= 1, ++q;
	for(register int i = 0; i < p; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << q);
	return;
}

inline void NTT(int *f, bool Inverse = false)
{
	for(register int i = 0; i < p; i++) if(i < rev[i]) swap(f[i], f[rev[i]]);
	for(register int len = 2; len <= p; len <<= 1)
	{
		int k = (len >> 1), g = Pow(Inverse ? Inv_Min_G : Min_G, (MOD - 1) / len);
		for(register int i = 0; i < p; i += len)
		{
			int w = 1;
			for(register int j = 0; j < k; j++)
			{
				int u = f[i + j], v = 1LL * w * f[i + j + k] % MOD;
				f[i + j] = Get_MOD(u + v);
				f[i + j + k] = Get_MOD(u - v + MOD);
				w = 1LL * w * g % MOD;
			}
		}
	}
	if(Inverse)
	{
		int Inv_N = Pow(p, MOD - 2);
		for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * Inv_N % MOD;
	}
	return;
}

int main()
{
	scanf("%d", &n);
	Init();
	for(register int i = 0; i <= n; i++)
	{
		f[i] = 1LL * ((i & 1) ? MOD - 1 : 1) * invf[i] % MOD;
		g[i] = 1LL * Pow(i, n) * invf[i] % MOD;
	}
	NTT(f), NTT(g);
	for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, true);
	for(register int i = 0; i <= n; i++) printf("%d ", f[i]);
	return 0;
}

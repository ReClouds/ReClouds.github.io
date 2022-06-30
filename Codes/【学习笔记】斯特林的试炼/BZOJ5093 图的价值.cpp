#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAXN 3000005
#define MOD 998244353
#define Min_G 3
#define Inv_Min_G 332748118

using namespace std;

int n, k, p, q, f[MAXN], g[MAXN], rev[MAXN], fac[MAXN], invf[MAXN];

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
				f[i + j] = (u + v) % MOD;
				f[i + j + k] = (u - v + MOD) % MOD;
				w = 1LL * w * g % MOD;
			}
		}
	}
	if(!Inverse) return;
	int Inv_N = Pow(p, MOD - 2);
	for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * Inv_N % MOD;
	return;
}

inline void Init(int k)
{
	fac[0] = 1;
	for(register int i = 1; i <= k; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
	invf[k] = Pow(fac[k], MOD - 2);
	for(register int i = k - 1; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % MOD;
	for(register int i = 0; i <= k; i++) f[i] = 1LL * ((i & 1) ? MOD - 1 : 1) * invf[i] % MOD;
	for(register int i = 0; i <= k; i++) g[i] = 1LL * Pow(i, k) * invf[i] % MOD;
	p = 1, q = -1;
	while(p <= (k << 1)) p <<= 1, ++q;
	for(register int i = 0; i < p; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << q);
	NTT(f), NTT(g);
	for(register int i = 0; i < p; i++) f[i] = 1LL * f[i] * g[i] % MOD;
	NTT(f, true);
	return;
}

inline void Run()
{
	scanf("%d%d", &n, &k);
	if(n == 1) return printf("%d\n", k == 0), void();
	int res = 0, C = n - 1;
	if(k == 0) res = Pow(2, n - 1);
	else
	{
		Init(k);
		for(register int i = 1; i <= k; i++)
		{
			if(i == n) break;
			res = (res + 1LL * C * f[i] % MOD * Pow(2, n - i - 1) % MOD) % MOD;
			C = 1LL * C * (n - i - 1) % MOD;
		}
	}
	res = 1LL * res * n % MOD * Pow(2, 1LL * (n - 1) * (n - 2) / 2 % (MOD - 1)) % MOD;
	return printf("%d\n", res), void();
}

int main()
{
	Run();
	return 0;
}

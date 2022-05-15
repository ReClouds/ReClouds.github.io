#include<iostream>
#include<cstdio>
#include<cstdlib>

#define Bitcnt(k) __builtin_popcount(k)

#define MAXN 2000005
#define MAXLOG 21
#define MOD 1000000009

using namespace std;

int n, m, a[MAXLOG][MAXN], b[MAXLOG][MAXN], c[MAXLOG][MAXN];

inline int GetMOD(int k) { if(k >= MOD) k -= MOD; return k; }

inline void FWT(int *f, int t = 1)
{
	for(register int len = 2; len <= m; len <<= 1)
	{
		int k = len >> 1;
		for(register int i = 0; i < m; i += len)
			for(register int j = 0; j < k; j++)
				f[i + j + k] = GetMOD(f[i + j + k] + 1LL * f[i + j] * t % MOD);
	}
	return;
}

int main()
{
	scanf("%d", &n), m = (1 << n);
	for(register int i = 0; i < m; i++) scanf("%d", &a[Bitcnt(i)][i]);
	for(register int i = 0; i < m; i++) scanf("%d", &b[Bitcnt(i)][i]);
	for(register int i = 0; i <= n; i++) FWT(a[i]), FWT(b[i]);
	for(register int i = 0; i <= n; i++)
		for(register int j = 0; j <= i; j++)
			for(register int k = 0; k < m; k++) c[i][k] = GetMOD(c[i][k] + 1LL * a[j][k] * b[i - j][k] % MOD);
	for(register int i = 0; i <= n; i++) FWT(c[i], MOD - 1);
	for(register int i = 0; i < m; i++) printf("%d ", c[Bitcnt(i)][i]);
	return 0;
}

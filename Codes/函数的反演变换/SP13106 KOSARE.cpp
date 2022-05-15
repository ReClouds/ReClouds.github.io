#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAXN 2000005
#define MAXM 21
#define MOD 1000000007

using namespace std;

int n, m, f[MAXN], F[MAXN], ans;

inline int GetMOD(int k) { if(k >= MOD) k -= MOD; return k; }
inline int Bitcnt(int k) { return __builtin_popcount(k); }

inline void FWT(int *f)
{
	for(register int len = 2; len <= (1 << m); len <<= 1)
	{
		int k = len >> 1;
		for(register int i = 0; i < (1 << m); i += len)
			for(register int j = 0; j < k; j++)
				f[i + j + k] = GetMOD(f[i + j + k] + f[i + j]);
	}
	return;
}

inline int Pow(int k, int p)
{
	int res = 1;
	while(p)
	{
		if(p & 1) res = 1LL * res * k % MOD;
		k = 1LL * k * k % MOD;
		p >>= 1;
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	for(register int i = 1; i <= n; i++)
	{
		int ki; scanf("%d", &ki);
		int st = 0;
		for(register int j = 1; j <= ki; j++)
		{
			int t; scanf("%d", &t);
			st |= (1 << (t - 1));
		}
		++f[st];
	}
	FWT(f);
	for(register int i = 0; i < (1 << m); i++) F[i] = Pow(2, f[i]) - 1;
	for(register int i = 0; i < (1 << m); i++)
	{
		if(Bitcnt(((1 << m) - 1) ^ i) & 1) ans = GetMOD(ans - F[i] + MOD);
		else ans = GetMOD(ans + F[i]);
	}
	printf("%d\n", ans);
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MOD 998244353

using namespace std;

int n, p, k, ans;

inline int GetMOD(int k) { if(k >= MOD) k -= MOD; return k; }

inline int Pow(int k, int q)
{
	int res = 1;
	while(q)
	{
		if(q & 1) res = 1LL * res * k % MOD;
		k = 1LL * k * k % MOD;
		q >>= 1;
	}
	return res;
}

inline int Inv(int k) { return Pow(k, MOD - 2); }

int main()
{
	scanf("%d%d%d", &n, &p, &k);
	const int G = Pow(3, (MOD - 1) / k);
	int w = 1;
	for(register int t = 0; t < k; t++)
	{		
		if(w == 1) ans = GetMOD(ans + GetMOD(1LL * n * p % MOD * Pow(p + 1, n - 1) % MOD + Pow(p + 1, n)));
		else ans = GetMOD(ans + 1LL * GetMOD(1LL * w * Pow(GetMOD(1LL * p * w % MOD + 1), n) % MOD - Pow(p + 1, n) + MOD) * Inv(w - 1) % MOD);
		w = 1LL * w * G % MOD;
	}
	ans = 1LL * ans * Inv(k) % MOD;
	ans = GetMOD(ans - Pow(p + 1, n) + MOD);
	printf("%d\n", ans);
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cmath>

#define MAXN 200005

using LL = long long;
using namespace std;

int len, m, pos1[MAXN], pos2[MAXN];
LL n, s, Prime[MAXN], sum1[MAXN], sum2[MAXN], val[MAXN], g1[MAXN], g2[MAXN];
bool NotPrime[MAXN];
const LL MOD = 1000000007LL, Inv2 = 500000004LL, Inv6 = 166666668LL;

inline LL GetMOD(LL k) { if(k >= MOD) k -= MOD; return k; }
inline LL Prefix1(LL k) { k %= MOD; return k * (k + 1LL) % MOD * Inv2 % MOD; }
inline LL Prefix2(LL k) { k %= MOD; return k * (k + 1LL) % MOD * GetMOD(k * 2LL % MOD + 1LL) % MOD * Inv6 % MOD; }
inline int GetPos(LL k) { if(k <= s) return pos1[k]; return pos2[n / k]; }

inline void Sieve()
{
	NotPrime[1] = true;
	for(register int i = 2; i <= s; i++)
	{
		if(!NotPrime[i])
		{
			Prime[++len] = i;
			sum1[len] = GetMOD(sum1[len - 1] + i) % MOD;
			sum2[len] = GetMOD(sum2[len - 1] + 1LL * i * i % MOD) % MOD;
		}
		for(register int j = 1; j <= len && i * Prime[j] <= s; j++)
		{
			NotPrime[i * Prime[j]] = true;
			if(i % Prime[j] == 0LL) break;
		}
	}
	return;
}

inline LL S(LL k, int p)
{
	if(Prime[p] > k) return 0LL;
	LL res = GetMOD(GetMOD(g2[GetPos(k)] - g1[GetPos(k)] + MOD) - GetMOD(sum2[p] - sum1[p] + MOD) + MOD);
	for(register int i = p + 1; i <= len && Prime[i] * Prime[i] <= k; i++)
	{
		LL pw = Prime[i];
		for(register int j = 1; pw <= k; pw = pw * Prime[i], j++) res = GetMOD(res + pw % MOD * GetMOD(pw % MOD - 1LL + MOD) % MOD * GetMOD(S(k / pw, i) + (j > 1)) % MOD);
	}
	return res;
}

int main()
{
	#ifdef FILE
		freopen("Input.in", "r", stdin);
	#endif
	scanf("%lld", &n), s = (LL)sqrt(n), Sieve();
	for(register LL l = 1, r; l <= n; l = r + 1)
	{
		r = n / (n / l), val[++m] = n / l;
		g1[m] = GetMOD(Prefix1(val[m]) - 1LL + MOD), g2[m] = GetMOD(Prefix2(val[m]) - 1LL + MOD);
		if(val[m] <= s) pos1[val[m]] = m; else pos2[n / val[m]] = m;
	}
	for(register int i = 1; i <= len; i++)
	{
		for(register int j = 1; j <= m && Prime[i] * Prime[i] <= val[j]; j++)
		{
			g1[j] = GetMOD(g1[j] - 1LL * Prime[i] * GetMOD(g1[GetPos(val[j] / Prime[i])] - sum1[i - 1] + MOD) % MOD + MOD); 
			g2[j] = GetMOD(g2[j] - 1LL * Prime[i] * Prime[i] % MOD * GetMOD(g2[GetPos(val[j] / Prime[i])] - sum2[i - 1] + MOD) % MOD + MOD);
		}
	}
	printf("%lld\n", GetMOD(S(n, 0) + 1LL));
	return 0;
}

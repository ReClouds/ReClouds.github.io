#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cmath>

#define MAXN 200005

using i64 = long long;
using namespace std;

int len, m, pos1[MAXN], pos2[MAXN];
i64 n, s, pr[MAXN], sum1[MAXN], sum2[MAXN], val[MAXN], g1[MAXN], g2[MAXN];
bool np[MAXN];
const i64 MOD = 1000000007LL, Inv2 = 500000004LL, Inv6 = 166666668LL;

inline i64 Get_MOD(i64 k) { if(k >= MOD) k -= MOD; return k; }
inline i64 Prefix1(i64 k) { k %= MOD; return k * (k + 1LL) % MOD * Inv2 % MOD; }
inline i64 Prefix2(i64 k) { k %= MOD; return k * (k + 1LL) % MOD * Get_MOD(k * 2LL % MOD + 1LL) % MOD * Inv6 % MOD; }
inline int Get_Pos(i64 k) { if(k <= s) return pos1[k]; return pos2[n / k]; }

inline void Sieve()
{
	np[1] = true;
	for(register int i = 2; i <= s; i++)
	{
		if(!np[i])
		{
			pr[++len] = i;
			sum1[len] = Get_MOD(sum1[len - 1] + i) % MOD;
			sum2[len] = Get_MOD(sum2[len - 1] + 1LL * i * i % MOD) % MOD;
		}
		for(register int j = 1; j <= len && i * pr[j] <= s; j++)
		{
			np[i * pr[j]] = true;
			if(i % pr[j] == 0LL) break;
		}
	}
	return;
}

inline i64 S(i64 k, int p)
{
	if(pr[p] > k) return 0LL;
	i64 res = Get_MOD(Get_MOD(g2[Get_Pos(k)] - g1[Get_Pos(k)] + MOD) - Get_MOD(sum2[p] - sum1[p] + MOD) + MOD);
	for(register int i = p + 1; i <= len && pr[i] * pr[i] <= k; i++)
	{
		i64 pw = pr[i];
		for(register int j = 1; pw <= k; pw = pw * pr[i], j++) res = Get_MOD(res + pw % MOD * Get_MOD(pw % MOD - 1LL + MOD) % MOD * Get_MOD(S(k / pw, i) + (j > 1)) % MOD);
	}
	return res;
}

int main()
{
	scanf("%lld", &n), s = (int)(sqrt(n)), Sieve();
	for(register i64 l = 1, r; l <= n; l = r + 1)
	{
		r = n / (n / l), val[++m] = n / l;
		g1[m] = Get_MOD(Prefix1(val[m]) - 1LL + MOD), g2[m] = Get_MOD(Prefix2(val[m]) - 1LL + MOD);
		if(val[m] <= s) pos1[val[m]] = m; else pos2[n / val[m]] = m;
	}
	for(register int i = 1; i <= len; i++)
	{
		for(register int j = 1; j <= m && pr[i] * pr[i] <= val[j]; j++)
		{
			g1[j] = Get_MOD(g1[j] - 1LL * pr[i] * Get_MOD(g1[Get_Pos(val[j] / pr[i])] - sum1[i - 1] + MOD) % MOD + MOD); 
			g2[j] = Get_MOD(g2[j] - 1LL * pr[i] * pr[i] % MOD * Get_MOD(g2[Get_Pos(val[j] / pr[i])] - sum2[i - 1] + MOD) % MOD + MOD);
		}
	}
	printf("%lld\n", Get_MOD(S(n, 0) + 1LL));
	return 0;
}

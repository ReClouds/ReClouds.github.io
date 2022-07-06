#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<unordered_map>

#define MAXN 5000005

using i64 = long long;
using namespace std;

int t, n;
int len, pr[MAXN];
i64 phi[MAXN], miu[MAXN];
bool np[MAXN];
unordered_map<int, i64> ansphi, ansmiu;

inline void Prework()
{
	phi[1] = miu[1] = 1LL;
	for(register int i = 2; i < MAXN; i++)
	{
		if(!np[i])
		{
			pr[++len] = i;
			phi[i] = i - 1LL;
			miu[i] = -1LL;
		}
		for(register int j = 1; j <= len && i * pr[j] < MAXN; j++)
		{
			np[i * pr[j]] = true;
			if(i % pr[j] == 0LL)
			{
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
			phi[i * pr[j]] = phi[i] * (pr[j] - 1LL);
			miu[i * pr[j]] = -miu[i];
		}
	}
	for(register int i = 1; i < MAXN; i++) phi[i] += phi[i - 1], miu[i] += miu[i - 1];
	return;
}

inline i64 Solve_phi(int n)
{
	if(n < MAXN) return phi[n];
	if(ansphi.count(n)) return ansphi[n];
	i64 ans = 1LL * n * (n + 1LL) / 2LL;
	for(register i64 l = 2LL, r; l <= n; l = r + 1LL)
	{
		r = n / (n / l);
		ans -= 1LL * (r - l + 1LL) * Solve_phi(n / l);
	}
	ansphi.insert(make_pair(n, ans));
	return ans;
}

inline i64 Solve_miu(int n)
{
	if(n < MAXN) return miu[n];
	if(ansmiu.count(n)) return ansmiu[n];
	i64 ans = 1LL;
	for(register i64 l = 2LL, r; l <= n; l = r + 1LL)
	{
		r = n / (n / l);
		ans -= 1LL * (r - l + 1LL) * Solve_miu(n / l);
	}
	ansmiu.insert(make_pair(n, ans));
	return ans;
}

int main()
{
	Prework();
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld %lld\n", Solve_phi(n), Solve_miu(n));
		continue;
	}
	return 0;
}

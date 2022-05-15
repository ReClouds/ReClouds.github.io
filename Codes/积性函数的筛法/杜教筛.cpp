#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<unordered_map>

#define MAXN 5000001

using LL = long long;
using namespace std;

int t, n;
int len, Prime[MAXN];
LL Phi[MAXN], Miu[MAXN];
bool NotPrime[MAXN];
unordered_map<int, LL> AnsPhi, AnsMiu;

inline void Prework()
{
	Phi[1] = Miu[1] = 1LL;
	for(register int i = 2; i < MAXN; i++)
	{
		if(!NotPrime[i])
		{
			Prime[++len] = i;
			Phi[i] = i - 1LL;
			Miu[i] = -1LL;
		}
		for(register int j = 1; j <= len && i * Prime[j] < MAXN; j++)
		{
			NotPrime[i * Prime[j]] = true;
			if(i % Prime[j] == 0LL)
			{
				Phi[i * Prime[j]] = Phi[i] * Prime[j];
				break;
			}
			Phi[i * Prime[j]] = Phi[i] * (Prime[j] - 1LL);
			Miu[i * Prime[j]] = -Miu[i];
		}
	}
	for(register int i = 1; i < MAXN; i++) Phi[i] += Phi[i - 1], Miu[i] += Miu[i - 1];
	return;
}

inline LL Solve_Phi(int n)
{
	if(n < MAXN) return Phi[n];
	if(AnsPhi.count(n)) return AnsPhi[n];
	LL ans = 1LL * n * (n + 1LL) / 2LL;
	for(register LL l = 2LL, r; l <= n; l = r + 1LL)
	{
		r = n / (n / l);
		ans -= 1LL * (r - l + 1LL) * Solve_Phi(n / l);
	}
	AnsPhi.insert(make_pair(n, ans));
	return ans;
}

inline LL Solve_Miu(int n)
{
	if(n < MAXN) return Miu[n];
	if(AnsMiu.count(n)) return AnsMiu[n];
	LL ans = 1LL;
	for(register LL l = 2LL, r; l <= n; l = r + 1LL)
	{
		r = n / (n / l);
		ans -= 1LL * (r - l + 1LL) * Solve_Miu(n / l);
	}
	AnsMiu.insert(make_pair(n, ans));
	return ans;
}

int main()
{
	#ifdef FILE
		freopen("Input.in", "r", stdin);
	#endif
	Prework();
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld %lld\n", Solve_Phi(n), Solve_Miu(n));
		continue;
	}
	return 0;
}

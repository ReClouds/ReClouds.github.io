#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAXN 20000005

using uint = unsigned int;
using namespace std;

int T, N, K, len, Prime[MAXN];
uint f[MAXN], F[MAXN];
bool NotPrime[MAXN];

inline uint Pow(uint a, uint b)
{
	uint res = 1;
	while(b)
	{
		if(b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

inline void Sieve(int n, int k)
{
	f[1] = F[1] = 1;
	for(register int i = 2; i <= n; i++)
	{
		if(!NotPrime[i])
		{
			Prime[++len] = i;
			f[i] = i - 1;
			F[i] = Pow(i, k);
		}
		for(register int j = 1; j <= len && i * Prime[j] <= n; j++)
		{
			NotPrime[i * Prime[j]] = true;
			F[i * Prime[j]] = F[i] * F[Prime[j]];
			if(i % Prime[j] == 0)
			{
				if((i / Prime[j]) % Prime[j]) f[i * Prime[j]] = -Prime[j] * f[i / Prime[j]];
				break;
			}
			f[i * Prime[j]] = f[i] * f[Prime[j]];
		}
	}
	for(register int i = 2; i <= n; i++) f[i] = f[i - 1] + f[i] * F[i], F[i] += F[i - 1];
	for(register int i = 2; i <= n; i++) F[i] += F[i - 1];
	return;
}

inline uint Count(int k) { return F[k * 2] - F[k] * 2; }

int main()
{
	scanf("%d%d%d", &T, &N, &K), Sieve(N << 1, K);
	while(T--)
	{
		int n; scanf("%d", &n);
		uint ans = 0;
		for(register int l = 1, r; l <= n; l = r + 1)
		{
			r = n / (n / l);
			ans += Count(n / l) * (f[r] - f[l - 1]);
		}
		printf("%u\n", ans);
	}
	return 0;
}


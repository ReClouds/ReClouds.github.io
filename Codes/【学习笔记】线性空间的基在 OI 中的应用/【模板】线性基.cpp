#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAXN 50

using i64 = long long;
using namespace std;

int n, cnt;
bool Zero;
i64 a[MAXN], b[MAXN], p[MAXN];

inline void Build()
{
	for(register int i = 0; i < n; i++)
	{
		if(!a[i]) { Zero = false; continue; }
		for(register int j = MAXN - 1; j >= 0; j--)
		{
			if(a[i] >> j & 1LL)
			{
				if(b[j]) a[i] ^= b[j];
				else
				{
					b[j] = a[i], ++cnt;
					for(register int k = j - 1; k >= 0; k--) if(b[j] >> k & 1LL) b[j] ^= b[k];
					for(register int k = j + 1; k < MAXN; k++) if(b[k] >> j & 1LL) b[k] ^= b[j];
					break;
				}
			}
		}
	}
	int len = 0;
	for(register int j = 0; j < MAXN; j++) if(b[j]) p[len++] = b[j];
	return;
}

inline i64 Kth(i64 k)
{
	if(Zero) --k;
	if(!k) return 0LL;
	i64 res = 0LL;
	for(register int i = 0; i < cnt; i++) if(k >> i & 1LL) res ^= p[i];
	return res;
}

int main()
{
	scanf("%d", &n);
	for(register int i = 0; i < n; i++) scanf("%lld", a + i);
	Build();
	printf("%lld\n", Kth((1LL << cnt) - 1 + Zero));
	return 0;
}
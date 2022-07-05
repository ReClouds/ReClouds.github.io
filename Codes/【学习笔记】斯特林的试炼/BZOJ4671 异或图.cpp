#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cstring>

#define MAXN 11
#define MAXM 61

using i64 = long long;
using namespace std;

int s, n, mp[MAXN], in[MAXM];
i64 fac[MAXN], ans;
bool t[MAXM][MAXN][MAXN];
char g[MAXN * MAXN];

namespace Linear_Basis
{
	int cnt;
	i64 b[MAXM];

	inline void Insert(i64 val)
	{
		for(register int i = s - 1; i >= 0; i--)
		{
			if((val >> i & 1LL) ^ 1) continue;
			if(b[i]) { val ^= b[i]; continue; }
			++cnt, b[i] = val;
			break;
		}
		return;
	}
}

using namespace Linear_Basis;

inline void DFS(int i, int j)
{
	if(i == n + 1)
	{
		cnt = 0, memset(b, 0LL, sizeof b);
		for(register int a = 1; a < n; a++)
		{
			for(register int c = a + 1; c <= n; c++)
			{
				if(in[a] == in[c]) continue;
				i64 val = 0LL;
				for(register int q = 0; q < s; q++) if(t[q][a][c]) val |= 1LL << q;
				Insert(val);
			}
		}
		i64 f = 1LL << (s - cnt);
		ans += (j & 1 ? 1LL : -1LL) * fac[j - 1] * f;
		return;
	}
	for(register int k = 1; k <= j; k++) in[i] = k, DFS(i + 1, j); 
	in[i] = j + 1, DFS(i + 1, j + 1);
	return;
}

int main()
{
	for(register int i = 2; i < MAXN; i++) mp[i * (i - 1) / 2] = i;
	scanf("%d", &s);
	for(register int i = 0; i < s; i++)
	{
		scanf("%s", g);
		n = mp[(int)strlen(g)];
		int tot = 0;
		for(register int j = 1; j < n; j++)
		{
			for(register int k = j + 1; k <= n; k++)
			{
				if(g[tot] == '1') t[i][j][k] = true;
				++tot;
			}
		}
	}
	fac[0] = 1LL; for(register int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
	DFS(1, 0);
	printf("%lld\n", ans);
	return 0;
}

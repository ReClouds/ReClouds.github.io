#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define MAXN 200005
#define MOD 998244353
#define Inv2 499122177

using namespace std;

int n, A[MAXN], B[MAXN], a[MAXN], b[MAXN];

inline int GetMOD(int k) { if(k >= MOD) k -= MOD; return k; }
inline void Copy() { return memcpy(a, A, sizeof A), memcpy(b, B, sizeof B), void(); }
inline void Multiply() { for(register int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % MOD; return; }
inline void Output() { for(register int i = 0; i < n; i++) printf("%d ", a[i]); return putchar('\n'), void(); }

inline void Or(int *f, int t = 1)
{
	for(register int len = 2; len <= n; len <<= 1)
	{
		int k = len >> 1;
		for(register int i = 0; i < n; i += len)
			for(register int j = 0; j < k; j++) 
				f[i + j + k] = GetMOD(f[i + j + k] + GetMOD(1LL * f[i + j] * t % MOD));
	}
	return;
}

inline void And(int *f, int t = 1)
{
	for(register int len = 2; len <= n; len <<= 1)
	{
		int k = len >> 1;
		for(register int i = 0; i < n; i += len)
			for(register int j = 0; j < k; j++)
				f[i + j] = GetMOD(f[i + j] + GetMOD(1LL * f[i + j + k] * t % MOD));
	}
	return;
}

inline void Xor(int *f, int t = 1)
{
	for(register int len = 2; len <= n; len <<= 1)
	{
		int k = len >> 1;
		for(register int i = 0; i < n; i += len)
			for(register int j = 0; j < (len >> 1); j++)
			{
				int u = f[i + j], v = f[i + j + k];
				f[i + j] = GetMOD(u + v);
				f[i + j + k] = GetMOD(u - v + MOD);
				f[i + j] = 1LL * f[i + j] * t % MOD, f[i + j + k] = 1LL * f[i + j + k] * t % MOD;
			}
	}
	return;
}

int main()
{
	scanf("%d", &n), n = (1 << n);
	for(register int i = 0; i < n; i++) scanf("%d", A + i);
	for(register int i = 0; i < n; i++) scanf("%d", B + i);
	Copy(), Or(a), Or(b), Multiply(), Or(a, MOD - 1), Output();
	Copy(), And(a), And(b), Multiply(), And(a, MOD - 1), Output();
	Copy(), Xor(a), Xor(b), Multiply(), Xor(a, Inv2), Output();
	return 0;
}

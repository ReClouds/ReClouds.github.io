#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<ctime>

using LL = long long;
using namespace std;

int t;
LL si, n, p;

struct Complex
{
	LL a, b;
	
	Complex operator * (const Complex &t) const
	{
	 	Complex res = (Complex){0LL, 0LL};
		res.a = (a * t.a % p + b * t.b % p * si % p) % p;
		res.b = (a * t.b % p + b * t.a % p) % p;
		return res;
	}
};

inline LL Pow_Real(LL a, LL b)
{
	LL res = 1LL;
	while(b)
	{
		if(b & 1LL) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

inline LL Pow_Complex(Complex a, LL b)
{
	Complex res = (Complex){1LL, 0LL};
	while(b)
	{
		if(b & 1LL) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res.a;
}

inline LL Solve(LL n, LL p)
{
	if(Pow_Real(n, (p - 1LL) / 2LL) != 1LL) return -1LL;
	LL k;
	while(true)
	{
		k = 1LL * rand() * rand() % p;
		si = ((k * k % p - n) % p + p) % p;
		if(Pow_Real(si, (p - 1LL) / 2LL) != 1LL) break;
	}
	Complex val = (Complex){k, 1};
	return Pow_Complex(val, (p + 1LL) / 2LL);
}

int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &n, &p), n %= p;
		if(n == 0LL) { puts("0"); continue; }
		LL ans1 = Solve(n, p), ans2;
		if(ans1 == -1LL) { puts("Hola!"); continue; }
		else
		{
			ans2 = p - ans1;
			if(ans1 > ans2) swap(ans1, ans2);
			printf("%lld %lld\n", ans1, ans2);
			continue;
		}
	}
	return 0;
}
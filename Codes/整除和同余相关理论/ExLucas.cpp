#include<iostream>
#include<cstdio>
#include<cstdlib>

using LL = long long;
using namespace std;

LL n, m, p;

inline LL Get(LL k, LL p) { if(k >= p) k -= p; return k; }

inline void Exgcd(LL a, LL b, LL &x, LL &y)
{
	if(b == 0LL) return x = 1LL, y = 0LL, void();
	Exgcd(b, a % b, y, x);
	return y -= a / b * x, void();
}

inline LL Pow(LL a, LL b, LL p)
{
	LL res = 1LL;
	while(b)
	{
		if(b & 1) res = res * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return res;
}

inline LL Fac(LL k, LL pi, LL pk)
{
	if(!k) return 1LL;
	LL res = 1LL;
	for(register LL i = 2LL; i <= pk; i++) if(i % pi) res = res * i % pk;
	res = Pow(res, k / pk, pk);
	for(register LL i = 2LL; i <= k % pk; i++) if(i % pi) res = res * i % pk;
	return res * Fac(k / pi, pi, pk) % pk; 
}

inline LL Inv(LL k, LL p)
{
	LL x, y; Exgcd(k, p, x, y);
	return Get(x % p + p, p);
}

inline LL CRT(LL k, LL t) { return k * (p / t) % p * Inv(p / t, t) % p; }

inline LL C(LL n, LL m, LL pi, LL pk)
{
	LL v1 = Fac(n, pi, pk), v2 = Fac(m, pi, pk), v3 = Fac(n - m, pi, pk);
	LL k = 0LL;
	for(register LL i = n; i; i /= pi) k += i / pi;
	for(register LL i = m; i; i /= pi) k -= i / pi;
	for(register LL i = n - m; i; i /= pi) k -= i / pi;
	return v1 * Inv(v2, pk) % pk * Inv(v3, pk) % pk * Pow(pi, k, pk) % pk;
}

inline LL ExLucas(LL n, LL m, LL p)
{
	LL ans = 0LL, t = p, pt = 1;
	for(register int i = 2; i * i <= p; i++) if(t % i == 0)
	{
		while(t % i == 0) pt *= i, t /= i;
		ans = Get(ans + CRT(C(n, m, i, pt), pt), p);
		pt = 1;
	}
	if(t > 1) ans = Get(ans + CRT(C(n, m, t, t), t), p);
	return ans;
}

int main()
{
	scanf("%lld%lld%lld", &n, &m, &p);
	printf("%lld\n", ExLucas(n, m, p));
	return 0;
}
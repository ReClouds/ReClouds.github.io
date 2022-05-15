#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<map>

using namespace std;

int a, p, b;
map<int, int> Hash;

inline int Read()
{
	int v = 0; char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) v = (v << 3) + (v << 1) + c - '0', c = getchar();
	return v;
}

inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

inline void Exgcd(int a, int b, int &x, int &y)
{
	if(b == 0) return x = 1, y = 0, void();
	Exgcd(b, a % b, y, x);
	return y -= a / b * x, void();
}

inline int Inv(int a, int b)
{
	int x, y; Exgcd(a, b, x, y);
	return ((x % b) + b) % b;
}

inline int Pow(int a, int b, int p)
{
	int res = 1;
	while(b)
	{
		if(b & 1) res = 1LL * res * a % p;
		a = 1LL * a * a % p;
		b >>= 1;
	}
	return res;
}

inline int BSGS(int a, int b, int p)
{
	Hash.clear(), b %= p;
	int t = (int)(sqrt(p) + 1), w = 1;
	for(register int i = 0; i < t; i++)
	{
		int val = 1LL * b * w % p;
		Hash[val] = i;
		w = 1LL * w * a % p;
	}
	int val = 1; a = Pow(a, t, p), val = 1;
	if(!a) return b ? -1 : 1;
	for(register int i = 1; i <= t; i++)
	{
		val = 1LL * val * a % p;
		int j = Hash.find(val) == Hash.end() ? -1 : Hash[val]; 
		if((~j) && i * t - j >= 0) return i * t - j;
	}
	return -1;
}

inline int ExBSGS(int a, int b, int p)
{
	if(b == 1 || p == 1) return 0;
	int g = gcd(a, p), k = 0, q = 1;
	while(g ^ 1)
	{
		if(b % g) return -1;
		++k; b /= g, p /= g;
		q = 1LL * q * (a / g) % p;
		if(q == b) return k;
		g = gcd(a, p);
	}
	int res = BSGS(a, 1LL * b * Inv(q, p) % p, p);
	return (~res) ? res + k : res;
}

int main()
{
	a = Read(), p = Read(), b = Read();
	while(a || p || b)
	{
		a %= p, b %= p;
		int ans = ExBSGS(a, b, p);
		if(ans == -1) puts("No Solution");
		else printf("%d\n", ans);
		a = Read(), p = Read(), b = Read();
	}
	return 0;
}
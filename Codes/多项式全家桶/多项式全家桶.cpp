#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<ctime>
#include<algorithm>
#include<complex>

using namespace std;

namespace Quadratic_Residue
{
	#define MOD 998244353
	
	int si;

	struct Complex_MOD
	{
		int a, b;

		Complex_MOD operator * (const Complex_MOD &t) const
		{
			Complex_MOD res;
			res.a = (1LL * a * t.a % MOD + 1LL * b * t.b % MOD * si % MOD) % MOD;
			res.b = (1LL * a * t.b % MOD + 1LL * b * t.a % MOD) % MOD;
			return res;
		}
	};

	inline int Pow_Real(int a, int b)
	{
		int res = 1;
		while(b)
		{
			if(b & 1) res = 1LL * res * a % MOD;
			a = 1LL * a * a % MOD;
			b >>= 1;
		}
		return res;
	}

	inline int Pow_Complex(Complex_MOD val, int t)
	{
		Complex_MOD res;
		res.a = 1, res.b = 0;
		while(t)
		{
			if(t & 1) res = res * val;
			val = val * val;
			t >>= 1;
		}
		return res.a;
	}

	inline int Solve(int n)
	{
		if(n == 0) return 0;
		srand((unsigned)(time(NULL)));
		int p1, p2;
		while(true)
		{
			p1 = 1LL * rand() * rand() % MOD;
			p2 = (1LL * p1 * p1 % MOD - n + MOD) % MOD;
			if(Pow_Real(p2, (MOD - 1) / 2) != 1) break;
		}
		si = p2;
		Complex_MOD val;
		val.a = p1, val.b = 1;
		int ans = Pow_Complex(val, (MOD + 1) / 2);
		if(MOD - ans < ans) ans = MOD - ans;
		return ans;
	}

	#undef MOD
}

namespace Polynomial
{
	#define MAXN 5000005
	#define MOD 998244353
	#define Min_G 3
	#define Inv_Min_G 332748118
	#define BASE 15
	#define MAXM (1 << 15)

	typedef complex<double> complex;

	int n, f[MAXN], g[MAXN], t[MAXN], h[MAXN], s[MAXN], r[MAXN], u[MAXN];
	int p, q, rev[MAXN], seq[3][MAXN];
	complex wn[MAXN], f0[MAXN], f1[MAXN], g0[MAXN], g1[MAXN], c[MAXN], v[MAXN];
	const double PI = acos(-1.0);
	const complex I(0, 1); 

	struct Point { int xi, yi; } pt[MAXN];

	inline int Get_MOD(int k, int p = MOD) { if(k >= p) k -= p; return k; }

	inline int Get_Int(complex k, int p)
	{
		double t = k.real();
		return t < 0 ? (long long)(t - 0.5) % p : (long long)(t + 0.5) % p;
	}

	inline void Read_Get_MOD(int &k1, int &k2, int &k3)
	{
		k1 = k2 = k3 = 0;
		char c = getchar();
		while(!isdigit(c)) c = getchar();
		while(isdigit(c))
		{
			k1 = (10LL * k1 + (c - '0')) % MOD; 
			k2 = (10LL * k2 + (c - '0')) % (MOD - 1);
			if(k3 < n) k3 = 10 * k3 + (c - '0'); 
			c = getchar();
		}
		return;
	}

	inline int Pow(int a, int b)
	{
		int res = 1;
		while(b)
		{
			if(b & 1) res = 1LL * res * a % MOD;
			a = 1LL * a * a % MOD;
			b >>= 1;
		}
		return res;
	}

	inline int Lagrange_Interpolation(Point *p, int n, int k)
	{
		int ans = 0;
		for(register int i = 1; i <= n; i++)
		{
			int mul = p[i].yi, inv = 1;
			for(register int j = 1; j <= n; j++)
			{
				if(i == j) continue;
				mul = 1LL * mul * Get_MOD(k - p[j].xi + MOD) % MOD;
				inv = 1LL * inv * Get_MOD(p[i].xi - p[j].xi + MOD) % MOD;
			}
			ans = Get_MOD(ans + 1LL * mul * Pow(inv, MOD - 2) % MOD);
		}
		return ans;
	}

	inline void Init(int n)
	{
		p = 1, q = -1;
		while(p < n) p <<= 1, ++q;  
		for(register int i = 0; i < p; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << q);
		return;
	}

	inline void Get_Operation_Sequence(int n, int *seq)
	{
		seq[0] = 0;
		while(n != 1)
		{
			seq[++seq[0]] = n;
			n = (n + 1) >> 1;
		}
		seq[++seq[0]] = 1;
		return;
	}

	inline void Get_Derivative(int *f, int *g, int n)
	{
		for(register int i = 1; i < n; i++)
			g[i - 1] = 1LL * i * f[i] % MOD;
		return g[n - 1] = 0, void();
	}

	inline void Get_Integral(int *f, int *g, int n)
	{
		for(register int i = n - 1; i >= 1; i--)
			g[i] = 1LL * f[i - 1] * Pow(i, MOD - 2) % MOD;
		return g[0] = 0, void();
	}

	inline void FFT(complex *f, int n, double t = 1)
	{
		if(t == -1) for(register int i = 1; i < n; i++) if(i < n - i) swap(f[i], f[n - i]);
		for(register int i = 0; i < n; i++) if(i < rev[i]) swap(f[i], f[rev[i]]);
		for(register int len = 2; len <= n; len <<= 1)
		{
	   	    int k = len >> 1;
			for(register int i = 0; i < n; i += len)
			{
				for(register int j = 0; j < k; j++)
				{
					complex u = f[i + j], v = wn[n / k * j] * f[i + j + k];
					f[i + j] = u + v;
					f[i + j + k] = u - v;
				}
			}
		}
  	  	if(t == -1) for(register int i = 0; i < n; i++) f[i] /= n;
		return;
	}

	inline void NTT(int *f, int n, bool Inverse = false)
	{
		for(register int i = 0; i < n; i++) if(i < rev[i]) swap(f[i], f[rev[i]]);
		for(register int len = 2; len <= n; len <<= 1)
		{
			int k = (len >> 1), g = Pow(Inverse ? Inv_Min_G : Min_G, (MOD - 1) / len);
			for(register int i = 0; i < n; i += len)
			{
				int w = 1;
				for(register int j = 0; j < k; j++)
				{
					int u = f[i + j], v = 1LL * w * f[i + j + k] % MOD;
					f[i + j] = Get_MOD(u + v);
					f[i + j + k] = Get_MOD(u - v + MOD); 
					w = 1LL * w * g % MOD;
				}
			}
		}
		if(Inverse) 
		{
			int Inv_N = Pow(n, MOD - 2);
			for(register int i = 0; i < n; i++) f[i] = 1LL * f[i] * Inv_N % MOD;
		}
		return;
	}

	inline void Separate(int *f, int n, complex *f0, complex *f1)
	{
		for(register int i = 0; i <= n; i++)
		{
			f0[i] = f[i] & (MAXM - 1);
			f1[i] = f[i] >> BASE;
		}
		return;
	}

	inline void Double_FFT(complex *f0, complex *f1, int n)
	{
		for(register int i = 0; i < p; i++) f0[i] = f0[i] + I * f1[i];
		FFT(f0, p);
		for(register int i = 0; i < p; i++) f1[i] = conj(f0[i ? p - i : 0]);
		for(register int i = 0; i < p; i++)
		{
			complex u = f0[i], v = f1[i];
			f0[i] = (u + v) * 0.5;
			f1[i] = (v - u) * 0.5 * I;
		}
		return;
	}

	inline void MTT(int *f, int n, int *g, int m, int *h, int tm)
	{
		Init(n + m + 1);
		for(register int i = 0; i < p; i++) wn[i] = complex(cos(PI / p * i), sin(PI / p * i));
		Separate(f, n, f0, f1), Separate(g, m, g0, g1), Double_FFT(f0, f1, n), Double_FFT(g0, g1, m);
		for(register int i = 0; i < p; i++)
		{
			c[i] = f1[i] * g1[i] + I * f0[i] * g0[i];
			v[i] = f0[i] * g1[i] + I * f1[i] * g0[i];
		}
		FFT(c, p, -1), FFT(v, p, -1);
		for(register int i = 0; i <= n + m; i++)
		{
			h[i] = Get_MOD(h[i] + Get_MOD(1LL * MAXM * MAXM % tm * Get_Int(c[i].real(), tm) % tm + Get_Int(c[i].imag(), tm), tm), tm);
			h[i] = Get_MOD(h[i] + 1LL * MAXM * Get_MOD(Get_Int(v[i].real(), tm) + Get_Int(v[i].imag(), tm), tm) % tm, tm);
		}
		return;
	}

	inline void Get_Inverse_Element(int *f, int *g, int n)
	{
		Get_Operation_Sequence(n, seq[0]);
		for(register int k = seq[0][0]; k >= 1; k--)
		{
			int m = seq[0][k];
			if(m == 1)
			{
				g[0] = Pow(f[0], MOD - 2);
				continue;
			}
			Init(m << 1);
			memcpy(t, f, sizeof(int) * m);
			fill(t + m, t + p, 0);
			NTT(t, p), NTT(g, p);
			for(register int i = 0; i < p; i++) g[i] = 1LL * g[i] * Get_MOD(2LL - 1LL * t[i] * g[i] % MOD + MOD) % MOD;
			NTT(g, p, true), fill(g + m, g + p, 0);
			continue;
		}
		return;
	}
	
	inline void Multiply(int *f, int n, int *g, int m, int *v)
	{
		Init(n + m - 1);
		memcpy(h, f, sizeof(int) * n), fill(h + n, h + p, 0);
		memcpy(s, g, sizeof(int) * m), fill(s + m, s + p, 0);
		NTT(h, p), NTT(s, p);
		for(register int i = 0; i < p; i++) v[i] = 1LL * h[i] * s[i] % MOD;
		return NTT(v, p, true), fill(v + n + m - 1, v + p, 0), void();
	}

	inline void Divide(int *f, int n, int *g, int m, int *v)
	{
		memcpy(s, g, sizeof(int) * m);
		reverse(s, s + m);
		Get_Inverse_Element(s, r, n - m + 1);
		memcpy(t, f, sizeof(int) * n);
		reverse(t, t + n);
		Multiply(t, n, r, n - m + 1, v);
		return reverse(v, v + n - m + 1);
	}

	inline void Get_Remainder(int *f, int n, int *g, int m, int *v, int *x)
	{
		Multiply(g, m, v, n - m + 1, x);
		for(register int i = 0; i < m; i++) x[i] = Get_MOD(f[i] - x[i] + MOD);
		return;
	}

	inline void Get_Sqrt(int *f, int *g, int n)
	{
		Get_Operation_Sequence(n, seq[1]);
		for(register int k = seq[1][0]; k >= 1; k--)
		{
			int m = seq[1][k];
			if(m == 1)
			{
				g[0] = Quadratic_Residue :: Solve(f[0]);
				continue;
			}
			Init(m << 1);
			memset(h, 0, sizeof(int) * p);
			Get_Inverse_Element(g, h, m);
			memcpy(s, f, sizeof(int) * m);
			fill(s + m, s + p, 0);
			NTT(g, p), NTT(h, p), NTT(s, p);
			int Inv2 = Pow(2, MOD - 2);
			for(register int i = 0; i < p; i++) g[i] = 1LL * Inv2 * Get_MOD(g[i] + 1LL * h[i] * s[i] % MOD) % MOD;
			NTT(g, p, true), fill(g + m, g + p, 0);
			continue;
		}
		return;
	}

	inline void Get_Ln(int *f, int *g, int n)
	{
		Get_Inverse_Element(f, g, n);
		memset(t, 0, sizeof(int) * p);
		Get_Derivative(f, t, n);
		NTT(g, p), NTT(t, p);
		for(register int i = 0; i < p; i++) g[i] = 1LL * g[i] * t[i] % MOD;
		return NTT(g, p, true), Get_Integral(g, g, n), void();
	}

	inline void Get_Exp(int *f, int *g, int n)
	{
		Get_Operation_Sequence(n, seq[2]);
		for(register int k = seq[2][0]; k >= 1; k--)
		{
			int m = seq[2][k];
			if(m == 1)
			{
				g[0] = 1;
				continue;
			}
			Get_Ln(g, h, m);
			Init(m << 1);
			fill(h + m, h + p, 0);
			memcpy(s, f, sizeof(int) * m);
			fill(s + m, s + p, 0);
			NTT(g, p), NTT(h, p), NTT(s, p);
			for(register int i = 0; i < p; i++) g[i] = 1LL * g[i] * Get_MOD(Get_MOD(1LL - h[i] + MOD) + s[i]) % MOD;
			NTT(g, p, true), fill(g + m, g + p, 0), memset(h, 0, sizeof(int) * p);
		}
		return;
	}

	inline void Get_Quick_Pow(int *f, int *g, int n, int k1, int k2)
	{
		int st = 0;
		while(st < n && f[st] == 0) ++st;
		if(st == n || 1LL * st * k1 > n)
		{
			for(register int i = 0; i < n; i++) putchar('0'), putchar(' ');
			putchar('\n');
			return;
		}
		int inv = Pow(f[st], MOD - 2), mul = Pow(f[st], k2);
		for(register int i = 0; i < n; i++) f[i] = 1LL * f[i + st] * inv % MOD;
		Get_Ln(f, r, n);
		for(register int i = 0; i < p; i++) r[i] = 1LL * r[i] * k1 % MOD;
		Get_Exp(r, g, n);
		int tk = st * k1;
		for(register int i = 0; i < tk; i++) putchar('0'), putchar(' ');
		for(register int i = tk; i < n; i++) printf("%lld ", 1LL * g[i - tk] * mul % MOD);
		putchar('\n');
		return;
	}

	inline void Run()
	{
		/*
		 * You wanna do something here?
		 */
	}

	#undef MAXN
	#undef MOD
	#undef Min_G
	#undef Inv_Min_G
	#undef BASE
	#undef MAXM
}

int main()
{
	Polynomial :: Run();
	return 0;
}

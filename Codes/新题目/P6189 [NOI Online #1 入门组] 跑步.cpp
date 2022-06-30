#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>

using namespace std;

namespace IO
{
    int f, c;

    template<typename T> inline void _Read(T &k)
    {
        k = 0, f = 1, c = getchar();
        while(!isdigit(c))
        {
            if(c == '-') f = -1;
            c = getchar();
        }
        while(isdigit(c))
        {
            k = (k << 3) + (k << 1) + c - '0';
            c = getchar();
        }
        return k *= f, void();
    }

    template<typename T> inline void _Write(T k)
    {
        if(k < 0) putchar('-'), k = -k;
        if(k > 9) _Write(k / 10);
        return putchar(k % 10 + '0'), void();
    }

    inline int Read32() { int k; _Read(k); return k; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write32;

namespace Program
{
    const int MAXN = 100005;
	const int MAXM = 405;

    int n, p, s, f[MAXN][MAXM], a[MAXN], b[MAXN], ans;

	inline int Get_MOD(int k) { return k - (k >= p) * p; }

    inline int Run()
    {
        n = Read32(), p = Read32(), s = (int)(sqrt(n));
		for(register int i = 0; i <= s; i++) f[0][i] = 1;
		a[0] = 1;
		for(register int i = 1; i <= n; i++)
		{
			for(register int j = 1; j <= s; j++)
			{
				f[i][j] = f[i][j - 1];
				if(i >= j) f[i][j] = Get_MOD(f[i][j] + f[i - j][j]);
				if(j == s) a[i] = f[i][j];
			}
		}
		memset(f, 0, sizeof f);
		int c = (n - 1) / (s + 1) + 1;
		f[s + 1][1] = 1, b[0] = 1;
		for(register int i = 0; i <= n; i++)
		{
			for(register int j = 1; j <= c; j++)
			{
				if(i >= s + 1) f[i][j] = Get_MOD(f[i][j] + f[i - s - 1][j - 1]);
				if(i >= j) f[i][j] = Get_MOD(f[i][j] + f[i - j][j]);
			}
		}
		for(register int i = 1; i <= n; i++) for(register int j = 1; j <= c; j++) b[i] = Get_MOD(b[i] + f[i][j]);
		ans = 0;
		for(register int i = 0; i <= n; i++) ans = Get_MOD(ans + 1LL * a[i] * b[n - i] % p);
        return Write32(ans), 0;
    }
}

int main() { return Program :: Run(); }
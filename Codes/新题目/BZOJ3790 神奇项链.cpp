#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

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
	const int MAXN = 200005;

	int n, tot, p[MAXN];
	char t[MAXN], s[MAXN];

	struct Segment
	{
		int l, r;
		bool operator < (const Segment &t) const { return l == t.l ? r < t.r : l < t.l; }
	} seg[MAXN];

	inline void Manacher()
	{
		tot = 0, memset(p, 0, sizeof p);
		for(register int i = 1, mid = 0, r = 0; i <= n; i++)
        {
            if(i <= r) p[i] = min(p[(mid << 1) - i], r - i + 1);
            while(s[i - p[i]] == s[i + p[i]]) ++p[i];
            if(i + p[i] - 1 > r) mid = i, r = i + p[i] - 1;
			seg[++tot] = (Segment){i - p[i] + 1, i + p[i] - 1};
        }
		return;
	}

    inline int Run()
    {
        while(~scanf("%s", t + 1))
		{
			n = strlen(t + 1);
			for(register int i = 1; i <= n; i++)
			{
				s[i << 1] = t[i];
				s[(i << 1) - 1] = '#';
			}
			n = (n << 1 | 1);
			s[n] = '#';
			s[0] = '<', s[n + 1] = '>';
			Manacher();
			sort(seg + 1, seg + tot + 1);
			int r = 1, p = 1, res = 0;
			while(r < n)
			{
				int mx = 0;
				while(p <= tot && seg[p].l <= r) mx = max(mx, seg[p].r), ++p;
				r = mx, ++res;
			}
			Write32(res - 1);
		}
		return 0;
    }
}

int main() { return Program :: Run(); }
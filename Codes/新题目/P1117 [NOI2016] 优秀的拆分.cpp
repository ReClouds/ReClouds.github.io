#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>

#define i64 long long

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
    inline i64 Read64() { i64 k; _Read(k); return k; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Read64;
using IO :: Write32;
using IO :: Write64;

namespace Program
{
	const int MAXN = 200005;
	const int MAXLOG = 18;

	int t, n, pre[MAXN], suf[MAXN];

	struct String
	{
		int sa[MAXN], rk[MAXN], trk[MAXN], cnt[MAXN], id[MAXN], rkid[MAXN], ht[MAXN], st[MAXN][MAXLOG];
		char s[MAXN];

		inline bool Compare(int u, int v, int w) { return trk[u] != trk[v] || trk[u + w] != trk[v + w]; }

        inline void Get_Suffix_Array()
        {
			memset(sa, 0, sizeof sa), memset(cnt, 0, sizeof cnt), memset(rk, 0, sizeof rk), memset(trk, 0, sizeof trk), memset(id, 0, sizeof id), memset(rkid, 0, sizeof rkid);
            int m = 26;
            for(register int i = 1; i <= n; i++) ++cnt[rk[i] = s[i] - 'a' + 1];
            for(register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for(register int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
            int w = 1;
            while(true)
            {
                int p = 0;
                for(register int i = n; i > n - w; i--) id[++p] = i;
                for(register int i = 1; i <= n; i++) if(sa[i] > w) id[++p] = sa[i] - w;
                memset(cnt, 0, sizeof cnt);
                for(register int i = 1; i <= n; i++) ++cnt[rkid[i] = rk[id[i]]];
                for(register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
                for(register int i = n; i >= 1; i--) sa[cnt[rkid[i]]--] = id[i];
                swap(rk, trk), m = 0;
                for(register int i = 1; i <= n; i++) rk[sa[i]] = (m += Compare(sa[i], sa[i - 1], w));
                if(n == m) break;
                w <<= 1;
            }
            return;
        }

        inline void Get_Height()
        {
            memset(ht, 0, sizeof ht);
            for(register int i = 1, k = 0; i <= n; i++)
            {
                if(rk[i] == 1) continue;
                if(k) --k;
                while(i + k <= n && sa[rk[i] - 1] + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
                ht[rk[i]] = k;
            }
            return;
        }

		inline void ST_Init()
		{
			memset(st, 0x3F, sizeof st);
			for(register int i = 1; i <= n; i++) st[i][0] = ht[i];
			for(register int j = 1; j < MAXLOG; j++)
				for(register int i = 1; i <= n; i++)
					st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			return;
		}

		inline int LCP(int l, int r)
		{
			if(l < 0 || l > n || r < 0 || r > n) return 0;
            int rkl = rk[l], rkr = rk[r];
			l = min(rkl, rkr) + 1, r = max(rkl, rkr);
			int k = (int)log2(r - l + 1);
			return min(st[l][k], st[r - (1 << k) + 1][k]);
		}
	} a, b;

    inline int Run()
    {
		t = Read32();
		while(t--)
		{
			scanf("%s", a.s + 1), n = strlen(a.s + 1);
			for(register int i = 1; i <= n; i++) b.s[i] = a.s[n - i + 1];
			a.Get_Suffix_Array(), a.Get_Height(), a.ST_Init();
			b.Get_Suffix_Array(), b.Get_Height(), b.ST_Init();
			memset(pre, 0, sizeof pre), memset(suf, 0, sizeof suf);
			for(register int len = 1; len <= n / 2; len++)
			{
				for(register int i = len; i + len <= n; i += len)
				{
					int l = i, r = i + len;
					int lcp = min(len, a.LCP(l, r));
					l = n - (l - 1) + 1, r = n - (r - 1) + 1;
					int lcs = min(len - 1, b.LCP(l, r));
                    l = i, r = i + len;
					int cov = lcp + lcs - len + 1;
					if(cov > 0)
					{
						++pre[r + lcp - cov], --pre[r + lcp];
						++suf[l - lcs], --suf[l - lcs + cov];
					}
				}
			}
			for(register int i = 1; i <= n; i++) pre[i] += pre[i - 1], suf[i] += suf[i - 1];
			i64 ans = 0;
			for(register int i = 1; i < n; i++) ans += 1LL * pre[i] * suf[i + 1];
			Write64(ans);
		}
        return 0;
    }
}

int main() { return Program :: Run(); }
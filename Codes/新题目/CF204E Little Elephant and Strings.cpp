#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<cmath>

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
    const int MAXLOG = 19;

    int n, k, m, len, s[MAXN], r[MAXN][2], in[MAXN], nw, c[MAXN], ed[MAXN], q[MAXN << 1], tot, seg[MAXN << 1][2];
    i64 ans[MAXN], val[MAXN << 1];
    char a[MAXN];

    namespace Suffix_Array
    {
        int sa[MAXN], rk[MAXN], trk[MAXN], cnt[MAXN], id[MAXN], rkid[MAXN], ht[MAXN], st[MAXN][MAXLOG];

		inline bool Compare(int u, int v, int w) { return trk[u] != trk[v] || trk[min(u + w, len + 1)] != trk[min(v + w, len + 1)]; }

        inline void Get_Suffix_Array()
        {
            for(register int i = 1; i <= len; i++) ++cnt[rk[i] = s[i]];
            for(register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for(register int i = len; i >= 1; i--) sa[cnt[rk[i]]--] = i;
            int w = 1;
            while(true)
            {
                int p = 0;
                for(register int i = len; i > len - w; i--) id[++p] = i;
                for(register int i = 1; i <= len; i++) if(sa[i] > w) id[++p] = sa[i] - w;
                memset(cnt, 0, sizeof cnt);
                for(register int i = 1; i <= len; i++) ++cnt[rkid[i] = rk[id[i]]];
                for(register int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
                for(register int i = len; i >= 1; i--) sa[cnt[rkid[i]]--] = id[i];
                swap(rk, trk), m = 0;
                for(register int i = 1; i <= len; i++) rk[sa[i]] = (m += Compare(sa[i], sa[i - 1], w));
                if(len == m) break;
                w <<= 1;
            }
            return;
        }

        inline void Get_Height()
        {
            for(register int i = 1, k = 0; i <= len; i++)
            {
                if(rk[i] == 1) continue;
                if(k) --k;
                while(i + k <= len && sa[rk[i] - 1] + k <= len && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
                ht[rk[i]] = k;
            }
            return;
        }

        inline void ST_Init()
		{
			memset(st, 0x3F, sizeof st);
			for(register int i = 1; i <= len; i++) st[i][0] = ht[i];
			for(register int j = 1; j < MAXLOG; j++)
				for(register int i = 1; i <= len; i++)
					st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			return;
		}

		inline int LCP(int l, int r)
		{
			if(l < 0 || l > len || r < 0 || r > len) return 0;
            int rkl = rk[l], rkr = rk[r];
			l = min(rkl, rkr) + 1, r = max(rkl, rkr);
			int k = (int)log2(r - l + 1);
			return min(st[l][k], st[r - (1 << k) + 1][k]);
		}
    }

    using namespace Suffix_Array;

    inline int Run()
    {
        n = Read32(), k = Read32(), m = 26;
        for(register int i = 1; i <= n; i++)
        {
            scanf("%s", a + 1);
            int t = strlen(a + 1);
            for(register int j = len + 1; j <= len + t; j++) s[j] = (int)(a[j - len] - 'a' + 1), in[j] = i;
            r[i][0] = len + 1, r[i][1] = len + t;
            len += t + 1, s[len] = ++m;
            if(k == 1) Write64(1LL * t * (t + 1) >> 1, " \n"[i == n]);
        }
        if(k == 1) return 0;
        Get_Suffix_Array(), Get_Height(), ST_Init();
        for(register int i = 1, p = 1; i <= len - n; i++)
        {
            if(!c[in[sa[i]]]) ++nw;
            ++c[in[sa[i]]];
            while(nw >= k)
            {
                if(nw == k) ++tot, seg[tot][0] = p, seg[tot][1] = i, val[tot] = LCP(sa[p], sa[i]);
                if(c[in[sa[p]]] == 1)
                {
                    if(nw == k) break;
                    --nw;
                }
                --c[in[sa[p]]], ++p;
            }
        }
        int l = 1, r = 0, p = 0;
        for(register int i = 1; i <= len - n; i++)
        {
            while(l <= r && seg[q[l]][1] < i) ++l;
            while(p <= tot && seg[p][0] <= i)
            {
                while(l <= r && val[p] >= val[q[r]]) --r;
                q[++r] = p++;
            }
            if(l <= r) ans[in[sa[i]]] += val[q[l]];
        }
        for(register int i = 1; i <= n; i++) Write64(ans[i], " \n"[i == n]);
        return 0;
    }
}

int main() { return Program :: Run(); }
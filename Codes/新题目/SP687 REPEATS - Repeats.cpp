#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<cmath>
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
    inline char Read_Char() { char c = getchar(); while(c != 'a' && c != 'b') c = getchar(); return c; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Read_Char;
using IO :: Write32;

namespace Program
{
    const int MAXN = 200005;
    const int MAXLOG = 17;

    int t, n, ans;

    struct String
    {
        int m, s[MAXN], sa[MAXN], rk[MAXN], trk[MAXN], cnt[MAXN], id[MAXN], rkid[MAXN], ht[MAXN], st[MAXN][MAXLOG];

        inline void Clear()
        {
            memset(sa, 0, sizeof sa);
            memset(rk, 0, sizeof rk);
            memset(trk, 0, sizeof trk);
            memset(cnt, 0, sizeof cnt);
            memset(id, 0, sizeof id);
            memset(rkid, 0, sizeof rkid);
            memset(ht, 0, sizeof ht);
            memset(st, 0x3F, sizeof st);
            return;
        }

        inline bool Compare(int u, int v, int w) { return (trk[u] != trk[v]) || (trk[u + w] != trk[v + w]); }

        inline void Get_Suffix_Array()
        {
            m = 2;
            for(register int i = 1; i <= n; i++) ++cnt[rk[i] = s[i]];
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
                m = 0, swap(rk, trk);
                for(register int i = 1; i <= n; i++) rk[sa[i]] = (m += Compare(sa[i], sa[i - 1], w));
                if(m == n) break;
                w <<= 1;
            }
            return;
        }

        inline void Get_Height()
        {
            int k = 0;
            for(register int i = 1; i <= n; i++)
            {
                if(rk[i] == 1) continue;
                k = max(0, k - 1);
                while(i + k <= n && sa[rk[i] - 1] + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
                ht[rk[i]] = k;
            }
        }

        inline void ST_Init()
        {
            for(register int i = 1; i <= n; i++) st[i][0] = ht[i];
            for(register int j = 1; j < MAXLOG; j++)
                for(register int i = 1; i <= n; i++)
                    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            return;
        }

        inline int LCP(int l, int r)
        {
            if(l < 0 || l > n || r < 0 || r > n) return 0;
            if(rk[l] > rk[r]) swap(l, r);
            int rkl = rk[l] + 1, rkr = rk[r], k = (int)(log2(rkr - rkl + 1));
            return min(st[rkl][k], st[rkr - (1 << k) + 1][k]);
        }
    } s1, s2;

    inline int Run()
    {
        t = Read32();
        while(t--)
        {
            n = Read32();
            for(register int i = 1; i <= n; i++) s1.s[i] = (int)(Read_Char() - 'a' + 1), s2.s[n - i + 1] = s1.s[i];
            s1.Clear(), s1.Get_Suffix_Array(), s1.Get_Height(), s1.ST_Init();
            s2.Clear(), s2.Get_Suffix_Array(), s2.Get_Height(), s2.ST_Init();
            ans = 1;
            for(register int k = 1; k <= n / 2; k++)
            {
                for(register int i = k; i + k <= n; i += k)
                {
                    int l = i, r = i + k, lcp = s1.LCP(l, r), lcs = s2.LCP(n - (l - 1) + 1, n - (r - 1) + 1);
                    ans = max(ans, (lcp + lcs) / k + 1);
                }
            }
            Write32(ans);
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
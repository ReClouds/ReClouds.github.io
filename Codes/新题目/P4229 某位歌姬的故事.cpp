#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<vector>

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
    const int MAXN = 505;
    const int MOD = 998244353;

    int t, n, q, a, len, seq[MAXN << 1], ran[MAXN][2], m[MAXN], mx[MAXN << 1], p[MAXN], tot, pos[MAXN << 1], mxl[MAXN << 1], f[MAXN << 1][MAXN << 1], ans;
    vector<pair<int, int> > mi;

    inline int Get_MOD(int k) { return k - (k >= MOD) * MOD; }
    inline bool Compare(int u, int v) { return m[u] == m[v] ? u < v : m[u] < m[v]; }

    inline void Discretization()
    {
        sort(seq + 1, seq + len + 1), len = unique(seq + 1, seq + len + 1) - seq - 1;
        for(register int i = 1; i <= q; i++) ran[i][0] = lower_bound(seq + 1, seq + len + 1, ran[i][0]) - seq, ran[i][1] = lower_bound(seq + 1, seq + len + 1, ran[i][1]) - seq;
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

    inline int Size(int v) { return Get_MOD(seq[v + 1] - seq[v] + MOD); }
    inline int Count(int k, int v) { return Get_MOD(Pow(k, v) - Pow(k - 1, v) + MOD); }

    inline int Solve(int k, int l, int r)
    {
        tot = 0;
        for(register int i = 1; i <= len; i++) if(mx[i] == k) pos[++tot] = i;
        memset(mxl, 0, sizeof mxl);
        for(register int i = l; i <= r; i++)
        {
            int L = lower_bound(pos + 1, pos + tot + 1, ran[p[i]][0]) - pos, R = lower_bound(pos + 1, pos + tot + 1, ran[p[i]][1]) - 1 - pos;
            mxl[R] = max(mxl[R], L);
        }
        for(register int i = 1; i <= tot; i++) mxl[i] = max(mxl[i], mxl[i - 1]);
        f[0][0] = 1;
        for(register int i = 1; i <= tot; i++)
        {
            f[i][i] = 0;
            int eq = Count(k, Size(pos[i])), neq = Pow(k - 1, Size(pos[i]));
            for(register int j = 0; j < i; j++)
            {
                f[i][i] = Get_MOD(f[i][i] + 1LL * f[i - 1][j] * eq % MOD);
                if(mxl[i] <= j) f[i][j] = 1LL * f[i - 1][j] * neq % MOD; else f[i][j] = 0;
            }
        }
        int res = 0;
        for(register int i = 0; i <= tot; i++) res = Get_MOD(res + f[tot][i]);
        return res;
    }

    inline int Run()
    {
        t = Read32();
        while(t--)
        {
            n = Read32(), q = Read32(), a = Read32();
            len = 0, mi.clear();
            for(register int i = 1; i <= q; i++)
            {
                seq[++len] = ran[i][0] = Read32(), seq[++len] = ran[i][1] = Read32() + 1, m[i] = Read32();
                mi.push_back(make_pair(ran[i][0], 1)), mi.push_back(make_pair(ran[i][1], -1));
                p[i] = i;
            }
            Discretization();
            memset(mx, 0x3F, sizeof mx);
            for(register int i = 1; i <= q; i++) for(register int j = ran[i][0]; j != ran[i][1]; j++) mx[j] = min(mx[j], m[i]);
            bool f = true;
            for(register int i = 1; i <= q; i++)
            {
                f = false;
                for(register int j = ran[i][0]; j != ran[i][1]; j++) if(mx[j] == m[i]) { f = true; break; } 
                if(!f) break; else continue;
            }
            if(!f) { puts("0"); continue; }
            sort(p + 1, p + q + 1, Compare);
            ans = 1;
            for(register int l = 1, r = 1; l <= q; l = r + 1)
            {
                r = l;
                while(r + 1 <= q && m[p[l]] == m[p[r + 1]]) ++r;
                ans = 1LL * ans * Solve(m[p[l]], l, r) % MOD;
            }
            sort(mi.begin(), mi.end());
            int cur = 0, pre = 1;
            for(register int l = 0, r = 0; l < (int)(mi.size()); l = r + 1)
            {
                if(!cur) ans = 1LL * ans * Pow(a, mi[l].first - pre) % MOD;
                r = l, cur += mi[l].second;
                while(r + 1 < (int)(mi.size()) && mi[l].first == mi[r + 1].first) cur += mi[++r].second;
                pre = mi[l].first;
            }
            ans = 1LL * ans * Pow(a, n - pre + 1) % MOD;
            Write32(ans);
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
/*

                                                                 /@@@O
                                                              =@@@@@@@@@
                                                           ]/@@@@@@@@@@@
                                             ]]]]]/@@@@@@@@@@@@@@@@@@@@@
                       @@@@@\]]]]]]]]@@@@@@@@@@OO/          /@@@@@@@@@@@@
                      =@@@@@@@@@@O/[[                    [ @@@O[     O@@@\
                      =@@@@@@@@@@@]                     /@@/            \@\
                      =@@@@@      O@@@@\]]           /@@@[               \@@\
                      @@@@@             /@@@@@\    /@@[                    O@O
                     =@@ =@                  [\@@@@@\]                       @@O
                     @@/ O@                   /@@   [O@@@@\]                  =@@
                    /@   =@@               /@@/            @@@@@OO [            @@]
                   /@@    @@             @@@                     \@@@@O]         \@@
                   @@     @@         =O@@/                             \@@@@O/O    @@@\
                  @@      =@       /@@/                                      \@@@@@@@@@@@@
                =/@@      =@     @@@/                                             \@@@@@@@
                =@@       =@@ O@@O                                                  =@@@@@
                @@         @@@@[
              =/@O       O@@@
              =@@     \@@@ \@
              @@    @@@/   =@\
            =@@/[]@@@[     =@@
           /@@@@@@          @@
         /@@@@@@@           @@
         @@@@@@@            =@
          \@@@@@@\          =@
             @@@@@@@\       =@@
               @@\[@@@       @@
                =@@  \@@\    @@
                 =@@/  [@@@  @@
                  =@@\    =@@@@O
                    \@@     =@@@]                                                    /@@@O
                     \@@     =@@@@\                                                @@@@@@@
                      =@@     @@ [@@@                                        ]]@@@@@@@@@@@
                        @@    =@     @@\                              ]]@@@@@/[ /O@@@@[
                         \@@  =@\      \@@\                   \]@@@@@@O[       O@@[
                          =@@ /@@         @@O          ]/@@@@@@/[           /@@/
                           \@@@@@@          O@@]/O@@@@@/[                ]O@@/
                           =@@@@@@@@\]]]]\@@@@@@@O                     O@@
                           =@@@@@@@@@@@@@/       O@@\                @@@
                           =@@@@@@@@@@@@]          [@@\           /@@O
                            @@@@@@@@@@@@@@@@@@@O\]    \@@@O  ]]/@@@[
                              [@@/             [O@@@@@@@@@@@@@@@@/
                                                       \@@@@@@@@
                                                          \@@@@
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<set>

using i64 = long long;
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
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write64;

namespace Program
{
    const int MAXN = 100005;

    int n, m, a[MAXN], len, seq[MAXN << 1], pre[MAXN], cnt;

    struct Operation { int opt, l, r, k; } op[MAXN];
    struct Color_Segment { int l, r, c; Color_Segment(int _l = 0, int _r = 0, int _c = 0) : l(_l), r(_r), c(_c) {} bool operator < (const Color_Segment &t) const { return l < t.l; } }; set<Color_Segment> s, t[MAXN << 1];

    namespace Segment_Tree
    {
        #define ls (now << 1)
        #define rs (now << 1 | 1)
        #define mid ((l + r) >> 1)

        i64 sum[MAXN << 2], tag[MAXN << 2];

        inline void Pushup(int now) { return sum[now] = sum[ls] + sum[rs], void(); }
        inline void Pushtag(int now, int l, int r, i64 val) { return sum[now] += val * (r - l + 1), tag[now] += val, void(); }

        inline void Pushdown(int now, int l, int r)
        {
            if(!tag[now]) return;
            return Pushtag(ls, l, mid, tag[now]), Pushtag(rs, mid + 1, r, tag[now]), tag[now] = 0, void();
        }

        inline void Modify(int now, int l, int r, int L, int R, i64 val)
        {
            if(L <= l && r <= R) return Pushtag(now, l, r, val);
            Pushdown(now, l, r);
            if(L <= mid) Modify(ls, l, mid, L, R, val);
            if(R > mid) Modify(rs, mid + 1, r, L, R, val);
            return Pushup(now);
        }


        inline i64 Query(int now, int l, int r, int L, int R)
        {
            if(L <= l && r <= R) return sum[now];
            Pushdown(now, l, r); i64 res = 0;
            if(L <= mid) res += Query(ls, l, mid, L, R);
            if(R > mid) res += Query(rs, mid + 1, r, L, R);
            return res;
        }

        #undef ls
        #undef rs
        #undef mid
    }

    using namespace Segment_Tree;

    inline void Discretization()
    {
        sort(seq + 1, seq + len + 1);
        len = unique(seq + 1, seq + len + 1) - seq - 1;
        for(register int i = 1; i <= n; i++) a[i] = lower_bound(seq + 1, seq + len + 1, a[i]) - seq;
        for(register int i = 1; i <= m; i++) if(op[i].opt & 1) op[i].k = lower_bound(seq + 1, seq + len + 1, op[i].k) - seq;
        return;
    }

    inline void Modify_Subsegment(int l, int r, i64 val)
    {
        Modify(1, 1, n, l, l, val);
        if(r + 1 <= n) Modify(1, 1, n, r + 1, r + 1, -val);
        return;    
    }

    inline void Modify_Arithmetic_Sequence(int l, int r, i64 st, i64 di)
    {
        Modify_Subsegment(l, r, st - di);
        Modify(1, 1, n, l, r, di); if(r + 1 <= n) Modify(1, 1, n, r + 1, r + 1, di * (l - r - 1));
        return;
    }

    inline int Get_Pre(int pos)
    {
        auto in = s.lower_bound(Color_Segment(pos, 0, 0));
        int k = in -> c;
        if(t[k].empty()) return 0;
        in = t[k].lower_bound(Color_Segment(pos, 0, 0));
        return (in == t[k].begin() ? 0 : (--in) -> r);
    }

    inline void Modify_Color_Segment(int l, int r, i64 val)
    {
        int p = pre[l];
        Modify_Subsegment(1, n - p, 1 * val);
        Modify_Arithmetic_Sequence(1, n - l + 1, l * val, 1 * val); if(n - l + 2 <= n - p) Modify_Subsegment(n - l + 2, n - p, n * val);
        Modify_Subsegment(1, l - p, l * (-val)); if(l - p + 1 <= n - p) Modify_Arithmetic_Sequence(l - p + 1, n - p, (l + 1) * (-val), 1 * (-val));
        if(r - l > 0) Modify_Subsegment(1, n - r + 1, (r - l) * val); if(n - r + 2 <= n - l) Modify_Arithmetic_Sequence(n - r + 2, n - l, (r - l - 1) * val, 1 * (-val));
        return;
    }

    inline void Assign(int l, int r, int c)
    {
        auto st = s.lower_bound(Color_Segment(l, 0, 0)), ed = s.lower_bound(Color_Segment(r, 0, 0));
        if(st == s.end() || st -> l > l) --st; if(ed == s.end() || ed -> l > r) --ed;
        int L = st -> l, R = ed -> r, lc = st -> c, rc = ed -> c;
        for(auto it = st, nxt = st; ; it = nxt)
        {
            auto tmp = t[it -> c].lower_bound(Color_Segment(it -> l, it -> r, it -> c));
            if(tmp != (--t[it -> c].end()))
            {
                auto p = tmp, suf = tmp; ++suf;
                Modify_Color_Segment(suf -> l, suf -> r, -1);
                if(p != t[it -> c].begin()) pre[suf -> l] = (--p) -> r; else pre[suf -> l] = 0;
                Modify_Color_Segment(suf -> l, suf -> r, 1);
            }
            t[it -> c].erase(tmp);
            Modify_Color_Segment(it -> l, it -> r, -1), pre[it -> l] = 0;
            nxt = ++it; s.erase(--it);
            if(it == ed) break;
        }
        if(L != l)
        {
            s.insert(Color_Segment(L, l - 1, lc));
            auto tmp = t[lc].insert(Color_Segment(L, l - 1, lc)).first;
            pre[L] = Get_Pre(L), Modify_Color_Segment(L, l - 1, 1);
            if(tmp != (--t[lc].end()))
            {
                auto suf = tmp; ++suf;
                Modify_Color_Segment(suf -> l, suf -> r, -1);
                pre[suf -> l] = l - 1;
                Modify_Color_Segment(suf -> l, suf -> r, 1);
            }
        }
        s.insert(Color_Segment(l, r, c));
        auto tmp = t[c].insert(Color_Segment(l, r, c)).first;
        pre[l] = Get_Pre(l), Modify_Color_Segment(l, r, 1);
        if(tmp != (--t[c].end()))
        {
            auto suf = tmp; ++suf;
            Modify_Color_Segment(suf -> l, suf -> r, -1);
            pre[suf -> l] = r;
            Modify_Color_Segment(suf -> l, suf -> r, 1);
        }
        if(r != R)
        {
            s.insert(Color_Segment(r + 1, R, rc));
            auto tmp = t[rc].insert(Color_Segment(r + 1, R, rc)).first;
            pre[r + 1] = Get_Pre(r + 1), Modify_Color_Segment(r + 1, R, 1);
            if(tmp != (--t[rc].end()))
            {
                auto suf = tmp; ++suf;
                Modify_Color_Segment(suf -> l, suf -> r, -1);
                pre[suf -> l] = R;
                Modify_Color_Segment(suf -> l, suf -> r, 1);
            }
        }
        auto now = s.lower_bound(Color_Segment(l, 0, 0));
        set<Color_Segment> :: iterator lst = now;
        if(l != 1)
        {
            --lst;
            if(lst -> c == now -> c)
            {
                int tl = lst -> l, tr = now -> r; lc = lst -> c;
                t[lc].erase(t[lc].lower_bound(Color_Segment(lst -> l, 0, 0))), t[lc].erase(t[lc].lower_bound(Color_Segment(now -> l, 0, 0)));
                Modify_Color_Segment(lst -> l, lst -> r, -1), Modify_Color_Segment(now -> l, now -> r, -1), pre[now -> l] = 0;
                s.erase(lst), s.erase(now), now = s.insert(Color_Segment(tl, tr, lc)).first, t[lc].insert(Color_Segment(tl, tr, lc)), pre[lst -> l] = Get_Pre(lst -> l), Modify_Color_Segment(tl, tr, 1);
            }
        }
        set<Color_Segment> :: iterator nxt = now;
        if(r != n)
        {
            ++nxt;
            if(now -> c == nxt -> c)
            {
                int tl = now -> l, tr = nxt -> r; rc = nxt -> c;
                t[rc].erase(t[rc].lower_bound(Color_Segment(now -> l, 0, 0))), t[rc].erase(t[rc].lower_bound(Color_Segment(nxt -> l, 0, 0)));
                Modify_Color_Segment(now -> l, now -> r, -1), Modify_Color_Segment(nxt -> l, nxt -> r, -1), pre[nxt -> l] = 0;
                s.erase(now), s.erase(nxt), now = s.insert(Color_Segment(tl, tr, rc)).first, t[rc].insert(Color_Segment(tl, tr, rc)), pre[now -> l] = Get_Pre(now -> l), Modify_Color_Segment(tl, tr, 1);
            }
        }
        return;
    }

    namespace Segment_Tree_Color
    {
        #define ls (now << 1)
        #define rs (now << 1 | 1)
        #define mid ((l + r) >> 1)

        int col[MAXN], tag[MAXN << 2];

        inline void Pushtag(int now, int l, int r, int c)
        { 
            if(l == r) col[l] = c;
            else tag[now] = c;
            return;
        }

        inline void Pushdown(int now, int l, int r)
        {
            if(!tag[now]) return;
            Pushtag(ls, l, mid, tag[now]);
            Pushtag(rs, mid + 1, r, tag[now]);
            return tag[now] = 0, void();
        }

        inline void Modify(int now, int l, int r, int L, int R, int c)
        {
            if(L <= l && r <= R) return Pushtag(now, l, r, c);
            Pushdown(now, l, r);
            if(L <= mid) Modify(ls, l, mid, L, R, c);
            if(R > mid) Modify(rs, mid + 1, r, L, R, c);
            return;
        }

        inline void Transform(int now, int l, int r)
        {
            if(l == r) return a[l] = col[l], void();
            Pushdown(now, l, r);
            return Transform(ls, l, mid), Transform(rs, mid + 1, r);
        }

        #undef ls
        #undef rs
        #undef mid
    }

    namespace Subtask
    {
        const int MAXM = 1001;

        int cnt[MAXN];
        bool Flag = true;

        inline int Solve()
        {
            for(register int i = 1; i <= n; i++) Segment_Tree_Color :: Modify(1, 1, n, i, i, a[i]);
            for(register int i = 1; i <= m; i++)
            {
                if(op[i].opt & 1)
                {
                    Segment_Tree_Color :: Modify(1, 1, n, op[i].l, op[i].r, op[i].k);
                    continue;
                }
                else
                {
                    int k = op[i].k;
                    Segment_Tree_Color :: Transform(1, 1, n);
                    i64 ans = 0, now = 0;
                    for(register int i = 1; i <= n; i++)
                    {
                        now += (cnt[a[i]] == 0), ++cnt[a[i]];
                        if(i > k) now -= (cnt[a[i - k]] == 1), --cnt[a[i - k]];
                        if(i >= k) ans += now;
                    }
                    Write64(ans);
                    for(register int i = n; i > n - k; i--) --cnt[a[i]];
                }
            }
            return 0;
        }
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) a[i] = seq[++len] = Read32();
        for(register int i = 1; i <= m; i++)
        {
            op[i].opt = Read32();
            if(op[i].opt & 1) op[i].l = Read32(), op[i].r = Read32(), op[i].k = seq[++len] = Read32();
            else ++cnt, op[i].k = Read32();
        }
        if(cnt < Subtask :: MAXM) return Subtask :: Solve();
        Discretization();
        s.insert(Color_Segment(1, n, 0)), Modify_Color_Segment(1, n, 1), t[0].insert(Color_Segment(1, n, 0));
        int lst = 1;
        for(register int i = 1; i <= n; i++)
        {
            if(a[i] != a[lst])
            {
                Assign(lst, i - 1, a[lst]);
                lst = i;
            }
        }
        Assign(lst, n, a[lst]);
        for(register int i = 1; i <= m; i++)
        {
            if(op[i].opt & 1)
            {
                int l = op[i].l, r = op[i].r, c = op[i].k;
                Assign(l, r, c);
                continue;
            }
            else
            {
                int k = op[i].k;
                Write64(Query(1, 1, n, 1, k));
                continue;
            }
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
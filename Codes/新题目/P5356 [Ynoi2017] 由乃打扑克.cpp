#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<queue>

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
    const int MAXM = 605;
    const int INF = 0x7FFFFFFF;

    int n, m, s, mi, mx, a[MAXN], blen[MAXN];

    namespace Segment_Tree
    {
        #define ls (now << 1)
        #define rs (now << 1 | 1)
        #define mid ((l + r) >> 1)

        int cnt, d = 10, len[MAXM << 4], tag[MAXM << 4], bs[MAXM][MAXM], ans[MAXM];

        struct Position 
        { 
            int val, nl, nr;
            Position(int _val = 0, int _nl = 0 , int _nr = 0) : val(_val), nl(_nl), nr(_nr) {}
            bool operator < (const Position &t) const { return val < t.val; }
        } seq[MAXM << 4][MAXM];

        inline void Pushup(int now)
        {
            len[now] = 0, tag[now] = 0;
            int p = 1, q = 1, _p = p, _q = q;
            while(p <= len[ls] || q <= len[rs])
            {
                if(q > len[rs] || (p <= len[ls] && seq[ls][p].val + tag[ls] < seq[rs][q].val + tag[rs]))
                {
                    seq[now][++len[now]] = Position(seq[ls][p].val + tag[ls], _p, _q);
                    p = min(p + d, len[ls] + 1);
                    if(p == len[ls] + 1 || seq[ls][_p].val != seq[ls][p].val) _p = p;
                }
                else if(p > len[ls] || (q <= len[rs] && seq[rs][q].val + tag[rs] < seq[ls][p].val + tag[ls]))
                {
                    seq[now][++len[now]] = Position(seq[rs][q].val + tag[rs], _p, _q);
                    q = min(q + d, len[rs] + 1);
                    if(q == len[rs] + 1 || seq[rs][_q].val != seq[rs][q].val) _q = q;
                }
                else
                {
                    int tmp = seq[ls][p].val + tag[ls];
                    while(p <= len[ls] && seq[ls][p].val + tag[ls] == tmp)
                    {
                        seq[now][++len[now]] = Position(tmp, _p, _q);
                        p = min(p + d, len[ls] + 1);
                    }
                    while(q <= len[rs] && seq[rs][q].val + tag[rs] == tmp)
                    {
                        seq[now][++len[now]] = Position(tmp, _p, _q);
                        q = min(q + d, len[rs] + 1);
                    }
                    _p = p, _q = q;
                }
            }
            return;
        }

        inline void Build(int now, int l, int r)
        {
            if(l == r)
            {
                len[now] = blen[l];
                for(register int i = 1; i <= len[now]; i++) seq[now][i] = Position(bs[l][i], 0, 0);
                return;
            }
            return Build(ls, l, mid), Build(rs, mid + 1, r), Pushup(now);
        }

        inline void Maintain(int now, int l, int r, int pos)
        {
            if(l == r) 
            {
                tag[now] = 0;
                for(register int i = 1; i <= len[now]; i++) seq[now][i] = bs[l][i];
                return;
            }
            if(pos <= mid) Maintain(ls, l, mid, pos);
            else Maintain(rs, mid + 1, r, pos);
            return Pushup(now);
        }

        inline void Pushtag(int now, int l, int r, int L, int R, int k)
        {
            if(L <= l && r <= R) tag[now] += k;
            if(l == r) return;
            if(L <= mid) Pushtag(ls, l, mid, L, R, k);
            if(R > mid) Pushtag(rs, mid + 1, r, L, R, k);
            return;
        }

        inline void Modify(int now, int l, int r, int L, int R, int k)
        {
            if(L <= l && r <= R) return;
            if(L <= mid) Modify(ls, l, mid, L, R, k);
            if(R > mid) Modify(rs, mid + 1, r, L, R, k);
            return Pushup(now);
        }

        inline void Go(int now, int l, int r, int L, int R, int lst, int val)
        {
            if(r < L || R < l) return;
            while(lst > 1 && seq[now][lst - 1].val + tag[now] >= val) --lst;
            if(l == r) return ans[l] = lst - 1, void();
            Position res;
            if(lst <= len[now]) res = seq[now][lst];
            else res = Position(INF, len[ls] + 1, len[rs] + 1);
            return Go(ls, l, mid, L, R, res.nl, val), Go(rs, mid + 1, r, L, R, res.nr, val);
        }

        inline void Find(int L, int R, int val)
        {
            int now = 1, pos = lower_bound(seq[1] + 1, seq[1] + len[1] + 1, Position(val - tag[1], 0, 0)) - seq[1];
            Position res;
            if(pos <= len[1]) res = seq[1][pos];
            else res = Position(INF, len[ls] + 1, len[rs] + 1);
            int l = 1, r = cnt;
            Go(ls, l, mid, L, R, res.nl, val), Go(rs, mid + 1, cnt, L, R, res.nr, val);
            return;
        }

        #undef ls
        #undef rs
        #undef mid
    }

    namespace st = Segment_Tree;

    namespace Block
    {
        int cnt, in[MAXN], bl[MAXM], br[MAXM], len[MAXM], bmi[MAXN], bmx[MAXN], tag[MAXN];
        
        struct Position
        {
            int val, pos;
            Position(int _val = 0, int _pos = 0) : val(_val), pos(_pos) {}
            bool operator < (const Position &t) const { return val == t.val ? pos < t.pos : val < t.val; }
        } seq[MAXM][MAXM], s1[MAXM], s2[MAXM];

        inline void Build(int k)
        {
            for(register int i = bl[k]; i <= br[k]; i++) a[i] += tag[k];
            for(register int i = 1; i <= len[k]; i++) seq[k][i].val += tag[k];
            tag[k] = 0, bmi[k] = seq[k][1].val, bmx[k] = seq[k][len[k]].val;
            return;
        }

        inline void Modify(int l, int r, int k)
        {
            int p = in[l], q = in[r], len1 = 0, len2 = 0;
            if(p == q)
            {
                len1 = 0, len2 = 0;
                for(register int i = l; i <= r; i++) a[i] += k;
                for(register int i = 1; i <= len[p]; i++)
                {
                    if(l <= seq[p][i].pos && seq[p][i].pos <= r) s1[++len1] = Position(seq[p][i].val + k, seq[p][i].pos);
                    else s2[++len2] = seq[p][i];
                }
                int u = 1, v = 1, w = 1;
                while(w <= len[p])
                {
                    if(v > len2 || (u <= len1 && (s1[u] < s2[v]))) seq[p][w] = s1[u], ++u, ++w;
                    else seq[p][w] = s2[v], ++v, ++w;
                }
                Build(p);
                for(register int i = 1; i <= len[p]; i++) st :: bs[p][i] = seq[p][i].val;
                st :: Maintain(1, 1, cnt, p);
            }
            else
            {
                len1 = 0, len2 = 0;
                for(register int i = l; i <= br[p]; i++) a[i] += k;
                for(register int i = 1; i <= len[p]; i++)
                {
                    if(l <= seq[p][i].pos) s1[++len1] = Position(seq[p][i].val + k, seq[p][i].pos);
                    else s2[++len2] = seq[p][i];
                }
                int u = 1, v = 1, w = 1;
                while(w <= len[p])
                {
                    if(v > len2 || (u <= len1 && (s1[u] < s2[v]))) seq[p][w] = s1[u], ++u, ++w;
                    else seq[p][w] = s2[v], ++v, ++w;
                }
                Build(p);
                for(register int i = 1; i <= len[p]; i++) st :: bs[p][i] = seq[p][i].val;
                st :: Maintain(1, 1, cnt, p);
                len1 = 0, len2 = 0;
                for(register int i = bl[q]; i <= r; i++) a[i] += k;
                for(register int i = 1; i <= len[q]; i++)
                {
                    if(seq[q][i].pos <= r) s1[++len1] = Position(seq[q][i].val + k, seq[q][i].pos);
                    else s2[++len2] = seq[q][i];
                }
                u = 1, v = 1, w = 1;
                while(w <= len[q])
                {
                    if(v > len2 || (u <= len1 && (s1[u] < s2[v]))) seq[q][w] = s1[u], ++u, ++w;
                    else seq[q][w] = s2[v], ++v, ++w;
                }
                Build(q);
                for(register int i = 1; i <= len[q]; i++) st :: bs[q][i] = seq[q][i].val;
                st :: Maintain(1, 1, cnt, q);
                for(register int i = p + 1; i <= q - 1; i++) tag[i] += k, bmi[i] += k, bmx[i] += k;
                st :: Pushtag(1, 1, cnt, p + 1, q - 1, k), st :: Modify(1, 1, cnt, p + 1, q - 1, k);
            }
            mi = INF, mx = -INF;
            for(register int i = 1; i <= cnt; i++) mi = min(mi, bmi[i]), mx = max(mx, bmx[i]);
            return;
        }

        inline int Query(int l, int r, int k)
        {
            int res = 0, p = in[l], q = in[r];
            if(p == q)
            {
                for(register int i = l; i <= r; i++) if(a[i] + tag[p] < k) ++res;
                return res;
            }
            for(register int i = l; i <= br[p]; i++) if(a[i] + tag[p] < k) ++res;
            for(register int i = bl[q]; i <= r; i++) if(a[i] + tag[q] < k) ++res;
            st :: Find(p + 1, q - 1, k);
            for(register int i = p + 1; i <= q - 1; i++) res += st :: ans[i];
            return res;
        }
    }

    using namespace Block;

    inline int Run()
    {
        n = Read32(), m = Read32(), s = MAXM - 5;
        for(register int i = 1; i <= n; i++)
        {
            a[i] = Read32(), in[i] = (i - 1) / s + 1;
            if(!len[in[i]]) bl[in[i]] = i, br[in[i]] = min(n, i + s - 1), ++cnt;
            seq[in[i]][++len[in[i]]] = Position(a[i], i);
        }
        st :: cnt = cnt;
        mi = INF, mx = -INF;
        for(register int i = 1; i <= cnt; i++)
        {
            blen[i] = len[i];
            sort(seq[i] + 1, seq[i] + len[i] + 1);
            bmi[i] = seq[i][1].val, bmx[i] = seq[i][len[i]].val;
            mi = min(mi, bmi[i]), mx = max(mx, bmx[i]);
            for(register int j = 1; j <= len[i]; j++) st :: bs[i][j] = seq[i][j].val;
        }
        st :: Build(1, 1, cnt);
        while(m--)
        {
            int opt = Read32(), l = Read32(), r = Read32(), k = Read32();
            if(opt & 1)
            {
                if(k > (r - l + 1))
                {
                    puts("-1");
                    continue;
                }
                int L = mi, R = mx, ans = 0;
                while(L <= R)
                {
                    int mid = (L + R) >> 1;
                    if(Query(l, r, mid) + 1 <= k) ans = mid, L = mid + 1;
                    else R = mid - 1;
                }
                Write32(ans);
                continue;
            }
            else
            {
                Modify(l, r, k);
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
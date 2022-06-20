#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>

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
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write32;
using IO :: Write64;

namespace Program
{
    const int MAXN = 2000005;

    int n, ls, lt, cnt[MAXN], seq[MAXN], len, bin[MAXN];
    char s[MAXN], t[MAXN];
    bool vis[MAXN];

    namespace Suffix_Automaton
    {
        int tot, lst, nxt[MAXN][26], slink[MAXN], mxlen[MAXN];
        i64 si[MAXN];

        inline void Init() { return tot = lst = 0, slink[lst] = -1, mxlen[lst] = 0, si[lst] = 0, void(); }

        inline void Extend(int k)
        {
            int cur = ++tot, p = lst; mxlen[cur] = mxlen[lst] + 1, si[cur] = 1, lst = cur;
            while(p != -1 && !nxt[p][k]) nxt[p][k] = cur, p = slink[p];
            if(p == -1) return slink[cur] = 0, void();
            int q = nxt[p][k]; if(mxlen[q] == mxlen[p] + 1) return slink[cur] = q, void();
            int nw = ++tot; slink[nw] = slink[q], slink[cur] = slink[q] = nw, mxlen[nw] = mxlen[p] + 1;
            for(register int c = 0; c < 26; c++) nxt[nw][c] = nxt[q][c];
            while(p != -1 && nxt[p][k] == q) nxt[p][k] = nw, p = slink[p];
            return;
        }
    }

    using namespace Suffix_Automaton;

    inline int Run()
    {
        scanf("%s", s + 1), ls = strlen(s + 1), Init();
        for(register int i = 1; i <= ls; i++) Extend((int)(s[i] - 'a'));
        for(register int i = 1; i <= tot; i++) ++cnt[mxlen[i]];
        for(register int i = 1; i <= ls; i++) cnt[i] += cnt[i - 1];
        for(register int i = tot; i >= 1; i--) seq[cnt[mxlen[i]]--] = i;
        for(register int i = tot; i >= 1; i--) si[slink[seq[i]]] += si[seq[i]];
        n = Read32();
        while(n--)
        {
            scanf("%s", t + 1), lt = strlen(t + 1);
            for(register int i = lt + 1; i <= (lt << 1); i++) t[i] = t[i - lt];
            int nw = 0, l = 1, r = 1;
            while(r <= lt)
            {
                int k = (int)(t[r] - 'a');
                while(nw != -1 && !nxt[nw][k]) nw = slink[nw], l = r - (nw == -1 ? -1 : mxlen[nw]);
                if(nw == -1) nw = 0; else nw = nxt[nw][k];
                ++r;
            }
            i64 ans = 0; len = 0;
            while(r <= (lt << 1))
            {
                int k = (int)(t[r] - 'a');
                while(nw != -1 && !nxt[nw][k]) nw = slink[nw], l = r - (nw == -1 ? -1 : mxlen[nw]);
                if(nw == -1) nw = 0; else nw = nxt[nw][k];
                while(slink[nw] != -1 && mxlen[slink[nw]] >= lt) nw = slink[nw], l = r - mxlen[nw] + 1;
                if(r - l + 1 >= lt)
                {
                    if(vis[nw]) break;
                    vis[bin[++len] = nw] = true;
                    ans += si[nw];
                }
                ++r;
            }
            Write64(ans);
            for(register int i = 1; i <= len; i++) vis[bin[i]] = false;
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
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
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
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write32;

namespace Program
{
    const int MAXN = 305;
    const double PI = acos(-1.0);

    int n;

    struct Vector
    {
        double xi, yi;
        Vector(double _xi = 0.0, double _yi = 0.0) : xi(_xi), yi(_yi) {}
    } p[MAXN];

    struct Alpha
    {
        double ag;
        bool f;

        bool operator < (const Alpha &t) const { return ag < t.ag; }
    } a[MAXN];

    inline double Dist(Vector p, Vector q) { return (p.xi - q.xi) * (p.xi - q.xi) + (p.yi - q.yi) * (p.yi - q.yi); }
    
    inline int Solve(int n)
    {
        int res = n > 0;
        double tmp, rad;
        for(register int i = 1; i <= n; i++)
        {
            int m = 0;
            for(register int j = 1; j <= n; j++) if(i != j && (tmp = Dist(p[i], p[j])) <= 4.0)
            {
                rad = acos(sqrt(tmp) / 2.0);
                tmp = atan2(p[j].yi - p[i].yi, p[j].xi - p[i].xi);
                double a1 = tmp + rad, a2 = tmp - rad;
                if(a1 > PI) a1 -= PI * 2.0;
                if(a2 < -PI) a2 += PI * 2.0;
                if(a2 > a1)
                {
                    ++m, a[m].ag = a2, a[m].f = true;
                    ++m, a[m].ag = -PI, a[m].f = true;
                    ++m, a[m].ag = a1, a[m].f = false;
                }
                else
                {
                    ++m, a[m].ag = a2, a[m].f = true;
                    ++m, a[m].ag = a1, a[m].f = false;
                }
            }
            sort(a + 1, a + m + 1);
            for(register int j = 1, sum = 0; j <= m; j++)
            {
                if(a[j].f) ++sum; else --sum;
                res = max(res, sum + 1);
            }
        }
        return res;
    }

    inline int Run()
    {
        n = Read32();
        while(n)
        {
            for(register int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].xi, &p[i].yi);
            Write32(Solve(n));
            n = Read32();
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
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>

using namespace std;

namespace Program
{
    const int MAXN = 505;

    int n, cs;
    double a, mi, mx, h[MAXN], r[MAXN];

    struct Point
    {
        double xi, yi;
        Point(double _xi = 0.0, double _yi = 0.0) : xi(_xi), yi(_yi) {}
    };

    struct Circle
    {
        Point cen;
        double rad;
        Circle(Point _cen = Point(), double _rad = 0.0) : cen(_cen), rad(_rad) {}
    } cir[MAXN];

    inline bool In(Circle u, Circle v)
    {
        if((u.cen.xi - u.rad <= v.cen.xi - v.rad && v.cen.xi + v.rad <= u.cen.xi + u.rad) || (v.cen.xi - v.rad <= u.cen.xi - u.rad && u.cen.xi + u.rad <= v.cen.xi + v.rad)) return true;
        return false;
    }

    struct Segment
    {
        double ki, bi, xl, xr;
        Segment(double _ki = 0.0, double _bi = 0.0, double _xl = 0.0, double _xr = 0.0) : ki(_ki), bi(_bi), xl(_xl), xr(_xr) {}
    } seg[MAXN];

    inline Segment Get(Circle u, Circle v)
    {
        if(u.cen.xi > v.cen.xi) swap(u, v);
        double r1 = u.rad, r2 = v.rad;
        if(r1 == r2)
        {
            Segment t(0, r1, u.cen.xi, v.cen.xi);
            return t;
        }
        if(r1 > r2) swap(r1, r2);
        double d = fabs(u.cen.xi - v.cen.xi), k = (r1 * d) / (r2 - r1), b = r2 / (k + d);
        Point p, q;
        if(u.rad < v.rad)
        {
            if(u.rad == 0.0) p = u.cen;
            else p = Point(u.cen.xi - u.rad * b, sqrt(pow(k, 2) - pow(u.rad, 2)) * b);
            q = Point(v.cen.xi - v.rad * b, sqrt(pow(k + d, 2) - pow(v.rad, 2)) * b);
        }
        else
        {
            p = Point(u.cen.xi + u.rad * b, sqrt(pow(k + d, 2) - pow(u.rad, 2)) * b);
            if(v.rad == 0.0) q = v.cen;
            else q = Point(v.cen.xi + v.rad * b, sqrt(pow(k, 2) - pow(v.rad, 2)) * b);
        }
        double ki = (q.yi - p.yi) / (q.xi - p.xi), bi = p.yi - ki * (p.xi);
        Segment t = Segment(ki, bi, p.xi, q.xi);
        return t;
    }

    inline double F(double x)
    {
        double ans = 0.0;
        for(register int i = 1; i <= n; i++) if(cir[i].cen.xi - cir[i].rad <= x && x <= cir[i].cen.xi + cir[i].rad) ans = max(ans, sqrt(pow(cir[i].rad, 2) - pow(fabs(x - cir[i].cen.xi), 2)));
        for(register int i = 1; i <= cs; i++) if(seg[i].xl <= x && x <= seg[i].xr) ans = max(ans, seg[i].ki * x + seg[i].bi);
        return ans;
    }

    inline double Simpson(double l, double r)
    {
        double mid = (l + r) / 2.0;
        return (F(l) + F(mid) * 4.0 + F(r)) * (r - l) / 6.0;
    }

    inline double Solve(double l, double r, double now, double eps)
    {
        double mid = (l + r) / 2.0, lval = Simpson(l, mid), rval = Simpson(mid, r);
        if(fabs(lval + rval - now) <= eps) return lval + rval;
        return Solve(l, mid, lval, eps / 2.0) + Solve(mid, r, rval, eps / 2.0);
    }

    inline int Run()
    {
        scanf("%d%lf", &n, &a);
        for(register int i = 0; i <= n; i++) scanf("%lf", h + i);
        for(register int i = 1; i <= n; i++) scanf("%lf", r + i);
        double hs = h[0];
        mi = 0x7FFFFFFF, mx = -0x7FFFFFFF;
        for(register int i = 1; i <= n; i++)
        {
            cir[i].rad = r[i];
            cir[i].cen = Point(hs / tan(a), 0.0);
            mi = min(mi, cir[i].cen.xi - cir[i].rad), mx = max(mx, cir[i].cen.xi + cir[i].rad);
            hs += h[i];
        }
        cir[n + 1] = Circle(Point(hs / tan(a), 0.0), 0.0);
        mi = min(mi, cir[n + 1].cen.xi - cir[n + 1].rad), mx = max(mx, cir[n + 1].cen.xi + cir[n + 1].rad);
        for(register int i = 1; i <= n; i++)
        {
            if(In(cir[i], cir[i + 1])) continue;
            seg[++cs] = Get(cir[i], cir[i + 1]);
        }
        printf("%.2lf", Solve(mi, mx, Simpson(mi, mx), 1e-4) * 2.0);
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
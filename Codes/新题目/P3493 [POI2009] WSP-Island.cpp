#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
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

    inline int Read32() { int k; _Read(k); return k; }
}

using IO :: Read32;

namespace Program
{
    const int MAXN = 100005;
    const double EPS = 1e-8;

    int n, m, len, cnt, l, r;
    bool ban[MAXN];
    vector<int> vec[MAXN];

    struct Vector
    {
        double xi, yi;
        Vector(double _xi = 0.0, double _yi = 0.0) : xi(_xi), yi(_yi) {}

        Vector operator + (const Vector &t) const { return Vector(xi + t.xi, yi + t.yi); }
        Vector operator - (const Vector &t) const { return Vector(xi - t.xi, yi - t.yi); }
        Vector operator * (const double &t) const { return Vector(xi * t, yi * t); }
        double operator * (const Vector &t) const { return xi * t.yi - yi * t.xi; }
    } p[MAXN], it[MAXN];

    inline double Dist(Vector a, Vector b)
    {
        Vector tmp = b - a;
        return sqrt(tmp.xi * tmp.xi + tmp.yi * tmp.yi);
    }

    struct Line
    {
        Vector pos, dir;
        double ag;
        Line(Vector _pos = Vector(), Vector _dir = Vector()) : pos(_pos), dir(_dir) { ag = atan2(_dir.yi, _dir.xi); }

        friend inline bool operator < (const Line &a, const Line &b) { return a.ag - b.ag < EPS; }
    } li[MAXN], q[MAXN];

    inline Vector Intersection(Line a, Line b)
    {
        double k = ((b.pos - a.pos) * b.dir) / (a.dir * b.dir);
        return a.pos + a.dir * k;
    }
    
    inline bool Right(Line a, Vector b) { return (b - a.pos) * a.dir > EPS; }

    inline void Half_Plane()
    {
        sort(li + 1, li + cnt + 1);
        q[l = r = 1] = li[1];
        for(register int i = 2; i <= cnt; i++)
        {
            while(l < r && Right(li[i], it[r])) --r;
            while(l < r && Right(li[i], it[l + 1])) ++l;
            q[++r] = li[i];
            if(fabs(q[r - 1].dir * q[r].dir) < EPS)
            {
                --r;
                if(!Right(q[r], li[i].pos)) q[r] = li[i];
            }
            if(l < r) it[r] = Intersection(q[r - 1], q[r]);
        }
        while(l < r && Right(q[l], it[r])) --r;
        it[r + 1] = it[l] = Intersection(q[l], q[r]);
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].xi, &p[i].yi);
        for(register int i = 1; i <= m; i++)
        {
            int u = Read32(), v = Read32();
            if(u > v) swap(u, v);
            vec[u].push_back(v);
        }
        for(register int i = 1; i <= n; i++)
        {
            int k = i;
            for(register vector<int> :: iterator it = vec[i].begin(); it != vec[i].end(); it++) ban[*it] = true;
            for(register int j = n; j > i; j--) if(!ban[j]) { k = j; break; }
            if(i == 1 && k == n)
            {
                printf("%.10lf\n", Dist(p[1], p[n]));
                return 0;
            }
            if(i < k) li[++cnt] = Line(p[k], p[i] - p[k]);
            for(register vector<int> :: iterator it = vec[i].begin(); it != vec[i].end(); it++) ban[*it] = false;
        }
        li[++cnt] = Line(p[1], p[n] - p[1]);
        Half_Plane();
        double ans = 0.0;
        for(register int i = l; i <= r; i++) ans += Dist(it[i], it[i + 1]);
        ans -= Dist(p[1], p[n]);
        printf("%.10lf", ans);
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
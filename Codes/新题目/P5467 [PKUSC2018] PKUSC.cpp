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

    inline int Read32() { int k; _Read(k); return k; }
}

using IO :: Read32;

namespace Program
{
    const int MAXN = 205;
    const int MAXM = 505;
    const double EPS = 1e-6;
    const double PI = acos(-1.0);

    int n, m, cnt;
    double ans;

    inline int Sign(double a)
    {
        if(a > EPS) return 1;
        if(a < -EPS) return -1;
        return 0;
    }

    struct Vector
    {
        double xi, yi, ag;
        Vector(double _xi = 0.0, double _yi = 0.0) : xi(_xi), yi(_yi) {}

        Vector operator + (const Vector &t) const { return Vector(xi + t.xi, yi + t.yi); }
        Vector operator - (const Vector &t) const { return Vector(xi - t.xi, yi - t.yi); }
        Vector operator * (const double &t) const { return Vector(xi * t, yi * t); }
        double operator * (const Vector &t) const { return xi * t.yi - yi * t.xi; }
        Vector operator / (const double &t) const { return Vector(xi / t, yi / t); }
        bool operator < (const Vector &t) const { return Sign(ag - t.ag) < 0; }
        bool operator == (const Vector &t) const { return Sign(xi - t.xi) == 0 && Sign(yi - t.yi) == 0; }
    } p[MAXN], q[MAXM], it[MAXM << 1];

    inline double Dist(Vector a = Vector(), Vector b = Vector()) { return sqrt((a.xi - b.xi) * (a.xi - b.xi) + (a.yi - b.yi) * (a.yi - b.yi)); }

    struct Segment
    {
        Vector pos, dir, ed;
        double xl, xr, yl, yr;
        Segment(Vector _pos = Vector(), Vector _dir = Vector()) : pos(_pos), dir(_dir)
        {
            ed = pos + dir;
            xl = pos.xi, xr = ed.xi;
            if(Sign(xl - xr) > 0) swap(xl, xr);
            yl = pos.yi, yr = ed.yi;
            if(Sign(yl - yr) > 0) swap(yl, yr);
        }
    } seg[MAXM];

    inline Vector Get_Intersection(Segment a, Segment b)
    {
        double k = (b.pos - a.pos) * b.dir / (a.dir * b.dir);
        return a.pos + a.dir * k;
    }

    inline bool On(Segment s, Vector v, bool f = true)
    {
        if(f) return Sign(s.dir * (v - s.pos)) == 0 && Sign(v.xi - s.xl) >= 0 && Sign(s.xr - v.xi) >= 0 && Sign(v.yi - s.yl) >= 0 && Sign(s.yr - v.yi) >= 0;
        return Sign(v.xi - s.xl) >= 0 && Sign(s.xr - v.xi) >= 0 && Sign(v.yi - s.yl) >= 0 && Sign(s.yr - v.yi) >= 0;
    }

    inline bool In(Vector v)
    {
        for(register int i = 1; i <= m; i++) if(On(seg[i], v)) return false;
        int k = 0;
        Segment l = Segment(v, Vector(1926.0817, 1949.1001));
        for(register int i = 1; i <= m; i++)
        {
            Vector u = Get_Intersection(l, seg[i]);
            if(Sign(u.yi - v.yi) > 0 && On(seg[i], u, false)) ++k;
        }
        return (k & 1);
    }

    struct Circle
    {
        Vector cen;
        double rad;
        Circle(Vector _cen = Vector(), double _rad = 0.0) : cen(_cen), rad(_rad) {}
    } c[MAXN];

    inline void Check(Vector a, Vector b, double r)
    {
        Vector d = (b - a) / Dist(a, b);
        d = Vector(d.yi, -d.xi) * r;
        if(In(d))
        {
            if(Sign(b.ag - a.ag) < 0) ans += PI * 2.0;
            ans += b.ag - a.ag;
        }
        return;
    }

    inline void Intersection(Circle c, Segment s)
    {
        double dis = fabs(s.pos * s.ed) / Dist(s.pos, s.ed);
        if(Sign(dis - c.rad) >= 0) return;
        Vector r = s.dir / Dist(s.pos, s.ed);
        Segment k = Segment(Vector(), Vector(-s.dir.yi, s.dir.xi));
        Vector t = Get_Intersection(k, s);
        double d = sqrt(c.rad * c.rad - t.xi * t.xi - t.yi * t.yi);
        r = r * d;
        Vector u = t + r, v = t - r;
        if(On(s, u, false)) it[++cnt] = u; if(On(s, v, false)) it[++cnt] = v;
        return;
    }

    inline int Run()
    {
        n = Read32(), m = Read32();
        for(register int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].xi, &p[i].yi);
        for(register int i = 1; i <= m; i++) scanf("%lf%lf", &q[i].xi, &q[i].yi);
        for(register int i = 1; i <= m; i++)
        {
            if(i == m) seg[i] = Segment(q[i], q[1] - q[i]);
            else seg[i] = Segment(q[i], q[i + 1] - q[i]);
        }
        for(register int i = 1; i <= n; i++)
        {
            c[i] = Circle(Vector(), Dist(p[i]));
            if(Sign(c[i].rad) == 0)
            {
                ans += In(p[i]) * PI * 2.0;
                continue;
            }
            cnt = 0;
            for(register int j = 1; j <= m; j++) Intersection(c[i], seg[j]);
            if(cnt == 0)
            {
                ans += In(Vector(0.0, c[i].rad)) * PI * 2.0;
                continue;
            }
            for(register int j = 1; j <= cnt; j++) it[j].ag = atan2(it[j].yi, it[j].xi);
            sort(it + 1, it + cnt + 1);
            it[++cnt] = it[1];
            for(register int j = 1; j < cnt; j++)
            {
                if(it[j] == it[j + 1]) continue;
                Check(it[j], it[j + 1], c[i].rad);
            }
        }
        ans /= PI * 2.0;
        printf("%.5lf\n", ans);
        return 0;
    }
}

int main() { return Program :: Run(); }
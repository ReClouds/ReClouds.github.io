#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<algorithm>

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
    const int MAXN = 3005;

    int n;
    i64 ans;

    struct Vector
    {
        i64 xi, yi;
        Vector(i64 _xi = 0, i64 _yi = 0) : xi(_xi), yi(_yi) {}

        Vector operator + (const Vector &t) const { return Vector(xi + t.xi, yi + t.yi); }
        Vector operator - (const Vector &t) const { return Vector(xi - t.xi, yi - t.yi); }
        i64 operator * (const Vector &t) const { return xi * t.yi - yi * t.xi; }
    } p[MAXN], q[MAXN], sum[MAXN];

    inline bool Compare1(Vector a, Vector b) { return a.yi == b.yi ? a.xi < b.xi : a.yi < b.yi; }
    inline bool Compare2(Vector a, Vector b) { return a * b > 0; }

    inline int Run()
    {
        n = Read32();
        for(register int i = 1; i <= n; i++) p[i].xi = Read64(), p[i].yi = Read64();
        sort(p + 1, p + n + 1, Compare1);
        for(register int u = 1; u < n - 1; u++)
        {
            for(register int v = u + 1; v <= n; v++) q[v] = p[v] - p[u];
            sort(q + u + 1, q + n + 1, Compare2);
            sum[u] = Vector();
            for(register int v = u + 1; v <= n; v++) sum[v] = sum[v - 1] + q[v];
            for(register int v = u + 1; v < n; v++) ans += q[v] * (sum[n] - sum[v]);
        }
        if(ans & 1) Write64(ans >> 1, '.'), Write32(5, '\n');
        else Write64(ans >> 1, '.'), Write32(0, '\n');
        return 0;
    }
}

int main() { return Program :: Run(); }
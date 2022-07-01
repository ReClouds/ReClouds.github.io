#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
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

    inline i64 Read64() { i64 k; _Read(k); return k; }
    inline void Write64(i64 k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read64;
using IO :: Write64;

namespace Program
{
    const int MAXLOG = 61;
    const int MAXN = (1 << 16);

    int t[MAXLOG], lx[MAXLOG], rx[MAXLOG], ly[MAXLOG], ry[MAXLOG];
    i64 T, Lx, Rx, Ly, Ry, f[MAXLOG][MAXN];

    inline int State(int dx, int ux, int dy, int uy) { return dx | (ux << 1) | (dy << 2) | (uy << 3); }

    inline void Transfrom(i64 k, int *b)
    {
        int c = 0;
        while(c < MAXLOG) b[c++] = (k & 1), k >>= 1;
        return;
    }

    inline int Run()
    {
        T = Read64(), Lx = Read64(), Rx = Read64(), Ly = Read64(), Ry = Read64();
        Transfrom(T, t), Transfrom(Lx, lx), Transfrom(Rx, rx), Transfrom(Ly, ly), Transfrom(Ry, ry);
        f[MAXLOG - 1][1 << State(1, 1, 1, 1)] = 1;
        for(register int i = MAXLOG - 2; i >= 0; i--) for(register int S = 1; S < MAXN; S++) if(f[i + 1][S])
        {
            int tr[2] = {0, 0};
            for(register int dx = 0; dx < 2; dx++) for(register int ux = 0; ux < 2; ux++) for(register int dy = 0; dy < 2; dy++) for(register int uy = 0; uy < 2; uy++) if(S >> State(dx, ux, dy, uy) & 1)
            {
                for(register int bx = (dx ? lx[i] : 0); bx <= (ux ? rx[i] : 1); bx++) for(register int by = (dy ? ly[i] : 0); by <= (uy ? ry[i] : 1); by++)
                {
                    if((bx | by) != t[i]) continue;
                    tr[bx & by] |= (1 << State(dx & (bx == lx[i]), ux & (bx == rx[i]), dy & (by == ly[i]), uy & (by == ry[i])));
                }
            }
            for(register int j = 0; j < 2; j++) if(tr[j]) f[i][tr[j]] += f[i + 1][S];
        }
        i64 ans = 0;
        for(register int S = 1; S < MAXN; S++) ans += f[0][S];
        return Write64(ans), 0;
    }
}

int main() { return Program :: Run(); }
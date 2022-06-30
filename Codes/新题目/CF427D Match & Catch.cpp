#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>

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
    const int MAXN = 20005;

    int n, m, len, ans, z[MAXN], ca[MAXN], cb[MAXN];
    char a[MAXN], b[MAXN], s[MAXN];

    inline void Get_Z()
    {
        memset(z, 0, sizeof z);
        for(register int i = 2, l = 0, r = 0; i <= len; i++)
        {
            if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
            while(i + z[i] <= len && s[z[i] + 1] == s[i + z[i]]) ++z[i];
            if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return;
    }

    inline void Solve(int st)
    {
        len = 0;
        for(register int i = st; i <= n; i++) s[++len] = a[i];
        s[++len] = '<';
        for(register int i = 1; i <= n; i++) s[++len] = a[i];
        s[++len] = '>';
        for(register int i = 1; i <= m; i++) s[++len] = b[i];
        Get_Z(), z[n + 2] = 0;
        memset(ca, 0, sizeof ca), memset(cb, 0, sizeof cb);
        for(register int i = 1; i <= n - st + 1; i++) ++ca[z[i]];
        for(register int i = n - st + 3; i <= n * 2 - st + 2; i++) ++ca[z[i]];
        for(register int i = n * 2 - st + 4; i <= len; i++) ++cb[z[i]];
        int mx = 0, cmx = 0;
        for(register int i = len; i >= 1; i--) if(ca[i] + cb[i] > 0)
        {
            if(!mx) 
            {
                if(ca[i] == 0 && cb[i] == 1) mx = i;
                else break;
            }
            else
            {
                cmx = i;
                break;
            }
        }
        if(mx) ans = min(ans, cmx + 1);
        return;
    }

    inline int Run()
    {
        scanf("%s%s", a + 1, b + 1);
        n = strlen(a + 1), m = strlen(b + 1);
        ans = 0x3F3F3F3F;
        for(register int i = 1; i <= n; i++) Solve(i);
        if(ans != 0x3F3F3F3F) Write32(ans);
        else puts("-1");
        return 0;
    }
}

int main() { return Program :: Run(); }
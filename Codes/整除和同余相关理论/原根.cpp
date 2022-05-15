#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<algorithm>

#define MAXN 1000001

using namespace std;

int t, n, d, phi[MAXN], len, pr[MAXN], cnt, ans[MAXN];
bool np[MAXN], rt[MAXN];

inline void Sieve()
{
    for(register int i = 2; i < MAXN; i++) phi[i] = i;
    for(register int i = 2; i < MAXN; i++)
    {
        if(!np[i])
        {
            rt[i] = true; if((i << 1) < MAXN) rt[i << 1] = true; phi[i] = i - 1;
            for(register int j = 2; i * j < MAXN; j++) np[i * j] = true, phi[i * j] = phi[i * j] / i * (i - 1);
            if(i & 1 && i <= 1000)
            {
                int tmp = i * i;
                while(tmp < MAXN) { rt[tmp] = true; if((tmp << 1) < MAXN) rt[tmp << 1] = true; tmp *= i; }
            }
        }
    }
    return;
}

inline void Divide(int k)
{
    len = 0;
    for(register int i = 2; i * i <= k; i++)
    {
        if(k % i == 0)
        {
            pr[++len] = i;
            while(k % i == 0) k /= i;
        }
    }
    if(k > 1) pr[++len] = k;
    return;
}

inline int pw(int a, int b, int p)
{
    int res = 1;
    while(b)
    {
        if(b & 1) res = 1LL * res * a % p;
        a = 1LL * a * a % p; 
        b >>= 1;
    }
    return res;
}

inline bool Check(int a, int b, int p)
{
    for(register int i = 1; i <= len; i++) if(pw(a, b / pr[i], p) == 1) return false;
    return true;
}

inline int gcd(int a, int b) { if(b == 0) return a; return gcd(b, a % b); }

int main()
{
    Sieve();
    scanf("%d", &t);
    while(t--)
    {
        cnt = 0;
        scanf("%d%d", &n, &d);
        if(!rt[n]) { puts("0\n"); continue; }
        Divide(phi[n]);
        int g; for(register int i = 1; i < n; i++) if(pw(i, phi[n], n) == 1 && Check(i, phi[n], n)) { g = i; break; }
        int val = 1;
        for(register int i = 1; i <= phi[n]; i++)
        {
            val = 1LL * val * g % n;
            if(gcd(i, phi[n]) == 1) ans[++cnt] = val;
        }
        printf("%d\n", cnt), sort(ans + 1, ans + cnt + 1);
        for(register int i = d; i <= cnt; i += d) printf("%d ", ans[i]);
        putchar('\n');
    }
    return 0;
}
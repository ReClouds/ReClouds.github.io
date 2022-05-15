#include<iostream>
#include<cstdio>
#include<cstdlib>

#define MAXN 1005

using namespace std;

int n;
long long a[MAXN], b[MAXN], sum = 1, ans;

void exgcd(long long a, long long b, long long &x, long long &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - (a / b) * y;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i], &b[i]);
        sum *= a[i];
    }
    for(int i = 1; i <= n; i++)
    {
        long long m = sum / a[i], x = 0, y = 0;
        exgcd(m, a[i], x, y);
        ans += b[i] * m * (x < 0 ? x + a[i] : x);
    }
    printf("%lld", ans % sum);
    return 0;
}
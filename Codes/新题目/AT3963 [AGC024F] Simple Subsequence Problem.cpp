#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<string>

using namespace std;

namespace Program
{
    const int MAXN = 21;

    int n, k, f[1 << MAXN][MAXN], tr[1 << MAXN][MAXN][2], len, b[MAXN];
    string s;

    inline void Output(int ed, int val)
    {
        len = n;
        while(val) b[len--] = val & 1, val >>= 1;
        for(register int i = ed + 1; i <= n; i++) cout << b[i];
        return cout << endl, void();
    }

    inline int Run()
    {
        cin >> n >> k;
        for(register int i = 0; i <= n; i++)
        {
            cin >> s;
            for(register int j = 0; j < (1 << i); j++) if((int)(s[j] - '0') == 1) ++f[(1 << i) | j][n - i];
        }
        for(register int i = 1; i < (1 << (n + 1)); i++)
        {
            for(register int j = 0; j < n; j++)
            {
                for(register int k = 0; k < 2; k++)
                {
                    int pos = j + 1;
                    while(pos <= n && ((i >> (n - pos)) & 1) != k) ++pos;
                    tr[i][j][k] = pos;
                }
            }
        }
        for(register int i = (1 << (n + 1)) - 1; i > 0; i--)
        {
            for(register int j = 0; j < n; j++) if(f[i][j])
            {
                if(tr[i][j][0] <= n) f[((i >> (tr[i][j][0] - j - 1)) & (((1 << (n + 1)) - 1) ^ ((1 << (n - tr[i][j][0] + 1)) - 1))) | (i & ((1 << (n - tr[i][j][0] + 1)) - 1))][tr[i][j][0]] += f[i][j];
                if(tr[i][j][1] <= n) f[((i >> (tr[i][j][1] - j - 1)) & (((1 << (n + 1)) - 1) ^ ((1 << (n - tr[i][j][1] + 1)) - 1))) | (i & ((1 << (n - tr[i][j][1] + 1)) - 1))][tr[i][j][1]] += f[i][j];
                f[i >> (n - j)][n] += f[i][j];
            }
        }
        for(register int i = n; i > 0; i--)
        {
            for(register int j = 0; j < (1 << i); j++) if(f[(1 << i) | j][n] >= k)
            {
                Output(n - i, j);
                return 0;
            }
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
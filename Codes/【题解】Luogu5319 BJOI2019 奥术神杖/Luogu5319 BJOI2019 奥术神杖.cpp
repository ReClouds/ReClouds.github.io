#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>

#define MAXN 1505

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
    int n, m;
    char S[MAXN], T[MAXN];
	const double INF = 0x3F3F3F3F, LIMIT = log(INF), EPS = 1e-3;
	
	namespace Aho_Corasick_Automaton
	{
		int cnt, ch[MAXN][10], nxt[MAXN], sum[MAXN], g[MAXN][MAXN][2], ed;
		double t[MAXN], val[MAXN], f[MAXN][MAXN], ans;

		inline void Insert(char *s, int n, double k)
		{
			int now = 0;
			for(register int i = 1; i <= n; i++)
			{
				int c = s[i] - '0';
				if(!ch[now][c]) ch[now][c] = ++cnt;
				now = ch[now][c];
			}
			return ++sum[now], val[now] += k, void();
		}

		inline void Get_Fail()
		{
			queue<int> q;
			for(register int i = 0; i < 10; i++) if(ch[0][i]) q.push(ch[0][i]);
			while(!q.empty())
			{
				int u = q.front(); q.pop();
				for(register int i = 0; i < 10; i++)
				{
					int v = ch[nxt[u]][i];
					if(ch[u][i]) nxt[ch[u][i]] = v, sum[ch[u][i]] += sum[v], val[ch[u][i]] += val[v], q.push(ch[u][i]);
					else ch[u][i] = v;
				}
			}
			return;
		}

    	inline bool Check(double mid)
    	{
            for(register int i = 0; i <= cnt; i++) val[i] -= mid * sum[i];
		    for(register int i = 0; i <= cnt; i++) for(register int j = 0; j <= n; j++) f[i][j] = -INF;
		    f[0][0] = 0;
            for(register int i = 0; i < n; i++)
            {
                for(register int j = 0; j <= cnt; j++)
                {
                    for(register int k = 0; k < 10; k++)
                    {
                        if(S[i + 1] == '.' || S[i + 1] == k + '0')
                        {
                            int to = ch[j][k];
                            if(f[j][i] + val[to] > f[to][i + 1])
                            {
                                f[to][i + 1] = f[j][i] + val[to];
                                g[to][i + 1][0] = j, g[to][i + 1][1] = k;
                            }
                        }
                    }
                }
            }
            for(register int i = 0; i <= cnt; i++) val[i] += mid * sum[i];
            ans = -INF;
            for(register int i = 0; i <= cnt; i++)
            {
                if(f[i][n] > ans)
                {
                    ans = f[i][n];
                    ed = i;
                }
            }
		    return ans > 0;
	    }

        inline void Output()
        {
            int top = n; char ans[MAXN];
            while(top)
            {
                ans[top] = g[ed][top][1] + '0';
                ed = g[ed][top][0], --top;
            }
            for(register int i = 1; i <= n; i++) putchar(ans[i]);
            return putchar('\n'), void();
        }
    }

    using namespace Aho_Corasick_Automaton;

    inline int Run()
    {
        n = Read32(), m = Read32(), scanf("%s", S + 1);
        for(register int i = 1; i <= m; i++)
        {
            scanf("%s", T + 1);
            int l = strlen(T + 1); Insert(T, l, log(Read32()));
        }
		Get_Fail();
		double l = 0, r = LIMIT;
		while(r - l > EPS)
		{
			double mid = (l + r) / 2;
			if(Check(mid)) l = mid;
			else r = mid;
		}
        return Check(l), Output(), 0;
    }
}

int main() { return Program :: Run(); }
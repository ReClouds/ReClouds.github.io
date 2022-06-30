#define MAXN 30005

int cnt, mp[MAXN], seq[MAXN], f[MAXN >> 8][MAXN];

bool Flag = false;

inline void Init(int n)
{
	for(register int i = 1; i < n; i++)
	{
		int t = i;
		while(t % 2 == 0) t /= 2;
		while(t % 3 == 0) t /= 3;
		if(t == 1) seq[cnt] = i, mp[i] = cnt++;
	}
	for(register int yi = n - 1; yi >= 0; yi--)
	{
		for(register int t = cnt - 1; t >= 0; t--)
		{
			int xi = seq[t];
			if(xi + yi >= n) continue;
			if(xi + yi + 1 >= n || xi * 2 + yi >= n || xi * 3 + yi >= n) f[t][yi] = 1;
			else if(!f[mp[1]][xi + yi] || !f[mp[xi * 2]][yi] || !f[mp[xi * 3]][yi]) f[t][yi] = 1;
		}
	}
	return;
}

extern "C" int _opt(int n, int xi, int yi)
{
	if(!Flag) Init(n), Flag = true;
	if(xi + yi + 1 >= n || !f[mp[1]][xi + yi]) return 1;
	if(xi * 2 + yi >= n || !f[mp[xi * 2]][yi]) return 2;
	if(xi * 3 + yi >= n || !f[mp[xi * 3]][yi]) return 3;
}

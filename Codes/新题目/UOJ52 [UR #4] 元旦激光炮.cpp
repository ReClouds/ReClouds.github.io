#include<algorithm>
#include "kth.h"

using namespace std;

const int MAXN = 100005;

int nowa, nowb, nowc, len, seq[MAXN];

int query_kth(int n_a, int n_b, int n_c, int k)
{
	nowa = nowb = nowc = -1;
	while(true)
	{
		if(k <= 2)
		{
			len = 0;
			if(nowa + 1 < n_a) seq[++len] = get_a(nowa + 1); if(k > 1 && nowa + 2 < n_a) seq[++len] = get_a(nowa + 2);
			if(nowb + 1 < n_b) seq[++len] = get_b(nowb + 1); if(k > 1 && nowb + 2 < n_b) seq[++len] = get_b(nowb + 2);
			if(nowc + 1 < n_c) seq[++len] = get_c(nowc + 1); if(k > 1 && nowc + 2 < n_c) seq[++len] = get_c(nowc + 2);
			sort(seq + 1, seq + len + 1);
			return seq[k];
		}
		int t = k / 3, resa = get_a(nowa + t), resb = get_b(nowb + t), resc = get_c(nowc + t);
		if(resa <= resb && resa <= resc) nowa = nowa + t;
		else if(resb <= resa && resb <= resc) nowb = nowb + t;
		else if(resc <= resa && resc <= resb) nowc = nowc + t;
		k -= t;
	}
	return -1;
}
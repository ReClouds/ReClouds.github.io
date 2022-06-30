#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>

#define MAXN 1005

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
    int t, n, val[MAXN], tmp[MAXN];

    inline int Run()
    {
        cin >> t;
        while(t--)
        {
            memset(val, 0, sizeof val), memset(tmp, 0, sizeof tmp);
            cin >> n;
			int mi = 0x3F3F3F3F, mx = -1, k = 0;
			for(register int i = 2; i < n; i++)
			{
				cout << "? 1 " << i << " " << n << endl;
				cin >> val[i];
				mi = min(mi, val[i]);
				if(val[i] > mx) mx = val[i], k = i;
			}
			if(mi == mx)
            {
                int tmi = 0x3F3F3F3F, tmx = -1, p = 0;
                for(register int i = 1; i <= n; i++) if(i != 2 && i != n - 1)
                {
                    cout << "? 2 " << i << " " << n - 1 << endl;
                    cin >> tmp[i];
                    tmi = min(tmi, tmp[i]);
                    if(tmp[i] > tmx) tmx = tmp[i], p = i;
                }
                if(tmi != tmx)
                {
                    if(tmx > mx) cout << "! " << p << " " << p << endl;
                    else cout << "! 1 " << n << endl;
                }
                else if(mx > tmx) cout << "! 1 " << n << endl;
                else cout << "! 2 " << n - 1 << endl;
            }
			else
			{
				mi = 0x3F3F3F3F, mx = -1; int p = 0;
				for(register int i = 2; i <= n; i++) if(i != k)
				{
					cout << "? 1 " << i << " " << k << endl;
					int v; cin >> v;
					mi = min(mi, v);
					if(v > mx) mx = v, p = i;
				}
				if(mi == mx) cout << "! 1 " << k << endl;
				else cout << "! " << k << " " << p << endl;
			}
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
/*

                                                                 /@@@O
                                                              =@@@@@@@@@
                                                           ]/@@@@@@@@@@@
                                             ]]]]]/@@@@@@@@@@@@@@@@@@@@@
                       @@@@@\]]]]]]]]@@@@@@@@@@OO/          /@@@@@@@@@@@@
                      =@@@@@@@@@@O/[[                    [ @@@O[     O@@@\
                      =@@@@@@@@@@@]                     /@@/            \@\
                      =@@@@@      O@@@@\]]           /@@@[               \@@\
                      @@@@@             /@@@@@\    /@@[                    O@O
                     =@@ =@                  [\@@@@@\]                       @@O
                     @@/ O@                   /@@   [O@@@@\]                  =@@
                    /@   =@@               /@@/            @@@@@OO [            @@]
                   /@@    @@             @@@                     \@@@@O]         \@@
                   @@     @@         =O@@/                             \@@@@O/O    @@@\
                  @@      =@       /@@/                                      \@@@@@@@@@@@@
                =/@@      =@     @@@/                                             \@@@@@@@
                =@@       =@@ O@@O                                                  =@@@@@
                @@         @@@@[
              =/@O       O@@@
              =@@     \@@@ \@
              @@    @@@/   =@\
            =@@/[]@@@[     =@@
           /@@@@@@          @@
         /@@@@@@@           @@
         @@@@@@@            =@
          \@@@@@@\          =@
             @@@@@@@\       =@@
               @@\[@@@       @@
                =@@  \@@\    @@
                 =@@/  [@@@  @@
                  =@@\    =@@@@O
                    \@@     =@@@]                                                    /@@@O
                     \@@     =@@@@\                                                @@@@@@@
                      =@@     @@ [@@@                                        ]]@@@@@@@@@@@
                        @@    =@     @@\                              ]]@@@@@/[ /O@@@@[
                         \@@  =@\      \@@\                   \]@@@@@@O[       O@@[
                          =@@ /@@         @@O          ]/@@@@@@/[           /@@/
                           \@@@@@@          O@@]/O@@@@@/[                ]O@@/
                           =@@@@@@@@\]]]]\@@@@@@@O                     O@@
                           =@@@@@@@@@@@@@/       O@@\                @@@
                           =@@@@@@@@@@@@]          [@@\           /@@O
                            @@@@@@@@@@@@@@@@@@@O\]    \@@@O  ]]/@@@[
                              [@@/             [O@@@@@@@@@@@@@@@@/
                                                       \@@@@@@@@
                                                          \@@@@
*/
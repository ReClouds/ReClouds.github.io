# include <bits/stdc++.h>

using i64 = long long ;
using namespace std ;

namespace IO
{
    template < typename T > inline T Read ()
    {
        T v = 0, f = 1 ; char c = getchar () ;

        while ( !isdigit ( c ) )
        {
            if ( c == '-' ) f = -1 ;
            c = getchar () ;
        }

        while ( isdigit ( c ) )
        {
            v = ( v << 3 ) + ( v << 1 ) + ( c - '0' ) ;
            c = getchar () ;
        }

        return v *= f ;
    }

    template < typename T > inline void Write ( T v )
    {
        if ( v < 0 ) putchar ( '-' ), v = -v ;
        if ( v > 9 ) Write ( v / 10 ) ;
        return putchar ( v % 10 + '0' ), void () ;
    }
}

using IO :: Read ;
using IO :: Write ;

namespace Program
{
    const int MAXN = 1000005 ;

    int n, m, dis[MAXN] ;
    vector < pair < int, int > > ed[MAXN] ;

    inline void BFS ( int S )
    {
        memset ( dis, -1, sizeof dis ) ;

        deque <int> q ;
        q.push_back ( S ), dis[S] = 0 ;

        while ( !q.empty () )
        {
            int u = q.front () ; q.pop_front () ;
            for ( auto it : ed[u] )
            {
                int v = it.first, w = it.second ;
                if ( dis[v] == -1 ) 
                {
                    dis[v] = dis[u] + w ;
                    if ( w == 0 ) q.push_front ( v ) ;
                    else q.push_back ( v ) ;
                }
            }
        }

        return ;
    }

    inline int Run ()
    {
        n = Read <int> (), m = Read <int> () ;

        for ( register int i = 1; i <= m; ++i )
        {
            int l = Read <int> (), r = Read <int> () ;
            ed[r].emplace_back ( make_pair ( l - 1, 0 ) ), ed[l - 1].emplace_back ( make_pair ( r, 0 ) ) ;
        }
        for ( register int i = 1; i <= n; ++i ) ed[i].emplace_back ( make_pair ( i - 1, 1 ) ), ed[i - 1].emplace_back ( make_pair ( i, 1 ) ) ;

        BFS ( 0 ) ;
        for ( register int i = 1; i <= n; ++i ) Write ( dis[i] < dis[i - 1] ) ;
        putchar ( '\n' ) ;

        return 0 ;
    }
}

int main () { return Program :: Run () ; }


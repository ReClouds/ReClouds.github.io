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
    inline int Run ()
    {
        puts ( "ReClouds" ) ;
        puts ( "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" ) ;
        
        return 0 ;
    }
}

int main () { return Program :: Run () ; }
#include "square_lib.h"

const int DOWN  = 1;
const int RIGHT = 0;

int main() {
    int  N = getN();
    int  L = getL();
    int  x = 1, y = 1;
    long l = 0;

    while ( l < L && y < N ) { l += getWeight( x, y, DOWN ); ++y; }
    while ( l < L && x < N ) { l += getWeight( x, y, RIGHT); ++x; }

    if ( l < L )  solution( -1, -1 );
    if ( l == L ) solution(  x,  y );

    --y; l -= getWeight( x, y, DOWN ); 

    while ( 1 ) {
        if      ( l < L && x < N ) { l += getWeight( x, y, RIGHT  ); ++x; }
        else if ( l > L && y > 1 ) { --y; l -= getWeight( x, y, DOWN ); }
        else if ( l == L ) solution(  x,  y );
        else               solution( -1, -1 );
    }
    return 0;
}


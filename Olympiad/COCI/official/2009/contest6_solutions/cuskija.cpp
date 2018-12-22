#include <cstdio>
#include <vector>

using namespace std;

int n;
vector< int > a[3]; // a[i] je lista brojeva iz ulaza koji pri dijeljenju s tri daju ostatak i

void load() {
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i ) {
		int t;
		scanf( "%d", &t );
		a[ t%3 ].push_back( t );
	}
}

// moze kaze da li se svi brojevi koji daju ostatak jedan ili dva mogu sloziti u "k" nizova,
// tako da unutar jednog niza vrijedi da suma nijedna dva susjedna nije djeljiva sa tri
int moze( int k ) {
	if( k < 0 ) return 0;
	if( k == 0 ) return a[1].size()+a[2].size() == 0;
	if( k == 1 ) return a[1].size() == 0 || a[2].size() == 0;
	if( k > a[1].size()+a[2].size() ) return 0;
	return 1;
}

int pop( int m ) { // pop(m) uzme jedan broj koji ima ostatak m sa tri iz vektora a i ispise ga
	if( !a[m].size() ) return 0;
	printf( "%d ", a[m].back() );
	a[m].pop_back();
	return 1;
}

// slaze ulazne brojeve sa ostatkom 1 ili 2 u k grupa, a izmedju grupa stavlja broj dijeljiv s tri
void slozi( int k ) {
	for(; k; --k ) {
		if( k == 1 ) while( pop(1) || pop(2) );
		if( k == 2 ) {
			if( a[1].size() == 0 ) pop(2);
			else if( a[2].size() == 0 ) pop(1);
			else while( pop(1) );
		}
		if( k > 2 ) {
			if( a[1].size() ) pop(1);
			else pop(2);
		}
		pop( 0 );
	}
}

// skombinira da li ce prva i zadnja grupa biti broj dijeljiv s tri ili ne, i onda pozove slozi
void solve() {
	if( moze( a[0].size()-1 ) ) {
		pop( 0 );
		slozi( a[0].size() );
		return;
	}
	if( moze( a[0].size() ) ) slozi( a[0].size() );
	else {
		if( moze( a[0].size()+1 ) ) slozi( a[0].size()+1 );
		else printf( "impossible\n" );
	}
}

int main(void) {
	load();
	solve();
	return 0;
}

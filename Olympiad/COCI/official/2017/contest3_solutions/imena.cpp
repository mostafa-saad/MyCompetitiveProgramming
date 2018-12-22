#include <iostream>
#include <string>
using namespace std;

bool jeInterZnak( char c ) {
    return c == '.' || c == '?' || c == '!';
}

bool imaInterZnakNaZadnjemMjestu( string rijec ) {
    return jeInterZnak( rijec[ rijec.size()-1 ] );
}

bool jeIme( string rijec ) {
    // ako prvo slovo nije veliko slovo engleske abecede
    if( rijec[ 0 ] < 'A' || rijec[ 0 ] > 'Z' ) {
        return false;
    }

    for( int i = 1; i < rijec.size(); ++i ) {
        if( (rijec[ i ] < 'a' || rijec[ i ] > 'z') && jeInterZnak(rijec[ i ]) == false ) {
            return false;
        }
    }
    return true;
}

int main () {
    int n;
    cin >> n;
    for( int i = 0; i < n; ++i ) {
        int cnt = 0;
        string rijec;
        do {
            cin >> rijec;
            if( jeIme( rijec ) ) {
                ++cnt;
            }
        } while( imaInterZnakNaZadnjemMjestu( rijec ) == false );
        cout << cnt << endl;
    }
    return 0;
}

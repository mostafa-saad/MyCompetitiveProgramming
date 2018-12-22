#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int K, N, igra, T;
    char Z;
    cin >> K;
    cin >> N;

    igra = 0;
    while(igra < 210)
    {
        cin >> T >> Z;
        igra += T;
        if ((Z == 'T') & (igra <= 210))
            K = (K % 8) + 1;
    }
    cout << K;
return 0;
}

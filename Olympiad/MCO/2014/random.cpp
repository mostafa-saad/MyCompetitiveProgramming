#include <iostream>
#include <cstdio>
#include <cmath>
#include <bitset>
#include <vector>

using namespace std;

const int MAX = 700000;
bitset<700005> bs;
vector<int> prime;

void sieve(){
    bs.reset();
    bs.flip();
    bs.set(0, false);
    bs.set(1, false);
    for(long long i = 2; i <= MAX; i++){
        if(bs.test(i)){
            for(long long j = i*i; j <= MAX; j+=i){
                bs.set(j, false);
            }
            prime.push_back( (int)(i) );
        }
    }
}

bool is_valid(unsigned int r){
	//is the number at most 3 consecutive repeated digi?
	int last_digit = -1, consecutive = 1;
	while(r > 0){
		if(last_digit == r%10){
			consecutive++;
		}
		else{
			consecutive = 1;
		}
		if(consecutive > 3){
			return false;
		}
		last_digit = r%10;
		r /= 10;
	}
	return true;
}

int main()
{
	sieve();
	int n, k, limit;
	cin >> n >> k;
	unsigned int r;
	bool ans;
	for(int i = 0; i < n; i++){
		cin >> r;
		if(r <= k ){
			cout << "NO" << endl;
		}
		else if(is_valid(r)){
			ans = true;
			if(sqrt(r) < k){
				limit = sqrt(r+1);
			}
			else{
				limit = k;
			}
			for(int j = 0; prime[j] <= limit; j++){
				if(r%prime[j] == 0){
					cout << "NO" << endl;
					ans = false;
					break;
				}
			}
			if(ans){
				cout << "YES" << endl;
			}
		}
		else{
			cout << "NO" << endl;
		}

	}

    return 0;
}

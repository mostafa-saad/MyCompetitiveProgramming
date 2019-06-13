#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


int main()
{
	// speed up std::cin & std::cout
	std::ios::sync_with_stdio(false);

	long long N;
	int M;
	std::vector<std::string> S;
	std::vector<long long> K;

	std::cin >> N >> M;
	for(int i = 0; i < M; ++i) {
		std::string S_i;
		long long K_i;
		std::cin >> S_i >> K_i;
		S.push_back(S_i);
		K.push_back(K_i);
	}

	long long minimum = 0;
	long long global_count = 0;

	for(int section = M - 1; section >= 0; --section) {

		const std::string& S_i = S[section];
		const long long K_i = K[section];

		int local_count = 0, diff_minimum = 0;

		for(int index = S_i.size() - 1; index >= 0; --index) {
			const char c = S_i[index];
			local_count += (c == 'F' ? 1 : -1);
			diff_minimum = std::min(diff_minimum, local_count);
		}

		const long long candidate_first = global_count + diff_minimum;
		const long long candidate_last = global_count + (K_i - 1) * local_count
		                                 + diff_minimum;

		minimum = std::min(minimum, std::min(candidate_first, candidate_last));
		global_count += local_count * K_i;
	}

	long long answer;

	// global_count = |female| - |male|
	if(global_count < 0) {

		answer = -1;

	} else {

		if(minimum >= -1) {
			answer = 0;
		} else {
			answer = -(minimum + 1);
		}
	}

	std::cout << answer << std::endl;

	return 0;
}

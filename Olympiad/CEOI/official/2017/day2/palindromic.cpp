// Greedy solution with rolling string hashes. Repeatedly takes the smallest possible
// chunk from the sides, using string hashes to quickly check for equality of chunks.
// Hash updating and comparison takes O(1), so the total running time is O(n).

#include <algorithm>
#include <cstring>
#include "assert.h"
#include "stdio.h"

#define MAX_WORD_LENGTH 5100000

int longest_palindromic_partition(char *word) {
	const int n = strlen(word);
	const unsigned int base = 131;  // Prime larger than ord('z')

	int done_chars = 0;  // Number of chars processed (greedily) on each side.
	int n_chunks = 0;  // Number of chunks produced so far.

	while (done_chars * 2 < n) {
		unsigned int left_hash=0, right_hash=0;  // Hashes of left and right chunks.
		unsigned int base_power=1;  // `base` to the power of (chunk_size - 1).
		for (int chunk_size=1; true; chunk_size++) {
			const int left_chunk_start = done_chars;
			const int right_chunk_start = n - done_chars - chunk_size;
			if (left_chunk_start + chunk_size - 1 >= right_chunk_start) {
				// Left and right chunk overlap; we have to merge them into a final center chunk.
				return n_chunks + 1;
			}
			// Left hash: "ab" -> "abc": 'a'*B^0 + 'b'*B^1 -> 'a'*B^0 + 'b'*B^1 + 'c'*B^2
			base_power = chunk_size == 1 ? 1 : base_power * base;
			left_hash += static_cast<unsigned int>(word[left_chunk_start + chunk_size - 1]) * base_power; 
			// Right hash: "bc" -> "abc": 'b'*B^0 + 'c'*B^1 -> 'a'*B^0 + 'b'*B^1 + 'c'*B^2
			right_hash = static_cast<unsigned int>(word[right_chunk_start]) + right_hash * base;
			if (left_hash == right_hash && strncmp(word + left_chunk_start, word + right_chunk_start, chunk_size) == 0) {
				// We found a good chunk.
				n_chunks += 2;
				done_chars += chunk_size;
				break;
			}
		}
	}

	return n_chunks;
}

int main() {
	int n;
	char word[MAX_WORD_LENGTH];
	scanf("%d\n", &n);	
	for (int i=0; i<n; i++) {
		scanf("%s\n", word);
		assert(strlen(word) <= MAX_WORD_LENGTH);
		printf("%d\n", longest_palindromic_partition(word));
	}
	return 0;
}
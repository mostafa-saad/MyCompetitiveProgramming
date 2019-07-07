#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

int N;

struct Segment {
    int index, sortedIndex;
    int start, length;
    bool direction;

    Segment(int index, int start, int length) : 
        index(index),
        start(start), 
        length(length), 
        direction(0) {
    }

    // Check if this segment is completely inside another segment
    bool isSubsetOf(const Segment& other) const {
        int relativeStart = (start - other.start + N) % N;
        return relativeStart + length <= other.length;
    }
};

// Returns whether the given solution covers the whole circle
bool checkSolution(const vector<Segment>& segments) {
    for (int direction = 0; direction < 2; direction++) {
        size_t n = segments.size();
        int hi = 0;
        for (size_t i = 0; i < 2*n; i++) {
            size_t j = i%n;
            if (segments[j].direction != direction) {
                continue;
            }
            int start = segments[j].start;
            if (i < n) {
                start -= N;
            }
            if (start > hi) {
                return false;
            }
            int end = start + segments[j].length;
            hi = max(hi, end);
        }
        if (hi < N) {
            return false;
        }
    }
    return true;
}

void printSolution(const vector<Segment>& segments) {
    vector<bool> directions(segments.size());
    for (const Segment& segment : segments) {
        directions[segment.index] = segment.direction;
    }
    for (bool d : directions) {
        cout << d;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    int M;
    cin >> N >> M;

    vector<Segment> segments;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        segments.emplace_back(i, a-1, ((b-a+N)%N)+1);
    }

    sort(segments.begin(), segments.end(), [](const Segment& a, const Segment& b) -> bool {
        if (a.start == b.start) {
            return a.length > b.length;
        }
        return a.start < b.start;
    });

    for (int i = 0; i < M; i++) {
        segments[i].sortedIndex = i;
    }

    int hi[2] = {0, 0};
    for (int i = 0; i < 2*M; i++) {
        int j = i%M;
        int start = segments[j].start;
        if (i < M) {
            start -= N;
        }
        if (start > hi[0] || start > hi[1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        int end = start + segments[j].length;
        if (hi[0] < hi[1]) {
            segments[j].direction = 0;
        }
        else {
            segments[j].direction = 1;
        }
        hi[segments[j].direction] = max(hi[segments[j].direction], end);
    }
    if (checkSolution(segments)) {
        printSolution(segments);
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
}

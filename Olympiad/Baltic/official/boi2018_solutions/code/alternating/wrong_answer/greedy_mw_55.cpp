#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

int M, N;

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

set<pair<int, pair<int, pair<int, int> > > > checked;

void rec(vector<Segment>& segments, int i, int hi0, int hi1, int inRow) {
    if (i == 2*M) {
        if (checkSolution(segments)) {
            printSolution(segments);
            exit(0);
        }
        return;
    }
    auto key = make_pair(inRow, make_pair(i, make_pair(hi0, hi1)));
    if (checked.count(key))
        return;
    checked.insert(key);
    int j = i%M;
    int start = segments[j].start;
    if (i < M) {
        start -= N;
    }
    if (start > hi0 || start > hi1) {
        return;
    }
    int end = start + segments[j].length;
    if (end > hi1 || end <= hi0) {
        int newInRow = inRow;
        if (hi1 > hi0) {
            ++newInRow;
        }
        else {
            newInRow = 0;
        }
        if (newInRow < 2) {
            segments[j].direction = 1;
            rec(segments, i+1, hi0, max(hi1, end), newInRow);
        }
    }
    if (end > hi0 || end <= hi1) {
        int newInRow = inRow;
        if (hi0 > hi1) {
            ++newInRow;
        }
        else {
            newInRow = 0;
        }
        if (newInRow < 2) {
            segments[j].direction = 0;
            rec(segments, i+1, max(hi0, end), hi1, newInRow);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
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
    
    for (int iteration = 0; iteration < 1000; ++iteration) {
        int start = rand() % M;
        auto& startSegment = segments[start];
        startSegment.direction = 1;
        int hi[2] = {
            startSegment.start,
            startSegment.start + startSegment.length
        };
        for (int i = 1; i < M; i++) {
            auto& segment = segments[(i + start)%M];
            segment.direction = 0;
            if (hi[1] < hi[0]) {
                segment.direction = 1;
            }
            int startPos = segment.start;
            if (startPos < startSegment.start) {
                startPos += N;
            }
            int end = startPos + segment.length;
            hi[segment.direction] = max(hi[segment.direction], end);
        }
        if (checkSolution(segments)) {
            printSolution(segments);
            return 0;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

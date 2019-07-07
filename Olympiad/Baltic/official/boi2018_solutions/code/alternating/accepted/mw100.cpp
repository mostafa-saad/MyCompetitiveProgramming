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
    set<Segment*> enclosedSegments;
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

    // Set direction of all children in the opposite direction to this node
    void assignChildren() {
        for (Segment* child : enclosedSegments) {
            child->direction = !direction;
        }
    }

    // Set direction of this node and direction of all children in the opposite direction
    void assign(bool newDirection) {
        direction = newDirection;
        assignChildren();
    }
};

// Assign the children of each given segment in the opposite direction to the parent
void assignChildren(vector<Segment>& segments) {
    for (Segment& segment : segments) {
        segment.assignChildren();
    }
}

// Assign the given segments alternating directions, starting from startIndex
// Note that if independentSegments has an odd number of elements then
// independentSegments[startIndex-1] and independentSegments[startIndex] are
// assigned the same direction
void assignAlternating(vector<Segment*>& independentSegments, int startIndex) {
    for (size_t i = 0; i < independentSegments.size(); i++) {
        size_t j = (i + startIndex) % independentSegments.size();
        independentSegments[j]->assign(i%2);
    }
}

// Returns whether the interval between the beginning of the segment with
// index startIndex and the beginning of the segment with index endIndex
// is completely covered in the given direction
bool checkPartialSolution(const vector<Segment>& segments, size_t startIndex, size_t endIndex, bool direction) {
    size_t n = segments.size();
    int hi = segments[startIndex].start;
    size_t length = ((endIndex - startIndex + n - 1) % n) + 1;
    for (size_t i = 0; i < length; i++) {
        size_t j = (i+startIndex) % n;
        if (segments[j].direction != direction) {
            continue;
        }
        int start = segments[j].start;
        if (j < startIndex) {
            start += N;
        }
        if (start > hi) {
            return false;
        }
        int end = start + segments[j].length;
        hi = max(hi, end);
    }
    int start = segments[endIndex].start;
    if (endIndex <= startIndex) {
        start += N;
    }
    return start <= hi;
}

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
    
    vector<Segment*> independentSegments;
    Segment* lastSegment = &segments[0];
    for (int i = 1; i < 2*M; i++) {
        int j = i%M;
        Segment* currentSegment = &segments[j];
        if (currentSegment != lastSegment && currentSegment->isSubsetOf(*lastSegment)) {
            lastSegment->enclosedSegments.insert(currentSegment);
        }
        else {
            lastSegment = currentSegment;
            if (i >= M) {
                independentSegments.push_back(lastSegment);
            }
        }
    }

    if (independentSegments.size()%2 == 0) {
        assignAlternating(independentSegments, 0);
        assignChildren(segments);
        if (checkSolution(segments)) {
            printSolution(segments);
        }
        else {
            cout << "impossible" << endl;
        }
    }
    else {
        for (size_t i = 0; i < independentSegments.size(); i++) {
            auto A = independentSegments[(i+0)%independentSegments.size()];
            auto B = independentSegments[(i+1)%independentSegments.size()];
            auto C = independentSegments[(i+2)%independentSegments.size()];
            auto D = independentSegments[(i+3)%independentSegments.size()];
            A->assign(0);
            D->assign(0);
            B->assign(1);
            C->assign(1);
            if (checkPartialSolution(segments, A->sortedIndex, D->sortedIndex, 0)) {
                assignAlternating(independentSegments, int((i+2)%independentSegments.size()));
                assignChildren(segments);
                if (checkSolution(segments)) {
                    printSolution(segments);
                }
                else {
                    cout << "impossible" << endl;
                }
                return 0;
            }
        }
        cout << "impossible" << endl;
    }
}

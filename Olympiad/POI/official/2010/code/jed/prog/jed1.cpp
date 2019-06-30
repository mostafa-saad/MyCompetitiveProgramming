/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jed1.cpp                                      *
 *   Autor:                Przemyslaw Horban                             *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *                         Korzysta z STLa w minimalnym stopniu.         *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cassert> /* DO NOT DEFINE NDEBUG!!! */
#include<queue>
#include<vector>
#include<list>
#include<algorithm>
#include<map>
#include<cstring>
#include<cctype>

using namespace std;
#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define fi(i,n) for(int i = 0, i##end = (n); i < i##end; i++)
#define ft(i,a,b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define fd(i,a,b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define fs(i,C) fi(i,(C).size())
#define ALL(V) (V).begin(), (V).end()
#define SET(T, c) memset(T, c, sizeof(T))
#define VI vector<int>
#define PB push_back
#define PII pair<int, int>
#define SEC second
#define FST first
#define MP make_pair
#define SZ(C) (C).size()

typedef long long LL;

int ri() { int n; assert(scanf(" %d", &n) == 1); return n; }
void pi(int n) { printf("%d\n", n); }
template<class R, class T>
R conv(const T &t) { stringstream ss; ss << t; R r; ss >> r; return r; }
LL gcd(LL a, LL b) { if(b == 0) return a; else return gcd(b, a % b); }

class BinRep {
    friend class BinRepIter;
public:
    void push_front(int length, int value);
    void push_back(int length, int value);
    void pop_back(int length);
    int bit(int index) const;
    int size();
    void clear();
    void clearLead0();
private:
    deque<int> bLen;
    deque<bool> bVal;
};

class BinRepIter {
public:
    BinRepIter(const BinRep &rep);
    void step(int length);
    void currentBlock(int *length, int *value);
    bool atEnd();
private:
    void rewind();
    const BinRep &binRep;
    int nextBlockIdx;
    int steps;
    int value;
};

class BigBin {
public:
    BigBin();
    BigBin(const BinRep &rep);
    BigBin(int n);
    static BigBin powerOfTwo(int k);

    void read();
    void write();

    int size();
    int count1Groups();
    int operator[](int index) const;

    BigBin operator+(const BigBin &other) const;
    BigBin operator-(const BigBin &other) const;
    BigBin operator>>(int n) const;
private:
    void stepCommonBlock(BinRepIter &it1, BinRepIter &it2, int *length,
                         int *value1, int *value2) const;
    void initWithRep(const BinRep &rep);
    BinRep rep;
};

int main(){
    BigBin N;
    N.read();

    BigBin ls;
    if(N[N.size() - 2] == 1)
        ls = BigBin::powerOfTwo(N.size() - 1);
    else {

        ls = N - BigBin::powerOfTwo(N.size() - 2) + 1;
    }
    ls = ls + (N >> 1) + N.count1Groups();
    ls = ls - N.size();
    ls.write();
    return 0;
}

BigBin::BigBin() {
    initWithRep(BinRep());
}

BigBin::BigBin(const BinRep &rep) {
    initWithRep(rep);
}

BigBin::BigBin(int n) {
    while(n != 0) {
        rep.push_front(1, n & 1);
        n /= 2;
    }
}

BigBin BigBin::powerOfTwo(int k) {
    BinRep rep;
    rep.push_front(k, 0);
    rep.push_front(1, 1);
    return rep;
}

void BigBin::read() {
    rep.clear();
    int val = 1;
    fi(i, ri()) {
        rep.push_back(ri(), val);
        val = 1 - val;
    }
}

void BigBin::write() {
    vector<int> sizes;
    BinRepIter it(rep);
    int v_last = -1;
    while(!it.atEnd()) {
        int l, v; it.currentBlock(&l, &v);
        it.step(l);
        assert(sizes.empty() || v_last == 1 - v);
        sizes.push_back(l);
        v_last = v;
    }
    assert(sizes.size() == 0 || v_last == 1);
    pi(sizes.size());
    fd(i, sizes.size() - 1, 0) {
        printf("%d", sizes[i]);
        putchar(i > 0 ? ' ' : '\n');
    }
}

int BigBin::size() {
    return rep.size();
}

int BigBin::count1Groups() {
    BinRepIter it(rep);
    int cnt = 0;
    while(!it.atEnd()) {
        int l, v; it.currentBlock(&l, &v);
        cnt += v == 1;
        it.step(l);
    }
    return cnt;
}

int BigBin::operator[](int index) const {
    int b = rep.bit(index);
    if(b < 0) return 0;
    return b;
}

BigBin BigBin::operator+(const BigBin &other) const {
    BinRep rep;
    BinRepIter it1(this->rep), it2(other.rep);
    int c = 0;
    while(true) {
        int le, v1, v2; stepCommonBlock(it1, it2, &le, &v1, &v2);
        if(le == -1) break;
        if(v1 == 0 && v2 == 0) {
            if(c == 0)
                rep.push_front(le, 0);
            else {
                rep.push_front(1, 1);
                rep.push_front(le - 1, 0);
                c = 0;
            }
        }
        else if(v1 + v2 == 1) {
            rep.push_front(le, 1 - c);
        }
        else if(v1 == 1 && v2 == 1) {
            if(c == 0) {
                rep.push_front(1, 0);
                rep.push_front(le - 1, 1);
            }
            else
                rep.push_front(le, 1);
            c = 1;
        }
    }
    if(c == 1)
        rep.push_front(1, 1);
    return BigBin(rep);
}

BigBin BigBin::operator-(const BigBin &other) const {
    BinRep rep;
    BinRepIter it1(this->rep), it2(other.rep);
    int c = 0;
    while(true) {
        int le, v1, v2; stepCommonBlock(it1, it2, &le, &v1, &v2);
        if(le == -1) break;
        if(v1 == v2) {
            rep.push_front(le, c);
        }
        else if(v1 == 0 && v2 == 1) {
            if(c == 0) {
                rep.push_front(1, 1);
                rep.push_front(le - 1, 0);
                c = 1;
            }
            else {
                rep.push_front(le, 0);
            }
        }
        else if(v1 == 1 && v2 == 0) {
            if(c == 0) {
                rep.push_front(le, 1);
            }
            else {
                rep.push_front(1, 0);
                rep.push_front(le - 1, 1);
                c = 0;
            }
        }
    }
    assert(c == 0);
    return BigBin(rep);
}


BigBin BigBin::operator>>(int n) const {
    BigBin b(*this);
    b.rep.pop_back(n);
    return b;
}

void BigBin::initWithRep(const BinRep &rep) {
    this->rep = rep;
    this->rep.clearLead0();

    #ifndef NDEBUG
    BinRepIter it(this->rep);
    int v_last = -1;
    while(!it.atEnd()) {
        int l, v; it.currentBlock(&l, &v);
        it.step(l);
        assert(v == 1 || v == 0);
        assert(v_last == -1 || v_last == 1 - v);
        v_last = v;
    }
    assert(v_last == 1 || v_last == -1);
    #endif
}

void BigBin::stepCommonBlock(BinRepIter &it1, BinRepIter &it2, int *length,
                             int *value1, int *value2) const {
    if(it1.atEnd() && it2.atEnd()) {
        *length = -1;
        return;
    }

    int l1, l2;
    it1.currentBlock(&l1, value1);
    it2.currentBlock(&l2, value2);

    if(it1.atEnd()) {
        *value1 = 0;
        l1 = l2;
    }

    if(it2.atEnd()) {
        *value2 = 0;
        l2 = l1;
    }
    *length = (l1 < l2 ? l1 : l2);

    it1.step(*length);
    it2.step(*length);
}

void BinRep::push_front(int length, int value) {
    if(length <= 0) return;
    if(bVal.empty() || bVal.front() != value) {
        bVal.push_front(value);
        bLen.push_front(length);
    }
    else {
        bLen.front() += length;
    }
}

void BinRep::push_back(int length, int value) {
    if(length <= 0) return;
    if(bVal.empty() || bVal.back() != value) {
        bVal.push_back(value);
        bLen.push_back(length);
    }
    else {
        bLen.back() += length;
    }
}

void BinRep::pop_back(int length) {
    while(true) {
        if(length <= 0) break;
        if(bLen.empty()) break;
        if(bLen.back() > length) {
            bLen.back() -= length;
            length = 0;
        }
        else {
            length -= bLen.back();
            bLen.pop_back();
            bVal.pop_back();
        }
    }
}

int BinRep::bit(int index) const {
    if(index < 0) return -1;
    BinRepIter it(*this);
    while(true){
        if(it.atEnd()) return -1;
        int l, v; it.currentBlock(&l, &v);
        if(index < l) return v;
        else {
            it.step(l);
            index -= l;
        }
    }
}

int BinRep::size() {
    int l = 0;
    fe(e, bLen) l += *e;
    return l;
}

void BinRep::clear() {
    bLen.clear();
    bVal.clear();
}

void BinRep::clearLead0() {
    while(!bVal.empty() && (bVal.front() == 0 || bLen.front() == 0)) {
        bVal.pop_front();
        bLen.pop_front();
    }
}

BinRepIter::BinRepIter(const BinRep& rep): binRep(rep) {
    steps = 0;
    value = 0;
    nextBlockIdx = rep.bLen.size() - 1;
}

void BinRepIter::step(int length) {
    while(true) {
        rewind();
        if(length <= 0) return;
        if(atEnd()) return;
        if(length < steps) {
            steps -= length;
            length = 0;
        }
        else {
            length -= steps;
            steps = 0;
        }
    }
}

void BinRepIter::currentBlock(int *length, int *value) {
    rewind();
    *length = steps;
    *value = this->value;
    if(atEnd()) *length = -1;
}

bool BinRepIter::atEnd() {
    return steps == 0 && nextBlockIdx == -1;
}

void BinRepIter::rewind() {
    if(!atEnd() && steps == 0) {
        value = binRep.bVal[nextBlockIdx];
        steps = binRep.bLen[nextBlockIdx];
        nextBlockIdx--;
    }
}

#include "koala.h"
#include <bits/stdc++.h>
using namespace std;

#define FO(i,a,b) for (int i = (a); i < (b); i++)
#define pb push_back
#define sz(v) ((int)v.size())

struct Query {
    vector <int> am;
};

struct Response {
    vector <bool> v;
};

int N, W;

Response makeQuery (Query q) {
    int *B = (int *)malloc(sizeof(int)*N);
    FO (i,0,N) B[i] = q.am[i];
    int *R = (int *)malloc(sizeof(int)*N);
    playRound(B,R);
    Response r;
    FO (i,0,N) {
        if (R[i] > B[i]) {
            r.v.pb(true);
        } else {
            r.v.pb(false);
        }
    }
    free(B);
    free(R);
    return r;
}

Response makeUniformQuery (set<int> &cand, int am) {
    Query q;
    FO (i,0,N) {
        if (cand.find(i) != cand.end()) {
            q.am.pb(am);
        } else {
            q.am.pb(0);
        }
    }
    return makeQuery(q);
}

set<int> responseToSet (Response r) {
    set <int> s;
    FO (i,0,N) if (r.v[i]) s.insert(i);
    return s;
}

int minValue(int _N, int _W) {
    N = _N; W = _W;
    set <int> cand;
    cand.insert(0);
    Response r = makeUniformQuery(cand, 1);
    FO (i,0,N) {
        if (!r.v[i]) return i;
    }
    assert (false);
}

int actualGetMax() {
    set <int> cand;
    FO (i,0,N) cand.insert(i);
    while (cand.size() > 1) {
        Response r = makeUniformQuery(cand, W/(int)cand.size());
        set <int> newC;
        FO (i,0,N) if (cand.find(i) != cand.end() && r.v[i]) newC.insert(i);
        cand = newC;
    }
    return *(cand.begin());
}

int maxValue(int _N, int _W) {
    N = _N; W = _W;
    return actualGetMax();
}

int greaterValue(int _N, int _W) {
    N = _N; W = _W;
    set <int> f2 = {0,1};
    int cands[4] = {1,3,6,8};
    int lo = 0;
    int hi = 3;
    int mid;
    while (lo <= hi) {
        mid = (lo+hi)/2;
        Response r = makeUniformQuery(f2, cands[mid]);
        set <int> origRes = responseToSet(r);
        set <int> res;
        for (auto c : f2) {
            if (origRes.find(c) != origRes.end()) res.insert(c);
        }
        switch (res.size()) {
            case 0:
                hi = mid-1;
                break;
            case 1:
                return *(res.begin());
            case 2:
                lo = mid+1;
                break;
        }
    }
    assert(false);
}

vector <int> sortRange (vector <int> vals);
void solveMain(int *P);
void allValues(int _N, int _W, int *P) {
    N = _N; W = _W;
    if (_W == 2*_N) {
        vector <int> startVals;
        FO (i,0,N) startVals.pb(i);
        vector <int> endVals = sortRange(startVals);
        FO (i,0,N) P[endVals[i]] = N-i;
    } else {
        solveMain(P);
    }
}

// returns greater of the 2
int sub4cmp(int a, int b) {
    set<int> vals = {a,b};
    set<int> takens = responseToSet(makeUniformQuery(vals, W/2));
    if (takens.find(a) != takens.end()) return a;
    else return b;
}

vector <int> sortRange (vector <int> vals) {
    if (vals.size() == 1) return vals;
    vector <int> fV, sV;
    FO (i,0,sz(vals)) {
        if (i%2) sV.pb(vals[i]);
        else fV.pb(vals[i]);
    }
    vector <int> sF = sortRange(fV);
    vector <int> sS = sortRange(sV);
    int fI(0), sI(0);
    vector <int> retV;
    while (fI < sz(sF) || sI < sz(sS)) {
        if (fI == sz(sF)) retV.pb(sS[sI++]);
        else if (sI == sz(sS)) retV.pb(sF[fI++]);
        else {
            if (sub4cmp(sF[fI], sS[sI]) == sF[fI]) {
                retV.pb(sF[fI++]);
            } else {
                retV.pb(sS[sI++]);
            }
        }
    }
    return retV;
}

set <int> lowestVals;
#define N_BUCKETS 9
#define B_SIZ 10
vector <int> startBuckets[N_BUCKETS];
vector <int> sortedB[N_BUCKETS];
int valToPos[105];

int maxInSet(set<int> &s) {
    // Need this:
    assert(s.size() <= 9);
    set<int> qSet(s);
    for (int i = 10; i >= 1; i--) {
        if (qSet.size() == 9) break;
        qSet.insert(valToPos[i]);
    }
    set<int> taken;
    if (s.size() == 1) {
        taken = responseToSet(makeUniformQuery(qSet, 10));
    } else {
        taken = responseToSet(makeUniformQuery(qSet, 11));
    }
    for (int v : s) {
        if (taken.find(v) != taken.end()) return v;
    }
    assert(false);
}

void solveMain (int *P) {
    lowestVals.clear();
    FO (i,0,N_BUCKETS) {
        startBuckets[i].clear();
        sortedB[i].clear();
    }
    int mx = actualGetMax();
    set<int> mxSet({mx});
    set<int> notLowestVals = 
        responseToSet(makeUniformQuery(mxSet, 10));
    FO (i,0,N) {
        if (notLowestVals.count(i) == 0) lowestVals.insert(i);
    }
    assert(lowestVals.size() == 10);
    FO (i,0,N) {
        if (lowestVals.find(i) != lowestVals.end()) continue;
        FO (b,0,N_BUCKETS) {
            if (startBuckets[b].size() < B_SIZ) {
                startBuckets[b].pb(i);
                break;
            }
        }
    }
    // Get bottom 10:
    set <int> lowLeft (lowestVals);
    while (lowLeft.size()) {
        if (lowLeft.size() == 1) {
            valToPos[1] = *lowLeft.begin();
            break;
        }
        set <int> res =
            responseToSet(makeUniformQuery(lowLeft, lowLeft.size()-1));
        for (int v : res) {
            if (lowLeft.find(v) != lowLeft.end()) {
                valToPos[lowLeft.size()] = v;
                lowLeft.erase(v);
                break;
            }
        }
    }
    FO (b,0,N_BUCKETS) {
        set <int> remThings(startBuckets[b].begin(), startBuckets[b].end());
        while (remThings.size()) {
            if (remThings.size() == 10) {
                // one special case:
                set <int> res = responseToSet(makeUniformQuery(remThings, 10));
                set <int> cMax;
                for (int v : res) {
                    if (remThings.find(v) != remThings.end()) {
                        cMax.insert(v);
                    }
                }
                if (cMax.size() == 2) {
                    int mx = maxInSet(cMax);
                    sortedB[b].pb(mx);
                    cMax.erase(mx);
                    sortedB[b].pb(*cMax.begin());
                    remThings.erase(mx);
                    remThings.erase(*cMax.begin());
                } else if (cMax.size() == 1) {
                    sortedB[b].pb(*cMax.begin());
                    remThings.erase(*cMax.begin());
                } else {
                    assert(false);
                }
            } else {
                int mx;
                if (remThings.size() == 1) mx = *remThings.begin();
                else mx = maxInSet(remThings);
                sortedB[b].pb(mx);
                remThings.erase(mx);
            }
        }
    }
    // Merge buckets:
    // Sort buckets into increasing order not decreasing:
    FO (i,0,N_BUCKETS) reverse(sortedB[i].begin(), sortedB[i].end());
    vector <int> sortedAll;
    while(true) {
        set <int> cFronts;
        FO (i,0,N_BUCKETS) {
            if (sortedB[i].size()) {
                cFronts.insert(sortedB[i].back());
            }
        }
        if (cFronts.empty()) break;
        int mx = maxInSet(cFronts);
        sortedAll.pb(mx);
        FO (i,0,N_BUCKETS) {
            if (sortedB[i].size() && sortedB[i].back() == mx) {
                sortedB[i].pop_back();
            }
        }
    }
    for (int i = 10; i >= 1; i--) {
        sortedAll.pb(valToPos[i]);
    }
    FO (i,0,sz(sortedAll)) {
        P[sortedAll[i]] = N-i;
    }
}


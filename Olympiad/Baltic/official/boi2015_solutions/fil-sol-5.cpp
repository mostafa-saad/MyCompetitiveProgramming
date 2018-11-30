/* BOI 2015
 * Task "File paths"
 * Alternative model solution
 * Michał Glapa
 */
#include<bits/stdc++.h>
using namespace std;

namespace solution {
    const int MX = (1e4),
          MXK = (1e6) + 7;

    int n, m, k, symlinkLength;

    int symlinkPathLengths[MXK],
        cycleLengths[MXK];

    vector<int> factors[MXK];

    vector<pair<int,int>> graph[MX];
    bool result[MX];


    void computeFactors(int k) {
        for(int i = 1; i <= k; i++)
            for(int j = 0; j <= k; j+=i)
                factors[j].push_back(i);
    }

    bool isFile(int a) {
        return a >= n + 1;
    }

    bool isDir(int a) {
        return a <= n;
    }

    void readAndConstructGraph() {
        cin >> n >> m >> k;
        cin >> symlinkLength;
        symlinkLength++;

        for(int i = 1; i <= n; i++) {
            int tmp, length;
            cin >> tmp >> length;
            graph[tmp].push_back(make_pair(i, length + 1));
        }

        //files will be named from n + 1 to n + m;
        for(int i = n + 1; i <= n + m; i++) {
            int tmp, length;
            cin >> tmp >> length;
            graph[tmp].push_back(make_pair(i, length));
        }
    }
    void findSymlinkPathLengths(int v = 0, int length = 1) {
        if(isDir(v)) {
            if(length + symlinkLength <= k)
                symlinkPathLengths[length + symlinkLength] = true;
        }
        for(auto i : graph[v])
            findSymlinkPathLengths(i.first, length + i.second);
    }

    vector<pair<int,int>> dfsStack;

    //assumes that DFS currently has just visited v
    template<bool useCycles>
        void computeResult(int v, int length) {
            assert(isFile(v));
            result[v] = false;

            if(length == k)
                result[v] = true;
            for(auto i : dfsStack) {
                int lengthDown = length - i.second;
                if(symlinkPathLengths[k - lengthDown] == true)
                    result[v] = true;
            }

            if(useCycles) {
                int needToFillWithCycles = k - length;

                for(auto i : factors[needToFillWithCycles])
                    if(cycleLengths[i] > 0)
                        result[v] = true;
            }
        }

    void addCyclesDown(int v, int length, int rootLength, int mod) {
        if(isFile(v))
            return;
        int cycLength = length - rootLength + symlinkLength;
        assert(cycLength >= 2);
        if(cycLength <= k)
            cycleLengths[cycLength] += mod;
        for(auto i : graph[v])
            addCyclesDown(i.first, length + i.second, rootLength, mod);

    }

    template<bool useCycles>
        void mainDfs(int v = 0, int length = 1) {
            if(isDir(v))
                dfsStack.push_back(make_pair(v, length));
            else
                computeResult<useCycles>(v, length);

            addCyclesDown(v, length, length, 1);

            for(auto i : graph[v])
                mainDfs<useCycles>(i.first, length + i.second);

            addCyclesDown(v, length, length, -1);

            if(isDir(v))
                dfsStack.pop_back();
        }
};
#ifndef NOT_SOLUTION
int main() {
    solution::readAndConstructGraph();
    solution::computeFactors(solution::k);
    solution::findSymlinkPathLengths();
    solution::mainDfs<true>();
    for(int i = solution::n + 1; i <= solution::n + solution::m; i++)
        cout << (solution::result[i] ? "YES\n" : "NO\n");
}
#endif


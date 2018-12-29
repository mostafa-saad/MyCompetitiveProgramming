/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klo.cpp                                                   *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Sposrod n stosow klockow wybrac takie k kolejnych, by ich *
 *             wysokosci mozna bylo wyrownac dokladajac lub zdejmujac jak*
 *             najmniejsza liczbe klockow.                               *
 *             Dla ustalonych k kolejnych stosow optymalna wysokoscia    *
 *             jest mediana wysokosci. Koszt to suma odleg³oaci wysoko¶ci*
 *             stosow od mediany. Wystarczy wiec policzyc dynamiczna     *
 *             mediane.                                                  *
 *                                                                       *
 *************************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define LL long long

vector<int> vi;

// Lewy syn, prawy syn i rodzic danego wierzcho³ka.
#define LEFT(x)  ((x)<<1)
#define RIGHT(x) (LEFT(x) | 1)
#define PAR(x)   ((x)>>1)

struct Node {
    LL value_;
    int count_;
    int subtree_size_;
    LL subtree_sum_;

    Node() : value_(0), count_(0), subtree_size_(0), subtree_sum_(0) {}
};

class Tree {
    public:
    Tree() {}
    Tree(vector<int> values) : tab_(values.size() << 2) {
        fill_tab(values.begin(), values.end(), 1);
    }

    int find(int x) const {
        int idx = 1;
        while (true) {
            if (x < tab_[idx].value_) {
                idx = LEFT(idx);
            } else if (x > tab_[idx].value_) {
                idx = RIGHT(idx);
            } else {
                return idx;
            }
        }
    }

    // Popraw liczno¶æ poddrzew oraz sumê warto¶ci na ¶cie¿ce od idx do korzenia.
    void fix(int idx) {
        while (idx != 1) {
            idx = PAR(idx);
            int idx2 = LEFT(idx);
            tab_[idx].subtree_size_ = tab_[idx].count_ + tab_[idx2].subtree_size_ + tab_[idx2 | 1].subtree_size_;
            tab_[idx].subtree_sum_ = tab_[idx].value_ * tab_[idx].count_ + tab_[idx2].subtree_sum_ + tab_[idx2 | 1].subtree_sum_;
        }
    }

    void insert(int x) {
        int pos = this->find(x);
        ++tab_[pos].count_;
        ++tab_[pos].subtree_size_;
        tab_[pos].subtree_sum_ += tab_[pos].value_;
        this->fix(pos);
    }

    void erase(int x) {
        int pos = this->find(x);
        --tab_[pos].count_;
        --tab_[pos].subtree_size_;
        tab_[pos].subtree_sum_ -= tab_[pos].value_;
        this->fix(pos);
    }

    int median() const {
        int sz = (tab_[1].subtree_size_ >> 1) + 1;
        int pos = 1;
        while (true) {
            int pos2 = LEFT(pos);
            if (sz <= tab_[pos2].subtree_size_) {
                pos = pos2;
            } else if (sz <= tab_[pos2].subtree_size_ + tab_[pos].count_) {
                return tab_[pos].value_;
            } else {
                sz -= tab_[pos2].subtree_size_ + tab_[pos].count_;
                pos = pos2 | 1;
            }
        }
    }

    LL error() const {
        LL med = this->median();
        LL err = 0;
        int sz = (tab_[1].subtree_size_ >> 1) + 1;
        int pos = 1;
        while (true) {
            int pos2 = pos << 1;
            if (sz <= tab_[pos2].subtree_size_) {
                // Mediana jest po lewej, czyli jest mniejsza od aktualnej warto¶ci.
                err += (tab_[pos].value_ - med) * tab_[pos].count_;
                err += tab_[pos2 | 1].subtree_sum_ - med * tab_[pos2 | 1].subtree_size_;
                pos = pos2;
            } else if (sz <= tab_[pos2].subtree_size_ + tab_[pos].count_) {
                err += med * tab_[pos2].subtree_size_ - tab_[pos2].subtree_sum_;
                err += tab_[pos2 | 1].subtree_sum_ - med * tab_[pos2 | 1].subtree_size_;
                return err;
            } else {
                // Mediana jest po prawej, czyli jest wiêksza od aktualnej warto¶ci.
                err += (med - tab_[pos].value_) * tab_[pos].count_;
                err += med * tab_[pos2].subtree_size_ - tab_[pos2].subtree_sum_;
                sz -= tab_[pos2].subtree_size_ + tab_[pos].count_;
                pos = pos2 | 1;
            }
        }

    }

    private:
    template<typename iterator>
    void fill_tab(iterator beg, iterator end, int idx) {
        if (beg == end) return;

        iterator mid = beg + ((end - beg) >> 1);
        tab_[idx].value_ = *mid;

        fill_tab(beg, mid, LEFT(idx));
        fill_tab(mid + 1, end, RIGHT(idx));
    }

    vector<Node> tab_;
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        vi.push_back(x);
    }

    vector<int> vi_sorted = vi;
    sort(vi_sorted.begin(), vi_sorted.end());

    LL best_error = vi.size() * 1000000000LL;
    int best_pos = 0;
    int best_val = -1;

    Tree tree(vi_sorted);
    for (int i = 0; i < k - 1; ++i) tree.insert(vi[i]);

    for (int i = k - 1; i < n; ++i) {
        tree.insert(vi[i]);

        LL cand = tree.error();
        if (cand < best_error) {
            best_error = cand;
            best_pos = i;
            best_val = tree.median();
        }

        tree.erase(vi[i + 1 - k]);
    }

    for (int i = best_pos + 1 - k; i <= best_pos; ++i) vi[i] = best_val;

    printf("%lld\n", best_error);
    for (int i = 0; i < n; ++i) printf("%d\n", vi[i]);
}

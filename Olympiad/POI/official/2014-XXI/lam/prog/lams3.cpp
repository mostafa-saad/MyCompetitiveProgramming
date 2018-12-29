/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Zlozonosc pamieciowa: O(n log n)                                    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Drzewo 2D                                     *
 *                                                                       *
 *************************************************************************/

#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

namespace treap {
struct Node {
    Node* left;
    Node* right;
    const long long key;
    const int weight;
    int size;

    Node(long long key) : left(NULL), right(NULL), key(key), weight(rand()), size(1) {}
    ~Node() {
        delete left;
        delete right;
    }

    void UpdateSize();
};

int NodeSize(const Node* node) {
    return node ? node->size : 0;
}

void Node::UpdateSize() {
    size = 1 + NodeSize(left) + NodeSize(right);
}

Node* Insert(Node* root, long long key) {
    if (!root) {
        return new Node(key);
    }

    if (key < root->key) {
        Node* other = Insert(root->left, key);
        if (other->weight < root->weight) {
            root->left = other->right;
            other->right = root;
            root->UpdateSize();
            other->UpdateSize();
            return other;
        } else {
            root->left = other;
            root->UpdateSize();
            return root;
        }
    } else {
        Node* other = Insert(root->right, key);
        if (other->weight < root->weight) {
            root->right = other->left;
            other->left = root;
            root->UpdateSize();
            other->UpdateSize();
            return other;
        } else {
            root->right = other;
            root->UpdateSize();
            return root;
        }
    }
}

int CountLessOrEqual(Node* root, long long key) {
    int result = 0;
    while (root) {
        if (root->key <= key) {
            result += 1 + NodeSize(root->left);
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return result;
}
}  // namespace treap

typedef pair<pair<long long, long long>, int> Lamp;  // ((x, y), id)

void Distort(long long &x, long long& y) {
    long long m = max(max(x, -x), max(y, -y));
    long long d = (2 * 1000 * 1000 * 1000 + 2 + m - 1) / m;
    x *= d;
    y *= d;
    ++x;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 * y2 == x2 * y1)
        Distort(x2, y2);
    if (x1 * y2 - x2 * y1 < 0) {
        swap(x1, x2);
        swap(y1, y2);
    }
    vector<Lamp> lamps;
    for (int i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;
        lamps.push_back(make_pair(
                            make_pair(x1 * y - y1 * x, y2 * x - x2 * y), i));
    }

    vector<int> k(n);
    for (int i = 0; i < n; ++i)
        cin >> k[i];

    sort(lamps.begin(), lamps.end());

    int T = 1;  // rozmiar (liczba lisci) drzewka przedzialowego
    while (T < n) T *= 2;
    vector<treap::Node*> tree(2 * T);

    vector<int> result(n);
    for (size_t i = 0; i < lamps.size(); ++i) {
        const int lamp_id = lamps[i].second;
        // obliczenie odpowiedzi dla lampy lamp_id
        int cur_k = k[lamp_id];
        int a = 1;
        while (a < T) {
            int temp = CountLessOrEqual(tree[2 * a], lamps[i].first.second);
            if (temp < cur_k) {
                cur_k -= temp;
                a = 2 * a + 1;
            } else {
                a = 2 * a;
            }
        }
        a -= T;
        // zapisanie odpowiedzi
        result[lamp_id] = min(a, lamp_id);
        // wstawienie lampy do drzewa 2d
        int b = T + result[lamp_id];
        while (b > 0) {
            tree[b] = treap::Insert(tree[b], lamps[i].first.second);
            b /= 2;
        }
    }

    for (int i = 0; i < 2 * T; ++i) delete tree[i];

    int dbg_count = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0)
            cout << " ";
        cout << 1 + result[i];
        if (result[i] < i) ++dbg_count;
    }
    cout << endl;
    cerr << "n = " << n << ", lit by others = " << dbg_count << endl;
    return 0;
}

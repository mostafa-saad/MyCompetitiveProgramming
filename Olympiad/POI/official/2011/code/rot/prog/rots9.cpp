/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Rozwiazanie losuje kolejnosc dodawania           *
 *                      wierzcholkow                                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

#define LEFT  0
#define RIGHT 1

const int MAXN = 2*200031;

using namespace std;


struct Node{
    int value_;
    int balance_;
    int size_;
    Node *left_;
    Node *right_;
    Node *father_;

    Node(int v);
    void clear();
    void add(Node *a);
};

Node::Node(int v) {
    this->clear();
    value_   = v;
    size_    = 1;
}

void Node::clear() {
    balance_ = 0;
    size_    = 0;
    left_    = NULL;
    right_   = NULL;
    father_  = NULL;
}

// adding b into a
void add(Node *a, Node *b) {
    b->clear();
    int v = b->value_;
    bool inserted = false;

    if (a == NULL) {
        a = b;
        return ;
    }
    while (!inserted) {
        if (a->value_ > v) {
            if (a->left_ == NULL) {
                b->father_ = a;
                a->left_   = b;
                inserted   = true;
            } else {
                a = a->left_;
            }
        } else {
            //a->value_ < v
            if (a->right_ == NULL) {
                b->father_ = a;
                a->right_  = b;
                inserted   = true;
            } else {
                a = a->right_;
            }
        }
    }
    while (b != NULL) {
        b->size_++;
        b = b->father_;
    }
    // go from b up to the root
}


int mniejszych(Node *a, int v) {
    if (a == NULL) {
        return 0;
    }
    int s = 0;

    while (a != NULL) {
        if (a->value_ == v) {
            s += (a->left_==NULL?0:a->left_->size_);
            return s;
        } else 
        if (a->value_ > v) {
            a = a->left_;
        } else {
            s += 1 + (a->left_==NULL?0:a->left_->size_);
            a = a->right_;
        }
    }
    return s;
}
////////

struct my_node {
    int id_;
    my_node* father_;
    my_node* left_;
    my_node* right_;
    Node* tree_;
    my_node(int id, my_node *father):id_(id), father_(father), left_(NULL), right_(NULL), tree_(NULL) {}
};

int named_nodes = 0;
int deg[MAXN];
my_node *root;
queue<int> q;
my_node* v[MAXN];
int p_v = 0;

void read_tree(my_node *father, int son) {
    my_node *a = new my_node(named_nodes++, father);
    v[p_v++] = a;
    if (father != NULL) {
        if (son == LEFT) {
            father->left_ = a;
        } else {
            father->right_ = a;
        }
    } else {
        root = a;
    }
        
    int x;
    scanf("%d",&x);
    if (x == 0) {
        read_tree(a, LEFT);
        read_tree(a, RIGHT);
        deg[a->id_] = 0;
        if (a->left_->tree_ == NULL) deg[a->id_]++;
        if (a->right_->tree_== NULL) deg[a->id_]++;
    } else {
        deg[a->id_] = 0;
        a->tree_ = new Node(x);
    }
    if (deg[a->id_] == 0) {
        q.push(a->id_);
    }
}

Node* g[MAXN];
int p_g = 0;

void get(Node *a) {
    if (a->left_ != NULL) get(a->left_);
    g[p_g++] = a;
    if (a->right_ != NULL) get(a->right_);
}


void clearNode(Node *a) {
    if (a->left_ != NULL) clearNode(a->left_);
    if (a->right_!=NULL) clearNode(a->right_);
    delete a;
}

void clearMyNode(my_node *a) {
    if (a->left_ != NULL) clearMyNode(a->left_);
    if (a->right_ != NULL) clearMyNode(a->right_);
    delete a;
}


int main() {
    int n;
    srand(123);
    long long wynik = 0;
    scanf("%d",&n);
    read_tree(NULL, 0);

    while (!q.empty()) {
        my_node *a = v[q.front()]; q.pop();
        
        if (a->tree_ == NULL) {
            Node *c1 = a->left_->tree_;
            Node *c2 = a->right_->tree_;
            
            if (c1->size_ < c2->size_) {
                swap(c1, c2);
            }
            
            p_g = 0;
            get(c2);
            long long wtmp = 0;
            for(int i=0; i<p_g; i++) {
                wtmp+=(c1->size_)-mniejszych(c1, g[i]->value_);
            }

            long long wtmp2 = c1->size_;
            wtmp2*=c2->size_;
            wtmp2-=wtmp;

            wynik += wtmp<wtmp2?wtmp:wtmp2;
            
            random_shuffle(g, g+p_g);

            for(int i=0; i<p_g; i++) {
                add(c1, g[i]);
            }
            a->tree_ = c1;
            if (a->father_ != NULL) {
                deg[a->father_->id_]--;
                if (deg[a->father_->id_]==0) {
                    q.push(a->father_->id_);
                }
            }
        }
    }
    clearNode(root->tree_);
    clearMyNode(root);
    printf("%lld\n",wynik);
    return 0;
}

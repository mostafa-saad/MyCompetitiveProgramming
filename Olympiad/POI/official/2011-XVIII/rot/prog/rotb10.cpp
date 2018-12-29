/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie bledne                               *
 *                      jakis blad w robieniu rotacji                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <queue>

#define LEFT  0
#define RIGHT 1

const int MAXN = 2*200031;

using namespace std;


struct Node{
    int value_;
    int depth_;
    int size_;
    Node *left_;
    Node *right_;
    Node *father_;

    Node(int v);
    void clear();
    void add(Node *a);
};


Node *local_root;

Node::Node(int v) {
    this->clear();
    value_   = v;
    size_    = 1;
}

void Node::clear() {
    depth_ = 0;
    size_    = 0;
    left_    = NULL;
    right_   = NULL;
    father_  = NULL;
}


inline int getDepth(Node *b) {
    if (b != NULL) {
        return b->depth_;
    } else {
        return -1;
    }
}

inline int getSize(Node *b) {
    if (b != NULL) {
        return b->size_;
    } else {
        return 0;
    }
}

inline void update(Node *a) {
    a->father_ = NULL;
    a->depth_ = 1 + max(getDepth(a->left_), getDepth(a->right_));
    a->size_  = 1 + getSize(a->left_) + getSize(a->right_);

    if (a->left_ != NULL) {
        a->left_->father_ = a;
    }
    
    if (a->right_ != NULL) {
        a->right_->father_ = a;
    }
}

void fix(Node *b) {
    while (b != NULL) {
        int d_l = getDepth(b->left_);
        int d_r = getDepth(b->right_);
        Node *next_to = b->father_;

        if (d_l - d_r == 2) {
            Node *x = b;
            Node *y = b->left_;
            Node *z = NULL;
            if (getDepth(y->right_) - getDepth(y->left_) == 1) {
                z = y->right_;

                if (b->father_ != NULL) {
                    if (b->father_->right_ == b) {
                        b->father_->right_ = z;
                    } else {
                        b->father_->left_ = z;
                    }
                } else {
                    local_root = z;
                }
                y->right_ = z->left_;
                x->left_  = z->right_;

                z->right_ = x;
                z->left_  = y;
            
                update(y);
                update(x);
                update(z);

                z->father_ = next_to;
            } else {
                z = y->left_;
                if (b->father_ != NULL) {
                    if (b->father_->right_ == b) {
                        b->father_->right_ = y;
                    } else {
                        b->father_->left_ = y;
                    }
                } else {
                    local_root = y;
                }

                x->left_ = y->right_;
                y->right_ = x;

                update(x);
                update(y);
                y->father_ = next_to;
            }
        } else if (d_r - d_l == 2) {
            Node *x = b;
            Node *y = b->right_;
            Node *z = NULL;
            if (getDepth(y->right_) - getDepth(y->left_) == 1) {
                z = y->right_;

                if (b->father_ != NULL) {
                    if (b->father_->right_ == b) {
                        b->father_->right_ = y;
                    } else {
                        b->father_->left_ = y;
                    }
                } else {
                    local_root = y;
                }

                x->right_ = y->left_;
                y->left_ = x;

                update(x); 
                update(y); 
                y->father_ = next_to;
            } else {
                z = y->left_;
                if (b->father_ != NULL) {
                    if (b->father_->right_ == b) {
                        b->father_->right_ = z;
                    } else {
                        b->father_->left_ = z;
                    }
                } else {
                    local_root = z;
                }

                x->right_ = z->right_; // BLAD, powinno byc z->left_
                y->left_  = z->left_;  // BLAD, powinno byc z->right_

                z->left_ = x;
                z->right_ = y;

                update(x);
                update(y);
                update(z);
                z->father_ = next_to;
            }
        } else {
            b->size_++;
            b->depth_ = 1 + max(getDepth(b->left_), getDepth(b->right_));
        }
    b = next_to;
    } 
}

// adding b into a
void add(Node *a, Node *b) {
    local_root = a;
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
    fix(b);
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

////////////////////////////////////////////////

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
int c_v = 0;


void read_tree(my_node *father, int son) {
    my_node *a = new my_node(named_nodes++, father);
    v[c_v++] = a;
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
int g_v = 0;

void get(Node *a) {
    g[g_v++] = a;
    if (a->left_ != NULL) get(a->left_);
    if (a->right_ != NULL) get(a->right_);
}

int n;

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

            g_v = 0;
            get(c2);
            long long wtmp = 0;
            for(int i=0; i<g_v; i++) {
                wtmp+=(c1->size_)-mniejszych(c1, g[i]->value_);
            }

            long long wtmp2 = c1->size_;
            wtmp2*=c2->size_;
            wtmp2-=wtmp;

            wynik += wtmp<wtmp2?wtmp:wtmp2;

            for(int i=0; i<g_v; i++) {
                add(c1, g[i]);
                c1 = local_root;
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

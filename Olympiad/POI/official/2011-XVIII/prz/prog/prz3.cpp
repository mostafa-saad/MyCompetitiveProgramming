/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Przekladanka                                     *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const char* invalid = "NIE DA SIE";

struct Circle {
    Circle(int* x, int n)
        : n_(n)
        , begin_(0)
        , lastPosition_(0)
        , ansPosition_(0) {
            x_ = new int[n_];
            ans_ = new short[n_ * n_];
            for(int i=0; i<n_; i++) x_[i] = x[i];
        }

    ~Circle() {
        delete[] x_;
        delete[] ans_;
    }
   
    void move(int from, int dest);

    bool sort();

    int distance(int from, int dest);
    int distance2(int from, int dest) {
        return distance(dest, from);
    }

    void performPlus(int x);
    void performMinus(int x);

    int* x_;
    short* ans_;
    int n_;
    int begin_;
    int lastPosition_;
    int ansPosition_;
};

int Circle::distance(int from, int dest) {
    int dist = from - dest;
    if (dist < 0) {
        dist += n_;
    }
    return dist;
}

void Circle::performPlus(int x) {
    if (x == 0 || x == n_) return ;

    begin_ -= x;
    if (begin_ < 0) begin_ += n_;

    ans_[ansPosition_++] = x;
}

void Circle::performMinus(int x) {
   int fi = begin_;
   int se = (begin_ + 1) % n_;
   int th = (begin_ + 2) % n_;

   int x_fi = x_[fi];
   int x_se = x_[se];
   int x_th = x_[th];

   if (x == 1) {
       x_[fi] = x_th;
       x_[se] = x_fi;
       x_[th] = x_se;
   } else {
       x_[fi] = x_se;
       x_[se] = x_th;
       x_[th] = x_fi;
   }

   ans_[ansPosition_++] = (-1) * x;
}


void Circle::move(int from, int dest) {
    int dist = distance(from, dest);
    if (dist == 0) return ;

    int newPos = from;
    while (dist >= 2) {
        newPos -= 2;
        if (newPos < 0) newPos += n_;
        performPlus(distance2(newPos, begin_));
        performMinus(1);
        dist -= 2;
    }
    if (dist == 1) {
        newPos = dest;
        performPlus(distance2(newPos, begin_));
        performMinus(2);
    }
}

bool Circle::sort() {
    // finding '1' in our set
    for(int i=0; i<n_; i++) if (x_[i] == 1) {
        lastPosition_ = i;
        break;
    }

    int from = -1, dest = (lastPosition_ + 1) % n_;

    for(int i=2; i<=n_-2; i++) {
        for(int j=0; j<n_; j++) {
            if (x_[j] == i) {
                from = j;
                break;
            }
        }
        move(from, dest);
        dest = (dest + 1) % n_;

    }
    if (x_[(dest + 1) % n_] != n_) {
        if (n_ % 2) return false;

        performPlus(distance2(dest, begin_));
        performMinus(2);
        
        for(int i=0; i<n_/2 - 1; i++) {
            performPlus(n_ - 2);
            performMinus(2);
        }
    }
    for(int i = 0; i < n_; i++) if (x_[i] == 1) {
        performPlus(distance2(i, begin_));
        break;
    }
    return true;
}

const int MAXN = 2013;

int main() {
    int n;
    int a[MAXN];
    
    scanf("%d",&n);
    for(int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }

    if (n == 2) {
        if (a[0] == 1) printf("0\n"); else printf("1\n1a\n");
        return 0;
    }

    Circle cir(a, n);

    if (cir.sort()) {
        printf("%u\n",cir.ansPosition_);
        for(int i=0; i<cir.ansPosition_; i++) {
            int x = cir.ans_[i];
            if (x > 0) {
                printf("%da ",x);
            } else {
                printf("%db ",x * (-1));
            }
        }
    } else {
        printf("%s",invalid);
    }
    return 0;
}

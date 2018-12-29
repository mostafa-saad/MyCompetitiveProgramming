/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jed.c                                         *
 *   Autor:                Przemyslaw Horban                             *
 *   Opis:                 Rozwiązanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <assert.h> /* DO NOT DEFINE NDEBUG!!! */
#include <stdlib.h>

#define fi(i,n) for(i = 0, i##end = (n); i < i##end; i++)
#define ft(i,a,b) for(i = (a), i##end = (b); i <= i##end; i++)
#define fd(i,a,b) for(i = (a), i##end = (b); i >= i##end; i--)
#define SET(T, c) memset(T, c, sizeof(T))

#define MAX_BLOCK_LEN 1000000000

int ri() { int n; assert(scanf(" %d", &n) == 1); return n; }

typedef int bool;
#define true 1
#define false 0

typedef struct {
    int length;
    int value;
} Block;

typedef struct {
    char *bVal;
    int *bLen;
    int blockCount;
    int capacity;
} BigBin;

typedef struct {
    BigBin *bigBin;
    int countLeft;
    char value;
    int nextBlock;
} BigBinIter;

BigBinIter *getIterator(BigBin *b);
bool atEnd(BigBinIter *it);
void rewindIterator(BigBinIter *it);

void nextBlock(BigBinIter *it, int *length, int *value);
void step(BigBinIter *it, int length);
void stepCommonBlock(BigBinIter *it1, BigBinIter *it2, int *length,
                     int *value1, int *value2);
void append(BigBin *b, int length, char value);

BigBin *iterAdd(BigBinIter *it1, BigBinIter *it2);
BigBin *iterSub(BigBinIter *it1, BigBinIter *it2);

BigBin *ofInt(int n);
BigBin *powOfTwo(int k);
BigBin *makeBigBin(int blockCount);
BigBin *readBigBin();
void writeBigBin(BigBin *b);

int length(BigBin *b);
int bit(BigBin *b, int k);
void clearFirstBit(BigBin *b);
int count1Groups(BigBin *b);

void fixLead(BigBin *b);
void assertCorrect(BigBin *b);

int main(){
    BigBin *N = readBigBin();

    // ps = floor(N / 2) + count1Groups(N)
    BigBinIter *hN = getIterator(N);
    step(hN, 1);
    BigBin *ps = iterAdd(hN, getIterator(ofInt(count1Groups(N))));

    // cs = floor(lg(N)) + 1
    BigBin *cs = ofInt(length(N));

    // ls = 2 ^ (k-1) + (n mod 2^k), n=(10...)
    //      2 ^ k, n=(11...)
    BigBin *ls;
    int k = length(N) - 1;
    if(bit(N, k-1) == 0) {
        clearFirstBit(N);
        ls = iterAdd(getIterator(powOfTwo(k-1)), getIterator(N));
        ls = iterAdd(getIterator(ls), getIterator(ofInt(1)));
    }
    else {
        ls = powOfTwo(k);
    }
    writeBigBin(iterSub(getIterator(iterAdd(getIterator(ls),
                                            getIterator(ps)
                                           )
                                   ),
                        getIterator(cs)
                       )
               );
    return 0;
}

BigBinIter *getIterator(BigBin *b) {
    BigBinIter *it = (BigBinIter*)malloc(sizeof(BigBinIter));
    it->bigBin = b;
    it->countLeft = 0;
    it->value = 0;
    it->nextBlock = 0;
    rewindIterator(it);
    return it;
}

bool atEnd(BigBinIter *it) {
    return it->countLeft == 0 && 
           it->nextBlock == it->bigBin->blockCount;
}

void rewindIterator(BigBinIter *it) {
    if(atEnd(it)) return;
    if(it->countLeft == 0) {
        it->countLeft = it->bigBin->bLen[it->nextBlock];
        assert(it->nextBlock == 0 ||
               1 - it->value == it->bigBin->bVal[it->nextBlock]);
        it->value = it->bigBin->bVal[it->nextBlock];
        it->nextBlock++;
    }
}

void nextBlock(BigBinIter *it, int *length, int *value) {
    if(atEnd(it))
        *length = -1;
    else {
        rewindIterator(it);
        *length = it->countLeft;
        *value = it->value;
    }
}

void step(BigBinIter *it, int length) {
    while(true) {
        if(length == 0) return;
        if(atEnd(it))
            return;
        else
            rewindIterator(it);

        if(it->countLeft > length) {
            it->countLeft -= length;
            length = 0;
        }
        else {
            length -= it->countLeft;
            it->countLeft = 0;
        }
    }
}

void stepCommonBlock(BigBinIter *it1, BigBinIter *it2, int *length,
                     int *value1, int *value2) {
    int l1, l2;
    nextBlock(it1, &l1, value1);
    nextBlock(it2, &l2, value2);
    if(l1 == -1 && l2 == -1) {
        *length = -1;
        return;
    }
    if(l1 == -1) {
        l1 = l2;
        *value1 = 0;
    }
    if(l2 == -1) {
        l2 = l1;
        *value2 = 0;
    }
    *length = (l1 < l2 ? l1 : l2);
    step(it1, *length);
    step(it2, *length);
}

void append(BigBin *b, int length, char value) {
    if(length == 0) 
        return;
    else if(b->blockCount != 0 && b->bVal[b->blockCount - 1] == value)
        b->bLen[b->blockCount - 1] += length;
    else {
        assert(b->capacity > b->blockCount);
        b->blockCount++;
        b->bLen[b->blockCount - 1] = length;
        b->bVal[b->blockCount - 1] = value;
    }
}

BigBin *iterAdd(BigBinIter *it1, BigBinIter *it2) {
    BigBin *b = makeBigBin(2 * (it1->bigBin->blockCount +
                                it2->bigBin->blockCount));
    int r = 0;
    while(true) {
        int len, val1, val2;
        stepCommonBlock(it1, it2, &len, &val1, &val2);
        if(len == -1) break;

        if(val1 == 0 && val2 == 0) {
            if(r == 0)
                append(b, len, 0);
            else {
                append(b, 1, 1);
                append(b, len - 1, 0);
                r = 0;
            }
        }
        else if(val1 + val2 == 1)
            append(b, len, 1 - r);
        else if(val1 == 1 && val2 == 1) {
            if(r == 0) {
                append(b, 1, 0);
                append(b, len - 1, 1);
            }
            else
                append(b, len, 1);
            r = 1;
        }
    }
    if(r == 1) append(b, 1, 1);
    fixLead(b);
    assertCorrect(b);
    return b;
}

BigBin *iterSub(BigBinIter *it1, BigBinIter *it2) {
    BigBin *b = makeBigBin(2 * (it1->bigBin->blockCount +
                                it2->bigBin->blockCount));
    int r = 0;
    while(true) {
        int len, val1, val2;
        stepCommonBlock(it1, it2, &len, &val1, &val2);
        if(len == -1) break;

        if(val1 == 0 && val2 == 0)
            append(b, len, r);
        else if(val1 == 1 && val2 == 0) {
            if(r == 0)
                append(b, len, 1);
            else {
                append(b, 1, 0);
                append(b, len - 1, 1);
                r = 0;
            }
        }
        else if(val1 == 1 && val2 == 1)
            append(b, len, r);
        else if(val1 == 0 && val2 == 1) {
            if(r == 0) {
                append(b, 1, 1);
                append(b, len - 1, 0);
                r = 1;
            }
            else
                append(b, len, 0);
        }

    }
    assert(r == 0);
    fixLead(b);
    assertCorrect(b);
    return b;
}

BigBin *ofInt(int n) {
    BigBin *b = makeBigBin(32);
    while(n != 0) {
        append(b, 1, (n & 1));
        n /= 2;
    }
    assertCorrect(b);
    return b;
}

BigBin *powOfTwo(int k) {
    BigBin *b = makeBigBin(2);
    if(k > 0)
        append(b, k, 0);
    append(b, 1, 1);
    assertCorrect(b);
    return b;
}

BigBin *makeBigBin(int blockCount) {
    BigBin *b = (BigBin*)malloc(sizeof(BigBin));
    b->bLen = (int*)malloc(sizeof(int) * blockCount);
    b->bVal = (char*)malloc(sizeof(char) * blockCount);
    b->blockCount = 0;
    b->capacity = blockCount;
    return b;
}

BigBin *readBigBin() {
    int n; assert(scanf("%d", &n) == 1);
    BigBin *b = makeBigBin(n);
    b->blockCount = n;
    int val = 1;
    int i, iend;
    fd(i, n - 1, 0) {
        assert(scanf("%d", &b->bLen[i]) == 1);
        b->bVal[i] = val;
        val = 1 - val;
    }
    assertCorrect(b);
    return b;
}

void writeBigBin(BigBin *b) {
    assertCorrect(b); 
    printf("%d\n", b->blockCount);
    int i, iend;
    fd(i, b->blockCount - 1, 0) {
        printf("%d", b->bLen[i]);
        if(i > 0)
            putchar(' ');
        else
            putchar('\n');
    }
}

int length(BigBin *b) {
    int cnt = 0;
    int i, iend;
    fi(i, b->blockCount) cnt += b->bLen[i];
    return cnt;
}

int bit(BigBin *b, int k) {
    int block = 0;
    while(true) {
        if(block >= b->blockCount)
            return 0;
        else if(k < b->bLen[block])
            return b->bVal[block];
        else {
            k -= b->bLen[block];
            block++;
        }
    }
}

void clearFirstBit(BigBin *b) {
    int *l = &b->blockCount; // shortcut
    assert(b->bLen[*l - 1] > 0);
    assert(b->bVal[*l - 1] == 1);
    b->bLen[*l - 1]--;
    fixLead(b);
    assertCorrect(b);
}

int count1Groups(BigBin *b) {
    return (b->blockCount + 1) / 2;
}

void fixLead(BigBin *b) {
    int *l = &b->blockCount; // shortcut
    while(*l > 0 && (b->bVal[*l - 1] == 0 || b->bLen[*l - 1] == 0))
        (*l)--;
}

void assertCorrect(BigBin *b) {
#ifndef NDEBUG
    assert(b->blockCount <= b->capacity);
    if(b->blockCount == 0) return;
    assert(b->bVal[b->blockCount - 1] == 1);
    assert(b->bLen[b->blockCount - 1] > 0);
    int i, iend;
    fd(i, b->blockCount - 2, 0) {
        assert(1 - b->bVal[i + 1] == b->bVal[i]);
        assert(b->bLen[i] > 0);
        assert(b->bLen[i] <= MAX_BLOCK_LEN);
    }
#endif
}

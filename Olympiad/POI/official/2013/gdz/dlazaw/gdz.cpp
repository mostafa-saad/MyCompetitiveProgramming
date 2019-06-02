// gdz.cpp - Przykladowe użycie biblioteki do zadania GDZ
#include "cgdzlib.h"

int main(void) {
    int n = inicjuj(), mini = 1, i;
    for (i = 2; i <= n; ++i) {
        if (g(mini, i)) {
            mini = i;
        }
    }
    odpowiedz(mini);
    return 0;
}

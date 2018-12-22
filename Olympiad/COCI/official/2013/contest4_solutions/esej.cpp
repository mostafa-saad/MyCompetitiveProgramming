#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int n, na, nb, r;
string s;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        cin >> s;

        na = 0; nb = 0;
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == 'A') na++;
            else nb++;
        }

        if (!(na % 2) && !(nb % 2)) r++;
    }

    printf("%d", r);

    return 0;
}

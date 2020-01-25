#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for(int i = a; i < b; i++)

int n;

bool poc_izb = 0, kraj_izb = 0;
int cnt1 = 0, cnt4 = 0;

vector <pair <int, int> > lijevo_izb;
vector <pair <int, int> > lijevo_udub;
vector <pair <int, int> >::iterator izb, udub;

vector <int> rj;
int zadnji;

void nemoguce()
{
    printf("-1\n");
    exit(0);
    return;
}

int main()
{
    scanf("%d", &n);
    int x, a;
    FOR(i, 0, n)
    {
        scanf("%d%d", &x, &a);
        if(x == 5 || x == 6) rj.push_back(a);
        else if(x == 7 || x == 8) zadnji = a;
        if(x == 5) poc_izb = 1;
        else if(x == 7) kraj_izb = 1;
        else if(x == 1) cnt1++;
        else if(x == 4) cnt4++;
        if(x == 1 || x == 2) lijevo_izb.push_back(make_pair(a, x));
        else if(x == 3 || x == 4) lijevo_udub.push_back(make_pair(a, x));
    }
    if(poc_izb && kraj_izb && cnt4 != cnt1 + 1) nemoguce();
    if(!poc_izb && !kraj_izb && cnt1 != cnt4 + 1) nemoguce();
    if(poc_izb ^ kraj_izb)
    {
        if(cnt1 != cnt4) nemoguce();
        if(cnt1 == 0)
        {
            if(poc_izb && (int)lijevo_izb.size()) nemoguce();
            if(kraj_izb && (int)lijevo_udub.size()) nemoguce();
        }
    }
    sort(lijevo_izb.begin(), lijevo_izb.end());
    sort(lijevo_udub.begin(), lijevo_udub.end());
    int zadnja_promjena = 0;
    bool treba_izb = !poc_izb;
    izb = lijevo_izb.begin();
    udub = lijevo_udub.begin();
    while(!((izb == lijevo_izb.end() && treba_izb) || (udub == lijevo_udub.end() && !treba_izb)))
    {
        if(treba_izb)
        {
            if(izb -> second == 1)
            {
                treba_izb = 0;
                zadnja_promjena = (int)rj.size() - 1;
            }
            rj.push_back(izb -> first);
            izb++;
        }
        else
        {
            if(udub -> second == 4)
            {
                treba_izb = 1;
                zadnja_promjena = (int)rj.size() - 1;
            }
            rj.push_back(udub -> first);
            udub++;
        }
    }
    FOR(i, 0, zadnja_promjena + 1)
    {
        printf("%d ", rj[i]);
    }
    while(izb != lijevo_izb.end())
    {
        printf("%d ", izb -> first);
        izb++;
    }
    while(udub != lijevo_udub.end())
    {
        printf("%d ", udub -> first);
        udub++;
    }
    FOR(i, zadnja_promjena + 1, (int)rj.size())
    {
        printf("%d ", rj[i]);
    }
    printf("%d\n", zadnji);
    return 0;
}

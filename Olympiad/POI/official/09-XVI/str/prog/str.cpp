/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     str.cpp                                                   *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie wzorcowe O((p+z)*log(p+z))                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int Z = (int)1e5;
const int P = (int)1e5;
const int inf = (int)1e9;

int n,m,z,p,x[Z],y[Z],w[3*P];
vector< vector<int> > x1,x2,x3,x4;

inline int sign(int xx)
{
    if(!xx) return 0;
    return xx>0?1:-1;
}

vector<int> wekt(int a,int b,int c,int d,int e)
{
    vector<int> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    return v;
}

vector<int> wek(int a,int b,int c)
{
    vector<int> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    return v;
}

vector<int> u;

int szukaj(int a)
{
    int lx=0,px=u.size()-1,sx;
    while(lx<px)
    {
        sx=(lx+px)/2;
        if(u[sx]<a) lx=sx+1;
        else px=sx;
    }
    return lx;
}

const int M = 1<<19;
int e[2*M];

void insert(int a)
{
    a+=M;
    while(a)
    {
        e[a]++;
        a/=2;
    }
}

int pyt(int a)
{
    int ret=0;
    a+=M;
    while(a>1)
    {
        if(a%2)
            ret+=e[a-1];
        a/=2;
    }
    return ret;
}

int pytaj(int a,int b)
{
    return pyt(b+1)-pyt(a);
}

void zamiec(vector< vector<int> > &xx)
{
    for(int i=0;i<(int)xx.size();i++)
        if(xx[i][1]>=0 && xx[i][3]>xx[i][4])
        {
            xx[i]=xx.back();
            xx.pop_back();
        } 
    sort(xx.begin(),xx.end());
    u.clear();
    for(int i=0;i<2*M;i++) 
        e[i]=0;
    for(int i=0;i<(int)xx.size();i++)
        if(xx[i][1]<0)
            u.push_back(xx[i][2]);
        else
        {
            u.push_back(xx[i][3]);
            u.push_back(xx[i][4]);
        }
    sort(u.begin(),u.end());
    for(int i=0;i<(int)xx.size();i++)
        if(xx[i][1]<0)
            insert(szukaj(xx[i][2]));
        else
            w[xx[i][1]]+= pytaj( szukaj(xx[i][3]), szukaj(xx[i][4]) ) * xx[i][2];
}

int main()
{
    scanf("%d %d %d %d",&n,&m,&z,&p);
    for(int i=0;i<z;i++)
        scanf("%d %d",&x[i],&y[i]);
    for(int j=0;j<p;j++)
    {
        int a,b,c,d,komu=0;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        if(a>c) komu=1;
        if(a==c)
        {
            if(b>d) komu=1;
            x2.push_back( wekt( (b+d-1)/2,      3*j+komu,  1, 0,            inf ) );
            x2.push_back( wekt( (b+d)/2,    3*j+2,     1,  0,           inf ) );
        }
        else if(b==d)
        {
            x1.push_back( wekt( (a+c-1)/2,      3*j+komu,  1,  0,           inf ) );
            x1.push_back( wekt( (a+c)/2,    3*j+2,     1,  0,           inf ) );

        }
        else if(abs(a-c)==abs(b-d))
        {
            if(a+b==c+d)
            {
                x3.push_back( wekt( inf+c-b-1,  3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                x3.push_back( wekt( inf+c-b,    3*j+2,     1, min(b,d),     max(b,d)-1 ) );
                x1.push_back( wekt( max(a,c)-1, 3*j+komu,  1, max(b,d),     inf ) );
                x1.push_back( wekt( max(a,c),   3*j+2,     1, max(b,d),     inf ) );

                x1.push_back( wekt( min(a,c),   3*j+2,     1, 0,            min(b,d)-1 ) );

                w[3*j+2]+=z;
                x2.push_back( wekt( max(b,d)-1,     3*j+2,     1, 0    ,   max(a,c) ) );
                x2.push_back( wekt( inf,            3*j+2,    -1, 0    ,   max(a,c) ) );
                x2.push_back( wekt( max(b,d)-1,     3*j+2,    -1, 0    ,   inf ) );
            }
            else
            {
                x4.push_back( wekt( b+c-1,      3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                x4.push_back( wekt( b+c,        3*j+2,     1, min(b,d)+1,   max(b,d) ) );
                x1.push_back( wekt( max(a,c)-1, 3*j+komu,  1, 0,            min(b,d) ) );
                x1.push_back( wekt( max(a,c),   3*j+2,     1, 0,            min(b,d) ) );

                x1.push_back( wekt( min(a,c),   3*j+2,     1, max(b,d)+1,   inf ) );

                x2.push_back( wekt( min(b,d),   3*j+2,     1, max(a,c)+1,   inf ) );
            }
        }
        else if(abs(a-c)>abs(b-d))
        {
            if(sign(a-c)==sign(b-d))
            {
                unsigned s=a+b;
                s+=c+d;
                x4.push_back( wekt( (s-1)/2,            3*j+komu,  1, min(b,d),     max(b,d) ) );
                x4.push_back( wekt( s/2,                3*j+2,     1, min(b,d),     max(b,d) ) );
                x1.push_back( wekt( (s-1)/2-max(b,d),   3*j+komu,  1, max(b,d)+1,   inf ) );
                x1.push_back( wekt( s/2-max(b,d),       3*j+2,     1, max(b,d)+1,   inf ) );
                x1.push_back( wekt( (s-1)/2-min(b,d),   3*j+komu,  1, 0,            min(b,d)-1 ) );
                x1.push_back( wekt( s/2-min(b,d),       3*j+2,     1, 0,            min(b,d)-1 ) );
            }
            else
            {
                unsigned s=inf+a-b;
                s+=inf+c-d;
                x3.push_back( wekt( (s-1)/2,                3*j+komu,  1, min(b,d),     max(b,d) ) );
                x3.push_back( wekt( s/2,                    3*j+2,     1, min(b,d),     max(b,d) ) );
                x1.push_back( wekt( (s-1)/2-inf+max(b,d),   3*j+komu,  1, max(b,d)+1,   inf ) );
                x1.push_back( wekt( s/2-inf+max(b,d),       3*j+2,     1, max(b,d)+1,   inf ) );
                x1.push_back( wekt( (s-1)/2-inf+min(b,d),   3*j+komu,  1, 0,            min(b,d)-1 ) );
                x1.push_back( wekt( s/2-inf+min(b,d),       3*j+2,     1, 0,            min(b,d)-1 ) );
            }
        }
        else
        {
            if(sign(a-c)==sign(b-d))
            {
                unsigned s=a+b;
                s+=c+d;
                x4.push_back( wekt( (s-1)/2,    3*j+komu,  1, (s-1)/2-max(a,c)+1,   (s-1)/2-min(a,c) ) );
                x4.push_back( wekt( s/2,        3*j+2,     1, s/2-max(a,c)+1,   s/2-min(a,c)     ) );
                x1.push_back( wekt( inf,        3*j+komu,  1, 0,                (s-1)/2-max(a,c) ) );
                x1.push_back( wekt( inf,        3*j+2,     1, 0,                s/2-max(a,c)     ) );
            }
            else
            {
                unsigned s=inf+a-b;
                s+=inf+c-d;
                x3.push_back( wekt( (s-1)/2,    3*j+komu,  1, min(a,c)+inf-(s-1)/2,     max(a,c)+inf-(s-1)/2-1 ) );
                x3.push_back( wekt( s/2,        3*j+2,     1, min(a,c)+inf-s/2,         max(a,c)+inf-s/2-1 ) );
                x1.push_back( wekt( inf,        3*j+komu,  1, max(a,c)+inf-(s-1)/2,     inf      ) );
                x1.push_back( wekt( inf,        3*j+2,     1, max(a,c)+inf-s/2,         inf      ) );
            }
        }
        w[3*j+1-komu]=-1;
    }
    for(int i=0;i<z;i++)
        x1.push_back( wek( x[i], -1, y[i] ) );
    zamiec(x1);
    for(int i=0;i<z;i++)
        x2.push_back( wek( y[i], -1, x[i] ) );
    zamiec(x2);
    for(int i=0;i<z;i++)
        x3.push_back( wek( inf+x[i]-y[i], -1, y[i] ) );
    zamiec(x3);
    for(int i=0;i<z;i++)
        x4.push_back( wek( x[i]+y[i], -1, y[i] ) );
    zamiec(x4);
    for(int j=0;j<p;j++)
    {
        for(int k=0;k<2;k++)
            if(w[3*j+k]<0)
            {
                w[3*j+k]=z-w[3*j+2];
                w[3*j+2]-=w[3*j+1-k];
            }
        printf("%d %d %d\n",w[3*j],w[3*j+1],w[3*j+2]);
    }
    return 0;
}

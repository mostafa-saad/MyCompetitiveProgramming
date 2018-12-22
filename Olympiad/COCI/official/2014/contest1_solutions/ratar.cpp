#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
const int c=2500000;


int n;
int a[101][101];

int bio[2*c];
int pp[101][101];

int val (int x1,int y1,int x2,int y2)
{
    if ( x1 > 0)
    {
        if (y1 > 0)
        {
            return (pp[x2][y2]+pp[x1-1][y1-1]-pp[x1-1][y2]-pp[x2][y1-1]);
        }
        else
        {
            return (pp[x2][y2]-pp[x1-1][y2]);
        }
    }
    else
    {
        if (y1 > 0)
        {
            return (pp[x2][y2]-pp[x2][y1-1]);
        }
        else
        {
            return pp[x2][y2];
        }
    }
}
int main()
{
    cin>>n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin>>a[i][j];

    pp[0][0]=a[0][0];

    for (int i=1; i<n; i++)
        {
            pp[i][0]=pp[i-1][0]+a[i][0];
            pp[0][i]=pp[0][i-1]+a[0][i];
        }

    for (int i=1; i<n; i++)
        for (int j=1; j<n; j++)
        pp[i][j]=pp[i][j-1]+pp[i-1][j]-pp[i-1][j-1]+a[i][j];

    int rj=0;

    for (int i=1; i<n; i++)
        for (int j=1; j<n; j++)
        {
            for (int x = 0; x < i; x++)
                for (int y=0; y < j; y++)
                    bio[val(x,y,i-1,j-1)+c]++;

            for (int x = i; x < n; x++)
                for (int y=j; y < n; y++)
                        rj+=bio[val(i,j,x,y)+c];

            for (int x = 0; x < i; x++)
                for (int y=0; y < j; y++)
                    bio[val(x,y,i-1,j-1)+c]--;


            for (int x = 0; x < i; x++)
                for (int y=j; y < n; y++)
                    bio[val(x,j,i-1,y)+c]++;

            for (int x = i; x < n; x++)
                for (int y = 0; y < j; y++)
                        rj+=bio[val(i,y,x,j-1)+c];

            for (int x = 0; x < i; x++)
                for (int y=j; y < n; y++)
                    bio[val(x,j,i-1,y)+c]--;


        }
    cout<<rj<<endl;
    //end = clock();
    //cout<< (double)(end - begin) / CLOCKS_PER_SEC<<endl;
    return 0;
}

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int mxn = 26;

int count[mxn][mxn];
//count[i][j] counts how many words begin with i, and end with j

int main()
{
  int n;
  scanf( "%d", &n );

  char word[20];
  for( int i = 0; i < n; i++ )
  {
    scanf( "%s", word );
    count[word[0]-'A'][word[strlen(word)-1]-'A']++;
  }

  int firstLevel, secondLevel, thirdLevel;
  long long ret = 0;

  for( int upperLeft = 0; upperLeft < mxn; upperLeft++ )
  {
    for( int upperRight = 0; upperRight < mxn; upperRight++ )
    {
      firstLevel = count[upperLeft][upperRight];
      count[upperLeft][upperRight]--;

      for( int lowerLeft = 0; lowerLeft < mxn; lowerLeft++ )
      {
            secondLevel = count[upperLeft][lowerLeft];
            count[upperLeft][lowerLeft]--;

            for( int lowerRight = 0; lowerRight < mxn; lowerRight++ )
            {
                thirdLevel = count[upperRight][lowerRight]--;

                ret +=
                    (long long)count[lowerLeft][lowerRight] *
                    firstLevel *
                    secondLevel *
                    thirdLevel;

                count[upperRight][lowerRight]++;
            }

            count[upperLeft][lowerLeft]++;
      }

      count[upperLeft][upperRight]++;
    }
  }

  cout << ret << endl;
  return 0;
}

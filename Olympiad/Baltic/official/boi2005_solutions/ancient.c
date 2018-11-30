/*
TASK:ANCIENT
LANG:C
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <ctime>
//using namespace std;

  typedef long long int i64;

  int isVowel(char c) {
    return c=='a'-'a' || c=='e'-'a' || c=='i'-'a' || c=='o'-'a' || c=='u'-'a';
  }

  i64 goSolve(char *s, int EV, int CV, int EC, int CC) {
    int i, j, k, l, m, L=strlen(s), _s=0, _t=1, c, d, cl, ch;
    i64 tw[2], dp[2][26][4][4];
    memset(dp, 0, sizeof dp);
    memset(tw, 0, sizeof tw);
    cl=0;
    ch=25;
    if (isalpha(s[0])) cl=ch=s[0]-'a';
    for (c=cl; c<=ch; c++) {
      dp[0][c][0][0]=1;
      tw[0]++;
    }
    for (i=1; i<L; i++) {
      cl=0;
      ch=25;
      if (isalpha(s[i])) cl=ch=s[i]-'a';
      for (c=cl; c<=ch; c++)
        for (d=0; d<26; d++)
          for (j=0; j<4; j++)
            for (k=0; k<4; k++)
              if (isVowel(c)+isVowel(d)==1) {
                dp[_t][c][0][0]+=dp[_s][d][j][k];
                tw[_t]+=dp[_s][d][j][k];
              } else if (isVowel(c)) {
                l=(c==d ? j+2 : 1);
                m=k+2;
                if (l<=EV && m<=CV) {
                  dp[_t][c][l-1][m-1]+=dp[_s][d][j][k];
                  tw[_t]+=dp[_s][d][j][k];
                }
              } else {
                l=(c==d ? j+2 : 1);
                m=k+2;
                if (l<=EC && m<=CC) {
                  dp[_t][c][l-1][m-1]+=dp[_s][d][j][k];
                  tw[_t]+=dp[_s][d][j][k];
                }
              }
      _s^=1;
      _t^=1;
      memset(dp[_t], 0, sizeof dp[_t]);
      tw[_t]=0;
    }
    return tw[_s];
  }

int main() {
  FILE *f;
  FILE *g;

  f = fopen("ANCIENT.IN", "r");
  g = fopen("ANCIENT.OUT", "w");
 
  int EV, CV, EC, CC; char s[32];
 
    fscanf(f,"%d %d %d %d %s", &EV, &CV, &EC, &CC, s);
    fprintf(g,"%lld\n", goSolve(s, EV, CV, EC, CC));
  return(0);
}

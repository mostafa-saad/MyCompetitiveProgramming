#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
const int maxn=10;
int n;
double r[maxn];
string in;

double res(string s){
  if (s.size()==2){
    return r[s[1]-'0'-1];
  }
  int ns=s.size();
  string s2="";
  int e=-1;
  int un=0;
  double sol=0.0;
  for (int i=1;i<ns-1;i++){
    if (!un&&(s[i]=='-'||s[i]=='|')){
      if (e==-1){
        e=(s[i]=='|');
      }
      sol+=(e?1/res(s2):res(s2));
      s2="";
      continue;
    }
    if (s[i]=='('){
      un++;
    }
    if (s[i]==')'){
      un--;
    }
    s2+=s[i];
  }
  sol+=(e?1/res(s2):res(s2));
  if (e){
    sol=1/sol;
  }
  return sol;
}

int main (void){
  cin >> n;
  for (int i=0;i<n;i++){
    cin >> r[i];
  }
  cin >> in;
  printf("%.5lf\n", res(in));
  return 0;
}

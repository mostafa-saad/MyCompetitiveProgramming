#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int n;
vector<string> numbers;

void parse_line(string &line) {
  string number = "";
  int status = 0;

  line += 'x';

  for(int i = 0; i < (int)line.size(); ++i) {
    char c = line[i];

    if(isdigit(c)) {
      if(c == '0' && status != 2) {
	status = 1;
	continue;
      }
      
      status = 2;
      number += c;
    } else if(status != 0) {					
      if(status == 1) 
	number = "0";
      
      numbers.push_back(number);
      number = "";
      status = 0;
    }
  }
}

void load_and_parse() {
  cin >> n;
  
  for(int i = 0; i < n; ++i) {
    string line;
    
    cin >> line;
    parse_line(line);
  }
}

struct cmp {
  bool operator() (const string &s1, const string &s2) const {
    if(s1.size() == s2.size())
      return s1 < s2;
    else
      return s1.size() < s2.size();
  }
};


void print() {
  for(int i = 0; i < (int)numbers.size(); ++i)
    cout << numbers[i] << endl;
}

int main() {
  load_and_parse();

  sort(numbers.begin(), numbers.end(), cmp());

  print();
  
  return 0;
}

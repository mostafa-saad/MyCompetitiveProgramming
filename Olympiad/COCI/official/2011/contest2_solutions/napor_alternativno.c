#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100
#define MAXM 500

char line[MAXL+2];
char numbers[MAXM][MAXL+1];
char *points[MAXM];
int n, m;


void parse_line() {
  int i, k = 0, len;
  int status = 0;
  char c;

  strcat(line, "x");
  len = strlen(line);

  for(i = 0; i < len; ++i) {
    c = line[i];

    if(isdigit(c)) {

      if(c == '0' && status != 2) {
	status = 1;
	continue;
      }

      status = 2;
      numbers[m][k++] = c;

    } else if(status != 0) {

      if(status == 1) 
	numbers[m][k++] = '0';
      
      numbers[m][k] = '\0';
      points[m] = numbers[m];

      status = 0;
      k = 0;
      m++;
    }
  }
}

void load_and_parse() {
  int i;

  scanf("%d", &n);

  for(i = 0; i < n; ++i) {
    scanf("%s", line);
    parse_line();
  }
}


int cmp (const char *s1, const char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  
  if(len1 == len2)
    return strcmp(s1, s2) < 0;
  else
    return len1 < len2;
}

void print() {
  int i;
  for(i = 0; i < m; ++i)
    printf("%s\n", points[i]);
}

void solve() {
  int i, j, done;

  char *tmp;

  for(i = 0; i < m-1; ++i) {
    done = 1;
    for(j = 0; j < m-1; ++j) 
      if(!cmp(points[j], points[j+1])) {
	tmp = points[j];
	points[j] = points[j+1];
	points[j+1] = tmp;
	done = 0;
      }

    if(done) 
      break;
  }
}



int main() {
  load_and_parse();

  solve();
  
  print();
  
  return 0;
}

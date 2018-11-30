#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

#include "oi.h"
using namespace oi;

void endf(const char* msg, int line, int position)
{
  printf("WRONG\nWiersz %d: %s\n", line, msg);
  exit(1);
}

int n,sum;
Scanner *test;
bool magic[41];
long long u,w,x;
int main(int argc, char **argv) {
	magic[0]=magic[14]=magic[4]=magic[6]=magic[39]=true;

  if(argc != 4) {
    printf("Uruchomienie: %s in out wzo\n", argv[0]);
    return 1;
  }

  // HINT: Plikow fin i fwzo nie trzeba czytac Scannerem.
  FILE *fin = fopen(argv[1], "r");
  fscanf(fin, "%d", &n);
  //fclose(fin);

  FILE *wzo = fopen(argv[3], "r");
	sum=0;
	for(int i=0;i<n;i++){
		fscanf(fin, "%lld", &x);
		sum+=x;
	}
	//cout<<sum<<endl;
	sum=abs(sum);
	sum%=40;
  test = new Scanner(argv[2], endf, PL);
	for(int i=0;i<n;i++){
		test->skipWhitespaces();
		u=test->readLL();
		fscanf(wzo, "%lld", &w);
		if(u!=w && ((!magic[sum])||i+1==n))
			
			test->error("Wrong Answer");
	}
	test->skipWhitespaces();
	test->readEof();
fclose(wzo);
fclose(fin);

  std::cout << "OK"<< std::endl;
  delete test;
  return 0;
}

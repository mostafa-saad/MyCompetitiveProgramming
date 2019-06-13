#include<stdio.h>
#include<algorithm>
using namespace std;
char str[1100000];
int now[40];
char word[6]="IOJ";
int main(){
	int a;scanf("%d",&a);
	scanf("%s",str);
	int ret=999999999;
	int n=(1<<(a*2));
	for(int i=0;i<(n/2);i++)swap(str[i],str[n-1-i]);
	int at=0;
	for(int i=0;i<a*3;i++){
		int len=1<<(i/3*2);
		int cnt=0;
		for(int j=0;j<len;j++){
			if(str[at]!=word[i%3])cnt++;
			at++;
		}
		now[i]=cnt;
	}
	for(int i=0;i<n;i++){
		at=i;
		for(int j=0;j<a*3;j++){
			if(str[at]!=word[j%3])now[j]--;
			at=(at+(1<<(j/3*2)))%n;
			if(str[at]!=word[j%3])now[j]++;
		}
		int tmp=0;
		for(int j=0;j<a*3;j++)tmp+=now[j];
		ret=min(ret,tmp);
	}
	printf("%d\n",ret);
}

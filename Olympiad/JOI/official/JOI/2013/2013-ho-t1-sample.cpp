#include <cstdio>

int N;
int lights[100008];
int list_size=0;
int list[100002];
int main() {
	scanf("%d",&N);
	for(int i=0;i<N;i++) scanf("%d",&lights[i]);
	int sequence=0;
	for(int i=0;i<N;i++) {
		if(sequence>0) {
			if(lights[i]==lights[i-1]) {
				list[list_size++]=sequence;
				sequence=0;
			}
		}
		sequence++;
	}
	if(sequence>0) list[list_size++]=sequence;
	int total=0;
	int max=0;
	for(int i=0;i<list_size;i++) {
		total+=list[i];
		if(i>2) total-=list[i-3];
		if(max<total) max=total;
	}
	printf("%d\n",max);
	return 0;
}

#include <cstdio>

int M,N;
char flags[1002][1002];
char symbols[5][5];

int main() {
	scanf("%d%d",&M,&N);
	for(int i=0;i<M;i++) scanf("%s",flags[i]);
	for(int i=0;i<2;i++) scanf("%s",symbols[i]);
	int defsol=0;
	for(int i=0;i<M-1;i++) {
		for(int j=0;j<N-1;j++) {
			int exists=1;
			for(int x=0;x<2;x++) {
				for(int y=0;y<2;y++) {
					if(flags[i+x][j+y]!=symbols[x][y]) exists=0;
				}
			}
			defsol+=exists;
		}
	}
	int changemax=0;
	for(int i=0;i<M;i++) {
		for(int j=0;j<N;j++) {
			char def=flags[i][j];
			int deleted_emblems=0;
			int addmax=0;
			for(int x=-1;x<=0;x++) {
				for(int y=-1;y<=0;y++) {
					if(i+x>=0&&i+x+1<M) {
						if(j+y>=0&&j+y+1<N) {
							int exists=1;
							for(int v=0;v<2;v++) {
								for(int w=0;w<2;w++) {
									if(flags[i+x+v][j+y+w]!=symbols[v][w]) exists=0;
								}
							}
							deleted_emblems+=exists;
						}
					}
				}
			}
			for(int types=0;types<3;types++) {
				if(types==0) flags[i][j]='J';
				if(types==1) flags[i][j]='O';
				if(types==2) flags[i][j]='I';
				int addvl=0;
				for(int x=-1;x<=0;x++) {
					for(int y=-1;y<=0;y++) {
						if(i+x>=0&&i+x+1<M) {
							if(j+y>=0&&j+y+1<N) {
								int exists=1;
								for(int v=0;v<2;v++) {
									for(int w=0;w<2;w++) {
										if(flags[i+x+v][j+y+w]!=symbols[v][w]) exists=0;
									}
								}
								addvl+=exists;
							}
						}
					}
				}
				if(addmax<addvl) addmax=addvl;
			}
			if(changemax<addmax-deleted_emblems) changemax=addmax-deleted_emblems;
			flags[i][j]=def;
		}
	}
	printf("%d\n",changemax+defsol);
	return 0;
}

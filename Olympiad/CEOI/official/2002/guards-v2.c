#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 257
#define DEBUG 0

typedef struct { int x,y,twin,matched; } thrana; // edge

int M,N; // rows and cols
int i,j; // temporary
int R,C; // number of row/col segments
int A[MAXN][MAXN]; // original map
int BR[MAXN][MAXN],BC[MAXN][MAXN]; // row/col segments
int Coord[MAXN*MAXN*2]; // row/col of a segment
int V[MAXN*MAXN*2]; // vertex indices in edge array
int Ma[MAXN*MAXN*2]; // matched vertex?
thrana E[MAXN*MAXN]; // edges
int EC; // edge count
int from[MAXN*MAXN*2]; // where did i come from?
int count=0; // guard count
int finish,kde,ec;

int mycmp(const void *a, const void *b){
	thrana *aa,*bb;
	aa=(thrana *)a; bb=(thrana *)b;
	if ((aa->x)!=(bb->x)) return ((aa->x)-(bb->x));
	return ((aa->y)-(bb->y));
}

int FindPath(void){

	int seen[MAXN*MAXN*2]; // seen a vertex?
	int Q[MAXN*MAXN*2]; // queue
	int qs,qf; // queue start/finish
	int i,kde,kam;

	bzero(seen,sizeof(seen));
	qs=qf=0;
	for (i=0;i<R;i++) if (!Ma[i]) {
		from[i]=-1; Q[qf++]=i; seen[i]=1;
	}
	while (qf>qs) {
		kde=Q[qs++];
		if (kde<R) {
			// follow an unmatched edge
			for (i=V[kde];i<V[kde+1];i++) if (!E[i].matched) {
				kam=E[i].y;
				if (!seen[kam]) { Q[qf++]=kam; seen[kam]=1; from[kam]=kde; }
				if (!Ma[kam]) { finish=kam; return 1; }
			}
		} else {
			// follow a matched edge
			for (i=V[kde];i<V[kde+1];i++) if (E[i].matched) {
				kam=E[i].y;
				if (!seen[kam]) { Q[qf++]=kam; seen[kam]=1; from[kam]=kde; }
			}
		}
	}
	return 0;
}

int EdgeNo(int x, int y) {
  thrana pom,*p2;
	
	pom.x=y; pom.y=x; pom.twin=0;
	p2=(thrana *)bsearch(&pom,E,EC,sizeof(thrana),mycmp);
	if (p2==NULL) return -1;
	return (p2-E);
}

int main(void){
  FILE *f;
  f=fopen("guards.in","r"); stdin=f;
  f=fopen("guards.out","w"); stdout=f;
	scanf("%d %d ",&M,&N);
	for (i=1;i<=M;i++) for (j=1;j<=N;j++) scanf("%d",&A[i][j]);
  for (i=0;i<=M+1;i++) { A[i][0]=A[i][N+1]=2; }
  for (j=0;j<=N+1;j++) { A[0][j]=A[M+1][j]=2; }
	for (i=0;i<=M+1;i++) for (j=0;j<=N+1;j++) BR[i][j]=BC[i][j]=A[i][j];
  
  R=C=0;

if (DEBUG){
fprintf(stderr,"Input:\n");
for(i=1;i<=M;i++){for(j=1;j<=N;j++)fprintf(stderr,"%d ",A[i][j]);
fprintf(stderr,"\n");}
}

	for (i=1;i<=M;i++) { // numbers the rows
		j=0; 
		while (BR[i][j]==2) j++;
		while (j<=N) {
			while (BR[i][j]!=2) { BR[i][j]=-R; j++; }
			Coord[R]=i;
			R++;
		  while ((j<=N)&&(BR[i][j]==2)) j++;
		}
	}

if (DEBUG){
fprintf(stderr,"Rows:\n");
for(i=1;i<=M;i++){
	for(j=1;j<=N;j++) fprintf(stderr,"%d ",BR[i][j]); fprintf(stderr,"\n");}
}
	
  for (j=1;j<=N;j++) { // numbers the cols
		i=0; 
		while (BC[i][j]==2) i++;
		while (i<=M) {
			while (BC[i][j]!=2) { BC[i][j]=-C; i++; }
			Coord[R+C]=j;
			C++; // :-)) C++ rulez
		  while ((i<=M)&&(BC[i][j]==2)) i++;
		}
	}

if (DEBUG){
fprintf(stderr,"Cols:\n");
for(i=1;i<=M;i++){
	for(j=1;j<=N;j++)fprintf(stderr,"%d ",BC[i][j]); fprintf(stderr,"\n");}
}
	
  
	// build the graph
	EC=0;
	for (i=1;i<=M;i++) for (j=1;j<=N;j++) if (A[i][j]==0) {
		E[EC].x=-BR[i][j]; E[EC].y=R-BC[i][j]; 
		E[EC].twin=-1; E[EC].matched=0; EC++;
		E[EC].x=R-BC[i][j]; E[EC].y=-BR[i][j];
		E[EC].twin=-1; E[EC].matched=0; EC++;
  }
	qsort(E,EC,sizeof(thrana),mycmp);
	E[EC].x=E[EC].y=R+C+47;

if (DEBUG){
fprintf(stderr,"Edges:\n");
for (i=0;i<EC;i++) fprintf(stderr,"[%d %d] ",E[i].x,E[i].y); 
fprintf(stderr,"\n");
}
	
  for (i=0;i<R+C;i++) V[i]=-1;
  i=j=0;
	while (j<EC) {
		if (E[j].x>=i) { V[i]=j; i++; } else j++;
	}
	V[R+C]=EC;

if (DEBUG){
fprintf(stderr,"Vertices start:\n");
for (i=0;i<R+C;i++) fprintf(stderr,"%d ",V[i]); 
fprintf(stderr,"\n");
}

  for (i=0;i<EC;i++) if (E[i].twin==-1) 
		E[i].twin=EdgeNo(E[i].x,E[i].y);
 
if (DEBUG){
fprintf(stderr,"Twins:\n");
for (i=0;i<R+C;i++) fprintf(stderr,"%d ",E[i].twin); 
fprintf(stderr,"\n");
}

  // find maximum matching

  for (i=0;i<R+C;i++) Ma[i]=0;
  while (FindPath()){
		count++;
		// switch the edges along the path
		kde=finish;
		Ma[kde]=1;
		while (from[kde]!=-1) { 
			ec=EdgeNo(kde,from[kde]);
			E[ec].matched=1-E[ec].matched; 
			E[E[ec].twin].matched=1-E[E[ec].twin].matched;
			kde=from[kde]; 
			if (kde!=-1) Ma[kde]=1;
		}
	}

	printf("%d\n",count);
  for (i=0;i<EC;i++) 
		if ((E[i].matched)&&(E[i].x<E[i].y)) 
			printf("%d %d\n",Coord[E[i].x],Coord[E[i].y]);

  return 0;
}

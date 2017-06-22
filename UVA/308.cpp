// Src: I think author solution
/*
	Algorithm:	Interval Compression & Flood Fill
	Complexity:	n^2
*/
#include <iostream>
#include <algorithm>
using namespace std;

int qh, qt, aserholes;
int x[256], y[256], uniqe[256];
char bitmap[32768];		//Play on Bits Not Array 2D of Bytes

#define QS 8192	  /* Queue Size for floodfill 512 x 512 */
#define TEST(x,y) (bitmap[64*(x)+(y)/8]& (1<<(y)%8) )
#define SET(x,y)  (bitmap[64*(x)+(y)/8]|=1<<((y)%8) )
#define MIN(a,b)  ((a<b)?a:b)
#define MAX(a,b)  ((a>b)?a:b)

struct coordinate
{
	int x, y;
};
coordinate flood_queue[QS];

//South / North / West/ East
int dirx[4] = { -1, 1, 0, 0 };
int diry[4] = { 0, 0, -1, 1 };

int cmp(const void *a, const void *b)
{
	return (*(int*)a) - (*(int*)b);
}

int compress(int *axis, int n)//Interval Compression
{
	int i, j;

	memcpy(uniqe, axis, n *  sizeof(int));
	qsort (uniqe, n   , sizeof(int), cmp);	//Muse be Sorted

	for(j = 0, i = 1; i < n; i++)		//Remove duplication
	{
		if(uniqe[j] != uniqe[i])		//Found new Value
			uniqe[++j] = uniqe[i];		//Resue the hole of duplication
	}

	j++;  //Now uniqe array has no repetation with lenght j for an axis.

	for(i = 0; i < n; i++)	//2* For simplicity; 1 Make no overlapping
		axis[i] = 2*((int*)bsearch(&axis[i], uniqe, j, 4, cmp)-uniqe+1);

	return 2*(j+1);		//2*( + 1) For Boundary Frame
}

void flood_fill(int i, int j)
{
	int k, ii, jj, iii, jjj;
	SET(i,j);		//Will be flooded & its neighbours
	//Set in queue frons
	flood_queue[0].x = i;
	flood_queue[0].y = j;
	qh = 1;		  qt = 0;

	while(qh != qt)	//Untill flooding its neighbours in queue
	{
		ii = flood_queue[qt].x;
		jj = flood_queue[qt].y;
		qt = (qt+1)%QS;	//For Circular Queue [Reuse]

		for(k = 0; k < 4; k++)	//Flood in the 4 directions
		{
			//(iii, jjj) new pos to flood (ii, jj) neighbour.
			iii = ii + dirx[k];
			jjj = jj + diry[k];

			if(TEST(iii,jjj))
			{
				if(!aserholes)
					continue;

				iii += dirx[k];
				jjj += diry[k];

				if(TEST(iii,jjj)) // We are Flooding inside a hole |
					continue;	  // Already Flooded | Outside boundary
			}

			SET(iii,jjj); //Will be flooded & its neighbours

			//Set curent pos in queue to re-Flood fill in [qh].
			flood_queue[qh].x = iii;
			flood_queue[qh].y = jjj;
			qh = (qh+1)%QS; //For Circular Queue [Reuse]
		}
	}
	aserholes++;	//Stoping to Flood means There is a hole
}
//Frame For Not going outside boundary : Outside neighbours range
void set_rectangle_frame(int xn, int yn)
{
	int i, j;
	//Set bits in rows 0, yn [row boundry]
	for(i = 0; i <= xn; i++)
	{
		SET(i,0);
		SET(i,yn);
	}
	//Set bits in col 0, xn [col boundry]
	for(j = 1; j <= yn; j++)
	{
		SET(0,j);
		SET(xn,j);
	}
}

void set_input_frames(int n)
{
	int a, b, c, i;
	for(i = 0; i < 2*n; i+=2)	//Next Two points
	{
		if(x[i] == x[i+1])//Make relation between start and end cuts
		{
			a = MIN(y[i], y[i+1]);
			b = MAX(y[i], y[i+1]);
			c = x[i];

			for(; a <= b; a++)	//So line of bits exist on Y-axis
				SET(c, a);

		}
		else
		{
			a = MIN(x[i], x[i+1]);
			b = MAX(x[i], x[i+1]);
			c = y[i];
			for(; a <= b; a++) //So line of bits exist on X-axis
				SET(a, c);
		}
	}
}

void main()
{
	int i, j, n, xn, yn;

	while(cin>>n && n)
	{
		memset(bitmap, 0, sizeof(bitmap));	///Use Bitwise Operators

		for(i = 0; i < 2*n; i++)
			cin>>x[i]>>y[i];

		//Compress to another Simple Interval/No need for real positions
		xn = compress(x, 2*n);
		yn = compress(y, 2*n);

		set_input_frames(n);			//Set bits as lines of uts

		aserholes = 0;
		set_rectangle_frame(xn, yn);	//Make Boundaryies For Flooding

		for(i = 1; i < xn; i++)
		{
			for(j = 1; j < yn; j++)
			{	//i, j inside the bounday
				if( TEST(i,j) )
					continue;	//Already flooded & its neighbours

				flood_fill(i, j);
			}
		}
		cout<< aserholes-1<<"\n";
	}
}
/*
Why aserholes-1????????????????? The idea is Simple
You have two situations During Flooding

  1)When Flooding in space[No holes] the Flood queue will
  Contain all possiple points that is not inside a hole
  When Flooding Finish all out holes bits will be One
  and flooding stop.It can not do more the [aserholes++;]

  *)Now assume there where no holes = 0 so need aserholes-1;

  2)Assume there were 3 holes.
  When iterating inside Flood Fill 2 Loops Assume
  First some luck to fill all out holes spaces and stop

  when loop ask to flood already flooded it continue
  But when start again to Flood for sure it is a hole
  after flooding this hole bondaries with ones will stop it

  If another flood_fill() was called so there is another hole....
*/

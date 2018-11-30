/*
TASK: MAZE
LANG: C
*/
#include <stdio.h>

#define MAXW 510
#define MAXH 510

#define WHITE  0
#define BLACK  1

#define INFINITY 1000000

    typedef struct vertex {
        int n;       /* how many moves to reach this vertex?  */
        
        int nedges;  /* number of neighbouring vertices (0..6) */
        int e[6];    /* neighbouring vertices */
    } vertex;
    
    int other(int c) {
        return c ^ 1;
    }

    int vertexn(int x, int y, int c) {
        return ((y * MAXW + x) * 2 + c);
    }

    void addedge(vertex *v, int p) {
        v->e[v->nedges++] = p;
    }

    vertex maze[MAXH*MAXW*2];
    int    W, H, Sx, Sy, Fx, Fy;    
    
void readdata(void)
{
    int  i, j, t, color;
    int  x, y, x1, x2, y1, y2;
    char buff[MAXW*2+2];
    
    FILE *f = fopen("MAZE.IN", "rt");
    fscanf(f, "%d %d\n", &W, &H);
    fscanf(f, "%d %d %d %d\n", &Sx, &Sy, &Fx, &Fy);
    
    for (j = 0; j < 2*H + 1; j++) {         // reading lines
        y = j / 2;
        t = (j % 2 == 0) ? W : 2*W + 1;
        fgets(buff, MAXW*2 + 2, f);
        for (i = 0; i < t; i++)
            if (buff[i] != 'n') {
                if (j % 2 == 0) {           // horizontal edges
                    x = i; x1 = x; x2 = x + 1; y1 = y2 = y;
                } else 
                    if (i % 2 == 0) {       // non-horizontal edges
                        x = i/2; x1 = x2 = x; y1 = y; y2 = y + 1;
                    } else {
                        x = i/2 + 1; x1 = x; x2 = x - 1; y1 = y; y2 = y + 1;
                    }
                color = (buff[i] == 'w') ? WHITE : BLACK;

                addedge(&maze[vertexn(x1, y1, other(color))], vertexn(x2, y2, color));
                addedge(&maze[vertexn(x2, y2, other(color))], vertexn(x1, y1, color));
            }
    }

    fclose(f);
}

void writedata(void)
{
    FILE *f = fopen("MAZE.OUT", "wt");
    fprintf(f, "%d\n", maze[vertexn(Fx, Fy, WHITE)].n < maze[vertexn(Fx, Fy, BLACK)].n ?
                       maze[vertexn(Fx, Fy, WHITE)].n : maze[vertexn(Fx, Fy, BLACK)].n);    
    fclose(f);
}

    int queue[MAXW*MAXH*2 + 10];
    int Q = 0;
    
    void enqueue(int p) {
        queue[Q++] = p;
    }

int main(void)
{
    int i, j;
    int q, v, k;
    
    readdata();

    for (j = 0; j <= H; j++)
        for (i = 0; i <= W; i++) {
            maze[vertexn(i, j, WHITE)].n = INFINITY;
            maze[vertexn(i, j, BLACK)].n = INFINITY;
        }

    /* performing BFS */

    enqueue(vertexn(Sx, Sy, WHITE));
    enqueue(vertexn(Sx, Sy, BLACK));
    
    maze[vertexn(Sx, Sy, WHITE)].n = maze[vertexn(Sx, Sy, BLACK)].n = 0;
    
    for (q = 0; q < Q; q++) { /* while haven't reached the end of the queue */
        v = queue[q];
        for (i = 0; i < maze[v].nedges; i++) { /*  */
            k = maze[v].e[i];
            if (maze[k].n == INFINITY) {
                maze[k].n = maze[v].n + 1;
                enqueue(k);
            }
        }
    }
    
    writedata();
    return 0;
}

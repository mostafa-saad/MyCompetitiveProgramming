#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const char *DIRS = "DRUL";
const int DIRX[] = {1, 0, -1, 0};
const int DIRY[] = {0, 1, 0, -1};
const int MAX = 200;

int n, m;
char warehouse[MAX][MAX+1];
struct coords {
    int x, y;
    coords( int X=-1, int Y=-1 ) { x = X; y = Y; }

    bool ok() { return x >= 0 && x < n && y >= 0 && y < m && warehouse[x][y] != '#'; }

    coords adj(int dir) { return coords(x + DIRX[dir], y + DIRY[dir]); }
};
bool operator < (const coords &A, const coords &B) {
    if( A.x != B.x ) return A.x < B.x; else return A.y < B.y;
}
bool operator != (const coords &A, const coords &B) { return A < B || B < A; }

int dist;
coords MIN, target[2];

int output( int id, char d ) {
    printf( "%d %c\n", id, d );
    fflush( stdout );
    int ret;
    scanf( "%d", &ret );
    return ret;
}

struct Robot {
    int id;
    int last_dir;
    coords pos;
    Robot *other;

    Robot(int ID) {
        id = ID;
        pos = coords(0, 0);
    }

    bool go(int dir) {
        int new_dist = output(id, DIRS[dir]);
        if( new_dist == dist ) return false;

        pos = pos.adj(dir);

        last_dir = dir;
        dist = new_dist;
        return true;
    }

    bool go_anywhere() {
        for( int dir = 0; dir < 4; ++dir )
            if( go(dir) ) return true;
        return false;
    }

    bool go_back() {
        return go((last_dir+2)%4);
    }
} *robot1 = new Robot(1), *robot2 = new Robot(2);

bool move(Robot *robot, int dir) {
    if( robot->go(dir) ) return true;
    if( dist > 1 ) return false;

    Robot *other = robot->other;

    bool collision;
    if( other->go_anywhere() ) {
        if( (collision = robot->go(dir)) ) robot->go_back();
        other->go_back();
    } else {
        robot->go_anywhere();
        if( (collision = other->go((dir+2)%4)) ) other->go_back();
        robot->go_back();
    }
    if( collision ) {
        other->pos = robot->pos;
        robot->pos = robot->pos.adj(dir);
        std::swap(robot->id, other->id);
    }
    return collision;
}

struct DFS {
    char seen_[2*MAX+1][2*MAX+1];
    char& seen(int x, int y) { return seen_[x+MAX][y+MAX]; }

    coords min;

    DFS() {
        memset(seen_, 0, sizeof seen_);
        min = coords(0, 0);
    }

    void visit(Robot *robot) {
        seen(robot->pos.x, robot->pos.y) = 1;
        if( robot->pos < min ) min = robot->pos;

        for( int dir = 0; dir < 4; ++dir ) {
            coords new_pos = robot->pos.adj(dir);
            if( seen(new_pos.x, new_pos.y) ) continue;

            if( move(robot, dir) ) {
                visit(robot);
                move(robot, (dir+2)%4);
            }
        }
    }
};

void localize() {
    DFS dfs;
    dfs.visit(robot1);

    robot1->pos.x = MIN.x + robot1->pos.x - dfs.min.x;
    robot1->pos.y = MIN.y + robot1->pos.y - dfs.min.y;

    robot2->pos.x = MIN.x + robot2->pos.x - dfs.min.x;
    robot2->pos.y = MIN.y + robot2->pos.y - dfs.min.y;
}

void bfs(Robot *robot, coords target) {
    std::queue<coords> q;

    int how[MAX][MAX];
    memset(how, -1, sizeof how);

    q.push(target);
    how[target.x][target.y] = -2;
    for( q.push(target); !q.empty(); q.pop() ) {
        for( int dir = 0; dir < 4; ++dir ) {
            coords p = q.front().adj(dir);
            if( !p.ok() || how[p.x][p.y] != -1) continue;

            how[p.x][p.y] = (dir+2)%4;
            q.push(p);
        }
    }

    while( robot->pos != target )
        move(robot, how[robot->pos.x][robot->pos.y]);
}

void init() {
    scanf( "%d%d", &n, &m );
    for( int i = 0; i < n; ++i )
        scanf( "%s", warehouse[i] );
    scanf( "%d", &dist );

    for( int i = 0; i < n; ++i ) {
        for( int j = 0; j < m; ++j ) {
            if( warehouse[i][j] != '#' && MIN.x == -1 ) MIN = coords(i, j);
            if( warehouse[i][j] == 'x' )
                if( target[0].x == -1 ) target[0] = coords(i, j);
                else target[1] = coords(i, j);
        }
    }
    robot1->other = robot2;
    robot2->other = robot1;
}

int main() {
    init();
    localize();

    bfs(robot1, target[0]);
    bfs(robot2, target[1]);
    bfs(robot1, target[0]);

    printf( "0\n" );
    return 0;
}

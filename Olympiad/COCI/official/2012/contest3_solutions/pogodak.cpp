#include <cstdio>

using namespace std;

struct dice{
  int row[4];
  int up, down;

  dice(){
    row[0] = 4;
    row[1] = 6;
    row[2] = 3;
    row[3] = 1;
    up = 5;
    down = 2;
  }

  void roll_down(){
    int old_up = up;

    up = row[1];
    row[1] = down;
    down = row[3];
    row[3] = old_up;
  }

  void roll_right(){
    int old_left = row[0];

    for( int i = 0; i < 3; i++ )
      row[i] = row[i+1];
    row[3] = old_left;
  }

  void roll_left(){
    roll_right();
    roll_right();
    roll_right();
  }

  void roll( bool dir ){
    if( !dir ) roll_right();
    else roll_left();
  }
  
  int top(){ return row[3]; }
  int sum_row(){ return row[0] + row[1] + row[2] + row[3]; } //uvijek 14
};

int main(){
  dice curr;

  int r, c;
  scanf( "%d %d", &r, &c );

  long long sol = 0;
  bool dir = 0;

  for( int row = 0; row < r; row++, dir = !dir ){
    sol += curr.top();

    int repeat = (c-1) / 4;
    sol += repeat * curr.sum_row();

    int rest = (c-1) % 4;
    for( int i = 0; i < rest; i++ ){
      curr.roll(dir);
      sol += curr.top();
    }

    curr.roll_down();
  }

  printf( "%lld\n", sol );
  return 0;
}

/* Task PUZZLE */
/* Correct solution */
/* Time complexity: O(n^2) */

#include<iostream>
#include<stdio.h>

using namespace std;
const int MAX_N = 210;

int n; // size of the board
int board[MAX_N][MAX_N];
int position[MAX_N*MAX_N];
int moves;
int move_table[400000][3];
bool possible = true;
int tmp[210];

/* saving logs about moves */
void m_row(int row_no, int count) { 
	move_table[moves][0] = 2;
	move_table[moves][1] = row_no+1;
	move_table[moves][2] = count;
	moves++;
	return;
}
void m_column(int kol_no, int count) {	
	move_table[moves][0] = 1;
	move_table[moves][1] = kol_no+1;
	move_table[moves][2] = count;
	moves++;
	return;
}

void set_pos(int zm1, int zm2) { 
	position[board[zm1][zm2]] = zm1*1000 + zm2;
	return;
}

// changes three fields 
void change_by_one(int x1, int y1, int x2, int y2, int x3, int y3) { 
	int q1 = board[x1][y1];
	board[x1][y1] = board[x3][y3];
	board[x3][y3] = board[x2][y2];
	board[x2][y2] = q1;
	set_pos(x1,y1);
	set_pos(x2,y2);
	set_pos(x3,y3);
	return;
}
	

	


void move_column(int kol_no, int count) { 
	m_column(kol_no,count);
	count = n - count;
	for (int i=0; i<count; i++) tmp[i] = board[i][kol_no];
	for (int i=count; i<n; i++) { 
		board[i-count][kol_no] = board[i][kol_no];
		set_pos(i-count,kol_no);
	}
	for (int i=n-count; i<n; i++) {
		board[i][kol_no] = tmp[i-(n-count)];
		set_pos(i,kol_no);
	}
	return;
}

void move_row(int row_no, int count) { 
	m_row(row_no,count);
	count = n - count;
	for (int j=0; j<count; j++) tmp[j] = board[row_no][j];
	for (int j=count; j<n; j++) { 
		board[row_no][j-count] = board[row_no][j];
		set_pos(row_no,j-count);
	}
	for (int j=n-count; j<n; j++) {
		board[row_no][j] = tmp[j-(n-count)];
		set_pos(row_no,j);
	}
	return;
}
				
void move_piece(int x1, int y1, int x2, int y2) { 
// 1 possibility
	if ((x1==x2)&&(y1==y2)) return;
// 2 possibility
	if (x1==x2) {
		m_column(y1,1);
		m_row(x1+1,1);
		m_column(y1,n-1);
		m_row(x1+1,n-1);
		if (y1!=0) { 
			change_by_one(x1,y1,x1+1,y1,x1+1,y1-1);
		} else change_by_one(x1,y1,x1+1,y1,x1+1,n-1);

		move_piece(x1+1,y1,x2,y2);
		return;
	}
// 3 possibility
	if (y1==y2) { 
		m_row(x1,1);
		if (x1>x2) m_column(y1,x1-x2); else m_column(y1,x2-x1);
		m_row(x1,n-1);
		if (x1>x2) m_column(y1,n-(x1-x2)); else m_column(y1,n-(x2-x1));
		if (y1!=0) { 
			change_by_one(x1,y1,x2,y2,x1,y2-1);
		} else change_by_one(x1,y1,x2,y2,x1,n-1);
		return;		
		/*+=1;
		if (y1==n) y1 = 0;*/
	}
// 4 posiibility	
	if (x1>x2) m_column(y2,x1-x2); else m_column(y2,x2-x1);
	int move_val = 0;
	if (y2>y1) {
		move_val = y2-y1;
		m_row(x1,y2-y1);
	} else {
		m_row(x1,n-(y1-y2));
		move_val = n-(y1-y2);
	}
	if (x1>x2) m_column(y2,n-(x1-x2)); else m_column(y2,n-(x2-x1));
	move_val *=-1;
	while (move_val<0) move_val+=n;
	if (move_val!=0) m_row(x1,move_val);
	change_by_one(x1,y2,x1,y1,x2,y2);
	
	return;
}

void swap_in_last_line(int t1, int t2, int t3) { 
	m_column(t1,n-1);
	int first_move;
	if (t2>t1) { 
		m_row(n-1,n-(t2-t1));
		first_move = n-(t2-t1);
	} else {
		m_row(n-1,t1-t2);
		first_move = t1-t2;
	}
	m_column(t1,1);
	int sec_move;
	if (t3>t1) { 
		sec_move = n-(t3-t1);
	} else sec_move = t1-t3;
	int mo = sec_move - first_move;
	if (mo<0) mo+=n;
	if (mo!=0) m_row(n-1,mo);
	m_column(t1,n-1);
	int las = -mo-first_move;
	while (las<0) las+=n;
	if (las!=0) m_row(n-1,las);
	m_column(t1,1);
	change_by_one(n-1,t1,n-1,t2,n-1,t3);	
	return;
}
	

void set_last_line(int y1, int y2) { 
	if (y1==y2) return;

	int tar1 = y1;
	int tar2 = y2;
	int tar3 = -1;
	for (int i=(n-1); i>y2; i--) {
		if (i!=y1) { 
			tar3 = i;
			break;
		}
	}
	if (tar3==-1) { cout << "ERROR !!!!!!!"<< endl; exit(1); }
	swap_in_last_line(tar1,tar2,tar3);
	return;
}

void check_possibility() {
	bool cycle[210];
	for (int j=0; j<n; j++) cycle[j] = false;
	int length = 0;
	for (int j=0; j<n; j++) {
		if (cycle[j]==false) { 
			int akt = j;
			cycle[j] = true;
			while ((board[n-1][akt]-1)%n!=j) {
				akt = (board[n-1][akt]-1)%n;
				cycle[akt] = true;
				length++;
			}
		}
	}
	if (length%2==1) { 
		if (n%2==0) { 
			move_row(n-1,1);
			possible = true;
			return;
		} else
			possible = false;
	} else possible = true;
	return ;
}

int main () { 
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		 for (int j=0; j<n; j++) { 
			 scanf("%d",&board[i][j]);
			 set_pos(i,j);
		 }
	}
	moves = 0;
	for (int aktual_piece=1; aktual_piece<=n*(n-1); aktual_piece++) {
		move_piece(position[aktual_piece]/1000,position[aktual_piece]%1000,(aktual_piece-1)/n, (aktual_piece-1)%n);
	}
	check_possibility();
	if (possible) {
		for (int aktual_piece=n*(n-1)+1; aktual_piece<=n*n; aktual_piece++) { 
			set_last_line(position[aktual_piece]%1000, (aktual_piece-1)%n);
		}
	}

	if (!possible) {
		printf("NO\n");
		return 0;
	} 
	printf("%d\n",moves);
	for (int i=0; i<moves; i++) {
		if (move_table[i][0]==1) printf("C "); else printf("R ");
		printf("%d %d\n",move_table[i][1],move_table[i][2]);
	}
	
	return 0;
}

	
	
	
	

	

	

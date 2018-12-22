#include <iostream>
#include <string>
#include <vector>
#define SQR(x) ((x)*(x))

using namespace std;

vector<string> tlocrt;
vector<pair<int, int> > bakice;
vector<pair<int, int> > sjedala;

int dist(int b, int s){
    return SQR(bakice[b].first - sjedala[s].first) + SQR(bakice[b].second - sjedala[s].second);
}

int main(){
    int r, s;
    cin >> r >> s;
    for (int i = 0; i < r; i++){
	string a;
	cin >> a;
	tlocrt.push_back(a);
    }
   
    for (int i = 0; i < r; i++)
	for (int j = 0; j < s; j++){
	    if ( tlocrt[i][j] == 'X' ){
		bakice.push_back(make_pair(i, j));
	    }
	    else if ( tlocrt[i][j] == 'L' ){
		sjedala.push_back(make_pair(i, j));
	    }
	}

    int boom = 0;
    char done = 0;
    while ( !done ){
	int najnajblizi = -1;
	vector<int> najblizi(bakice.size(), -1);
	done = 1;
	
	for (int b = 0; b < bakice.size(); b++)
	    if ( tlocrt[bakice[b].first][bakice[b].second] == 'X' ){
		int best = -1;
		for (int s = 0; s < sjedala.size(); s++)
		    if ( tlocrt[sjedala[s].first][sjedala[s].second] == 'L' ){
			if ( best == -1 || dist(b, s) < dist(b, best) )
			    best = s;
		    }
		if ( best == -1 )
		    break;

		done = 0;
		najblizi[b] = best;
		if ( najnajblizi == -1 || dist(b, best) < dist(najnajblizi, najblizi[najnajblizi]) )
		    najnajblizi = b;
	    }

	if ( done ) 
	    break;

/*	cout << "+++++++" << endl;
	for (int i = 0; i < najblizi.size(); i++){
	    if ( i == najnajblizi ) cout << "->";
	    cout << najblizi[i] << endl; 
	}*/
	
	vector<int> explodes;
	for (int b = 0; b < bakice.size(); b++)
	    if ( tlocrt[bakice[b].first][bakice[b].second] == 'X' )
		if ( najblizi[b] == najblizi[najnajblizi] && dist(b, najblizi[najnajblizi]) == dist(najnajblizi, najblizi[najnajblizi]) )
		    explodes.push_back(b);

	if ( explodes.size() > 1 )
	    boom++;
	
	for (int i = 0; i < explodes.size(); i++)
	    tlocrt[bakice[explodes[i]].first][bakice[explodes[i]].second] = '.';
	
	tlocrt[sjedala[najblizi[najnajblizi]].first][sjedala[najblizi[najnajblizi]].second] = '.';
    }

    printf("%d\n", boom);

    return 0;
}

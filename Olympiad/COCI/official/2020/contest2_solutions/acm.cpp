#include <string>
#include <iostream>
using namespace std;

const int maxm = 20;
const int maxn = 1005;

int n, m;
string name[maxn];
int penalty[maxn];

int teamIndex;
int solved[maxn];
int endList[maxn];

int getNumber(string &task) {
	int ret = 0;
	while (task[0] != '/') {
		ret = ret * 10 + (task[0] - '0');
		task = task.substr(1);
	}
	task = task.substr(1);
	return ret;
}

int dig(char x) {
	return x - '0';
}

int parseTime(string taskTime) {
	return dig(taskTime[1]) * 60 * 60 + dig(taskTime[3]) * 10 * 60 + dig(taskTime[4]) * 60 + dig(taskTime[6]) * 10 + dig(taskTime[7]);
}

void load(int index) {
	solved[index] = 0;
	penalty[index] = 0;
	for (int i = 0; i < m; i++) {
		string task;	
		cin >> task;
		if (task[0] != '-') {
			solved[index]++;
			task = task.substr(1);
			int submissions = getNumber(task);
			penalty[index] += submissions * 20 * 60 + parseTime(task);			
		}
	}	
}

bool cmp(int x, int y) {
	if (solved[x] != solved[y])
		return solved[x] > solved[y];
	if (penalty[x] != penalty[y])
		return penalty[x] < penalty[y];
	return name[x] < name[y];
}

int main (void) {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> name[i];
		if (name[i] == "NijeZivotJedanACM") 
			teamIndex = i;
		load(i);
	}	
	cin >> name[teamIndex];
	load(teamIndex);
	int sol = 1;
	for (int i = 0; i < n; i++)
		if (i != teamIndex) 
			sol += (int)cmp(i, teamIndex);
	cout << sol << endl;
	return 0;
}

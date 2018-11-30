#include <cstdio>
#include <deque>
#include <utility>
#include <iostream>
using namespace std;

typedef pair<short,short> PSS;

char m[4200][4200];
int h,w;
int main()
{
	scanf("%d %d", &h, &w);
	for(int i = 0; i < h; ++i)
		scanf("%s", m[i+1]+1);

	deque<PSS> q;
	q.push_back(PSS(1,1));
	char last = 'R'+'F'-m[1][1];
	int count = 0;
	while(!q.empty())
	{
		PSS pos = q.front();
		q.pop_front();
		char curr = m[pos.first][pos.second];
		if(curr == 0)
			continue;	// already visited
		m[pos.first][pos.second] = 0;
		//cout << "doing: " << pos.first << " " << pos.second << " " << curr << endl;
		if(curr != last)
		{
			last = curr;
			++count;
		}
		PSS pos2; char next;
		pos2 = PSS(pos.first+1, pos.second);
		next = m[pos2.first][pos2.second];
		if(next == curr)
			q.push_front(pos2);
		else if(next + curr == 'R'+'F')
			q.push_back(pos2);

		pos2 = PSS(pos.first-1, pos.second);
		next = m[pos2.first][pos2.second];
		if(next == curr)
			q.push_front(pos2);
		else if(next + curr == 'R'+'F')
			q.push_back(pos2);

		pos2 = PSS(pos.first, pos.second+1);
		next = m[pos2.first][pos2.second];
		if(next == curr)
			q.push_front(pos2);
		else if(next + curr == 'R'+'F')
			q.push_back(pos2);

		pos2 = PSS(pos.first, pos.second-1);
		next = m[pos2.first][pos2.second];
		if(next == curr)
			q.push_front(pos2);
		else if(next + curr == 'R'+'F')
			q.push_back(pos2);
	}

	printf("%d\n", count);
}

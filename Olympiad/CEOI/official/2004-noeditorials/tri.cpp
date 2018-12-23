/* TASK : TRIPS
 * Greedy solution
 * Complexity: O(n log n) + O(n + mlogm)
 *
 * Implementation uses STL sort and heap
 *
 * Author: Marcin Michalski
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

#define REP(i,a) for (int i=0; i<(a); i++)
#define FOR(i,a,b) for (int i=(a); i<=(b); i++)
#define FORD(j,a,b) for (int j=(a); j>=(b); j--)

struct group{
	int original_number; // original number of group
	int size;	     // group size
	int matched;	     // -1 if group not matched, number of trip otherwise
};
struct trip{
	int original_number;
	int minim; // minimal number of people
	int maxim; // maximal number of people 
};

int n; //number of groups
int m; //number of trips

vector<group> groups;
vector<trip> trips;

vector<int> heap; // This vector will be used as heap

// Comparing two group members
bool ascend(group smaller, group larger) {
	if (smaller.size<larger.size) return true;
	return false;
}
//Comparing two trip members
bool ascend2(trip smaller, trip larger) {
	if (smaller.minim<larger.minim) return true;
	return false;
}

// Comparing for heap
// in heap the biggest is on top
bool heap_order(int smaller, int greater) {
	if (trips[smaller].maxim>trips[greater].maxim) return true;
	return false;
}
	

void add_heap(int number) {
	heap.push_back(number);
	if (heap.size()>1) { 
		push_heap(heap.begin(),heap.end(),heap_order);
	}
	return;
}

int get_from_heap() {
	if (heap.size()==0) return -1;
	int result = heap[0];
	if (heap.size()>1) pop_heap(heap.begin(), heap.end(),heap_order);
	heap.pop_back();
	return result;
}
	


void read_data() {
// READING DATA SECTION	
	int size_of_group; 
	REP(i,n) {
		scanf("%d",&size_of_group);
		groups[i].original_number = i;
		groups[i].size = size_of_group;
		groups[i].matched = -1;
	}
	int minimum,maximum; // minimal and maximal number of people for the trip
	REP(i,m) {
		scanf("%d%d",&minimum,&maximum);
		trips[i].original_number = i;
		trips[i].minim = minimum;
		trips[i].maxim = maximum;
	}
	return;
}

int main () {
	scanf("%d%d",&n,&m);
	groups.resize(n);
	trips.resize(m);
	read_data();
//SORTING
	sort(groups.begin(),groups.end(),ascend);
	sort(trips.begin(),trips.end(),ascend2);
	int current_trip = 0; // the number of the next trip that is not used
	int result = 0; // counting the number of "matchings"
	int best_trip;
	REP(i,n){
		// adding all trips that weren't added and has
		// minimal demands smaller than size of current group
		while ((current_trip<m)&&(trips[current_trip].minim<=groups[i].size)){
			add_heap(current_trip);
			current_trip++;
		}
		best_trip = get_from_heap();
		while ((best_trip!=-1)&&(trips[best_trip].maxim<groups[i].size)){
			best_trip = get_from_heap();
		}
		if (best_trip!=-1) { 
			// we found a match
			result++;
			groups[i].matched = trips[best_trip].original_number;
		}
	}
	printf("%d\n",result);
	REP(i,n){
		if (groups[i].matched!=-1) 
			printf("%d %d\n",groups[i].original_number+1,groups[i].matched+1);
	}
	return 0;
}

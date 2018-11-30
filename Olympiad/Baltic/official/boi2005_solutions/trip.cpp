// BOI 2005
// Task: BUS TRIP
// Solution
// Author: Martin Pettai

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const char *iname = "trip.in";
const char *oname = "trip.out";

const int MAXN = 50000;
const int MAXM = 100000;

struct Busline {
   int src, dest; // source and destination towns of the bus line
   int starttime, fintime, waittime; // the earliest departure time, the latest arrival time, and the maximum waiting time of bus line

   bool operator< (const Busline &b) const { return fintime < b.fintime; }
};

struct State {
   int tim;
   int waittime; // time waited till time 'tim'

   State(int a, int b): tim(a), waittime(b) {}

   bool operator< (const State &b) const { return tim < b.tim; }
};

Busline lines[MAXM];
vector<State> sta[MAXN];

int main() {
   int N, M, P, T;

   FILE *ifile = fopen(iname, "rt");
   fscanf(ifile, "%d %d %d %d", &N, &M, &P, &T);
   P--; // adjust for 0-based arrays

   for (int i=0; i<M; i++) {
      int b, c;
      fscanf(ifile, "%d %d %d %d %d %d", &lines[i].src, &lines[i].dest,
         &lines[i].starttime, &b, &c, &lines[i].fintime);
      lines[i].waittime = b - lines[i].starttime + lines[i].fintime - c;
      lines[i].src--;
      lines[i].dest--;
   }
   sort(lines, lines+M);
   fclose(ifile);

   sta[0].push_back(State(0,0));

   for (int i=0; i<M; i++) {
      int starttime = lines[i].starttime;
      int src = lines[i].src;
      int dest = lines[i].dest;

      if (lines[i].fintime > T) // the bus arrives too late
         break;

      // it is not possible to be at the source town by the earliest departure time of the line
      if (sta[src].empty() || sta[src][0].tim > starttime)
         continue;

      // binary search
      State beginst = *(upper_bound(sta[src].begin(), sta[src].end(), State(starttime,0))-1);
      State endst(lines[i].fintime, beginst.waittime + (starttime - beginst.tim) + lines[i].waittime);

      if (sta[dest].size() > 0) {
         State last = sta[dest][sta[dest].size()-1];
         if (last.waittime + (endst.tim - last.tim) < endst.waittime)
            continue;
      }
      sta[dest].push_back(endst);
   }

   FILE *ofile = fopen(oname, "wt");
   if (sta[P].empty())
      fprintf(ofile, "-1\n");
   else
      fprintf(ofile, "%d\n", sta[P][sta[P].size()-1].waittime + (T - sta[P][sta[P].size()-1].tim));
   fclose(ofile);

   return 0;
}

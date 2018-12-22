
/*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak STRAZA
  Programski jezik C++

  Rovove smo predstavili duzinama. Pretpostavimo da se nijedne dvije
  duzine koje se nalaze na istom pravcu ne sijeku. U tom slucaju svake
  tri duzine, koje se sijeku svaka sa svakom, a da ta tri sjecista
  nisu u istoj tocki, predstavljaju jedno rjesenje - strazare mozemo
  postaviti u sjecista tih duzina. Za svaku trojku duzina provjerimo
  vrijede li ta svojstva, i ako da ubrojimo ju u rjesenje.  Preostaje
  samo osigurati pretpostavku. Ako postoje dvije duzine koje se nalaze
  na istom pravcu i sijeku se, mozemo ih spojiti i tretirati kao jednu
  duzinu. Taj postupak ponavljamo sve dok imamo sto za spojiti i
  osigurali smo pretpostavku.

  Da bismo izbrojali rjesenja potrebno je provjeriti sve trojke duzina
  sto daje slozenost O(N^3).
*/

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

#define EPS 1e-9
#define eq(a,b) ( ((a)-EPS <= (b)) && ((b) <= (a)+EPS) )
#define lt(a,b) ( (a)+EPS < (b) )
#define gt(a,b) ( (a)-EPS > (b) )

struct tocka {
   double x, y;
   tocka() { x = y = 0; }
   tocka( const tocka &drugi ) { *this = drugi; }
   tocka( double X, double Y ) { x = X; y = Y; }
   friend bool operator==(const tocka &p1, const tocka &p2)
   {
      return eq(p1.x,p2.x) && eq(p1.y,p2.y);
   }
};

struct duzina {
   tocka a, b;
   duzina( const tocka &A, const tocka &B ) { a = A; b = B; }
};

struct pravac { // !! Ax+By=C, a ne Ax+By+C=0 !!
   double A, B, C;
   pravac( const duzina &S ) {
      A = S.b.y - S.a.y;
      B = S.a.x - S.b.x;
      C = A*S.a.x + B*S.a.y;
   }
};

int mysgn( double val ) {
   if( lt( val, 0 ) ) return -1;
   if( gt( val, 0 ) ) return 1;
   return 0;
}

int ccw( const tocka &A, const tocka &B, const tocka &C )
{  return mysgn( (B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y) );  }

int strana( const pravac &L, const tocka &T )
{  return mysgn( L.A*T.x + L.B*T.y - L.C );  }

bool sijece( const pravac &L, const tocka &P )
{  return eq( L.A*P.x + L.B*P.y - L.C, 0 ); }

bool sijece( const duzina &S, const tocka &P ) {
   return sijece( pravac(S), P ) &&
      eq( fabs(S.b.x-P.x)+fabs(S.a.x-P.x), fabs(S.b.x-S.a.x) ) &&
      eq( fabs(S.b.y-P.y)+fabs(S.a.y-P.y), fabs(S.b.y-S.a.y) );
}
bool sijece( const pravac &L1, const pravac &L2 )
{  return !eq( L1.A*L2.B, L2.A*L1.B );  }

bool sijece( const pravac &L, const duzina &S )
{  return strana( L, S.a ) * strana( L, S.b ) <= 0; }

bool sijece( const duzina &S1, const duzina &S2 ) {
   if( sijece( pravac(S1), S2.a ) && sijece( pravac(S1), S2.b ) )
      return sijece( S1, S2.a ) || sijece( S1, S2.b ) ||
         sijece( S2, S1.a ) || sijece( S2, S1.b );
   return sijece( pravac(S1), S2 ) && sijece( pravac(S2), S1 );
}

tocka sjeciste( const pravac &L1, const pravac &L2 ) {
   return tocka( (L1.C*L2.B-L2.C*L1.B) / (L1.A*L2.B-L2.A*L1.B),
                 (L1.A*L2.C-L2.A*L1.C) / (L1.A*L2.B-L2.A*L1.B) );
}

vector<duzina> niz;

bool izmedu(const tocka &A, const tocka &B, const tocka &C)
{
   if(lt(fabs(A.x-C.x),fabs(A.x-B.x))) return 0;
   if(lt(fabs(A.y-C.y),fabs(A.y-B.y))) return 0;
   if(lt(fabs(A.x-C.x),fabs(C.x-B.x))) return 0;
   if(lt(fabs(A.y-C.y),fabs(C.y-B.y))) return 0;
   return 1;
}

bool treba_spojit(const duzina &s1, const duzina &s2)
{
   if(ccw(s1.a,s1.b,s2.a)!=0 || ccw(s1.a,s1.b,s2.b)!=0) return 0;
   if(izmedu(s1.a,s2.a,s1.b) || izmedu(s1.a,s2.b,s1.b)) return 1;
   return 0;
}

duzina spoji(const duzina &s1, const duzina &s2)
{

   if(izmedu(s1.a,s2.a,s1.b) && izmedu(s1.a,s2.b,s1.b)) return s1;
   if(izmedu(s2.a,s1.a,s2.b) && izmedu(s2.a,s1.b,s2.b)) return s2;

   if(izmedu(s1.a,s2.a,s1.b))
      {
         if(izmedu(s2.a,s1.a,s2.b)) return duzina(s1.b,s2.b);
         if(izmedu(s2.a,s1.b,s2.b)) return duzina(s1.a,s2.b);
      }
   if(izmedu(s1.a,s2.b,s1.b))
      {
         if(izmedu(s2.a,s1.a,s2.b)) return duzina(s1.b,s2.a);
         if(izmedu(s2.a,s1.b,s2.b)) return duzina(s1.a,s2.a);
         return s1;
      }
   return s1; // ovo se nikad ne desi
}

int main()
{
   int n;
   scanf("%d",&n);
   for(int i=0;i<n;i++)
      {
         int x1,y1,x2,y2;
         scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
         niz.push_back(duzina(tocka(x1,y1),tocka(x2,y2)));
      }

   int spojio=1;
   while(spojio)
      {
         spojio=0;
         for(int i=0;i<(int)niz.size();i++)
            for(int j=i+1;j<(int)niz.size();j++)
               {
                  if(treba_spojit(niz[i],niz[j]))
                     {
                        spojio=1;
                        niz[i]=spoji(niz[i],niz[j]);
                        niz.erase(niz.begin()+j);
                        break;
                     }
               }
      }
   int rez=0;
   for(int i=0;i<(int)niz.size();i++)
      for(int j=i+1;j<(int)niz.size();j++)
        for(int k=j+1;k<(int)niz.size();k++)
            {
               if(sijece(niz[i],niz[j]) && sijece(niz[i],niz[k]) && sijece(niz[j],niz[k]))
                  {
                     if(!(sjeciste(niz[i],niz[j])==sjeciste(niz[i],niz[k]))) rez++;
                  }
            }

   printf("%d\n",rez);
   return 0;
}

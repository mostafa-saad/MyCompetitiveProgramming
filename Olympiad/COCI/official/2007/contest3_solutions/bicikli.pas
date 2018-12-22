
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task BICIKLI
  Programming language Pascal
*/

program bicikli;

type brid = record
   a, b : longint;
end;
type niz_bridova = array[1..100001] of brid;
type graf = record
   bridovi : niz_bridova;
   start : array[1..10001] of longint;
   dostupan : array[1..10000] of longint;
end;

var
   n, m : longint;
   i, a, b : longint;
   broj, rjesenje : longint;

   normalan_graf, obrnuti_graf : graf;

   jelvelik : longint;
   memo : array[1..10000] of longint;
   boja : array[1..10000] of longint;

procedure dfs( var G : graf; i : longint );
var
   j : longint;
begin
   if G.dostupan[i] = 1 then exit;
   G.dostupan[i] := 1;

   for j := G.start[i] to G.start[i+1]-1 do
      dfs( G, G.bridovi[j].b );
end;

function rekurzija( i : longint ) : longint;
var
   j, k : longint;
begin
   if boja[i] = 2 then begin
      rekurzija := memo[i];
      exit;
   end;
   if boja[i] = 1 then begin
      jelvelik := 2;
      rekurzija := 0;
      exit;
   end;

   boja[i] := 1;

   memo[i] := 0;
   if i = 2 then memo[i] := 1;

   for j := normalan_graf.start[i] to normalan_graf.start[i+1]-1 do begin
      k := normalan_graf.bridovi[j].b;
      if (normalan_graf.dostupan[k] = 1) and (obrnuti_graf.dostupan[k] = 1) then begin
         memo[i] := memo[i] + rekurzija( k );
         if memo[i] >= 1000000000 then begin
            jelvelik := 1;
            memo[i] := memo[i] - 1000000000;
         end;
      end;
   end;

   boja[i] := 2;

   rekurzija := memo[i];
end;

var
   tmp : niz_bridova;

procedure mergesort( var x : niz_bridova; lo, hi : longint );
var
   mid : longint;
   i, j, k : longint;
begin
   if lo <> hi then begin
      mid := (lo+hi) div 2;
      mergesort( x, lo, mid );
      mergesort( x, mid+1, hi );

      i := lo;
      j := mid+1;
      k := lo;
      while (i <= mid) and (j <= hi) do begin
         if x[i].a < x[j].a then begin
            tmp[k] := x[i];
            i := i + 1;
         end else begin
            tmp[k] := x[j];
            j := j + 1;
         end;
         k := k + 1;
      end;
      while i <= mid do begin
         tmp[k] := x[i];
         i := i + 1;
         k := k + 1;
      end;
      while j <= hi do begin
         tmp[k] := x[j];
         j := j + 1;
         k := k + 1;
      end;
      for i := lo to hi do x[i] := tmp[i];
   end;
end;

procedure pripremi( var G : graf );
var
   i, j : longint;
begin
   mergesort( G.bridovi, 1, m );
   G.bridovi[m+1].a := 30000;

   j := 1;
   for i := 1 to n do begin
      while G.bridovi[j].a < i do j := j + 1;
      G.start[i] := j;
   end;
   G.start[n+1] := m+1;

   for i := 1 to n do G.dostupan[i] := 0;
end;

begin
   jelvelik := 0;
   readln( n, m );
   for i := 1 to m do begin
      readln( a, b );

      normalan_graf.bridovi[i].a := a; normalan_graf.bridovi[i].b := b;
      obrnuti_graf.bridovi[i].a := b; obrnuti_graf.bridovi[i].b := a;
   end;

   pripremi( normalan_graf );
   pripremi( obrnuti_graf );

   for i := 1 to n do boja[i] := 0;

   dfs( normalan_graf, 1 );
   dfs( obrnuti_graf, 2 );

   rjesenje := rekurzija( 1 );

   if jelvelik = 2 then writeln( 'inf' );
   if jelvelik = 1 then begin
      broj := 100000000;
      while rjesenje < broj do begin
         broj := broj div 10;
         write( '0' );
      end;
   end;
   if jelvelik <> 2 then writeln( rjesenje );
end.

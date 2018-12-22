
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task TENKICI
  Programming language Pascal
*/

program tenkici;

type niz = array[1..500] of integer;

var
   r, s : niz;
   n : integer;
   i, K : longint;
   rjesenje_tenk : array[1..2*500*500] of integer;
   rjesenje_smjer : array[1..2*500*500] of char;

{ rasporedjuje tenkice po retcima (stupcima) }
procedure rasporedi( a : niz; n : integer; X, Y : char );
var
   index : niz;
   i, j, tmp : integer;
begin
   for i := 1 to n do
      index[i] := i;

   { sortiraj }
   for i := 1 to n do
      for j := i+1 to n do
         if a[j] < a[i] then begin
            tmp := a[i]; a[i] := a[j]; a[j] := tmp;
            tmp := index[i]; index[i] := index[j]; index[j] := tmp;
         end;

   { pomakni sve koji idu gore (lijevo) }
   for i := 1 to n do
      while a[i] > i do begin
         a[i] := a[i] - 1;
         K := K + 1;
         rjesenje_tenk[K] := index[i];
         rjesenje_smjer[K] := X;
      end;

   { pomakni sve koji idu dolje (desno) }
   for i := n downto 1 do
      while a[i] < i do begin
         a[i] := a[i] + 1;
         K := K + 1;
         rjesenje_tenk[K] := index[i];
         rjesenje_smjer[K] := Y;
      end;
end;

begin
   readln( n );

   for i := 1 to n do
      readln( r[i], s[i] );

   rasporedi( r, n, 'U', 'D' ); { rasporedi tenkice po retcima }
   rasporedi( s, n, 'L', 'R' ); { rasporedi tenkice po stupcima }

   writeln( K );
   for i := 1 to K do
      writeln( rjesenje_tenk[i], ' ', rjesenje_smjer[i] );
end.

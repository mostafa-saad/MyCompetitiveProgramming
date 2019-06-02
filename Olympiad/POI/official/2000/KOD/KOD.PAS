{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: KOD                                            *}
{*   Plik:                KOD.PAS                                        *}
{*   Autor:               Marcin Mucha                                   *}
{*************************************************************************}

{$M 32768,0,655360}
const
   fin_name = 'kod.in';
   fout_name = 'kod.out';

   K_MAX = 26;

var
   fin, fout : text;

   k : byte;
   n : longint;
   code : string;

   { counter[i,j] = liczba drzew o i w©zˆach z korzeniem nr j (j od 0)}
   { Warto zwr¢ci† uwag©, ¾e counter[i,0] to przy okazji liczba wszystkich }
   { drzew o i-1 w©zˆach. }
   counter : array[0..K_MAX,0..K_MAX-1] of longint;
   { Sumy cz©˜ciowe dla poprzedniej tablicy. }
   total_counter : array[0..K_MAX,0..K_MAX-1] of longint;


procedure gen_code( k : byte);
{ Funkcja generuj¥ca tablic© counter i total_counter }
var
   i, j : integer;
begin
   counter[0,0] := 1;
   total_counter[0,0] := 1;
   counter[1,0] := 1;
   total_counter[1,0] := 1;

   for i := 2 to k do
      begin
         counter[i,0] := total_counter[i-1,i-2];
         total_counter[i,0] := counter[i,0];
         for j := 1 to i - 1 do
            begin
               counter[i,j] := counter[j+1,0] * counter[i-j,0];
               total_counter[i,j] := total_counter[i,j-1] + counter[i,j]
            end
      end
end;

function get_code( n : longint; k : byte) : string;
{ Funkcja rekurencyjna znajduj¥ca (n,k)-kod. }
var
   i, j : integer;
   nr, nr1, nr2 : longint;
   s1, s2 : string;
begin
   if k = 0 then
      get_code := ''
   else
      begin
         i := 0;
   { Tu mo¾na zastosowa† wyszukiwanie binarne, tylko po co?}
         while total_counter[k,i] < n do inc( i);
         if i > 0 then
            nr := n - total_counter[k,i-1]
         else
            nr := n;
   { Musimy wyznaczy† drzewo numer nr spo˜r¢d
     k-wierzchoˆkowych drzew o korzeniu i.}
         nr1 := ( nr - 1) div counter[k-i,0] + 1;
         s1 := get_code( nr1, i);
         nr2 := ( nr - 1) mod counter[k-i,0] + 1;
         s2 := get_code( nr2, k - i - 1);
    { Dostajemy ``string'' zbudowany z liter 'a'..., nale¾y go przesun¥†. }
         for j := 1 to length( s2) do inc( s2[j], i + 1);
         get_code := char( ord('a') + i) + s1 + s2
      end
end;

begin
   assign( fin, fin_name);
   reset( fin);
   read( fin, n, k);
   close( fin);
   gen_code( k);
   code := get_code( n, k);
   assign( fout, fout_name);
   rewrite( fout);
   write( fout, code);
   close( fout);
end.
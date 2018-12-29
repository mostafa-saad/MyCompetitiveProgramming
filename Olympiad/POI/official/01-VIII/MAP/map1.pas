{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: MAPA GÊSTOŒCI                                  *}
{*   Plik:                MAP1.PAS                                       *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

{ Algorytm nieoptymalny O(n^2*r^2)                                        }

const
   fin_name = 'map.in';
   fout_name = 'map.out';

   N_MAX = 250;

type
   parray = ^tarray;
   tarray = array[1..N_MAX] of word;

var
   n, r : integer;
   T : array[1..N_MAX] of parray;

procedure read_data;
var
   fin : text;
   i, j : integer;
   x : word;
begin
   assign( fin, fin_name);
   reset( fin);
   readln( fin, n, r);
   for i := 1 to n do
      begin
         T[i] := new( parray);
         for j := 1 to n do
            read( fin, T[i]^[j]);
         readln( fin);
      end;
   close( fin)
end;

function min( a, b : integer) : integer;
begin
   if a < b then min := a else min := b
end;

function max( a, b : integer) : integer;
begin
   if a > b then max := a else max := b
end;

procedure write_map;
var
   fout : text;
   i, j : integer;
   i_minus, i_plus, j_minus, j_plus : integer;
   k,l : integer;
   sum : word;
begin
   assign( fout, fout_name);
   rewrite( fout);
   for i := 1 to n do
      begin
         i_minus := max( 1, i - r);
         i_plus := min( n, i + r);
         for j := 1 to n do
            begin
               j_minus := max( 1, j - r);
               j_plus := min( n, j + r);
               sum := 0;
               for k := i_minus to i_plus do
                  for l := j_minus to j_plus do
                     sum := sum + T[k]^[l];
               write( fout, sum);
               if j <> n then write( fout, ' ')
            end;
         writeln( fout)
      end;
   close( fout);

   for i := 1 to n do
      dispose( T[i])
end;


begin
   read_data;
   write_map;
end.

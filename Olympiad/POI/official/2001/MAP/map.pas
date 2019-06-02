{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: MAPA GÊSTOŒCI                                  *}
{*   Plik:                MAP.PAS                                        *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

program mapa;
const
   fin_name = 'map.in';
   fout_name = 'map.out';

   N_MAX = 250;

type
   parray = ^tarray;
   tarray = array[0..N_MAX] of word;

var
   n, r : integer;
   T : array[0..N_MAX] of parray;

procedure read_data;
var
   fin : text;
   i, j : integer;
   x : word;
begin
   assign( fin, fin_name);
   reset( fin);
   readln( fin, n, r);
   T[0] := new( parray);
   for i := 1 to n do
      begin
         T[i] := new( parray);
         for j := 1 to n do
            read( fin, T[i]^[j]);
         readln( fin);
      end;
   close( fin)
end;

procedure preprocess;
{ Obliczanie sum cz©˜ciowych}
var
   i, j : integer;
begin
   for j := 0 to n do
      T[0]^[j] := 0;
   for i := 0 to n do
      T[i]^[0] := 0;

   for i := 1 to n do
      for j := 1 to n do
         T[i]^[j] := T[i]^[j] + T[i-1]^[j] - T[i-1]^[j-1] + T[i]^[j-1]
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
begin
   assign( fout, fout_name);
   rewrite( fout);
   for i := 1 to n do
      begin
         i_minus := max( 0, i - r - 1);
         i_plus := min( n, i + r);
         for j := 1 to n do
            begin
               j_minus := max( 0, j - r - 1);
               j_plus := min( n, j + r);
               write( fout, T[i_plus]^[j_plus] - T[i_plus]^[j_minus] + T[i_minus]^[j_minus] - T[i_minus]^[j_plus]);
               if j <> n then write( fout, ' ')
            end;
         writeln( fout)
      end;
   close( fout);

   for i := 0 to n do
      dispose( T[i])
end;


begin
   read_data;
   preprocess;
   write_map;
end.

{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: GORSZY GOLDBACH                                *}
{*   Plik:                GOL.PAS                                        *}
{*   Autor:               MARCIN MUCHA                                   *}
{*************************************************************************}

const
   first : array[3..26] of integer =
   (3,0,5,0,7,5,0,7,11,7,13,11,7,11,17,11,11,13,11,17,11,13,13,11);

   COVER_SIZE=29;
   cover : array[1..COVER_SIZE] of longint =
   (1000000007,500000009,250000013,125000077,62500073,31250047,15625031,
   7812521,3906269,1953151,976601,488309,244177,122099,61057,30539,15277,
   7649,3833,1931,971,491,251,131,71,41,29,23,17);

const N_MIN = 27;

var
   fin, fout : text;
   stack : array[1..40] of longint;
   ssize : byte;

procedure result;
var
   i : byte;
begin
   writeln( fout, ssize);
   for i := ssize downto 1 do
   begin
      write( fout, stack[i]);
      if i <> 1 then write( fout, ' ');
   end;
   writeln( fout)
end;

procedure push( i : longint);
begin
   inc( ssize);
   stack[ssize] := i
end;

procedure search(n : longint);
var
   p, i : longint;
begin
   ssize := 0;
   i := 1;
   while n > 0 do
   begin
      if n < N_MIN then
         p := first[n]
      else
         begin
            while cover[i]+10 > n do inc( i);
            p := cover[i]
         end;
      push( p);
      n := n - p
   end
end;

var
   i, m : byte;
   n : longint;

begin
   assign( fin, 'gol.in');
   reset( fin);
   assign( fout, 'gol.out');
   rewrite( fout);
   readln( fin, m);
   for i := 1 to m do
   begin
      readln( fin, n);
      search( n);
      result;
   end;
   close( fout);
   close( fin);
end.


/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task LISTA
  Programming language Pascal
*/

program lista;

type cvor = record
   L, R : longint;
end;

var
   n, k : longint;
   list : array[0..500001] of cvor;

   prosli : array[0..500000] of longint;
   M : array[0..500000] of longint;

   A : array[0..500000] of longint;

   c : char;
   x, y : longint;
   i, j : longint;
   lo, hi, mid : longint;
   najdulji : longint;
   zadnji : longint;

begin
   readln( n, k );
   for i := 0 to n+1 do begin
      list[i].L := i-1;
      list[i].R := i+1;
   end;

   for i := 1 to k do begin
      readln( c, x, y );

      { izbaci x iz liste }
      list[list[x].R].L := list[x].L;
      list[list[x].L].R := list[x].R;

      { odredi nove susjede cvoru x }
      if c = 'A' then begin
         list[x].L := list[y].L;
         list[x].R := y;
      end else begin
         list[x].L := y;
         list[x].R := list[y].R;
      end;

      { ubaci x u listu }
      list[list[x].R].L := x;
      list[list[x].L].R := x;
   end;

   { nadji najdulji rastuci podniz }
   M[0] := 0;
   for i := 1 to n do M[i] := 1000000000;

   najdulji := 0;
   x := list[0].R;
   while x <> n+1 do begin
      lo := 0; hi := n;
      while lo <> hi do begin
         mid := (lo+hi) div 2;
         if M[mid] < x then lo := mid + 1 else hi := mid;
      end;
      M[lo] := x;
      prosli[x] := M[lo-1];
      if lo > najdulji then najdulji := lo;

      x := list[x].R;
   end;

   writeln( n - najdulji );

   k := 0;
   x := M[najdulji];
   while x <> 0 do begin
      A[najdulji-k] := x;
      k := k + 1;

      x := prosli[x];
   end;

   i := 1; j := 1;
   while i <= najdulji do begin
      if j = A[i] then i := i + 1
      else writeln( 'A ', j, ' ', A[i] );
      j := j + 1;
   end;

   zadnji := A[najdulji];
   while j <= n do begin
      writeln( 'B ', j, ' ', zadnji );
      zadnji := j;
      j := j + 1;
   end;
end.

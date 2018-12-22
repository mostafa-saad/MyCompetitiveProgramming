program baza;

var
   n, m : longint;
   s : string;
   a : array[1..30000] of string;

   sorted : array[1..30000,1..32] of char;
   counter : array[1..30000,1..32] of longint;
   before : array[1..30000,1..32] of longint;
   id : array[1..30000] of longint;
   start, finish : array[1..32] of longint;

   order, tmp : array[1..30000] of longint;

   i, j, qq, ret, row, column : longint;

procedure mergesort( lo, hi : longint );
var
   mid : longint;
   i, j, k : longint;
begin
   if lo <> hi then begin
      mid := (lo+hi) div 2;
      mergesort( lo, mid );
      mergesort( mid+1, hi );

      i := lo;
      j := mid+1;
      k := lo;
      while (i <= mid) and (j <= hi) do begin
         if a[order[i]] < a[order[j]] then begin
            tmp[k] := order[i];
            i := i + 1;
         end else begin
            tmp[k] := order[j];
            j := j + 1;
         end;
         k := k + 1;
      end;
      while i <= mid do begin
         tmp[k] := order[i];
         i := i + 1;
         k := k + 1;
      end;
      while j <= hi do begin
         tmp[k] := order[j];
         j := j + 1;
         k := k + 1;
      end;
      for i := lo to hi do order[i] := tmp[i];
   end;
end;



function findBorder( x : char; column, lo, hi : longint ) : longint;
var
   mid : longint;
begin
   if x > sorted[hi-1,column] then begin
      findBorder := hi;
   end else begin
      while lo + 1 < hi do begin
         mid := (lo+hi-1) div 2;
         if x > sorted[mid,column] then lo := mid+1 else hi := mid+1;
      end;
      findBorder := lo;
   end;
end;

function search( var s : string; column, lo, hi : longint ) : longint;
begin
   start[column] := 0;
   finish[column] := 0;

   if column > length( s ) then begin
      if sorted[lo,column] = '.' then search := lo else search := 0;
   end else begin
      start[column] := findBorder( s[column], column, lo, hi );
      finish[column] := findBorder( chr(ord(s[column])+1), column, lo, hi );

      if start[column] = finish[column] then search := 0
      else search := search( s, column + 1, start[column], finish[column] );
   end;
end;

begin
   readln( n );
   for i := 1 to n do begin
      readln( a[i] );
      order[i] := i;
   end;
   mergesort( 1, n );

   for i := 1 to n do begin
      for j := 1 to 32 do begin
         sorted[i,j] := '.';
         counter[i,j] := 0;
         before[i,j] := 0;
      end;
      for j := 1 to length( a[order[i]] ) do
         sorted[i,j] := a[order[i]][j];
   end;

   for i := 1 to n do begin
      row := search( a[i], 1, 1, n+1 );
      id[row] := i;

      column := 1;
      while start[column] < finish[column] do begin
         inc( counter[start[column],column] );
         before[row,column] := counter[start[column],column];
         inc( column );
      end;
   end;

   readln( m );
   for qq := 1 to m do begin
      readln( s );

      row := search( s, 1, 1, n+1 );
      if row = 0 then begin
         ret := n;
         column := 1;
         while start[column] < finish[column] do begin
            ret := ret + counter[start[column],column];
            inc( column );
         end;
      end else begin
         ret := id[row];
         column := 1;
         while start[column] < finish[column] do begin
            ret := ret + before[row,column];
            inc( column );
         end;
      end;

      writeln( ret );
   end;
end.

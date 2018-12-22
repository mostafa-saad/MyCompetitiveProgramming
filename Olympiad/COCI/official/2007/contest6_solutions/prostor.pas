
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task PROSTOR
  Programming language Pascal
*)

program prostor;

type
   dogadjaj = record tip, y, x1, x2, z1, z2 : longint; end;
   niz_dogadjaja = array[1..200000] of dogadjaj;
   dogadjaji = record A : niz_dogadjaja; N : longint; end;
   tabla = array[1..999, 1..999] of longint;
var
   tmp : niz_dogadjaja;

function less_than( a, b : dogadjaj ) : integer;
begin
   if a.y < b.y then less_than := 1
   else if b.y < a.y then less_than := 0
   else if a.tip < b.tip then less_than := 1
   else less_than := 0;
end;

procedure merge_sort( var a : niz_dogadjaja; lo, hi : longint );
var
   mid, i, j, k : longint;
begin
   if lo < hi then begin;
      mid := (lo+hi) div 2;
      merge_sort( a, lo, mid );
      merge_sort( a, mid+1, hi );

      i := lo; j := mid+1; k := lo;

      while (i <= mid) and (j <= hi) do begin
         if less_than( a[i], a[j] ) = 1 then begin
            tmp[k] := a[i]; inc(i); inc(k);
         end else begin
            tmp[k] := a[j]; inc(j); inc(k);
         end;
      end;
      while i <= mid do begin
         tmp[k] := a[i]; inc(i); inc(k);
      end;
      while j <= hi do begin
         tmp[k] := a[j]; inc(j); inc(k);
      end;

      for k := lo to hi do a[k] := tmp[k];
   end;
end;

procedure dodaj_dogadjaj( var sweep : dogadjaji; t, y, x1, x2, z1, z2 : longint );
begin
   inc(sweep.N);
   sweep.A[sweep.N].tip := t;
   sweep.A[sweep.N].y := y;
   sweep.A[sweep.N].x1 := x1;
   sweep.A[sweep.N].x2 := x2;
   sweep.A[sweep.N].z1 := z1;
   sweep.A[sweep.N].z2 := z2;
end;

var
   lo, hi : tabla;

procedure update( var loga : tabla; x, y, delta : longint );
var
   i, j : longint;
begin
   i := x;
   while i <= 999 do begin
      j := y;
      while j <= 999 do begin
         loga[i, j] := loga[i, j] + delta;
         j := j + (j and -j);
      end;

      i := i + (i and -i);
   end;
end;

function query2( var loga : tabla; x, y : longint ) : longint;
var
   i, j, ret : longint;
begin
   ret := 0;
   i := x;
   while i > 0 do begin
      j := y;
      while j > 0 do begin
         ret := ret + loga[i, j];
         j := j - (j and -j);
      end;

      i := i - (i and -i);
   end;
   query2 := ret;
end;

function query( var loga : tabla; X1, Y1, X2, Y2 : longint ) : longint;
begin
   query := query2( loga, X2, Y2 ) - query2( loga, X1-1, Y2 ) - query2( loga, X2, Y1-1 ) + query2( loga, X1-1, Y1-1 );
end;


function rijesi( var sweep : dogadjaji ) : int64;
var
   ret : int64;
   i, j : longint;
begin
   ret := 0;
   merge_sort( sweep.A, 1, sweep.N );

   for i := 1 to 999 do for j := 1 to 999 do lo[i, j] := 0;
   for i := 1 to 999 do for j := 1 to 999 do hi[i, j] := 0;

   for i := 1 to sweep.N do begin

      if (sweep.A[i].tip = 1) or (sweep.A[i].tip = 2) then begin
         ret := ret + query( lo, sweep.A[i].x1, 1, sweep.A[i].x2, sweep.A[i].z2 );
         ret := ret - query( hi, sweep.A[i].x1, 1, sweep.A[i].x2, sweep.A[i].z1 - 1 );
      end;

      if sweep.A[i].tip = 1 then begin
         update( lo, sweep.A[i].x1, sweep.A[i].z1, 1 );
         update( hi, sweep.A[i].x2, sweep.A[i].z2, 1 );
      end;

      if sweep.A[i].tip = 3 then begin
         update( lo, sweep.A[i].x1, sweep.A[i].z1, -1 );
         update( hi, sweep.A[i].x2, sweep.A[i].z2, -1 );
      end;

   end;
   rijesi := ret;
end;

var
   n : longint;
   i, t : longint;
   x1, y1, z1 : longint;
   x2, y2, z2 : longint;
   sweepXY, sweepYZ, sweepZX : dogadjaji;

begin
   readln( n );

   sweepXY.N := 0;
   sweepYZ.N := 0;
   sweepZX.N := 0;

   for i := 1 to n do begin
      readln( x1, y1, z1, x2, y2, z2 );

      if x2 < x1 then begin t := x1; x1 := x2; x2 := t; end;
      if y2 < y1 then begin t := y1; y1 := y2; y2 := t; end;
      if z2 < z1 then begin t := z1; z1 := z2; z2 := t; end;

      if x1 = x2 then begin
         dodaj_dogadjaj( sweepXY, 1, y1, x1, x2, z1, z2 );
         dodaj_dogadjaj( sweepZX, 2, x1, z1, z2, y1, y2 );
         dodaj_dogadjaj( sweepXY, 3, y2, x1, x2, z1, z2 );
      end;
      if y1 = y2 then begin
         dodaj_dogadjaj( sweepYZ, 1, z1, y1, y2, x1, x2 );
         dodaj_dogadjaj( sweepXY, 2, y1, x1, x2, z1, z2 );
         dodaj_dogadjaj( sweepYZ, 3, z2, y1, y2, x1, x2 );
      end;
      if z1 = z2 then begin
         dodaj_dogadjaj( sweepZX, 1, x1, z1, z2, y1, y2 );
         dodaj_dogadjaj( sweepYZ, 2, z1, y1, y2, x1, x2 );
         dodaj_dogadjaj( sweepZX, 3, x2, z1, z2, y1, y2 );
      end;
   end;

   writeln( rijesi( sweepXY ) + rijesi( sweepYZ ) + rijesi( sweepZX ) );

end.

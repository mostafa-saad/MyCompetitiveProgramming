program pravokutni;

const MAX = 1500;

type
   ray = record
      dx, dy : int64;
      quadrant : longint;
   end;

procedure rotate90( var R : ray );
var
   tmp : int64;
begin
   tmp := R.dx; R.dx := R.dy; R.dy := -tmp;
   R.quadrant := (R.quadrant+1) mod 4;
end;

var
   i, j, k, n : longint;
   x : array[1..MAX] of longint;
   y : array[1..MAX] of longint;
   rays : array[1..MAX] of ray;
   tmp : array[1..MAX] of ray;
   count : array[0..3] of longint;
   solution : longint;

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
         if rays[i].dy*rays[j].dx < rays[j].dy*rays[i].dx then begin
            tmp[k] := rays[i];
            i := i + 1;
         end else begin
            tmp[k] := rays[j];
            j := j + 1;
         end;
         k := k + 1;
      end;
      while i <= mid do begin
         tmp[k] := rays[i];
         i := i + 1;
         k := k + 1;
      end;
      while j <= hi do begin
         tmp[k] := rays[j];
         j := j + 1;
         k := k + 1;
      end;
      for i := lo to hi do rays[i] := tmp[i];
   end;
end;

begin
   readln( n );
   for i := 1 to n do readln( x[i], y[i] );

   solution := 0;

   for i := 1 to n do begin
      for j := 1 to n do begin
         rays[j].quadrant := 0;
         rays[j].dx := x[j]-x[i];
         rays[j].dy := y[j]-y[i];

         if i = j then begin

            rays[j].quadrant := rays[1].quadrant;
            rays[j].dx := rays[1].dx;
            rays[j].dy := rays[1].dy;

         end else begin

            while not ((rays[j].dx > 0) and (rays[j].dy >= 0)) do
               rotate90( rays[j] );

         end;
      end;


      mergesort( 2, n );

      j := 2;
      while j <= n do begin
         count[0] := 0;
         count[1] := 0;
         count[2] := 0;
         count[3] := 0;

         k := j;
         while (k <= n) and (rays[j].dy*rays[k].dx = rays[k].dy*rays[j].dx) do begin
            count[rays[k].quadrant] := count[rays[k].quadrant] + 1;
            k := k + 1;
         end;
         j := k;

         solution += count[0] * count[1];
         solution += count[1] * count[2];
         solution += count[2] * count[3];
         solution += count[3] * count[0];
      end;
   end;

   writeln( solution );
end.

program platforme;

var
   N, i, rez : longint;
   platforme : array[1..100] of record y, x1, x2 : longint; end;

function spusti( x : double; y : longint ) : longint;
var
   i, rez : longint;
begin
   rez := 0;
   for i := 1 to N do begin
      if (platforme[i].y  < y) and
         (platforme[i].x1 < x) and
         (platforme[i].x2 > x) and
         (platforme[i].y  > rez) then
         rez := platforme[i].y;
   end;
   spusti := rez;
end;

begin
   readln(N);
   for i := 1 to N do
      readln(platforme[i].y, platforme[i].x1, platforme[i].x2);

   rez := 0;
   for i := 1 to N do begin
      rez := rez + platforme[i].y - spusti(platforme[i].x1 + 0.5, platforme[i].y);
      rez := rez + platforme[i].y - spusti(platforme[i].x2 - 0.5, platforme[i].y);
   end;
   writeln( rez );
end.

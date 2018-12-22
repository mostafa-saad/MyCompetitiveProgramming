program kuhar;

const inf = 1000000000;

var
   i, n, k : longint;
   x, y : array[1..100] of longint;
   cm, sm : array[1..100] of longint;
   cv, sv : array[1..100] of longint;
   lo, hi, mid : longint;

function nabavi( grama, cm, sm, cv, sv : longint ) : longint;
var
   rez, malih, velikih : longint;
begin
   rez := inf;

   velikih := 0;
   repeat
      malih := (grama - velikih * sv + sm-1) div sm;
      if malih < 0 then malih := 0;

      if malih * cm + velikih * cv < rez then
         rez := malih * cm + velikih * cv;

      velikih := velikih + 1;
   until (velikih-1) * sv > grama;

   nabavi := rez;
end;

function moguce( porcija : longint ) : boolean;
var
   cijena, i : longint;
begin
   cijena := 0;
   for i := 1 to n do
      cijena := cijena + nabavi( x[i] * porcija - y[i], cm[i], sm[i], cv[i], sv[i] );

   if cijena <= k then moguce := true else moguce := false;
end;

begin
   readln( n, k );
   for i := 1 to n do
      readln( x[i], y[i], sm[i], cm[i], sv[i], cv[i] );

   lo := 0;
   hi := 1;
   while moguce( hi ) do hi := hi * 2;

   while lo < hi do begin
      mid := (lo+hi+1) div 2;
      if moguce( mid ) then lo := mid else hi := mid-1;
   end;

   writeln( lo );
end.

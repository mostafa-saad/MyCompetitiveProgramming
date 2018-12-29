(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n M^2)                                         *
 *   Opis:              Rozwiazanie powolne, programowanie dynamiczne    *
 *                                                                       *
 *************************************************************************)

program wyrs2;

const
   MAXN = 210;
   MAXM = 210;
   inf = 1000000000;

type
   ll = longint;

var
   n,i,z,zp : longint;
   a,b,x,y,bound,minw,g : ll;
   d,ai,bi : array[0..MAXN] of ll;
   dyn : array[0..MAXN, -MAXM..MAXM] of ll;
   

procedure euclid(a, b : ll; var x, y : ll);
var
   xp, yp : ll;
begin
   if b = 0 then begin
      x := 1;
      y := 0;
   end
   else begin
      euclid(b, a mod b, xp, yp);
      x := yp;
      y := xp - (a div b)*yp;
   end;
end;

function gcd(a, b : ll) : ll;
begin
   if b = 0 then gcd := a
   else gcd := gcd(b, a mod b);
end;

function max(a, b : ll) : ll;
begin
   if a > b then max := a
   else max := b;
end;

function min(a, b : ll) : ll;
begin
   if a < b then min := a
   else min := b;
end;



begin
   Read(n,a,b);
   if n > 200 then repeat until false;
   for i:=0 to n-1 do Read(d[i]);

   { Check whether solution exists }
   g := gcd(a,b);
   for i:=0 to n-1 do
      if d[i] mod g <> 0 then begin
         Writeln(-1);
         exit;
      end;
   for i:=0 to n-1 do
      d[i] := d[i] div g;
   a := a div g;
   b := b div g;

   { Initial solution }
   bound := max(a, b);
   for i:=0 to n-1 do
      bound := max(bound, abs(d[i]));
   
   euclid(a,b,x,y);
   ai[0] := 0;
   bi[0] := 0;
   for i:=0 to n-1 do begin
      ai[i+1] := x * d[i];
      bi[i+1] := y * d[i];

      { Initial pointwise-minimal solution }
      while abs(ai[i])+abs(bi[i]) > abs(ai[i]+b)+abs(bi[i]-a) do begin
         ai[i] := ai[i]+b; bi[i] := bi[i]-a;
      end;
      while abs(ai[i])+abs(bi[i]) > abs(ai[i]-b)+abs(bi[i]+a) do begin
         ai[i] := ai[i]-b; bi[i] := bi[i]+a;
      end;
   end;

   { Dynamic programming }
   for z:=-bound to bound do
      dyn[n,z] := abs(ai[n] + b*z) + abs(bi[n] - a*z);
   for i:=n-1 downto 0 do
      for z:=-bound to bound do begin
          minw := inf;
          for zp:=-bound to bound do
             minw := min(minw, dyn[i+1,zp]
                         + abs(ai[i+1] + b*zp - (ai[i] + b*z))
                         + abs(bi[i+1] - a*zp - (bi[i] - a*z)));
          dyn[i,z] := minw;
      end;

   Writeln(dyn[0,0] div 2);
end.

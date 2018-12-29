(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Wyrownywanie terenu                              *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n log M)                                       *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

program wyr1;

const
   MAXN = 100100;
   inf = 1000000000000000000;

type segment = record
   sl, beg, num : Int64;
end;
type pair = record
   first, second : Int64;
end;

var
   n,a,b : Int64;
   d : array[0..MAXN] of Int64;
   i,j : longint;
   ans : Int64;
   ex,ey : Int64;
   left,right : array[0..MAXN, 0..4] of segment;
   left_len,right_len : array[0..MAXN] of longint;
   arr : array[0..MAXN*5] of pair;
   arr_len : longint;
   alfa,beta : int64;
   g : int64;
   aa,bb,xx,yy,dd : array[0..MAXN] of Int64;
   b1,a1,sl,t,theans,sum,ile : int64;
   pr : pair;

procedure swapit(var a, b : pair);
var t : pair;
begin
   t := a; a := b; b := t;
end;

function min(a, b : int64): Int64;
begin
   if a < b then min := a
   else min := b;
end;
   
{ Quicksort}
function partition(l, r : longint) : longint;
var x, i, j : longint;
begin
   x := arr[l].first;
   i := l;
   j := r+1;
   repeat
      repeat inc(i) until arr[i].first >= x;
      repeat dec(j) until arr[j].first <= x;
      if i < j then swapit(arr[i], arr[j]);
   until j<=i;
   swapit(arr[l], arr[j]);
   partition := j;
end;

procedure quicksort(l, r : longint);
var q : longint;
begin
   if l < r then begin
      q := partition(l, r);
      if q - l > 1 then quicksort(l, q-1);
      if r - q > 1 then quicksort(q+1, r);
   end;
end;


procedure euclid(a, b : Int64; var x, y : Int64);
var
   xp, yp : Int64;
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

function gcd(a, b : int64) : Int64;
begin
   if b = 0 then gcd := a
   else gcd := gcd(b, a mod b);
end;


function flr(a, b : Int64) : Int64;
begin
   if (a > 0) or (a mod b = 0) then flr := a div b
   else flr := (a div b) - 1;
end;

function fun(k : Int64) : Int64;
begin
   fun := abs(beta + k*b) + abs(alfa - k*a);
end;

procedure add_segment(i : longint; sl, beg, eend : Int64);
var
   segm : segment;
begin
   segm.sl := sl;
   segm.num := eend - beg;
   if eend-beg = 0 then exit;
   if sl <= 0 then begin
      segm.beg := eend;
      left[i, left_len[i]] := segm;
      inc(left_len[i]);
   end;
   if sl >= 0 then begin
      segm.beg := beg;
      right[i, right_len[i]] := segm;
      inc(right_len[i]);
   end;
end;


begin
   Read(n,a,b);
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

   { Special case when a=b }
   if a = b then begin
      ans := abs(d[0]) + abs(d[n-1]);
      for i:=0 to n-2 do
         ans := ans + abs(d[i+1] - d[i]);
      Writeln(ans div 2);
      exit;
   end;

   { Calculate an initial solution }
   euclid(a,b,ex,ey);
   for i:=0 to n-1 do begin
      aa[i] := ex*d[i];
      bb[i] := ey*d[i];
   end;

   xx[0] := aa[0];
   for i:=0 to n-2 do xx[i+1] := aa[i+1] - aa[i];
   xx[n] := -aa[n-1];
   yy[0] := bb[0];
   for i:=0 to n-2 do yy[i+1] := bb[i+1] - bb[i];
   yy[n] := -bb[n-1];

   { Calculate the piecewise-linear functions F(k) }
   for i:=0 to n do begin
      right_len[i] := 0;
      left_len[i] := 0;

      beta := xx[i];
      alfa := yy[i];
      b1 := flr(-beta,b);
      a1 := flr(alfa,a);
      sl := b-a;

      if a1 < b1 then begin
         t := b1; b1 := a1; a1 := t;
         sl := a-b;
      end;

      add_segment(i, -(a+b), -inf, b1);
      if b1+1 <= a1 then begin
         add_segment(i, fun(b1+1) - fun(b1), b1, b1+1);
         add_segment(i, sl, b1+1, a1);
         add_segment(i, fun(a1+1) - fun(a1), a1, a1+1);
      end
      else
         add_segment(i, fun(b1+1) - fun(b1), b1, b1+1);
      add_segment(i, a+b, a1+1, inf);
   end;

   theans := -1;

   { Case right }
   sum := 0;
   ans := 0;
   for i:=0 to n do begin
      dd[i] := right[i,0].beg;
      sum := sum + dd[i];
      beta := xx[i];
      alfa := yy[i];
      ans := ans + fun(dd[i]);
   end;
   if sum > 0 then ans := -1
   else begin

      arr_len := 0;
      for i:=0 to n do
         for j:=0 to right_len[i]-1 do begin
            pr.first := right[i,j].sl;
            pr.second := right[i,j].num;
            arr[arr_len] := pr;
            inc(arr_len);
         end;
      pr.first := inf;
      arr[arr_len] := pr;
      quicksort(0,arr_len-1);
      for i:=0 to arr_len-1 do begin
         ile := min(arr[i].second, -sum);
         ans := ans + arr[i].first * ile;
         sum := sum + ile;
         if sum = 0 then break;
      end;

   end;
   if ans <> -1 then theans := ans;

   { Case left }
   sum := 0;
   ans := 0;
   for i:=0 to n do begin
      dd[i] := left[i, left_len[i]-1].beg;
      sum := sum + dd[i];
      beta := xx[i];
      alfa := yy[i];
      ans := ans + fun(dd[i]);
   end;
   if sum < 0 then ans := -1
   else begin
      
      arr_len := 0;
      for i:=0 to n do
         for j:=0 to left_len[i]-1 do begin
            pr.first := -left[i,j].sl;
            pr.second := left[i,j].num;
            arr[arr_len] := pr;
            inc(arr_len);
         end;
      pr.first := inf;
      arr[arr_len] := pr;
      quicksort(0,arr_len-1);
      for i:=0 to arr_len-1 do begin
         ile := min(arr[i].second, sum);
         ans := ans + arr[i].first * ile;
         sum := sum - ile;
         if sum = 0 then break;
      end;

   end;
   if (ans <> -1) and ((theans = -1) or (ans < theans)) then theans := ans;

   Writeln(theans div 2);
      
end.

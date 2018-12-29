program plahte;

const MAXT = 1000001;

var
   n, m             : longint;
   upit             : array[0..MAXT] of boolean;
   dodaj            : array[0..MAXT] of int64;
   koliko2, koliko4 : array[0..MAXT] of longint;
   x1, y1, x2, y2   : longint;

function min(a, b : int64) : int64; begin if a < b then min := a else min := b; end;
function max(a, b : int64) : int64; begin if a > b then max := a else max := b; end;
function abs(a : int64) : int64; begin if a > 0 then abs := a else abs := -a; end;

function presjek_kvadrata_s_pravokutnikom(t : longint) : int64;
var x, y : int64;
begin
   x := min(t, x2) - max(-t, x1) + 1;
   y := min(t, y2) - max(-t, y1) + 1;
   presjek_kvadrata_s_pravokutnikom := max(x, 0) * max(y, 0);
end;

procedure obradi(t1, t2 : longint);
var p0, p1, p2 : int64;
begin
   p0 := presjek_kvadrata_s_pravokutnikom(t1-1);
   p1 := presjek_kvadrata_s_pravokutnikom(t1);
   p2 := presjek_kvadrata_s_pravokutnikom(t1+1);
   dodaj[t1] := dodaj[t1] + (p1-p0);
   dodaj[t2] := dodaj[t2] - (p1-p0);
   if t2-t1 > 1 then begin
      dodaj[t2] := dodaj[t2] - (p2-2*p1+p0)*(t2-t1);
      if p2-2*p1+p0 = 2 then begin
         inc(koliko2[t1]);
         dec(koliko2[t2]);
      end else if p2-2*p1+p0 = 4 then begin
         inc(koliko4[t1]);
         dec(koliko4[t2]);
      end;
   end;
end;

var
   pp, i, j, d, tail, v, t : longint;
   tren                    : array[0..11] of longint;
   ret, add, k2, k4        : int64;

begin
   read(n);
   for pp:=0 to n-1 do begin
      read(x1, y1, x2, y2);

      tail := 0;
      for d:=-1 to 1 do begin
         tren[tail] := abs(x1+d); inc(tail);
         tren[tail] := abs(y1+d); inc(tail);
         tren[tail] := abs(x2+d); inc(tail);
         tren[tail] := abs(y2+d); inc(tail);
      end;

      (* insertion sort *)
      for i:=1 to tail-1 do begin
         v := tren[i];
         j := i;
         while j>0 do begin
            if tren[j-1] <= v then break;
            tren[j] := tren[j-1];
            dec(j);
         end;
         tren[j] := v;
      end;

      for i:=1 to tail-1 do obradi(tren[i-1], tren[i]);
   end;

   read(m);
   for i:=0 to m do begin
      read(t);
      upit[t] := true;
   end;

   ret := 0; add := 0; k2 := 0; k4 := 0;
   for t:=1 to MAXT do begin
      add := add+dodaj[t];
      ret := ret+add;

      k2 := k2 + koliko2[t];
      k4 := k4 + koliko4[t];
      add += 2*k2 + 4*k4;
      if upit[t] then writeln(ret);
   end;
end.

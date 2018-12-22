program trezor;

const MAX = 4000;

function gcd(a, b : longint) : longint;
begin if b = 0 then gcd := a else gcd := gcd(b, a mod b); end;

type vector = object
   n   : longint;
   arr : array[0..50] of longint;

   procedure init;
   procedure push_back(x : longint);
   procedure sortuniq;
end;

procedure vector.init;
begin
   n := 0;
end;

procedure vector.push_back(x : longint);
begin
   arr[n] := x;
   inc(n);
end;

procedure vector.sortuniq;
var i, j, t, last, deleted : longint;
begin
   if n = 0 then exit;

   for i:=0 to n-1 do
      for j:=i+1 to n-1 do
         if arr[i] > arr[j] then begin
            t := arr[i]; arr[i] := arr[j]; arr[j] := t;
         end;

   last := arr[0];
   deleted := 0;
   for i:=1 to n-1 do begin
      if arr[i] = last then
         inc(deleted)
      else begin
         arr[i-deleted] := arr[i];
         last := arr[i];
      end;
   end;
   n := n-deleted;
end;

var A, B, L : longint;

function umnozak(a, b : vector) : vector;
var
   ret  : vector;
   i, j : longint;
begin
   ret.init;
   for i:=0 to a.n-1 do begin
      for j:=0 to b.n-1 do
         if a.arr[i] = b.arr[j] then
            ret.push_back(a.arr[i])
         else
            ret.push_back(a.arr[i] * b.arr[j]);
   end;

   ret.sortuniq;
   umnozak := ret;
end;

function ne_vidi(a : vector) : int64;
var
   mask, x, bits, i : longint;
   ret              : int64;
begin
   ret := 0;
   for mask:=1 to (1 shl a.n)-1 do begin
      x := 1;
      bits := 0;
      for i:=0 to a.n-1 do begin
         if (mask shr i) and 1 <> 0 then begin
            x := x div gcd(x, a.arr[i]) * a.arr[i];
            inc(bits);
         end;
      end;

      if (bits mod 2) = 1 then
         ret := ret + L div x
      else
         ret := ret - L div x;
   end;
   ne_vidi := ret;
end;

procedure dump(v : vector);
var i : longint;
begin
   for i:=0 to v.n-1 do write(v.arr[i], ' ');
   writeln;
end;

var
   i, d, x, dx, koliko        : longint;
   rastav                     : array[0..MAX] of vector;
   nevidi1, nevidi2, nevidi12 : int64;
   vidi                       : array[0..2] of int64 = (0, 0, 0);

begin
   read(A, B, L);
   for i:=1 to MAX do begin
      x := i;
      d := 2;
      while d*d <= x do begin
         if x mod d = 0 then begin
            while x mod d = 0 do x := x div d;
            rastav[i].push_back(d);
         end;
         inc(d);
      end;
      if x > 1 then rastav[i].push_back(x);
   end;

   for dx:=0 to (A+B) div 2 do begin
      if dx = 0 then begin
         nevidi1 := L-1;
         nevidi2 := ne_vidi(rastav[A+B-dx]);
         nevidi12 := nevidi2;
      end else begin
         nevidi1 := ne_vidi(rastav[dx]);
         nevidi2 := ne_vidi(rastav[A+B-dx]);
         nevidi12 := ne_vidi(umnozak(rastav[dx], rastav[A+B-dx]));
      end;

      koliko := 1;
      if 2*dx <> A+B then inc(koliko);

      vidi[0] := vidi[0] + koliko*nevidi12;
      vidi[1] := vidi[1] + koliko*(nevidi1 + nevidi2 - 2*nevidi12);
      vidi[2] := vidi[2] + koliko*(L - nevidi1 - nevidi2 + nevidi12);
   end;

   for i:=0 to 2 do writeln(vidi[i]);
end.

program slikar;

const inf = 1000000000;

type data = record
               all0, all1, rec : longint;
            end;

var
   n, i, j : longint;
   a, b    : array[0..512, 0..512] of char;

function next_permutation(var a : array of longint) : boolean;
var n, i, j, k, t : longint;
begin
   next_permutation := false;
   n := length(a);
   
   for i:=n-2 downto 0 do
      if a[i] < a[i+1] then begin
         k := i+1;
         for j:=i+2 to n-1 do 
            if (a[j] > a[i]) and (a[j] < a[k]) then
               k := j;
         t := a[i]; a[i] := a[k]; a[k] := t;

         for j:=i+1 to n-1 do begin
            k := n-j+i;
            if j > k then break;
            t := a[j]; a[j] := a[k]; a[k] := t;
         end;
         next_permutation := true;
         break;
      end;
end;

function rec(r_lo, c_lo, r_hi, c_hi : longint) : data;
var
   ret                                 : data;
   kvadrati                            : array[0..1, 0..1] of data;
   size, r_mid, c_mid, i, j, val, r, c : longint;
   best, kvads                         : array[0..3] of longint;
begin
   if r_lo+1 = r_hi then begin
      if a[r_lo, c_lo] = '1' then begin
         ret.all0 := 1;
         ret.all1 := 0;
      end else begin
         ret.all0 := 0;
         ret.all1 := 1;
      end;
      ret.rec := 0;
      b[r_lo, c_lo] := a[r_lo, c_lo];
   end else begin
      size := (r_hi - r_lo) div 2;
      r_mid := r_lo + size;
      c_mid := c_lo + size;

      kvadrati[0, 0] := rec(r_lo, c_lo, r_mid, c_mid);
      kvadrati[1, 0] := rec(r_mid, c_lo, r_hi, c_mid);
      kvadrati[0, 1] := rec(r_lo, c_mid, r_mid, c_hi);
      kvadrati[1, 1] := rec(r_mid, c_mid, r_hi, c_hi);

      ret.all0 := 0;
      ret.all1 := 0;
      for i:=0 to 1 do
         for j:=0 to 1 do begin
            ret.all0 := ret.all0 + kvadrati[i, j].all0;
            ret.all1 := ret.all1 + kvadrati[i, j].all1;
         end;

      ret.rec := inf;
      kvads[0] := 0; kvads[1] := 1; kvads[2] := 2; kvads[3] := 3;
      repeat
         val := 
            kvadrati[kvads[0] div 2, kvads[0] mod 2].all0 + 
            kvadrati[kvads[1] div 2, kvads[1] mod 2].all1 + 
            kvadrati[kvads[2] div 2, kvads[2] mod 2].rec + 
            kvadrati[kvads[3] div 2, kvads[3] mod 2].rec;

         if val < ret.rec then begin
            ret.rec := val;
            for i:=0 to 3 do best[i] := kvads[i];
         end;
      until not next_permutation(kvads);

      for r:=0 to size-1 do 
         for c:=0 to size-1 do begin
            b[r_lo + (best[0] div 2)*size + r, c_lo + (best[0] mod 2)*size + c] := '0';
            b[r_lo + (best[1] div 2)*size + r, c_lo + (best[1] mod 2)*size + c] := '1';
         end;
   end;
   rec := ret;
end;

begin
   readln(n);
   for i:=0 to n-1 do begin
      for j:=0 to n-1 do
         read(a[i, j]);
      readln;
   end;

   writeln(rec(0, 0, n, n).rec);
   for i:=0 to n-1 do begin
      for j:=0 to n-1 do
         write(b[i, j]);
      writeln;
   end;
end.

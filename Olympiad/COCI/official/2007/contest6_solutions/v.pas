
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task V.PAS
  Programming language Pascal
*)

program v;

const GRANICA = 100000;

var
   A, B, X : int64;
   ok      : array[0..9] of boolean;
   memo    : array[0..11, 0..GRANICA-1, 0..1] of int64;

procedure ucitaj;
var
   i : longint;
   s : string;
begin
   readln(X, A, B);
   readln(s);

   for i:=0 to 9 do
      ok[i] := false;
   for i:=1 to length(s) do
      ok[ord(s[i])-ord('0')] := true;
end;

function jednostavno: int64;
var
   y, z : int64;
   cool : boolean;
   ret  : int64;
begin
   z := X;
   ret := 0;
   while z <= B do begin
      cool := true;
      y := z;
      while cool and (y > 0) do begin
         cool := cool and ok[y mod 10];
         y := y div 10;
      end;
      if cool and (z >= A) then
         ret := ret + 1;
      z := z + X;
   end;
   jednostavno := ret;
end;

function rek(n : longint; prefix: int64): int64;
var
   i, dig          : longint;
   mini, maxi, ret : int64;
   memoize         : boolean;
begin
   maxi := prefix; mini := prefix;
   for i:=1 to n do begin
      maxi := 10*maxi + 9;
      mini := 10*mini + 0;
   end;

   if (maxi < A) or (mini > B) then begin
      rek := 0;
      exit;
   end;
   if n = 0 then begin
      rek := ord(prefix mod X = 0);
      exit;
   end;

   memoize := (mini >= A) and (maxi <= B);
   if memoize and (memo[n, prefix mod X, ord(prefix=0)] >= 0) then begin
      rek := memo[n, prefix mod X, ord(prefix=0)];
      exit;
   end;

   ret := 0;
   for dig:=0 to 9 do
      if ok[dig] or ((dig=0) and (prefix=0)) then
         ret := ret + rek(n-1, prefix*10+dig);

   if memoize then
      memo[n, prefix mod X, ord(prefix=0)] := ret;
   rek := ret;
end;

function dinamika: int64;
var i, j, k : longint;
begin
   for i:=0 to 11 do
      for j:=0 to GRANICA-1 do
         for k:=0 to 1 do
            memo[i, j, k] := -1;
   dinamika := rek(11, 0);
end;

begin
   ucitaj;
   if X >= GRANICA then
      writeln(jednostavno)
   else
      writeln(dinamika);
end.

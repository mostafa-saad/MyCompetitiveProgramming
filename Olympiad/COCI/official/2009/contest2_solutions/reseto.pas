program reseto;

const MAXN = 1000;

var 
   n, k : longint;
   sito : array[2..MAXN] of boolean;

function solve : longint;
var
   i, j : longint;
begin
   for i := 2 to n do begin
      if sito[i] then continue;
      j := i;
      repeat
         if not sito[j] then begin         
            k := k - 1;
            if k = 0 then solve := j;            
            sito[j] := true;
         end;
         j := j + i;
      until j > n;
   end;
end;

begin
   readln( n, k );
   writeln( solve() );   
end.

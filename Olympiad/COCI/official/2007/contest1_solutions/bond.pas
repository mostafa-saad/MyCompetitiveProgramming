
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task BOND
  Programming language Pascal
*)

program bond;

var
   n            : integer;
   i, j, x      : integer;
   vjer         : array[0..20, 0..20] of double;
   vec_rijeseno : array[0..1 shl 21] of boolean;
   memo         : array[0..1 shl 21] of double;

function rijesi(d, s: integer): double;
var
   i        : integer;
   ret, tmp : double;
begin
   if d = n then begin
      rijesi := 1.0;
      exit;
   end;

   if vec_rijeseno[s] then begin
      rijesi := memo[s];
      exit;
   end;

   vec_rijeseno[s] := true;
   ret := 0.0;

   for i:=0 to n-1 do
      if (s and (1 shl i)) = 0 then begin
         tmp := vjer[d, i] * rijesi(d+1, s or (1 shl i));
         if tmp > ret then
            ret := tmp;
      end;

   memo[s] := ret;
   rijesi := ret;
end;

begin
   read(n);
   for i:=0 to n-1 do
      for j:=0 to n-1 do begin
         read(x);
         vjer[i, j] := x / 100;
      end;

   writeln( (rijesi(0, 0)*100):0:6 );
end.

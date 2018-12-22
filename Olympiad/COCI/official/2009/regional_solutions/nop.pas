program nop;

uses strings;

var
   prog : string;
   n, br_nop, i : longint;
begin
   readln( prog );
   n := length( prog );

   br_nop := 0;
   for i := 1 to n do begin
      if (prog[i] >= 'a') and (prog[i] <= 'z') then continue;
      
      while (i-1+br_nop) mod 4 <> 0 do br_nop := br_nop + 1;
   end;

   writeln( br_nop );
end.
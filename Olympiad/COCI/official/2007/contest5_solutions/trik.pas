
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task TRIK
  Programming language Pascal
*)

program trik;

var
   s       : string;
   gdje, i : integer;

begin
   readln(s);

   gdje := 1;
   for i:=1 to length(s) do begin
      if (s[i]='A') and (gdje <> 3) then gdje := 3-gdje;
      if (s[i]='B') and (gdje <> 1) then gdje := 5-gdje;
      if (s[i]='C') and (gdje <> 2) then gdje := 4-gdje;
   end;

   writeln(gdje);
end.

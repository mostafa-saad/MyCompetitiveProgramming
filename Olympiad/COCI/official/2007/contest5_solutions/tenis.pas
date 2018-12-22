
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task TENIS
  Programming language Pascal
*)

program tenis;

function provjeri_jedan_set(g1, g2, koji_set : integer;
                            ime1, ime2       : string;
                            var pob          : array of integer):boolean;
var
   t : integer;
   p : string;
begin
   if g1 = g2 then begin
      provjeri_jedan_set := false;
      exit;
   end;

   if g1 < g2 then begin
      t := g1; g1 := g2; g2 := t;
      p := ime1; ime1 := ime2; ime2 := p;
      pob[1] := pob[1] + 1;
   end else
      pob[0] := pob[0] + 1;

   if ime2 = 'federer' then
      provjeri_jedan_set := false
   else if g1 < 6 then
      provjeri_jedan_set := false
   else if g1 = 6 then
      provjeri_jedan_set := (g2 <= 4)
   else if (g1 = 7) and (koji_set < 3) then
      provjeri_jedan_set := (g2 = 5) or (g2 = 6)
   else if (g1 >= 7) and (koji_set = 3) then
      provjeri_jedan_set := (g1 = g2+2)
   else
      provjeri_jedan_set := false;
end;

var
   red, ime1, ime2         : string;
   n, i, poc, mec          : integer;
   koji_set, g1, g2, smece : integer;
   ok                      : boolean;
   pob                     : array[1..2] of integer;

begin
   readln(red);
   i := pos(' ', red);
   ime1 := copy(red, 1, i-1);
   ime2 := copy(red, i+1, length(red)-i);
   readln(n);
   for mec:=1 to n do begin
      readln(red);
      red := red + ' ';

      pob[1] := 0;
      pob[2] := 0;
      koji_set := 1;
      poc := 1;
      ok := true;

      for i:=1 to length(red) do begin
         if red[i]=':' then begin
            val(copy(red, poc, i-poc), g1, smece);
            poc := i+1;
         end else if red[i]=' ' then begin
            val(copy(red, poc, i-poc), g2, smece);
            poc := i+1;
            ok := ok and (pob[1] < 2) and (pob[2] < 2);
            ok := ok and provjeri_jedan_set(g1, g2, koji_set, ime1, ime2, pob);
            koji_set := koji_set + 1;
         end;
      end;

      ok := ok and ((pob[1] = 2) or (pob[2] = 2));
      if ok then
         writeln('da')
      else
         writeln('ne');
   end;
end.

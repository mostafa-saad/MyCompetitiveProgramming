
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 5 - Task LIGA
  Programming language Pascal
*)

program liga;

var
   n, i                       : integer;
   a, b, c, d, e              : integer;
   b1, b2, c1, c2, ta, td, te : integer;

procedure ucitaj1(var a, b, c, d, e : integer);
var
   izlaz               : array[1..5] of integer;
   red, token          : string;
   i, koji, poc, smece : integer;
begin
   readln(red);
   red := red + ' ';
   koji := 1;
   poc := 1;
   for i:=1 to length(red) do begin
      if red[i]=' ' then begin
         token := copy(red, poc, i-poc);
         poc := i+1;
         if token = '?' then
            izlaz[koji] := -1
         else
            val(token, izlaz[koji], smece);
         koji := koji+1;
      end;
   end;
   a := izlaz[1];
   b := izlaz[2];
   c := izlaz[3];
   d := izlaz[4];
   e := izlaz[5];
end;

begin
   readln(n);
   for i:=1 to n do begin
      ucitaj1(a, b, c, d, e);

      if b <> -1 then begin
         b1 := b;
         b2 := b;
      end else begin
         b1 := 0;
         b2 := 100;
      end;

      if c <> -1 then begin
         c1 := c;
         c2 := c;
      end else begin
         c1 := 0;
         c2 := 100;
      end;

      if (a = -1) and (d = -1) then
         d := 0;

      for b:=b1 to b2 do
         for c:=c1 to c2 do begin
            ta := a; td := d; te := e;

            if a = -1 then
               ta := b+c+d
            else if d = -1 then
               td := a-b-c;

            if e = -1 then
               te := 3*b+c;

            if (ta = b+c+td) and
               (ta >= 0) and (ta <= 100) and
               (td >= 0) and (td <= 100) and
               (te=3*b+c) then
               writeln(ta, ' ', b, ' ', c, ' ', td, ' ', te);
         end;
   end;
end.

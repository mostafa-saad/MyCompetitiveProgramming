
(*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak KOLONE
  Programski jezik Pascal

  Zadatak se moze rijesiti tako da sekundu po sekundu simuliramo
  preskakanja. Donja implementacija pokazuje takvo rjesenje.

  Efikasniji pristup je za svakog mrava izravno izracunati na kojem ce
  se mjestu nalaziti (za implementaciju vidi rjesenje u jeziku C++).
*)

program kolone;

var
   n1, n2, i, T, sad : integer;
   str, stanje, novo : string;
   prva, druga       : set of char;
   tmpc              : char;

begin
   readln(n1, n2);
   readln(str);
   for i:=1 to n1 do begin
      prva := prva + [ str[i] ];
      stanje := str[i] + stanje;
   end;
   readln(str);
   for i:=1 to n2 do begin
      druga := druga + [ str[i] ];
      stanje := stanje + str[i];
   end;

   readln(T);
   if T > n1+n2 then T := n1+n2;

   for sad:=1 to T do begin
      novo := stanje;

      for i:=1 to n1+n2-1 do begin
         if ( stanje[i] in prva ) and ( stanje[i+1] in druga ) then begin
            (* Skok! *)
            tmpc := novo[i];
            novo[i] := novo[i+1];
            novo[i+1] := tmpc;
         end;
      end;

      stanje := novo;
   end;

   writeln(stanje);
end.

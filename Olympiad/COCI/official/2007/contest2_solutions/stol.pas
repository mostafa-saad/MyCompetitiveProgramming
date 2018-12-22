
(*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak STOL
  Programski jezik Pascal

  Pretpostavimo jednu dimenziju stola. Konkretno, pretpostavimo da se
  stol proteze od stupca s1 do stupca s2. Da bi se stol mogao nalaziti
  u nekom retku, moraju sva polja tog retka izmedu stupaca s1 i s2
  biti prazna.

  Za svaki red moguce je utvrditi postoji li neki zid izmedu stupaca
  s1 i s2 u konstantnom vremenu: na pocetku za svaki stupac nekog reda
  izracunamo koliko se zidova nalazi lijevo od njega i to sapisemo u
  matricu suma[red][stupac]. Nakon sto smo to izracunali, izraz
  suma[red][s2] - suma[red][s1-1] ce nam reci koliko je zidova izmedu
  stupaca s1 i s2 (ako je on nula, stol se moze nalaziti u promatranom
  retku).

  Jednostavnim algoritmom nademo najveci uzastopni niz redova koji
  nemaju zidova izmedu s1 i s2 i time smo dobili maksimalno rjesenje
  za pocetnu pretpostavku. Isprobamo sve pretpostavke i izaberemo onu
  koja nam daje maksimalno rjesenje.

  Broj pretpostavki proporcionalan je s N^2. Koristenjem strukture
  podataka koja u konstantnom vremenu odgovara na pitanje nalazi li se
  neki zid u nekom retku izmedu dvaju stupaca provjeru radimo u
  linearnom vremenu, sto daje ukupno N^3.
*)

program stol;

var
   r, s, i, j, s1, s2    : integer;
   rez, sad, najdulje, x : integer;
   ploca                 : array[1..400, 1..400] of char;
   sum                   : array[1..400, 0..400] of integer;

begin
   readln(r, s);

   for i:=1 to r do begin
      for j:=1 to s do
         read(ploca[i, j]);
      readln;
   end;

   for i:=1 to r do begin
      sum[i, 0] := 0;
      for j:=1 to s do begin
         sum[i, j] := sum[i, j-1];
         if ploca[i, j] = 'X' then
            sum[i, j] := sum[i, j] + 1;
      end;
   end;

   rez := 0;
   for s1:=1 to s do begin
      for s2:=s1 to s do begin
         sad := 0; najdulje := 0;

         for i:=1 to r do begin
            if sum[i, s2] - sum[i, s1-1] = 0 then begin
               sad := sad+1;
               if sad > najdulje then
                  najdulje := sad;
            end
            else
               sad := 0;
         end;

         if najdulje > 0 then begin
            x := 2*najdulje + 2*(s2-s1+1);
            if x > rez then
               rez := x;
         end;
      end;
   end;

   writeln(rez-1);
end.

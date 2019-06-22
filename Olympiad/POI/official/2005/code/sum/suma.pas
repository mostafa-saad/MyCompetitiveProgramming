(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                suma.cpp                                       *
 *   Autor:               Marcin Kubica                                  *
 *   Opis:                Rozwiazanie autorskie                          *
 *                        Jêzyk: Pascal                                  *
 *                                                                       *
 *************************************************************************)

(* Liczby s? reprezentowane jako ci?g cyfr okre?lonej d?ugo?ci,       *)
(* w kolejno?ci od mniej do bardziej znacz?cych.                      *)
(* Dane s? znormalizowane, tzn. zawieraj? tylko cyfry 0 i 1,          *)
(* przy czym 1-ki nie s?siaduj? ze sob?.                              *)
(* W procedurach pomocniczych dane nie musz? by? znormalizowane, tzn. *)
(* mog? pojawia? si? 2-ki, a 1-ki mog? s?siadowa? ze sob? -- jest to  *)
(* wówczas zaznaczone w komentarzach.                                 *)
const
   MaxCyfr   =  1000005;
   
type liczba = record
                 n : 0..MaxCyfr;
                 c : array [1..Maxcyfr] of 0..2
              end; 


(* Wczytywanie danych *)
procedure read_liczba (var l : liczba);
var
   i : longint;
begin
   read (l.n);
   for i := 1 to l.n do read (l.c[i]);
   readln
end; { read_liczba }

    
(* Wypisywanie wynikow *)
procedure write_liczba (var l : liczba);
var
   i : longint;
begin
   write (l.n);
   for i := 1 to l.n do write (' ', l.c[i]);
   writeln
end; { write_liczba }


(* Zwykle sumowanie kolejnych cyfr na kolejnych pozycjach.            *) 
(* Dane znormalizowane, wynik nie, ale w wyniku 2-ki mog? s?siadowa?  *)
(* tylko z 0-mi.                                                      *)
procedure sumuj (var l1, l2, wynik : liczba);
var
   i :  longint;
begin
   i := 1;
   while (i <= l1.n) and (i <= l2.n) do begin
      wynik.c[i] := l1.c[i] + l2.c[i];
      inc(i)
   end;
   while (i <= l1.n) do begin
      wynik.c[i] := l1.c[i];
      inc(i)
   end;
   while (i <= l2.n) do begin
      wynik.c[i] := l2.c[i];
      inc(i)
   end;
   wynik.n := i-1
end; { sumuj }


(* Usuwa wiod?ce zera z danej liczby. *)
procedure usun_wiodace_zera (var l : liczba);
begin
   while (l.c[l.n] = 0) and (l.n > 0) do dec (l.n)
end; { usun_wiodace_zera }

(* Dodaje k wiod?cych zer w danej liczbie. *)
procedure dodaj_wiodace_zera (var l : liczba; k : longint);
begin
   while k > 0 do begin
      inc(l.n);
      l.c[l.n] := 0;
      dec(k);
   end
end; { dodaj_wiodace_zera }


(* Usuwanie s?siaduj?cych 1-ek. 2-ki mog? s?siadowa? tylko z 0-mi.    *)
(* W wyniku cyfry > 0 mog? s?siadowa? tylko z 0-mi.                   *)
(* Je?li w danych by?y 2-ki, to w wyniku te? mog? by?.                *)
procedure normalizuj (var l : liczba);
var
   i, c :  longint;
begin
   (* Dodaj wiod?ce zera, tak aby wynik si? zmie?ci?. *)
   dodaj_wiodace_zera (l, 3);

   i := 0; (* Liczba cyfr przejrzanych. *)
   c := 0; (* Dlugosc ciagu 1-ek ostatnio przejrzanych. *)

   (* Przegl?danie liczby -- od cyfr mniej do bardziej znacz?cych. *)
   while i < l.n do begin
      case l.c[i+1] of
        0 : begin
               if c = 0 then begin              (*     0    ->    0     *)
               end else if c = 1 then begin     (*    010   ->   010    *)
                  c := 0
               end else begin                   (* 01^(2k)0 -> (10)^k00 *)
                  c := c - (c mod 2);           (* 01^(2k)1 -> (10)^k01 *)
                  l.c[i-c+1] := 0;
                  while c > 0 do begin
                     l.c[i-c+2] := 0;
                     c := c - 2
                  end;
                  l.c[i+1] := 1;
                  c := 1
               end;
               inc(i)
            end;
        1 : begin
               inc (c);
               inc (i)
            end;
        2 : begin
               if c = 0 then begin                (*  020 -> 020  *)
               end else begin                     (* 0210 -> 1100 *)
                  { c = 1,2 }                     (* 0211 -> 1101 *)
                  l.c[i]   := 0;
                  l.c[i+1] := 1;
                  l.c[i+2] := 1;
                  c := 2;
               end;
               i := i + 2
            end
      end
   end;

   (* Usu? wiod?ce zera *)
   usun_wiodace_zera (l)
end; { normalizuj }


(* Eliminacja dwójek ze znormalizowanej liczby. *)
(* Dane znormalizowane, ale mog? zawiera? 2-ki. *)
procedure eliminuj (var l : liczba);
var
   i :  longint;
begin
   (* Eliminacja sekwencji 2010 i 200.                *)
   (* Przed ka?d? 2-k? mo?e pojawci si? ci?g jedynek, *)
   (* ale zawsze przed 2-k? s? cyfry: 0 lub 01*11.    *)


   { Najbardziej znaczaca cyfra moze byc 2-k?. }
   dodaj_wiodace_zera (l, 1);

   { Usu? sekwencje 2010 i 200, przegl?daj?c cyfry od bardziej znacz?cych. }
   i := l.n;
   while i > 2 do begin
      if (l.c[i]=2) and (l.c[i-1]=0) and (l.c[i-2]<=1) then begin
         (* 201 -> 112 *)
         (* 200 -> 111 *)
         l.c[i]   := 1;
         l.c[i-1] := 1;
         inc(l.c[i-2]);
         i := i - 2
      end else dec (i)
   end;
   (* Trzy najmniej znacz?ce cyfry s? ró?ne od 201. *)
   
   (* Je?li dwie najmniej znacz?ce cyfry to 20, to zamie? je na 12. *)
   if (l.n >= 2) and (l.c[2]=2) and (l.c[1]=0) then begin
      l.c[2] := 1;
      l.c[1] := 2
   end;

   (* Je?li najmniej znacz?ca cyfra to 2, to usu? j?.   *)
   (* Musi by? to sekwencja postaci: 01^i2.             *)
   (* 01^(2k)2 -> (10)^(k+1), 01^(2k+1)2 -> (10)^(k+1)1 *)
   (* Skoro przed t? operacj? nie by?o sekwencji 200,   *)
   (* to po jej wykonaniu nie pojawi si? 2010.          *)
   if (l.n > 0) and (l.c[1]=2) then begin
      i := 2;
      while l.c[i]=1 do inc (i);
      while i > 1 do begin
         l.c[i]   := 1;
         l.c[i-1] := 0;
         i := i - 2
      end;
      if i = 1 then l.c[1] := 1;
   end;

   (* W tym momencie liczba nie zawiera sekwencji 200, 2010,  *)
   (* ani najmniej znacz?ce cyfry to nie s? 201, 20, ani 2.   *)
   (* Ka?da 2-ka jest poprzedzona sekwencja 01*.              *)
   (* Po ka?dej 2-ce mo?e by? 02, 011 lub 10.                 *)


   (* Eliminacja pozosta?ych 2-ek, tym razem od mniej   *)
   (* znacz?cych, do bardziej znacz?cych.               *)
   i := 1;
   while i <= l.n do begin
      if l.c[i] = 2 then begin
         if (i > 3) and (l.c[i-1]=0) and
            (l.c[i-2]=1) and (l.c[i-3]=1) then begin
               (* 2011 -> 2100 *)
               l.c[i-1] := 1;
               l.c[i-2] := 0;
               l.c[i-3] := 0
            end
         else if l.c[i-1]=1 then begin
            (* 021 -> 110 *)
            (* 121 -> 210 *)
            l.c[i-1] := 0;
            l.c[i] := 1;
            inc(l.c[i+1]);
            inc (i)
         end else halt (1) { Ten przypadek nie zachodzi }
      end else inc (i)
   end;

   
   (* Normalizacja i usuni?cie wiod?cych zer. *)
   normalizuj (l);
   
end; { eliminuj }


(* Dodawanie *)
procedure suma (var x, y, wynik        : liczba);
begin
   sumuj (x, y, wynik);
   normalizuj (wynik);
   eliminuj (wynik)
end; { suma }


(* Program glowny *)
var
   k, l, w : liczba;
begin
   read_liczba (k);
   read_liczba (l);
   suma (k, l, w);
   write_liczba (w)
end.

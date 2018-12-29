(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sum1.cpp                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Jêzyk: Pascal                                  *
 *                                                                       *
 *************************************************************************)

Program Sum_1;
var
 liczba1, liczba2, wynik : array[0..1000100] of Byte;
 n, m, dlugosc_wyniku : LongInt; {n-d³ugo¶æ liczby1, m-d³ugo¶æ liczby2}

function max(x, y : LongInt) : LongInt;
begin
 if x > y then
  max := x
 else
  max := y
end; {max}


procedure wczytaj;
var i : LongInt;
begin
 Read(n);
 for i := 0 to n - 1 do
  Read(liczba1[i]);
 Read(m);
 for i := 0 to m - 1 do
  Read(liczba2[i])
end; {wczytaj}

procedure dodaj;
var i : LongInt;
begin
 dlugosc_wyniku := max(n,m) + 10;
 for i := 0 to dlugosc_wyniku do
  wynik[i] := 0;
 for i := 0 to n - 1 do
  wynik[i] := liczba1[i];
 for i := 0 to m - 1 do
  Inc(wynik[i],liczba2[i])
end; {dodaj}


procedure eliminuj_102_002;
var i : LongInt;
begin
 {chcemy wyeliminowac sekwencje 102 i 002
 ciag na wejsciu jest znormalizowany
 i kazda 2 jest "otoczona" zerami}
 for i := dlugosc_wyniku downto 2 do
 begin
  if wynik[i] = 2 then
  begin
   if (wynik[i - 1] = 0) and (wynik[i - 2] = 1) then
   begin
    {102 -> 211}
    wynik[i - 2] := 2;
    wynik[i - 1] := 1;
    wynik[i] := 1;
    continue;
   end; {if}
   
   if (wynik[i - 1] = 0) and (wynik[i - 2] = 0) then
   begin
    {002 -> 111}
    wynik[i - 2] := 1;
    wynik[i - 1] := 1;
    wynik[i] := 1
   end {if}
  end {if}
 end; {for}
 
 if (wynik[1] = 2) and (wynik[0] = 0) then
 begin
  wynik[1] := 1;
  wynik[0] := 2
 end {if}
 {teraz po ka¿dej dwójce jest pewna (niezerowa) liczba jedynek}
end; {eliminuj_102_002}

procedure eliminuj_przod;
var i, j, ile_jedynek : LongInt;
begin
 {usuwanie 2 z poczatku wyniku}
 if (wynik[0] = 2) and (wynik[1] = 0) then
 begin
  wynik[0] := 0;
  wynik[1] := 1;
 end; {if}
 i := 0;
 
 if wynik[i] = 2 then
 begin
  ile_jedynek := 0;
  while wynik[i + ile_jedynek + 1] = 1 do
   Inc(ile_jedynek);
  if (ile_jedynek <> 0) and (ile_jedynek mod 2 = 0) then
  begin
   {21^(2k)0 -> (01)^(k+1)}
   for j := 0 to ile_jedynek + 1 do
   begin
    if j mod 2 = 0 then
     wynik[i + j] := 0
    else
     wynik[i + j] := 1
   end; {for}
   Inc(i,ile_jedynek + 1)
  end; {if}
  
  if ile_jedynek mod 2 = 1 then
  begin
   {21^(2k+1)0 -> 1(01)^(k+1)}
   for j := 0 to ile_jedynek + 1 do
   begin
    if j mod 2 = 0 then
     wynik[i + j] := 1
    else
     wynik[i + j] := 0
   end; {for}
   Inc(i,ile_jedynek + 1)
  end {if}
 end {if}
 {poniewaz w danych nie bylo 002 to w wyniku nie bedzie 102}
end; {eliminuj_przod}

procedure eliminuj_reszte;
var i : LongInt;
begin
 {koñcowa eliminacja pozosta³ych dwójek z wyniku}
 for i := 2 to dlugosc_wyniku do
 begin
  if wynik[i] = 2 then
  begin
   {1102  -> 0012}
   if (wynik[i - 1] = 0) and (wynik[i - 2] = 1) and (wynik[i - 3] = 1) then
   begin
    wynik[i - 3] := 0;
    wynik[i - 2] := 0;
    wynik[i - 1] := 1;
    wynik[i] := 2;
    continue
   end {if}
  end; {if}
  
  if wynik[i - 1] = 2 then
  begin
  
   if wynik[i] = 0 then
   begin
    {120 -> 011}
    wynik[i - 2] := 0;
    wynik[i - 1] := 1;
    wynik[i] := 1;
    continue
   end; {if}
   
   if wynik[i] = 1 then
   begin
    {121 --> 012}
    wynik[i - 2] := 0;
    wynik[i - 1] := 1;
    wynik[i] := 2;
    continue
   end {if}
   
  end {if}
 end {for}
end; {eliminuj_reszte}

procedure normalizuj;
var i, j, ile_jedynek : LongInt;
begin
 {zajmuje sie usunieciem sasiednich jedynek
 i ³atwych do usuniêcia 2}
 ile_jedynek := 0;
 for i := 0 to dlugosc_wyniku do
 begin

(*****************************************)
  if wynik[i] = 0 then
  begin
   if ile_jedynek = 0 then
   begin
    ile_jedynek := 0;
    continue
    { 0 -> 0}
   end; {if}
   
   if ile_jedynek = 1 then
   begin
    ile_jedynek := 0;
    continue
    { 010 -> 010}
   end; {if}
   
   if ile_jedynek mod 2 = 0 then
   begin
    {01^(2k) -> 00 (01)^k}
    for j := 1 to ile_jedynek do
    begin
     wynik[i - j] := 0;
     if j mod 2 = 0 then
      wynik[i - j] := 1
    end; {for}
    wynik[i - ile_jedynek] := 0;
    wynik[i] := 1;
    ile_jedynek := 1;
    continue
   end; {if}
   
   {01^(2k+1) -> 010(01)^k}
   for j := 1 to ile_jedynek do
   begin
    wynik[i - j] := 0;
    if j mod 2 = 0 then
     wynik[i - j] := 1
   end; {for}
   wynik[i] := 1;
   wynik[i - ile_jedynek] := 1;
   wynik[i - ile_jedynek + 1] := 0;
   ile_jedynek := 1;
   continue
  end; {if}
  
(*****************************************)
  if wynik[i] = 1 then
   Inc(ile_jedynek);
  
(*****************************************)
  if wynik[i] = 2 then
  begin
   {nastepna zawsze jest = 0}
   if ile_jedynek = 0 then
    continue;
    
   if ile_jedynek = 1 then
   begin
    wynik[i - 1] := 0;
    wynik[i] := 1;
    wynik[i + 1] := 1;
    ile_jedynek := 1
    {0120 -> 0011}
   end; {if}
   
   if ile_jedynek = 2 then
   begin
    wynik[i - 1] := 0;
    wynik[i] := 1;
    wynik[i + 1] := 1;
    ile_jedynek := 1
    {01120 -> 01011}
   end {if}
  end {if}
  
 end {for}
end; {normalizuj}

procedure wypisz_wynik;
var i : LongInt;
begin
 while (dlugosc_wyniku>1) and (wynik[dlugosc_wyniku - 1] = 0) do
  Dec(dlugosc_wyniku);
 Write(dlugosc_wyniku);
 for i := 0 to dlugosc_wyniku - 1 do
  Write(' ',wynik[i]);
 Writeln
end; {wypisz_wynik}

begin
 wczytaj;
 dodaj;
 normalizuj;
 eliminuj_102_002;
 eliminuj_przod;
 eliminuj_reszte;
 normalizuj;
 wypisz_wynik
end. {program}

(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LUS (Lustrzana pu³apka)                        *
 *   Plik:                lus1.pas                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Implementacja rozwi±zania wzorcowego w Pascalu *
 *                                                                       *
 *************************************************************************)

program lustrzana_pulapka;

const MAX_ROZM = 1000; { maksymalna d³ugo¶æ boku skrzynki }

var licznik, ilosc : Integer;
rzedy : array[1..MAX_ROZM] of Byte; { tablica warto¶ci ord }
x, y, z : LongInt; { rozmiary skrzynki }
wyn_a, wyn_b, wyn_c : LongInt; { najlepsze skierowanie lasera }
wyn_odl : Int64; { d³ugo¶æ drogi dla najlepszego skierowania lasera }
koniec : Boolean; { koniec=true oznacza, ¿e znale¼li¶my rozwi±zanie }
odl : LongInt; { odleg³o¶æ rozwa¿anych punktów skierowania lasera
               od rogu skrzynki }
max_czas : LongInt; { maksymalny czas lotu promienia, równy 2*NWW(x,y,z) }
droga : Int64; { d³ugo¶æ drogi lasera aktualnie rozwa¿anego skierowania }
a1, b1 : LongInt; { zmienne pomocnicze w pêtlach }


(* POMOCNICZE FUNKCJE ARYTMETYCZNE *)

function min(a, b : LongInt) : LongInt;
begin
  if a < b then
    min := a
  else
    min := b
end; {min}

{ Najwiêkszy wspólny dzielnik }
function NWD(a, b : LongInt) : LongInt;
begin
  if b = 0 then
    NWD := a
  else
    NWD := NWD(b, a mod b)
end; {NWD}

{ Najmniejsza wspólna wielokrotno¶æ }
function NWW(a, b : LongInt) : LongInt;
var d : LongInt;
begin
  d := NWD(a, b);
  if d = 0 then { na pewno co najmniej jedna z liczb jest zerem }
    NWW := 0
  else
    NWW := LongInt((Int64(a) * Int64(b)) div d)
end; {NWW}

{ Funkcja oblicza ord(x). }
function rzad(x : LongInt) : Byte;
var wynik : Byte;
pom : LongInt;
begin
  wynik := 0;
  pom := x;
  while pom mod 2 = 0 do
  begin
    pom := pom div 2;
    Inc(wynik)
  end; {while}
  rzad := wynik
end; {rzad}

(* KONIEC FUNKCJI ARYTMETYCZNYCH *)


{ Funkcja dla danego skierowania lasera oblicza pierwszy czas
powrotu promienia lasera do ¼ród³a. }
function licz_czas(a, b, c : LongInt) : LongInt;
var a1, b1, c1 : LongInt;
begin
  if a = 0 then
    a1 := 1
  else
    a1 := NWW(2 * x, a) div a;
    
  if b = 0 then
    b1 := 1
  else
    b1 := NWW(2 * y, b) div b;
    
  if c = 0 then
    c1 := 1
  else
    c1 := NWW(2 * z, c) div c;
  licz_czas := NWW(NWW(a1, b1), c1)
end; {licz_czas}

{ Funkcja dla danego skierowania lasera oblicza drogê, jak± przebêdzie
promieñ lasera, zanim trafi spowrotem do ¼ród³a. }
function licz_droge(a, b, c : LongInt) : Int64;
begin
  licz_droge := Int64(licz_czas(a, b, c)) * Int64(a + b + c)
end; {licz_droge}


{ Procedura oblicza wszystkie potencjalnie potrzebne rzêdy i je zapamiêtuje
w tablicy rzedy. }
procedure licz_rzedy;
var i : Integer;
begin
  for i := 1 to MAX_ROZM do
    rzedy[i] := rzad(i)
end; {licz_rzedy}


{ Funkcja sprawdza dla danego skierowania lasera, czy laser
uderzy w jak±kolwiek krawêd¼ skrzynki. }
function trafi(a, b, c : LongInt) : Boolean;
begin
  trafi := (rzedy[a] - rzedy[b] = rzedy[x] - rzedy[y]) or
           (rzedy[b] - rzedy[c] = rzedy[y] - rzedy[z]) or
           (rzedy[a] - rzedy[c] = rzedy[x] - rzedy[z])
end; {trafi}



{ Inicjacja zmiennych. }
procedure inicjuj;
begin
  koniec := false;
  max_czas := licz_czas(1, 1, 1);
  wyn_odl := 0
end; {inicjuj}

{ Procedura analizuj±ca dane skierowanie strza³u. }
procedure sprawdz(a, b, c : LongInt);
begin
  if (NWD(NWD(a, b), c) = 1) and { rozwa¿amy tylko trójki "wzglêdnie pierwsze" }
     (not trafi(a, b, c)) then   { strza³ nie trafia w krawêd¼ }
  begin
    droga := licz_droge(a, b, c);
    if droga > wyn_odl then { uzyskali¶my najd³u¿sz± z dotychczasowych drogê }
    begin
      wyn_odl := droga;
      wyn_a := a; wyn_b := b; wyn_c := c
    end; {if}
    if wyn_odl = int64(max_czas) * int64(a + b + c) then
    { uzyskali¶my najd³u¿sz± mo¿liw± drogê }
      koniec := true
  end {if}
end; {sprawdz}


begin
  licz_rzedy;
  ReadLn(ilosc);
  for licznik := 1 to ilosc do
  begin
    ReadLn(x, y, z);
    inicjuj;
    odl := 1;
    { pêtla po kolejnych odleg³o¶ciach od rogu skrzynki }
    while (not koniec) and (odl < x + y + z) do
    begin
      for a1 := 0 to min(odl, x - 1) do
        if not koniec then
          for b1 := 0 to min(odl - a1, y - 1) do
            if (odl - a1 - b1 < z) and (not koniec) then
              sprawdz(x - a1, y - b1, z - (odl - a1 - b1));
      Inc(odl)
    end; {while}
    Writeln(wyn_a, ' ', wyn_b, ' ', wyn_c)
  end {for}
end. {program}

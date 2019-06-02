{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwiazanie zadania: PORÓWNYWANIE NASZYJNIKÓW                       *}
{*   Plik:                NAS.PAS                                        *}
{*   Autor:               PAWE£ WOLFF                                    *}
{*************************************************************************}

{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+}

program PorownywanieNaszyjnikow;

const PLIK_WE = 'NAS.IN';
      PLIK_WY = 'NAS.OUT';

      MAX_WZOROW    = 1000;
      MAX_DL_NAS    = 10000;
      MAX_POWTORZEN = 100000;

type
  { opisuje jeden ze wzorow naszyjnika }
  TOpisWzoru =
    record
      pocz : integer; { oznacza poczatek slowa opisujacego wzor  }
                      { w tablicy nas[i] - patrz nizej           }
      lPowt: longint; { oznacza liczbe powtorzen slowa w obrebie }
                      { danego wzoru                             }
      dl   : integer; { oznacza dlugosc slowa opisujacego wzor   }
    end;

  { okresla pozycje w naszyjniku }
  TPozycja =
    record
      nrObrotuNas: integer; { okresla, ktory raz przegladamy naszyjnik }
      nrWzoru    : integer; { numer przegladanego wzoru                }
      nrPowt     : longint; { numer powtorzenia slowa opisujacego dany }
                            { wzor                                     }
      poz        : integer; { okresla pozycje wewnatrz slowa           }
    end;

  TTabPozycji =
    array [1..2] of TPozycja;

  { typ opisujacy wynik porownania dwoch slow }
  TRezultat =
    (mniejsze, rowne, wieksze);


var
  nas: array [1..2] of array [1..MAX_DL_NAS] of char;
    { nas[i] - tablica slow opisujacych wzory w i-tym naszyjniku }

  lWzorow: array [1..2] of integer;
    { lWzorow[i] - liczba wzorow skladajacych sie na i-ty naszyjnik }

  wzor: array [1..2] of array [1..MAX_WZOROW] of TOpisWzoru;
    { wzor[i][j] - opis j-tego wzoru i-tego naszyjnika }


function PrzesunPozycje(var pozycja: TTabPozycji; n: longint): boolean;
{ przesuwa o n liter obie pozcyje opisane w tablicy pozycja;     }
{ n nie moze byc wieksze niz liczba liter, ktora zostala do      }
{ konca wzoru (w kazdym z dwoch naszyjnikow);                    }
{ zwraca 'true' wtw., gdy w przesuniecie w co najmniej jednym    }
{ z naszyjnikow spowodowalo przejscie na poczatek nowego wzoru;  }
{ uwaga: jesli n = 0, to moze zostac zwrocone 'true' w przypadku }
{ gdy co najmniej jedna pozycja wskazuje na koniec wzoru         }
{ (tzn. TPozycja.poz = TOpisWzoru.dl,                            }
{       TPozycja.nrPowt = TOpisWzoru.lPowt)                      }
var i: integer;
    nowyWzor: boolean;

begin
  nowyWzor := false;

  for i := 1 to 2 do
    with pozycja[i] do
      with wzor[i][nrWzoru] do begin
        Inc(poz, n mod dl);
        if poz >= dl then begin
          Inc(nrPowt);
          Dec(poz, dl)
        end;

        Inc(nrPowt, n div dl);

        if nrPowt > lPowt then begin
          nowyWzor := true;
          Inc(nrWzoru);
          if nrWzoru > lWzorow[i] then begin
            Inc(nrObrotuNas);
            nrWzoru := 1
          end;
          nrPowt := 1
        end
      end;

  PrzesunPozycje := nowyWzor
end;


function PorownajSlowa(var pozycja: TTabPozycji; var k: integer;
                       n: integer): TRezultat;
{ porownuje fragmenty naszyjnikow poczawszy od pozycji zadanych w tablicy }
{ pozycja; porownuje co najwyzej n par liter i nie dalej niz do konca     }
{ powtorzenia wzoru (w kazdym z dwoch naszyjnikow); zwraca rezultat       }
{ porownania (patrz: funkcja Porownaj); przez zmienna k przekazuje liczbe }
{ par porownanych liter                                                   }
var i: integer;
    saRowne: boolean;
    p: array [1..2] of integer;

begin
  for i := 1 to 2 do
    with pozycja[i] do
      with wzor[i][nrWzoru] do begin
        p[i] := pocz + poz;
        if n > dl - poz then
          n := dl - poz
      end;

  saRowne := true;
  k := 0;
  while (k < n) and saRowne do
    if nas[1][p[1] + k] = nas[2][p[2] + k] then
      Inc(k)
    else
      saRowne := false;

  if k = n then
    PorownajSlowa := rowne
  else begin
    if nas[1][p[1] + k] < nas[2][p[2] + k] then
      PorownajSlowa := mniejsze
    else
      PorownajSlowa := wieksze;
    Inc(k)
  end;

  for i := 1 to 2 do
    with pozycja[i] do
      Inc(poz, k)
end;


function Porownaj(var pozycja: TTabPozycji; n: longint): TRezultat;
{ porownuje litery naszyjnikow poczawszy od pozycji zadanych w tablicy }
{ pozycja; porownuje co najwyzej par n liter; jesli kolejnych n par    }
{ liter jest rownych, to zwraca 'rowne'; wpp. zwraca 'mniejsze'        }
{ lub 'wieksze' w zaleznosci od tego, czy dana litera z pierwszego     }
{ naszyjnika jest mniejsza czy wieksza od litery z drugiego naszyjnika }
var i: integer;
    ilePorownac, k: integer;
    ileZostalo, ilePrzesunac: longint;
    rezultat: TRezultat;
    nowyWzor: boolean;

begin
  nowyWzor := true;
  repeat
    if nowyWzor then begin
      ilePorownac := wzor[1][pozycja[1].nrWzoru].dl +
                     wzor[2][pozycja[2].nrWzoru].dl;
      nowyWzor := false
    end;

    if ilePorownac > n then
      ilePorownac := n;

    rezultat := PorownajSlowa(pozycja, k, ilePorownac);

    Dec(n, k);
    Dec(ilePorownac, k);

    nowyWzor := PrzesunPozycje(pozycja, 0);

    if (rezultat = rowne) and not nowyWzor and (ilePorownac = 0) then begin
      { mozemy przesunac obie pozycje w naszyjnikach tak, aby w jednym }
      { z nich pozycja wskazywala na poczatek kolejnego wzoru;         }
      { (w przypadku naszyjnika opisywanego przez jeden wzor bedzie to }
      { przesuniecie na poczatek tego naszyjnika);                     }
      { jednoczesnie przesuwamy o co najwyzej n liter                  }

      ilePrzesunac := n;
      for i := 1 to 2 do begin
        with pozycja[i] do
          with wzor[i][nrWzoru] do
            ileZostalo := (lPowt - nrPowt) * dl + (dl - poz);
        if ilePrzesunac > ileZostalo then
          ilePrzesunac := ileZostalo
      end;

      nowyWzor := PrzesunPozycje(pozycja, ilePrzesunac);

      Dec(n, ilePrzesunac)
    end
  until (rezultat <> rowne) or (n = 0);

  Porownaj := rezultat
end;


function CyklicznieRownowazne(n: longint): boolean;
{ Zwraca 'true' wtw., gdy zadane naszyjniki (slowa dlugosci n) }
{ sa cyklicznie rownowazne                                     }
var i: integer;
    cyklRown: boolean;
    pozycja, staraPozycja: TTabPozycji;

begin
  for i := 1 to 2 do
    { ustawianie pozycja[i] na poczatek i-tego naszyjnika }
    with pozycja[i] do begin
      nrObrotuNas := 1;
      nrWzoru := 1;
      nrPowt := 1;
      poz := 0
    end;

  cyklRown := false;
  while (pozycja[1].nrObrotuNas = 1) and
        (pozycja[2].nrObrotuNas = 1) and not cyklRown do begin

    for i := 1 to 2 do
      staraPozycja[i] := pozycja[i];

    case Porownaj(pozycja, n) of
      rowne    : cyklRown := true;

      mniejsze : begin
                   pozycja[1] := staraPozycja[1];

                   with pozycja[2] do
                     with wzor[2][nrWzoru] do
                       if nrPowt > 1 then begin
                         { przesuwamy pozycja[2] na ostatnie }
                         { powtorzenie aktualnego wzoru      }
                         nrPowt := lPowt;
                         if poz = 0 then begin
                           { ... a nawet na koniec wzoru }
                           poz := dl;
                           PrzesunPozycje(pozycja, 0)
                         end
                       end
                 end;

      wieksze  : begin
                   pozycja[2] := staraPozycja[2];

                   with pozycja[1] do
                     with wzor[1][nrWzoru] do
                       if nrPowt > 1 then begin
                         { przesuwamy pozycja[1] na ostatnie }
                         { powtorzenie aktualnego wzoru      }
                         nrPowt := lPowt;
                         if poz = 0 then begin
                           { ... a nawet na koniec wzoru }
                           poz := dl;
                           PrzesunPozycje(pozycja, 0)
                         end
                       end
                 end;
    end
  end;

  CyklicznieRownowazne := cyklRown
end;


procedure WczytajDane(var d1, d2: longint);
{ wczytuje dwa opisy naszyjnikow obliczajac dlugosc kazdego z nich; }
{ przez zmienne d1, d2 przekazywane sa dlugosci naszyjnikow         }
var p: text;
    i, j, k: integer;
    nastPocz: integer;
    d: array [1..2] of longint; { dlugosci naszyjnikow }
    znak: char;

begin
  Assign(p, PLIK_WE);
  Reset(p);

  for i := 1 to 2 do begin
    d[i] := 0;
    nastPocz := 1;
    Read(p, lWzorow[i]);

    for j := 1 to lWzorow[i] do
      with wzor[i][j] do begin
        Read(p, dl);
        pocz := nastPocz;
        Inc(nastPocz, dl);

        Read(p, znak); { wczytujemy spacje }

        { wcztywanie slowa opisujacego dany wzor }
        for k := 0 to dl - 1 do
          Read(p, nas[i][pocz + k]);

        Read(p, lPowt);
        Inc(d[i], dl * lPowt)
      end;

    Readln(p)
  end;

  Close(p);
  d1 := d[1];
  d2 := d[2]
end;


procedure ZapiszWynik(wynik: boolean);
var p:text;

begin
  Assign(p, PLIK_WY);
  Rewrite(p);
  if wynik then
    Writeln(p, 'TAK')
  else
    Writeln(p, 'NIE');
  Close(p)
end;


var dl1, dl2: longint;

begin
  WczytajDane(dl1, dl2);
  if dl1 = dl2 then
    ZapiszWynik(CyklicznieRownowazne(dl1))
  else
    ZapiszWynik(false)
end.

(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Zamek                                          *
 *   Plik:                zam2.pas                                       *
 *   Autor:               Pawe³ Wolff                                    *
 *   Uwagi:               Rozwi±zanie nieoptymalne, heurystyczne         *
 *************************************************************************)
{$I+,Q-,R-,S-}
{$M 100000}

program Zamek;

const
  PLIK_WE = 'zam.in';
  PLIK_WY = 'zam.out';

  MAX_N = 100;
  MAX_M = ((MAX_N - 1) * MAX_N) div 2;
  MAX_S = 1000;

  MAX_PROB = 100;

var
  n, m, w, k, s: integer;
  o: array [1..MAX_N] of integer;

  poz: array [0..MAX_N] of integer;
  e: array [1..2*MAX_M] of integer;
  { opis krawedzi grafu reprezentujacego komnaty zamku }

  trasa: array [1..MAX_S] of integer; { czesc szukanej trasy }
  dlTrasy: integer;

  petla: array [1..MAX_S] of integer;
  poczPetli, dlPetli: integer;

  opl: integer;


procedure WczytajDane;
var
  plik: text;
  a, b: integer;
  i: integer;
  pom: array [1..2*MAX_M] of integer;
  aktPoz: array [1..MAX_N] of integer;
begin
  Assign(plik, PLIK_WE);
  Reset(plik);

  Read(plik, n, m, w, k, s);

  for i := 1 to n do
    Read(plik, o[i]);

  for i := 0 to n do
    poz[i] := 0;

  for i := 1 to m do begin
    Read(plik, a, b);
    pom[2*i-1] := a;
    pom[2*i]   := b;
    Inc(poz[a]);
    Inc(poz[b]);
  end;

  Close(plik);

  for i := 1 to n do begin
    poz[i] := poz[i] + poz[i-1];
    aktPoz[i] := poz[i-1];
  end;

  for i := 1 to m do begin
    a := pom[2*i-1];
    b := pom[2*i];

    Inc(aktPoz[a]);
    e[aktPoz[a]] := b;

    Inc(aktPoz[b]);
    e[aktPoz[b]] := a;
  end;
end;


procedure ZapiszWynik;
var
  plik: text;
  i, j: integer;
begin
  Assign(plik, PLIK_WY);
  Rewrite(plik);

  { zapisanie trasy do pliku }
  for i := 1 to dlTrasy do begin
    if (dlPetli <> 0) and (trasa[i] = poczPetli) then begin
      { wypisanie petli do pliku }
      Write(plik, trasa[i], ' ');
      for j := 1 to dlPetli do
        Write(plik, petla[j], ' ');
      for j := dlPetli - 1 downto 1 do
        Write(plik, petla[j], ' ');
    end;

    Write(plik, trasa[i]);
    if i < dlTrasy then
      Write(plik, ' ')
    else
      Writeln(plik);
  end;

  Close(plik);
end;


procedure ZnajdzTrase(var opl: integer);
{ losowo (i az do skutku) szuka drogi laczacej komnaty w i k,
  ktorej waga nie przekracza s; przez zmienna opl przekazywana
  jest waga znalezionej drogi }
var
  i, kom: integer;
  jest: boolean;
begin
  repeat
    dlTrasy := 1;
    trasa[1] := w;
    kom := w;
    opl := o[w];

    while (kom <> k) and (opl <= s) do begin
      i := poz[kom - 1] + 1 + Random(poz[kom] - poz[kom - 1]);
      kom := e[i];
      Inc(opl, o[kom]);
      Inc(dlTrasy);
      trasa[dlTrasy] := kom;
    end;

    jest := (kom = k) and (opl <= s);
  until jest;
end;


function ZnajdzPetle(opl: integer): boolean;
{ losowo (wykonujac co najwyzej MAX_PROB) szuka petli odchodzacej
  od uprzednio znalezionej drogi (zmienna trasa), ktorej waga wynosi
  dokladnie opl; zwraca true, jezeli taka petla zostanie znaleziona,
  w przeciwnym razie zwraca false }
var
  i, j, kom: integer;
  opl1, poprzOpl: integer;
  jest: boolean;
begin
  if opl = 0 then begin
    dlPetli := 0;
    jest := true;
  end
  else begin
    jest := false;

    for i := 1 to MAX_PROB do begin
      poczPetli := trasa[1 + Random(dlTrasy)];
      dlPetli := 0;
      opl1 := 0;
      poprzOpl := o[poczPetli];
      kom := poczPetli;

      repeat
        j := poz[kom - 1] + 1 + Random(poz[kom] - poz[kom - 1]);
        kom := e[j];
        Inc(opl1, o[kom] + poprzOpl);
        Inc(dlPetli);
        petla[dlPetli] := kom;
        poprzOpl := o[kom];
      until opl1 >= opl;

      if opl1 = opl then begin
        jest := true;
        break;
      end;
    end;
  end;

  ZnajdzPetle := jest;
end;


begin
  Randomize;

  WczytajDane;

  repeat
    ZnajdzTrase(opl);
  until ZnajdzPetle(s - opl);

  ZapiszWynik;
end.

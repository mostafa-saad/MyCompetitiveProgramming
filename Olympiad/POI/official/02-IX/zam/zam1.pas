(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Zamek                                          *
 *   Plik:                zam1.pas                                       *
 *   Autor:               Pawe³ Wolff                                    *
 *   Uwagi:               Rozwi±zanie nieoptymalne, wyk³adnicze          *
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

var
  n, m, w, k, s: integer;
  o: array [1..MAX_N] of integer;

  poz: array [0..MAX_N] of integer;
  e: array [1..2*MAX_M] of integer;
  { opis krawedzi grafu reprezentujacego komnaty zamku }

  trasa: array [1..MAX_S] of integer; { szukana trasa }
  dlTrasy: integer;


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
  i: integer;
begin
  Assign(plik, PLIK_WY);
  Rewrite(plik);

  { zapisanie trasy do pliku }
  i := dlTrasy;
  while i > 1 do begin
    Write(plik, trasa[i], ' ');
    Dec(i);
  end;
  Writeln(plik, trasa[1]);

  Close(plik);
end;


function ZnajdzTrase(kom: integer; opl: integer): boolean;
var
  i: integer;
  jest: boolean;
begin
  if (opl - o[kom] < 0) or ((opl - o[kom] = 0) and (kom <> k)) then
    ZnajdzTrase := false
  else begin
    jest := false;

    if opl - o[kom] = 0 then { wtedy rowniez zachodzi: kom = k }
      jest := true;

    { przechodzenie po wszystkich krawedziach wychodzacych z wierzcholka kom }
    i := poz[kom - 1] + 1;
    while not jest and (i <= poz[kom]) do begin
      jest := ZnajdzTrase(e[i], opl - o[kom]);
      Inc(i);
    end;

    if jest then begin
      { dopisujemy numer biezacej komnaty do znalezionej trasy }
      Inc(dlTrasy);
      trasa[dlTrasy] := kom;
    end;

    ZnajdzTrase := jest;
  end;
end;


begin
  WczytajDane;
  dlTrasy := 0;
  if ZnajdzTrase(w, s) then
    ZapiszWynik;
end.

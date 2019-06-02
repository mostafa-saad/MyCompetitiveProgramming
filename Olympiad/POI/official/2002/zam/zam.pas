(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Zamek                                          *
 *   Plik:                zam.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *   Uwagi:               Rozwi±zanie wzorcowe                           *
 *************************************************************************)
{$I+,Q+,R+,S+}
{$M 500000}

program Zamek;

const
  PLIK_WE = 'zam.in';
  PLIK_WY = 'zam.out';

  MAX_N = 100;
  MAX_M = ((MAX_N - 1) * MAX_N) div 2;
  MAX_S = 1000;

type TWezel =
  record
    kom: integer; { numer komnaty }
    opl: integer; { uiszczona oplata na pewnej drodze z w do danej komnaty }
  end;

var
  n, m, w, k, s: integer;
  o: array [1..MAX_N] of integer;

  poz: array [0..MAX_N] of integer;
  e: array [1..2*MAX_M] of integer;
  { opis krawedzi grafu reprezentujacego komnaty zamku }

  trasa: array [1..MAX_N, 1..MAX_S] of integer;
  { trasa[kom, opl] zawiera numer komnaty, znajdujacej sie na pewnej trasie
    z komnaty w do kom, ktorej przejscie kosztuje dokladnie opl }


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
  v: TWezel;
  t: array [1..MAX_S] of integer;
begin
  Assign(plik, PLIK_WY);
  Rewrite(plik);

  { odtwarzanie trasy prowadzacej z komnaty k do komnaty w }
  i := 0;
  v.kom := k;
  v.opl := s;
  repeat
    Inc(i);
    t[i] := v.kom;
    v.kom := trasa[v.kom, v.opl];
    Dec(v.opl, o[t[i]]);
  until v.kom = 0;

  { zapisanie trasy do pliku }
  while i > 1 do begin
    Write(plik, t[i], ' ');
    Dec(i);
  end;
  Writeln(plik, t[1]);

  Close(plik);
end;


procedure ZnajdzTrase;
var
  i, j: integer;
  a: integer;
  v: TWezel;
  nowaOpl: integer;
  kolejka: array [0..MAX_N*MAX_S] of TWezel;
  glowa, ogon, rozmiar: longint;
begin
  for i := 1 to n do
    for j := 1 to s do
      trasa[i, j] := 0;

  { inicjalizacja kolejki zawierajacej jeden element -- (kom: w; opl: o[w]) }
  rozmiar := n * s + 1;
  glowa := 1;
  ogon := 0;
  with kolejka[0] do begin
    kom := w;
    opl := o[w];
  end;

  repeat
    { pobranie elementu z kolejki }
    v := kolejka[ogon];
    ogon := (ogon + 1) mod rozmiar;

    { przechodzenie po wszystkich krawedziach wychodzacych z wierzcholka
      v.kom w grafie reprezentujacym komnaty zamku }
    for i := poz[v.kom - 1] + 1 to poz[v.kom] do begin
      a := e[i];
      nowaOpl := v.opl + o[a];

      if nowaOpl <= s then
        if trasa[a, nowaOpl] = 0 then begin
          { wezel (kom: a; opl: nowaOpl) nie zostal jeszcze odwiedzony }
          trasa[a, nowaOpl] := v.kom;

          { wstawianie do kolejki wezla (kom: a; opl: nowaOpl) }
          with kolejka[glowa] do begin
            kom := a;
            opl := nowaOpl;
          end;
          glowa := (glowa + 1) mod rozmiar;
        end;
    end;
  until (ogon = glowa) or (trasa[k, s] <> 0); { (kolejka jest pusta) lub
                                                (wezel (kom: k; opl: s)
                                                 zostal odwiedzony) }
end;


begin
  WczytajDane;
  ZnajdzTrase;
  ZapiszWynik;
end.

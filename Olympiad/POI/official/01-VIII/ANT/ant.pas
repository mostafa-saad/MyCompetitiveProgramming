{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: LICZBY ANTYPIERWSZE                            *}
{*   Plik:                ANT.PAS                                        *}
{*   Autor:               MARCIN STEFANIAK                               *}
{*************************************************************************}

{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+}
{$M 16384,0,655360}
program Ant1;

const
      LPierwszych = 10;   {liczba rozpatrywanych liczb pierwszych}
      NAntyP = 2000;      {liczba rozp. liczb potencj. antypierwszych}
      NAnty  = 70;        {liczba liczb antypierwszych}

type
  TRozklad = array[0..LPierwszych] of integer; {rozklad na czynniki pierwsze}

  AntyP = record                       {potencjalna liczba antypierwsza}
    n : longint;  {liczba}
    d : integer;  {jej liczba dzielnikow}
  end;

  TAntyP = array[1..NAntyP] of AntyP;
  TAnty  = array[1..NAnty] of AntyP;

const Pierwsze : TRozklad = (0,2,3,5,7,11,13,17,19,23,29);

var anty : TAntyP;  {kolekcja potencjalnych liczb antypierwszych}
    lAnty: integer; {rozmiar kolekcji Anty}
    max  : longint;

    wynik: TAnty;   {tablica liczb antypierwszych}
    lwyn : integer;

procedure obliczAntyP(const r : TRozklad; var a: AntyP); {
  oblicza liczbe i jej sume dzielnikow na podstawie danego rozkladu
}
var i,j:integer;
begin
  with a do begin
    n := 1;
    d := 1;
    for i:=1 to LPierwszych do begin
      d := d * (r[i] + 1);
      for j:=1 to r[i] do n := n * Pierwsze[i];
    end;
  end;
end;

function zakres(const r : TRozklad; m: longint):boolean; {
  czy liczba o zadanym rozkladzie jest <= od ograniczenia m
}
var i,j:integer;
    n:longint;
begin
  n := 1;
  for i:=1 to LPierwszych do begin
    for j:=1 to r[i] do begin
      if (m div Pierwsze[i]) < n then begin
        zakres := false;
        exit;
      end;
      n := n * Pierwsze[i];
    end;
  end;
  zakres := true;
end;

function nastepnyRozklad(var r: TRozklad): boolean;
{ generuje nastepny (w porzadlku leksykograficznym)
  niemalejacy rozklad o wartosci liczbowej <= max
  zwraca false, gdy r byl ostatnim takim rozkladem }
var i, j :integer;
    r2 : TRozklad;

begin
  i := LPierwszych;
  while (i>0) do begin
    while (r[i-1] = r[i]) do dec(i);
    r2 := r;
    inc(r2[i]);
    for j:=i+1 to LPierwszych do r2[j] := 0;
    if zakres(r2, max) then begin
      r := r2;
      nastepnyRozklad := true;
      exit;
    end;
    dec(i);
  end;
  nastepnyRozklad := false;
end;

procedure QSortAnty(l, r: Integer);
var
  i, j, x: longint;
  y : AntyP;

begin
  i := l; j := r; x := anty[(l+r) DIV 2].n;
  repeat
    while anty[i].n < x do i := i + 1;
    while x < anty[j].n do j := j - 1;
    if i <= j then
    begin
      y := anty[i]; anty[i] := anty[j]; anty[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then QSortAnty(l, j);
  if i < r then QSortAnty(i, r);
end;


procedure generujAntyPierwsze; {
  generuje liczby potencjalnie antyPierwsze az do max
}
var rozklad : TRozklad;
    i,j : integer;
    pom : AntyP;

begin
  { ustalanie poczatkowego rozkladu }
  rozklad[0] := maxInt; {straznik}
  rozklad[1] := 1;
  for i:=2 to LPierwszych do rozklad[i] := 0;

  { obliczanie potencjalnych liczb antypierwszych }

  lAnty := 0;
  repeat
    inc(lAnty);
    obliczAntyP(rozklad, anty[lAnty]);
  until (not nastepnyRozklad(rozklad));

  { sortowanie liczb }

  QSortAnty(1, lAnty);

  (*for i:=1 to lAnty do
    for j:=1 to lAnty do
      if anty[i].n < anty[j].n then begin
        pom := anty[i]; anty[i] := anty[j]; anty[j] := pom;
      end;*)

  { wybranie liczb antypierwszych do wyniku }
  lwyn := 1;
  wynik[lwyn] := anty[1];
  for i := 2 to lAnty do begin
    if anty[i].d > wynik[lwyn].d then begin
      inc(lwyn);
      wynik[lwyn] := anty[i];
    end;
  end;
end;

function antyPierwsza(n : longint): longint; {
  obliczamy najwieksza l. antyPierwsza <= n
}
var i : integer;
    a : longint;

begin
  max := n;
  generujAntyPierwsze;
  i := 1;
  a := 1;
  while (i <= lwyn) and (wynik[i].n <= n) do begin
    a:=wynik[i].n;
    inc(i);
  end;
  antyPierwsza := a;
end;

var f : text;
    n : longint;

Begin
  assign(f, 'ant.in');
  reset(f);
  read(f,n);
  close(f);

  assign(f, 'ant.out');
  rewrite(f);
  write(f, antyPierwsza(n));
  close(f);
End.

{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: WÊDROWNI TRESERZY PCHE£                        *}
{*   Plik:                PCH.PAS                                        *}
{*   Autor:               ANDRZEJ G¥SIENICA-SAMEK                        *}
{*************************************************************************}


{ Andrzej Gasienica-Samek }
{ Zadanie Wedrowni treserzy pchel }

{ Zaminy: Pawel Wolff, 2001.03.21 }

{$M 65520,0,655360}

program PCH;

const
  MAX_N = 2000; { 2000 }

type
  TUklad = record
    Skok: array [0..MAX_N-1] of Integer;
    Syn: array [0..MAX_N-1] of Integer;
    { SynPocz[o] - Indeks pierwszego syna wezla o w tablicy Syn }
    SynPocz: array [0..MAX_N] of Integer;
    { Czy dany element zeton na cyklu }
    CzyCykl: array [0..MAX_N-1] of Boolean;
    { Pierwsze zetony w cyklach }
    Cykl: array [0..MAX_N-1] of Integer;
    CyklIle: Integer;
  end;

var
  Lewy, Prawy: TUklad;
  d, n: Integer;
  PlikWe, PlikWy: Text;

{ Odczytuje uklad z pliku wejsciowego,
  inicjuje tablice Skok ukladu. }
procedure Odczytaj(var u: TUklad);
var
  a, b: Integer;
begin
  for a := 0 to n-1 do
  begin
    Read(PlikWe, b);
    Dec(b);
    u.Skok[a] := b;
  end;
end;

{ Znajduje cykle, inicjuje tablice CzyCykl, Cykl
  oraz zmienna CyklIle. W tablicy Cykl umieszcza
  ktorykolwiek zeton z cyklu. }
procedure ZnajdzCykle(var u: TUklad);
var
  Tab: array [0..MAX_N-1] of Integer;
  a, b: Integer;
begin
  u.CyklIle := 0;
  for a := 0 to n-1 do
    Tab[a] := -1;
  for a := 0 to n-1 do
  begin
    b := a;
    while Tab[b] = -1 do
    begin
      Tab[b] := a;
      b := u.Skok[b];
    end;
    if Tab[b] = a then
    begin
      u.Cykl[u.CyklIle] := b;
      Inc(u.CyklIle);
    end;
  end;
  for a := 0 to n-1 do
    u.CzyCykl[a] := False;
  for a := 0 to u.CyklIle-1 do
  begin
    b := u.Cykl[a];
    while not u.CzyCykl[b] do
    begin
      u.CzyCykl[b] := True;
      b := u.Skok[b];
    end;
  end;
end;

{ Inicjuje tablice Syn i SynPocz, tymi wartosciami,
  ktore nie naleza do cyklu }
procedure TworzDrzewa(var u: TUklad);
var
  a, b: Integer;
begin
  for a := 0 to n do
    u.SynPocz[a] := 0;
  for a := 0 to n-1 do
    if not u.CzyCykl[a] then
      Inc(u.SynPocz[u.Skok[a]]);
  for a := 0 to n-1 do
    Inc(u.SynPocz[a+1], u.SynPocz[a]);
  for a := 0 to n-1 do
    if not u.CzyCykl[a] then
    begin
      b := u.Skok[a];
      Dec(u.SynPocz[b]);
      u.Syn[u.SynPocz[b]] := a;
    end;
end;

function IleSynow(var u: TUklad; w: Integer): Integer;
begin
  IleSynow := u.SynPocz[w+1] - u.SynPocz[w];
end;

function Syn(var u: TUklad; w, i: Integer): Integer;
begin
  Syn := u.Syn[u.SynPocz[w] + i];
end;

function PorDrzewo(var u1: TUklad; w1: Integer;
                   var u2: TUklad; w2: Integer): Integer;
var
  i, c: Integer;
begin
  if IleSynow(u1, w1) <> IleSynow(u2, w2) then
  begin
    if IleSynow(u1, w1) < IleSynow(u2, w2) then
      PorDrzewo := -1
    else
      PorDrzewo := 1;
    Exit;
  end;
  for i := 0 to IleSynow(u1, w1) - 1 do
  begin
    c := PorDrzewo(u1, Syn(u1, w1, i),
                   u2, Syn(u2, w2, i));
    if c <> 0 then
    begin
      PorDrzewo := c;
      Exit;
    end;
  end;
  PorDrzewo := 0;
end;

procedure NormalizujDrzewo(var u: TUklad; w: Integer);
var
  a, b, s, l, r: Integer;
begin
  l := u.SynPocz[w];
  r := u.SynPocz[w+1]-1;
  for a := l to r do
  begin
    s := u.Syn[a];
    NormalizujDrzewo(u, s);
    b := a;
    while b > l do
    begin
      if PorDrzewo(u, s, u, u.Syn[b-1]) >= 0 then
        Break;
      u.Syn[b] := u.Syn[b-1];
      Dec(b);
    end;
    u.Syn[b] := s;
  end;
end;

procedure NormalizujDrzewa(var u: TUklad);
var
  a: Integer;
begin
  for a := 0 to n-1 do
    if u.CzyCykl[a] then
      NormalizujDrzewo(u, a);
end;

function PorCykle(var u1: TUklad; c1: Integer;
                  var u2: TUklad; c2: Integer): Integer;
var
  p1, p2, r: Integer;
begin
  p1 := c1;
  p2 := c2;
  r := 0;
  repeat
    r := PorDrzewo(u1, c1, u2, c2);
    c1 := u1.Skok[c1];
    c2 := u2.Skok[c2];
  until (r <> 0) or (c1 = p1) or (c2 = p2);
  if r <> 0 then
    PorCykle := r
  else if (c1 = p1) and (c2 = p2) then
    PorCykle := 0
  else if (c1 = p1) then
    PorCykle := -1
  else
    PorCykle := 1;
end;

{ Zmienia wartosci w tablicy Cykl na wlasciwe poczatki
  kazdego cyklu }
procedure NormalizujCykle(var u: TUklad);
var
  a, pocz, min, bie: Integer;
begin
  for a := 0 to u.CyklIle-1 do
  begin
    pocz := u.Cykl[a];
    min := pocz;
    bie := u.Skok[pocz];
    while bie <> pocz do
    begin
      if PorCykle(u, bie, u, min) < 0 then
        min := bie;
      bie := u.Skok[bie];
    end;
    u.Cykl[a] := min;
  end;
end;

{ Porzadkuje cykle w tablicy Cykl }
procedure NormalizujUklad(var u: TUklad);
var
  a, b, c: Integer;
begin
  for a := 0 to u.CyklIle-1 do
  begin
    c := u.Cykl[a];
    b := a;
    while b > 0 do
    begin
      if PorCykle(u, c, u, u.Cykl[b-1]) >= 0 then
        Break;
      u.Cykl[b] := u.Cykl[b-1];
      Dec(b);
    end;
    u.Cykl[b] := c;
  end;
end;

{ Odczytuje i normalizuje uklad }
procedure Mieszaj(var u: TUklad);
begin
  Odczytaj(u);
  ZnajdzCykle(u);
  TworzDrzewa(u);
  NormalizujDrzewa(u);
  NormalizujCykle(u);
  NormalizujUklad(u);
end;

function PorUklad(var u1, u2: TUklad): Boolean;
var
  a: Integer;
begin
  PorUklad := False;
  if u1.CyklIle <> u2.CyklIle then
    Exit;
  for a := 0 to u1.CyklIle - 1 do
    if PorCykle(u1, u1.Cykl[a], u2, u2.Cykl[a]) <> 0 then
      Exit;
  PorUklad := True;
end;

begin
  Assign(PlikWe, 'PCH.IN');
  Reset(PlikWe);
  Assign(PlikWy, 'PCH.OUT');
  Rewrite(PlikWy);
  Read(PlikWe, d);
  while d > 0 do
  begin
    Read(PlikWe, n);
    Mieszaj(Lewy);
    Mieszaj(Prawy);
    if PorUklad(Lewy, Prawy) then
      Writeln(PlikWy, 'T')
    else
      Writeln(PlikWy, 'N');
    Dec(d);
  end;
  Close(PlikWy);
  Close(PlikWe);
end.

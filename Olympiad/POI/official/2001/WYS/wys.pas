{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: WYSPA                                          *}
{*   Plik:                WYS.PAS                                        *}
{*   Autor:               ANDRZEJ G¥SIENICA-SAMEK                        *}
{*************************************************************************}

{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 65520,0,655360}
program wyspa;
const
  MaxN = 100; { 100 }
  { Maksymalna ilosc panstw }
  MaxP = 2 * MaxN - 2;

type
  TTrojka = array [1..3] of Integer;

var
  n: Integer;
  { Odleglosci miedzy panstwami nadmorskimi }
  Odl: array [1..MaxN, 1..MaxN] of Integer;
  { Numery panstw sasiednich }
  PanSas: array [1..MaxP] of TTrojka;
  { Odleglosci od panstw sasiednich }
  PanOdl: array [1..MaxP] of TTrojka;
  { Bazy w kierunku panstw sasiednich }
  PanBaz: array [1..MaxP] of TTrojka;
  InputOk: Boolean;

procedure Odczytaj;
var
  Plik: Text;
{  Buf: array [0..8191] of Byte;}
  a, b: Integer;
begin
  Assign(Plik, 'WYS.IN');
{  SetTextBuf(Plik, Buf);}{Dodatkowe buforowanie wylaczone}
  Reset(Plik);
  Read(Plik, n);
  for a := 1 to n do
    for b := 1 to n do
      Read(Plik, Odl[b, a]);
  Close(Plik);
end;

procedure Zapisz;
var
  Plik: Text;
{  Buf: array [0..8191] of Byte;}
  a: Integer;
begin
  Assign(Plik, 'WYS.OUT');
{  SetTextBuf(Plik, Buf);}{Dodatkowe buforowanie wylaczone}
  Rewrite(Plik);
  for a := 1 to n do
    Writeln(Plik, PanSas[a, 1], ' ', PanOdl[a, 1]);
  for a := n + 1 to 2 * n - 2 do
    Writeln(Plik, PanSas[a, 1], ' ', PanOdl[a, 1], ' ',
                  PanSas[a, 2], ' ', PanOdl[a, 2], ' ',
                  PanSas[a, 3], ' ', PanOdl[a, 3]);
  Close(Plik);
end;

{ *********************************************************** }

{ ROZWIAZANIE }

function TrojkaZnajdz(var t: TTrojka; el: Integer): Integer;
var
  i: Integer;
begin
  for i := 1 to 3 do
    if t[i] = el then
    begin
      TrojkaZnajdz := i;
      Exit;
    end;
  RunError;
end;

{ Czy zostal tylko jeden }
function TrojkaUsun(var t: TTrojka; el: Integer): Boolean;
var
  i, j: Integer;
begin
  i := TrojkaZnajdz(t, el);
  for j := i to 2 do
    t[j] := t[j + 1];
  t[3] := 0;
  TrojkaUsun := t[2] = 0;
end;

procedure UstawSas(Pan, Index, Sas, Odl, Baz: Integer);
begin
  PanSas[Pan, Index] := Sas;
  PanOdl[Pan, Index] := Odl;
  PanBaz[Pan, Index] := Baz;
end;

{ Bierze bazy e, nie w kierunku a }
procedure WezBazy(e, a: Integer; var c, d: Integer);
var
  i: Integer;
begin
  i := TrojkaZnajdz(PanSas[e], a);
  c := PanBaz[e, i mod 3 + 1];
  d := PanBaz[e, (i + 1) mod 3 + 1];
end;

function Wstaw(a, e, b, f: Integer): Boolean;
var
  c, d, g, h, s, OdlBF, OdlEF, OdlAF: Integer;
begin
  WezBazy(e, a, c, d);
  WezBazy(a, e, g, h);
  if Odl[g, c] + Odl[b, d] > Odl[g, b] + Odl[c, d] then
  begin
    InputOK := False;
    OdlBF := Odl[b, g] + Odl[b, c] - Odl[g, c];
    if OdlBF and 1 = 1 then Exit;
    OdlBF := OdlBF div 2;
    if OdlBF < 1 then Exit;
    OdlEF := Odl[b, c] + Odl[b, d] - Odl[c, d];
    if OdlEF and 1 = 1 then Exit;
    OdlEF := OdlEF div 2 - OdlBF;
    if OdlEF < 1 then Exit;
    OdlAF := Odl[b, g] + Odl[b, h] - Odl[g, h];
    if OdlAF and 1 = 1 then Exit;
    OdlAF := OdlAF div 2 - OdlBF;
    if OdlAF < 1 then Exit;
    InputOK := True;
    UstawSas(f, 1, b, OdlBF, b);
    UstawSas(f, 2, a, OdlAF, g);
    UstawSas(f, 3, e, OdlEF, c);
    UstawSas(b, 1, f, OdlBF, g);
    s := TrojkaZnajdz(PanSas[a], e);
    UstawSas(a, s, f, OdlAF, b);
    s := TrojkaZnajdz(PanSas[e], a);
    UstawSas(e, s, f, OdlEF, b);
    Wstaw := True;
  end else
    Wstaw := False;
end;

procedure Dostaw(b, f: Integer);
var
  Kol: array [1..MaxP] of Integer;
  KolPocz, KolKon: Integer;
  Mozliwe: array [1..MaxP] of TTrojka;
  a, e, i: Integer;
begin
  for i := n + 1 to f - 1 do
    Mozliwe[i] := PanSas[i];
  for i := 1 to b - 1 do
    Mozliwe[i] := PanSas[i];
  for i := 1 to b - 1 do Kol[i] := i;
  KolKon := b - 1;
  KolPocz := 1;
  while True do
  begin
    if KolPocz >= KolKon then
    begin
      InputOK := False;
      Exit;
    end;
    a := Kol[KolPocz];
    e := Mozliwe[a, 1];
    if Wstaw(a, e, b, f) then Break;
    if not InputOK then Exit;
    if TrojkaUsun(Mozliwe[e], a) then
    begin
      Inc(KolKon);
      Kol[KolKon] := e;
    end;
    Inc(KolPocz);
  end;
end;

procedure Mieszaj;
var
  b: Integer;
begin
  InputOk := True;
  for b := 1 to n do
  begin
    UstawSas(b, 1, -1, -1, -1);
    UstawSas(b, 2, 0, 0, b);
    UstawSas(b, 3, 0, 0, b);
  end;
  UstawSas(1, 1, 2, Odl[1, 2], 2);
  UstawSas(2, 1, 1, Odl[1, 2], 1);
  for b := 3 to n do
  begin
    Dostaw(b, n + b - 2);
    if not InputOk then Exit;
  end;
end;

{ *********************************************************** }

begin
  Odczytaj;
  Mieszaj;
  if not InputOK then RunError;
  Zapisz;
end.

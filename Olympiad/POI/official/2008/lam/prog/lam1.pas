(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lam1.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Algorytm podobny jak w rozwiazaniu niewzorcowym, ale NWD  *
 *             jest liczone troche inaczej, a poza tym podstawa          *
 *             reprezentacji duzych liczb jest 10^9.                     *
 *             Izomorficzne z lam.cpp                                    *
 *                                                                       *
 *************************************************************************)

const
  MAX_N = 1000;
  MAX_D = 1001;
  BASEDIGS = 9;
  BASE = 1000000000;

type Natural = record
                 l : Integer;
                 t : array[0..MAX_D - 1] of LongInt;
               end;

var
  n : LongInt;
  p : array[0..MAX_N - 1] of LongInt;
  liczniki, mianowniki : array[0..MAX_N - 1] of Natural;
  licznik, mianownik : Natural;



(* Implementacja wlasnej arytmetyki. *)

(* Zwraca liczbe, skonstruowana na podstawie podanej malej liczby
   calkowitej. *)
function liczba(x : LongInt) : Natural;
begin
  liczba.l := 0;
  while x > 0 do
  begin
    liczba.t[liczba.l] := x mod BASE;
    x := x div BASE;
    Inc(liczba.l);
  end;
  if liczba.l = 0 then
  begin
    liczba.l := 1;
    liczba.t[0] := 0;
  end;
end;

function rowny_zero(x : Natural) : Boolean;
begin
  rowny_zero := (x.l = 1) and (x.t[0] = 0);
end;

procedure wypisz(x : Natural);
var
  i, j, pom : LongInt;
  s : String;
begin
  Write(x.t[x.l - 1]);
  for i := x.l - 2 downto 0 do
  begin
    pom := x.t[i];
    s := '';
    for j := 1 to BASEDIGS do
    begin
      s := s + Char(Ord('0') + pom mod 10);
      pom := pom div 10;
    end;
    for j := Length(s) downto 1 do
      Write(s[j]);
  end;
end;

(* x mod y z pewnoscia bedzie mala liczba calkowita. *)
function modulo(x : Natural; y : LongInt) : LongInt;
var
  i : LongInt;
begin
  modulo := 0;
  for i := x.l - 1 downto 0 do
    modulo := LongInt((Int64(modulo) * BASE + Int64(x.t[i])) mod y);
end;

(* Zalozenie: 0 < y <= BASE. *)
procedure podziel(var x : Natural; y : LongInt);
var
  i : LongInt;
  pom : Int64;
begin
  pom := 0;
  for i := x.l - 1 downto 0 do
  begin
    pom := pom * BASE + x.t[i];
    x.t[i] := LongInt(pom div y);
    pom := pom mod y;
  end;
  while (x.l > 1) and (x.t[x.l - 1] = 0) do
    Dec(x.l);
end;

(* Zalozenie: 0 <= x <= BASE. *)
procedure pomnoz(var x : Natural; y : LongInt);
var
  i : LongInt;
  pom : Int64;
begin
  if y = 0 then
  begin
    x.t[0] := 0;
    x.l := 1;
  end
  else
  begin
    pom := 0;
    for i := 0 to x.l - 1 do
    begin
      pom := pom + Int64(x.t[i]) * y;
      x.t[i] := LongInt(pom mod BASE);
      pom := pom div BASE;
    end;
    while pom > 0 do
    begin
      x.t[x.l] := LongInt(pom mod BASE);
      pom := pom div BASE;
      Inc(x.l);
    end;
  end;
end;

function nwd(a, b : LongInt) : LongInt;
begin
  if b = 0 then
    nwd := a
  else
    nwd := nwd(b, a mod b);
end;

(* Zalozenie: b>0. *)
function nwd(a : Natural; b : LongInt) : LongInt;
begin
  if b = 0 then
    nwd := 1
  else
    nwd := nwd(b, modulo(a, b));
end;


var i, a, b, d : LongInt;

begin
  ReadLn(n);
  for i := 0 to n - 1 do
    ReadLn(p[i]);
  licznik := liczba(1);
  mianownik := liczba(p[n - 1]);
  liczniki[n - 1] := licznik;
  mianowniki[n - 1] := mianownik;
  for i := n - 2 downto 0 do
  begin
    a := p[i + 1] - 1;
    b := p[i];
    d := nwd(a, b);
    a := a div d; b := b div d;
    d := nwd(licznik, b);
    podziel(licznik, d); b := b div d;
    d := nwd(mianownik, a);
    podziel(mianownik, d); a := a div d;
    pomnoz(licznik, a); pomnoz(mianownik, b);
    if rowny_zero(licznik) then
      mianownik := liczba(1);
    liczniki[i] := licznik; mianowniki[i] := mianownik;
  end;
  for i := 0 to n - 1 do
  begin
    wypisz(liczniki[i]);
    Write('/');
    wypisz(mianowniki[i]);
    WriteLn;
  end;
end.

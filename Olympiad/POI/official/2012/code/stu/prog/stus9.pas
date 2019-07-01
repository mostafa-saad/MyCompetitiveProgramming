(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * log(max(x_i)) * log(n))                    *
 *   Opis:              Rozwiazanie wolniejsze                           *
 *                      Uzycie drzewa przedzialowego                     *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;
const LEWA = 0;
const PRAWA = 1;

function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

var   n, h, p, q, r : longint;
    m, sumx : int64;
    x : array[0..MAXN] of longint;
    pom : array[0..MAXN] of longint;
    t : array[0..1,0..2100000] of int64; (* 0 - lewa, 1 - prawa*)

var  size : longint;

procedure clear(z : shortint);
var  i : longint;
begin
  for i:=0 to 2*size do
    t[z, i] := 0;
end;
procedure init(s : longint);
begin
  size := 1;
  while size < s do
    size := 2*size;
  clear(0);
  clear(1);
end;
procedure _add(pp, qq, vv : longint; z : shortint);
begin
  if pp + 1 = qq then
  begin
    t[z, pp] += vv;
    exit;
  end;
  if pp mod 2 = 1 then
  begin
    t[z, pp] += vv;
    _add(pp+1, qq, vv, z);
    exit;
  end;
  if qq mod 2 = 1 then
  begin
    t[z, qq-1] += vv;
    _add(pp, qq-1, vv, z);
    exit;
  end;
  _add(pp div 2, qq div 2, vv, z);
end;
procedure add(pp, qq, vv : longint; z : shortint);
begin
  if qq <= pp then
    exit;
  _add(size+pp, size+qq, vv, z);
end;
function query(x : longint; z : shortint) : int64;
var  ret : int64;
begin
  ret := 0;
  x += size;
  while x > 0 do
  begin
    ret += t[z, x];
    x := x div 2;
  end;
  query := ret;
end;


(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var  ruchy : int64;
      i : longint;
begin
  ruchy := 0;
  
  for i:=1 to n-1 do
  begin
    if pom[i] + p < pom[i+1] then
    begin
      ruchy := ruchy + pom[i+1] - (pom[i] + p);
      pom[i+1] := pom[i] + p;
    end;
  end;
  
  for i:=n downto 2 do
  begin
    if pom[i] + p < pom[i-1] then
    begin
      ruchy := ruchy + pom[i-1] - (pom[i] + p);
      pom[i-1] := pom[i] + p;
    end;
  end;
  wyrownaj := ruchy;
end;

(* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. *)

function gdzie_kopac(p : longint) : longint;
  var   i, pd, pm : longint;
      ruchy : int64;
begin
  for i:=1 to n do (* przygotowanie tablicy pomocniczej *)
    pom[i] := x[i];
  
  ruchy := wyrownaj(p);
  
  (* jesli Bajtazar nie ma wystarczajaco sily na wyrownanie terenu,
   * to tym bardziej na dokopanie sie do wody *)
  if m < ruchy then
  begin
    gdzie_kopac := -1;
    exit;
  end;
  
  clear(PRAWA);
  clear(LEWA);
  for i:=1 to n do
  begin
    pd := pom[i] div p;
    pm := pom[i] mod p;
    add(i, min(n+1, i + pd), p, LEWA);
    add(min(n+1, i + pd), min(n+1, i + pd + 1), pm, LEWA);
    
    add(max(1, i - pd + 1), i+1, p, PRAWA);
    add(max(0, i - pd), max(0, i - pd + 1), pm, PRAWA);
  end;
  
  (* wyliczenie kosztu dokopania sie do wody w punkcie 1 *)
  for i:=1 to n do
  begin
    if pom[i] <= (p*(i-1)) then
      break
    else
      ruchy += (pom[i] - p*(i-1));
  end;
  if ruchy <= m then
  begin
    gdzie_kopac := 1;
    exit;
  end;
  for i:=2 to n do
  begin
    (* Aktualizacja kosztu dokopania sie do wody w miejscu i
     * na podstawie poprzedniego kosztu oraz podanego wzoru *)
    ruchy := ruchy - query(i-1, LEWA) + query(i, PRAWA);
    if ruchy <= m then
    begin
      gdzie_kopac := i;
      exit;
    end;
  end;
  gdzie_kopac := -1;
end;

var i : longint;

begin
  read(n, m);
  init(n+4);
  h := 0;
  sumx := 0;
  for i:=1 to n do
  begin
    read(x[i]);
    sumx := sumx + x[i];
    h := max(h, x[i]);
  end;
  if sumx <= m then
  begin
    writeln('1 0');
    halt;
  end;
  
  p := 1;
  q := h;
  while p < q do (* wyszukiwanie binarne po wyniku *)
  begin
    r := (p+q) div 2;
    if gdzie_kopac(r) = -1 then
      p := r + 1
    else
      q := r;
  end;
  writeln(gdzie_kopac(p), ' ', p);
end.

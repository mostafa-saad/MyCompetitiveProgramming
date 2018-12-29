(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     robs7.pas                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Algorytm O(n^3), ktory przy sprawdzaniu kolizji rozwaza   *
 *             tylko brzeg, polaczony z heurystyka z programu robb1.cpp. *
 *             Przepisanie robs4.cpp na Pascala.                         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2000;

type pair = record
  first, second : Integer;
end;

var
  lodz : array[0..MAX_N, 0..MAX_N + 1] of Char;
  n, i, j : LongInt;
  odc : array[0..MAX_N] of LongInt; (* odcinki skladajace sie na lodke *)
  odcsize : LongInt;
  minx, miny, maxx, maxy : LongInt;
  sr : LongInt; (* srodek lodki *)
  polsz : LongInt;

  x, y : array[0..3] of LongInt;
  wynik : LongInt;
  sumy : array[0..MAX_N, 0..MAX_N] of LongInt;
  kol : array[0..6 * MAX_N * MAX_N] of pair;
  head, tail : LongInt;
  odl : array[0..3 * MAX_N, 0..2 * MAX_N] of LongInt;
  przedzial : array[0..2 * MAX_N + 1] of pair;


function make_pair(a, b : LongInt) : pair;
var
  p : pair;
begin
  p.first := Integer(a);
  p.second := Integer(b);
  make_pair := p
end;
  
function min(a, b : LongInt) : LongInt;
begin
  if a < b then
    min := a
  else
    min := b;
end;
 
function max(a, b : LongInt) : LongInt;
begin
  if a < b then
    max := b
  else
    max := a;
end;
 
(* Sprawdzanie poprawnosci ulozenia lodki *)
function lodka : Boolean;
var 
  i, j : LongInt;
  i1, i2 : LongInt; (* ile kawalkow pod osia symetrii, a ile nad *)
  czy : Boolean;
begin
  czy := true;
  minx := n; miny := n; maxx := -1; maxy := -1;
  odcsize := 0;
  for i := 0 to n - 1 do
    for j := 0 to n - 1 do
      if lodz[i, j] = 'r' then
      begin
        minx := min(minx, i);
        maxx := max(maxx, i);
        miny := min(miny, j);
        maxy := max(maxy, j);
      end;
  sr := (maxx + minx) div 2;
  polsz := (maxx - minx) div 2;
  for j := miny to maxy do
  begin
    i1 := 0; i2 := 0;
    for i := minx to maxx do
    begin
      if lodz[i, j] = 'r' then
      begin
        if i < sr then
          Inc(i1);
        if i > sr then
          Inc(i2);
      end
    end;
    if i1 <> i2 then
    begin
      (* Lodka nie jest symetryczna *)
      czy := false;
      Break;
    end;
    odc[odcsize] := i1;
    Inc(odcsize);
  end;
  lodka := czy;
end;

procedure odwroc;
var
  a, b, c : LongInt;
begin
  a := 0; b := odcsize - 1;
  while a < b do
  begin
    c := odc[a];
    odc[a] := odc[b];
    odc[b] := c;
    Inc(a); Dec(b);
  end
end;

function ins(a, m : LongInt) : Boolean;
begin
  ins := (a >= 0) and (a < m)
end;

(* Czy lodka moze miec poczatek w punkcie (a,b). *)
function mozliwa(a, b : LongInt) : Boolean;
var
  i, j : LongInt;
  czy : Boolean;
begin
  for j := 0 to maxy - miny do
  begin
    if not czy then
      Break;
    if not ins(b + j - n, n) then
      Continue;
    i := odc[j];
    (* Sprawdzamy tylko brzeg lodki *)
    if ins(a + i - n, n) and (lodz[a + i - n][b + j - n] = 'X') then
    begin
      czy := false;
      Break;
    end;      
    if ins(a - i - n, n) and (lodz[a - i - n][b + j - n] = 'X') then
    begin
      czy := false;
      Break;
    end;
    if (j > 0) and (odc[j] > odc[j - 1]) then
      while i > odc[j - 1] do
      begin
        if ins(a + i - n, n) and (lodz[a + i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        if ins(a - i - n, n) and (lodz[a - i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        Dec(i);
      end;
    if (j < odcsize - 1) and (odc[j] > odc[j + 1]) then
      while i > odc[j + 1] do
      begin
        if ins(a + i - n, n) and (lodz[a + i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        if ins(a - i - n, n) and (lodz[a - i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        Dec(i);
      end;
    i := odc[j];
    if (j = 0) or (j = odcsize - 1) then
      while i >= 0 do
      begin
        if ins(a + i - n, n) and (lodz[a + i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        if ins(a - i - n, n) and (lodz[a - i - n][b + j - n] = 'X') then
        begin
          czy := false;
          Break;
        end;
        Dec(i);
      end
  end;
  mozliwa := czy
end;

(* Liczy liczby pol 'X' w prostokatach o jednym z wierzcholkow
 * rownym (0,0). *)
procedure dynamik;
var
  i, j, akt : LongInt;
begin
  for i := 0 to n - 1 do
  begin
    akt := 0;
    for j := 0 to n - 1 do
    begin
      if lodz[i, j] = 'X' then
        Inc(akt);
      sumy[i, j] := akt;
      if i > 0 then
        Inc(sumy[i, j], sumy[i - 1, j]);
    end;
  end;
end;

(* Zwraca sume X-ow z odpowiedniego prostokata. *)
function policz(a, b : LongInt) : LongInt;
begin
  Dec(a, n); Dec(b, n);
  a := min(a, n - 1); b := min(b, n - 1);
  if (a < 0) or (b < 0) then
    policz := 0
  else
    policz := sumy[a, b];
end;

(* Czy lodka moze miec poczatek w punkcie (a,b) - zakladamy, ze jest
 * idealnym prostokatem. *)
function mozliwa1(a, b : LongInt) : Boolean;
begin
  mozliwa1 := ((policz(a + polsz, b + maxy - miny) - policz(a + polsz, b - 1)
    - policz(a - polsz - 1, b + maxy - miny) + policz(a - polsz - 1, b - 1)) = 0);
end;

(* Funkcja zwraca przykladowy pusty przedzial (obustronnie domkniety). *)
function pusty : pair;
begin
  pusty := make_pair(1, 0);
end;

(* Dla kazdego b liczy, w jakim przedziale musi sie znajdowac a,
 * zeby lodka o poczatku w polu (a,b) byla wewnatrz planszy. *)
procedure licz_przedzialy;
var
  i, j, k, p, mx : LongInt;
begin
  (* lodka przed plansza *)
  p := n - odcsize;
  for i := 0 to p do
    przedzial[i] := pusty;
  
  (* lodka nad/pod plansza *)
  mx := odc[0];
  for i := 1 to odcsize - 1 do
    mx := max(mx, odc[i]);
  for i := p + 1 to 2 * n - 1 do
    przedzial[i] := make_pair(n - mx, 2 * n - 1 + mx);

  (* lodka dochodzi do planszy *)
  j := 0;
  while (j < odcsize - 1) and (odc[j] <= odc[j + 1]) do
  begin
    Inc(p);
    przedzial[p] := make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    Inc(j);
  end;

  (* lodka odchodzi od planszy *)
  k := 2 * n - 1;
  j := odcsize - 1;
  while (j > 0) and (odc[j] <= odc[j - 1]) do
  begin
    przedzial[k] := make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    Dec(j);
    Dec(k);
  end;

  (* lodka za plansza *)
  przedzial[2 * n] := pusty;
end;

function wyplynela(a, b : LongInt) : Boolean;
begin
  wyplynela := ((a < przedzial[b].first) or (a > przedzial[b].second));
end;

(* BFS zaczynajacy od punktu (x0,y0). *)
function bfs(x0, y0 : LongInt) : LongInt;
var
  i, j, a, b : LongInt;
  p : pair;
  wyn : LongInt;
begin
  for i := 0 to 3 * n do
    for j := 0 to 2 * n do
      odl[i, j] := -1;
  odl[x0, y0] := 0;
  kol[0] := make_pair(x0, y0);
  head := 0; tail := 1;
  wyn := -1;

  while (wyn = -1) and (head <> tail) do
  begin
    p := kol[head];
    Inc(head);
    for i := 0 to 3 do
    begin
      a := p.first + x[i]; b := p.second + y[i];
      (* Wyszlismy poza plansze - sukces *)
      if wyplynela(a, b) then
      begin
        wyn := odl[p.first, p.second] + 1;
        Break;
      end;
      if (odl[a, b] = -1) and (mozliwa1(a, b) or mozliwa(a, b)) then
      begin
        odl[a, b] := odl[p.first, p.second] + 1;
        kol[tail] := make_pair(a, b);
        Inc(tail);
      end
    end
  end;
  bfs := wyn
end;

procedure Swap(var a, b : Char);
var
  c : Char;
begin
  c := a;
  a := b;
  b := c;
end;

begin
  x[0] := 1; x[1] := -1; x[2] := 0; x[3] := 0;
  y[0] := 0; y[1] := 0; y[2] := 1; y[3] := -1;
  ReadLn(n);
  for i := 0 to n - 1 do
    ReadLn(lodz[i]);
  if not lodka then (* czy lodka zorienowana poziomo *)
  begin
    (* Odbij wszystko wzgledem osi y=x *)
    for i := 1 to n - 1 do
      for j := 0 to i - 1 do
        Swap(lodz[i, j], lodz[j, i]);
    lodka; (* no to lodka zorientowana pionowo *)
  end;
  dynamik;
  odwroc;
  licz_przedzialy;
  odwroc;
  wynik := bfs(n + sr, n + miny);
  if wynik < 0 then
    WriteLn('NIE')
  else
    WriteLn(wynik);
end.

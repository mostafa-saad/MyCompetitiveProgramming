(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob4.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n^2), zgodne z idea   *
 *             rozwiazania autorskiego.                                  *
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
  kol : array[0..4 * MAX_N * MAX_N] of pair;
  head, tail : LongInt;
  odl : array[0..3 * MAX_N, 0..2 * MAX_N] of LongInt;

  zabr : array[0..3 * MAX_N, 0..3 * MAX_N] of Boolean;
  polowka : array[0..MAX_N] of LongInt;
  polowkasize : LongInt;
  
  (* dla danego promienia trzymamy numer najwiekszego mieszczacego sie
     przekroju *)
  przekroj : array[0..MAX_N] of LongInt;

  (* jaki najwiekszy numer przekroju polowki miesci sie w danym polu *)
  pole : array[0..3 * MAX_N, 0..MAX_N] of LongInt;
  gora, dol : array[0..3 * MAX_N] of LongInt;
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

(* Odwraca i-ty wiersz lodzi. *)
procedure reverse(i : LongInt);
var
  a, b : LongInt;
  c : Char;
begin
  a := 0; b := n - 1;
  while a < b do
  begin
    c := lodz[i, a];
    lodz[i, a] := lodz[i, b];
    lodz[i, b] := c;
    Inc(a); Dec(b);
  end
end;

(* Odwraca polowke. *)
procedure odwr;
var
  a, b : LongInt;
  c : LongInt;
begin
  a := 0; b := polowkasize - 1;
  while a < b do
  begin
    c := polowka[a];
    polowka[a] := polowka[b];
    polowka[b] := c;
    Inc(a); Dec(b);
  end
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

procedure policz_przekroj(rozm : LongInt);
var
  i, j : LongInt;
begin
  (* Liczymy tablice przekroj *)
  i := 0;
  for j := 0 to n - 1 do
  begin
    i := max(i, 0);
    while (i < rozm) and (polowka[i] <= j) do
      Inc(i);
    Dec(i);
    przekroj[j] := i;
  end
end;


procedure policz_przekroje_pol(rozm : LongInt);
var
  i, j, wlk : LongInt;
begin
  (* Liczymy tablice pole *)
  for j := 0 to n - 1 do
  begin
    gora[0] := n;
    for i := 1 to 3 * n - 1 do
      if (i >= n) and (i < 2 * n) and (lodz[i - n, j] = 'X') then
        gora[i] := 0
      else
        gora[i] := min(gora[i - 1] + 1, n);
    
    dol[3 * n - 1] := n;
    for i := 3 * n - 2 downto 0 do
      if (i >= n) and (i < 2 * n) and (lodz[i - n, j] = 'X') then
        dol[i] := 0
      else
        dol[i] := min(dol[i + 1] + 1, n);

    for i := 0 to 3 * n - 1 do
    begin
      wlk := min(gora[i], dol[i]) - 1;
      if wlk < 0 then
        pole[i, j] := -1
      else
        pole[i, j] := przekroj[wlk];
    end
  end
end;



procedure policz_polowke(przesuniecie : LongInt; na_odwrot : Boolean);
var
  i, j : LongInt;
  rozm : LongInt;
  numer : LongInt;
  przekr : LongInt; (* numer najlepszego biezacego przekroju *)
begin
  rozm := polowkasize;
  policz_przekroj(rozm);
  policz_przekroje_pol(rozm);
  
  (* Glowny algorytm szukania pol zabronionych *)
  for i := 0 to 3 * n - 1 do
  begin
    numer := rozm - 1; (* numer poprzedniego najlepszego przekroju *)
    for j := n to 3 * n - 1 do
    begin 
      if j < 2 * n then
        przekr := pole[i, j - n]
      else
        (* jestesmy poza plansza - a tam tylko woda *)
        przekr := rozm - 1;
      if numer = rozm - 1 then
        Dec(numer);
      (* Obliczamy najlepszy biezacy numer *)
      numer := min(numer + 1, przekr);

      if numer <> rozm - 1 then
      begin
        (* Mamy pole zabronione *)
        if na_odwrot then
          zabr[i, 3 * n - 1 - j - przesuniecie] := true
        else
          zabr[i, j - przesuniecie] := true;
      end
    end
  end
end;


procedure zabronione;
var
  i, wlk0 : LongInt;
begin
  (* Lewa polowka *)
  i := 0;
  polowka[0] := odc[i];
  polowkasize := 1;
  while odc[i] < polsz do
  begin
    Inc(i);
    polowka[polowkasize] := odc[i];
    Inc(polowkasize);
  end;
  wlk0 := polowkasize - 1;
  policz_polowke(wlk0, false);

  (* Prawa polowka *)
  polowkasize := 0;
  repeat
    polowka[polowkasize] := odc[i];
    Inc(polowkasize);
    Inc(i);
  until i >= odcsize;
  
  (* Odwracamy polowke i lodz *)
  odwr;
  for i := 0 to n - 1 do
    reverse(i);
  policz_polowke(wlk0, true);
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
      if (odl[a, b] = -1) and (not zabr[a, b]) then
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
  zabronione;
  odwroc;
  licz_przedzialy;
  wynik := bfs(n + sr, n + miny);
  if wynik < 0 then
    WriteLn('NIE')
  else
    WriteLn(wynik);
end.

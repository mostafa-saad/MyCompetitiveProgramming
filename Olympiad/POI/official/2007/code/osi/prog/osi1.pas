{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Osie (OSI)                                                 *}
{*   Plik:    osi1.pas                                                   *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe, zlozonosc obliczeniowa: O(n).        *}
{*            Dodaje dla bokow wielokata ich srodki, konwertuje wielokat *}
{*            do tekstu i szuka promieni palindromow                     *}
{*                                                                       *}
{*************************************************************************}
type POINT = record
    x, y : longint;
end;

var
    testy, n, x, i, j, k, res : longint;
    v   : array[0..200000] of POINT;
    tmp : POINT;
    rep : array[0..400000] of int64;
    rad : array[0..800000] of longint;
     
function Cyc(a, b : longint) : longint;
begin
    if a < 0 then 
    begin
  Cyc := a+b;
    end else 
    if a >= b then 
    begin
  Cyc := a-b;
    end else 
  Cyc := a;
end;

function sqr(a : longint) : int64;
begin
    sqr := int64(a) * int64(a);
end;

function Det(a, b, c : POINT) : int64;
begin
    Det := int64(b.x - a.x) * int64(c.y - a.y) - int64(b.y - a.y) * int64(c.x - a.x);
end;

function min(a, b : longint) : longint;
begin
    if a < b then
    begin
  min := a;
    end else 
  min := b;
end;

function max(a, b : longint) : longint;
begin
    if a > b then
    begin
  max := a;
    end else 
  max := b;
end;

begin
    readln(testy);
    while (testy > 0) do
    begin
  Dec(testy);
  ReadLn(n);
  for x := 0 to n-1 do
  begin
      ReadLn(v[2*x].x, v[2*x].y);
      v[2*x].x := 2 * v[2*x].x;
      v[2*x].y := 2 * v[2*x].y;
  end;
  for x := 0 to n-1 do
  begin
      v[2*x+1].x := (v[2*x].x + v[Cyc(2*x+2, 2*n)].x) div 2;
      v[2*x+1].y := (v[2*x].y + v[Cyc(2*x+2, 2*n)].y) div 2;
  end;
//  for x := 0 to 2*n-1 do
//      writeln(v[x].x,' ',v[x].y);
  for x := 0 to 2 * n - 1 do 
  begin
      rep[2*x] := sqr(v[x].x - v[Cyc(x-1, 2*n)].x) + sqr(v[x].y - v[Cyc(x-1, 2*n)].y);
      rep[2*x+1] := int64(2) * Det(v[x], v[Cyc(x-1, 2*n)], v[Cyc(x+1, 2*n)]);
      tmp.x := v[Cyc(x-1, 2*n)].y - v[x].y + v[x].x;
      tmp.y := -v[Cyc(x-1, 2*n)].x + v[x].x + v[x].y;
      if Det(v[x], tmp, v[Cyc(x+1, 2*n)]) < 0 then
     Inc(rep[2*x+1]);
  end;
  i := 1;
  j := 0;
  while(i < 8*n) do
  begin
      while((i+j+1 < 8*n) and (i - j > 0) and (rep[Cyc(i-j-1,4*n)] = rep[Cyc(i+j+1,4*n)])) do Inc(j);
      rad[i] := j;
      k := 1;
      while((k <= j) and (rad[i-k] <> j - k)) do 
      begin
    rad[i+k] := min(rad[i-k], j - k);
    Inc(k);
      end;
      j := max(0, j - k);
      Inc(i, k);
  end;
  res := 0;
  for x := 0 to 2 * n - 1 do
      if(rad[2*x+1+2*n] >= 2*n) then Inc(res);
  WriteLn(res div 2);
    end;
end.

{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Grzbiety i doliny (GRZ)                                    *}
{*   Plik:    grz1.pas                                                   *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe. Zlozonosc obliczeniowa: O(n^2)       *}
{*            Rozwiazanie wykorzystujace przeszukiwanie wszerz           *}
{*                                                                       *}
{*************************************************************************}
const
  MaxSize = 1002;

var
  pola : array[0..MaxSize,0..MaxSize] of longint;
  odw : array[0..MaxSize,0..MaxSize] of boolean;
  posx : array[0..MaxSize*MaxSize] of longint;
  posy : array[0..MaxSize*MaxSize] of longint;
  n, doliny, grzbiety, x, y : longint;

function SzukajDoliny(x,y : longint) : boolean;
var p, k, x1, y1 : longint;
  wynik : boolean;
begin
  posx[0] := x;
  posy[0] := y;
  odw[x][y] := true;
  p := 0;
  k := 1;
  wynik := true;
  while p < k do
  begin
    x := posx[p];
    y := posy[p];
    for x1 := -1 to 1 do for y1 := -1 to 1 do
    begin
      if pola[x + x1][y + y1] > pola[x][y] then wynik := false;
      if (odw[x + x1][y + y1] = false) and (pola[x + x1][y + y1] = pola[x][y]) then
      begin
        odw[x + x1][y + y1] := true;
        posx[k] := x + x1; 
        posy[k] := y + y1;
        Inc(k);
      end;
    end;
    Inc(p);
  end;
  SzukajDoliny := wynik;
end;

begin
  doliny := 0;
  grzbiety := 0;
  ReadLn(n);
  for x := n + 1 downto 0 do for y := n + 1 downto 0 do
  begin
    odw[x][y] := false;
    pola[x][y] := -2000000000;
  end;
  for x := n downto 1 do for y := n downto 1 do Read(pola[x][y]);
  for x := 1 to n do for y := 1 to n do if (odw[x][y] = false) and (SzukajDoliny(x, y)) then Inc(grzbiety);
  for x := n + 1 downto 0 do for y := n + 1 downto 0 do odw[x][y] := false;
  for x := n downto 1 do for y := n downto 1 do pola[x][y] := -pola[x][y];
  for x := 1 to n do for y := 1 to n do if (odw[x][y] = false) and (SzukajDoliny(x, y)) then Inc(doliny);
  Writeln(grzbiety, ' ', doliny);
end.

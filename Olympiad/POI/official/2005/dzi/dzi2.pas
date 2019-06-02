(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi2.pas                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Rozwi±zanie poprawne o zlozonosci O(n log * n).*
 *                        Z³o¿ono¶æ pamiêciowa jest liniowa. Program ten *
 *                        nie przechowuje w pamiêci krawêdzi grafu,      *
 *                        wykorzystuje reprezentacjê zbiorów roz³±cznych *
 *                        Find & Union w celu wykrywania cykli.          *
 *                                                                       *
 *************************************************************************)

program dziuple;

const MAXN = 1000000; {maksymalna liczba wierzcho³ków}

type tab = array [1..MAXN] of LongInt;

var 
  deg : tab; {tablica w której utrzymywane s± stopnie wierzcho³ków}
  fu : tab; {tablica w której pamiêtana jest struktura Find & Union}
  {tablice pomocnicze do sprawdzania pladzielno¶ci i symetrii}
  wezly, liscie, sasiad : tab;
  k, r : Int64; 
  n, m : LongInt; {liczba wierzcho³ków oraz liczba krawêdzi}

(* funkcja ta zwraca numer sk³adowej do której nale¿y
w danej chwili wierzcho³ek *)
function fufind(x : LongInt) : LongInt;
begin
  if fu[x] < 0
    then Exit(x);
  {kompresja scie¿ki}
  fu[x] := fufind(fu[x]);
  Exit(fu[x])
end; {fufind}

(* procedura uaktualnia informacje w tablicach pomocniczych
po dodaniu do grafu krawêdzi (a,b) *)
procedure dodaj(a, b : LongInt);
begin
  Inc(deg[a]);
  if deg[a] = 1 then
    sasiad[a] := b
  else
  begin
    Inc(wezly[b]);
    if deg[a] = 2 then
      Inc(wezly[sasiad[a]])
  end {else}
end; {dodaj}
  
(* funkcja wczytuje krawêdzie i sprawdza czy graf jest lasem *)
function cykl : Boolean;
var 
  i, a, b, c : LongInt;
begin
  for i := 1 to m do
  begin
    ReadLn(a, b);
    dodaj(a, b);
    dodaj(b, a);
    
    a := fufind(a);
    b := fufind(b);
    if a = b then 
      {wierzcho³ki nale¿± do tej samej
      spójnej sk³adowej, zatem powstaje cykl}
      Exit(true);
      
    if fu[a] < fu[b] then {³±czenie wed³ug rangi}
    begin
      c := b; b := a; a := c;
    end; {if}
    
    fu[b] := fu[b] + fu[a];
    fu[a] := b
  end; {for}
  Exit(false)
end; {cykl}

(* funkcja ta sprawdza, czy graf jest pladzielny *)
function pladzielny : Boolean;
var
  i : LongInt;
begin
  for i := 1 to n do
    if wezly[i] > 2 then
      Exit(false)
    else
      wezly[i] := 0;
  Exit(true)
end; {pladzielny}

procedure inicjuj;
var 
  i : LongInt;
begin
  for i := 1 to n do
  begin
    deg[i] := 0;
    fu[i] := -1; {ka¿dy wierzcho³ek nale¿y do innego zbioru}
    liscie[i] := 0;
    wezly[i] := 0;
  end {for}
end; {inicjuj}

(* g³ówna procedura programu, zlicza wszystkie konfiguracje *)
procedure licz;
var
  i, skladowe, izolowane : LongInt;
begin
  r := 1;
  ReadLn(n, m, k);
  inicjuj;
  
  if cykl or (not pladzielny) then
  begin
    WriteLn(0);
    Exit
  end; {if}

  izolowane := 0;
  {zliczanie liczby wierzcho³ków o poszczególnych stopniach}
  for i := 1 to n do 
    if deg[i] = 0
      then Inc(izolowane)
    else
      if deg[i] = 1 then 
      begin
        Inc(liscie[sasiad[i]]);
        r := (r * liscie[sasiad[i]]) mod k;
      end
      else
        Inc(wezly[fufind(i)]);
           
  skladowe := 0;
  for i := 1 to n do
    if fu[i] < -1 then
    {wierzcho³ek i jest korzeniem sk³adowej o liczbie wierzcho³ków > 1}
    begin
      Inc(skladowe);
      r := (r * (2 * skladowe)) mod k;
      if wezly[i] >= 2 then {sk³adowa nie jest symetryczna}
        r := (r * 2) mod k;
    end; {if}
  
  {trzeba jeszcze doliczyæ rozstawienia wierzcho³ków izolowanych}   
  for i := n + 1 downto n + 2 - izolowane do
    r := (r * i) mod k;
  WriteLn(r)
end; {licz}

begin
  licz
end. {program}

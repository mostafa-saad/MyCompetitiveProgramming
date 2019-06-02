{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klo2.pas                                                   *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie: Wzorcowe, poprzez drzewko licznikowe z        *}
{*            kolejnoscia lisci i-va[i], klocki przetwarzane             *}
{*            w kolejnosci val[i].                                       *}
{*                                                                       *}
{*************************************************************************}
const SIZE_ = 1024*128; { ponad 100000 }

var 
  tab : array [1 .. 2*SIZE_-1] of longint;
    { drzewko licznikowe: 
      maksimum z wysokosci wiezy po i-val[i]
      tzn. li¶cie s± indeksowane i-val[i]
      w kazdym korzeniu jest maksimum dla poddrzewa }
  gdzie_max : array [1 .. 2*SIZE_-1] of longint; 
    { dla ktorego i jest to maksimum }

function find_max(next : longint; var gdzie : longint) : longint;
 { szuka maksimum wsrod pozycji <next,
   w gdzie zwraca numer klocka, dla ktorego jest to maksimum }
var size, pos, wyn : longint;
begin
  size := SIZE_;
  pos := 1;
  wyn := 0;
  while (size>1) do
  begin
    size := size div 2;
    pos := pos * 2;
    if (next>=size) then { idz do prawego syna - wez maksimum z lewego }
    begin
      if (tab[pos]>wyn) then
      begin
        wyn := tab[pos];
        gdzie := gdzie_max[pos];
      end;
      inc(pos);
      next := next-size;
    end;
  end;
  find_max := wyn;
end;

procedure wstaw(cel, val, gdzie : longint);
  { wstawia now± warto¶æ val na pozycji cel, 
    o ktorej wiadomo, ze pochodzi od klocka gdzie }
var size, pos : longint;
begin  
  size := SIZE_;
  pos := 1;
  while (size>0) do
  begin
    if (val>tab[pos]) then
    begin
      tab[pos] := val;
      gdzie_max[pos] := gdzie;
    end;
    size := size div 2;
    pos := pos*2;
    if (cel>=size) then
    begin
      inc(pos);
      cel := cel-size;
    end;
  end;
end;

var 
  val : array [0 .. 100000-1] of longint; 
      { wartosci na i-tym klocku (od 0) }
  N : longint;

  prev : array [0 .. 100000-1] of longint; 
      { poprzedni klocek na dobrej wysokosci }

  posortuj : array [0 .. 100000-1, 0 .. 1] of longint; 
      { pary (val[i], i) }
  pom : array [0 .. 100000-1, 0..1] of longint;

procedure sortuj(pocz, kon : longint);
var m, l1, l2, lg : longint;
begin
  if (kon=pocz+1) then
    exit;
  m := (pocz+kon) div 2;
  sortuj(pocz, m);
  sortuj(m, kon);
  l1 := pocz;
  l2 := m;
  lg := pocz;
  while (l1<m) or (l2<kon) do 
  begin
    if (l2=kon) or ((l1<m) and (posortuj[l1][0]<posortuj[l2][0])) then
    begin
      pom[lg][0] := posortuj[l1][0];
      pom[lg][1] := posortuj[l1][1];
      inc(l1);
    end
    else
    begin
      pom[lg][0] := posortuj[l2][0];
      pom[lg][1] := posortuj[l2][1];
      inc(l2);
    end;
    inc(lg);
  end;
  for l1 := pocz to kon-1 do
  begin
    posortuj[l1][0] := pom[l1][0];
    posortuj[l1][1] := pom[l1][1];
  end
end;

var  
  a, wyn, p, best, best_pos, bpp, diff, x : longint;
  first : boolean;

begin
  read(N);
  for a := 0 to N-1 do
  begin
    read(val[a]);
    dec(val[a]);
    posortuj[a][0] := val[a];
    posortuj[a][1] := -a;
    prev[a] := -1;
  end;
  sortuj(0, N);
  best := 0;
  best_pos := -1;
  for p := 0 to N-1 do
  begin
    a := -posortuj[p][1];
{    writeln('Liczê dla ', a, ', val=', val[a]);}
    if (val[a]>a) then
      continue; { ten klocek nie moze byc na swoim miejscu, musialby podskoczyc }
    wyn := 1+find_max(a-val[a]+1, prev[a]);
{    writeln('   wyn=', wyn, ' poprz=', prev[a]);}
    wstaw(a-val[a], wyn, a);
    if (wyn>best) then
    begin
      best := wyn;
      best_pos := a;
    end;
  end;
  { WYPISYWANIE WYNIKU }
  if (best=0) then // nic sie nie da dopasowac, wiec nie trzeba nic usuwac
  begin
    writeln('0');
    writeln;
    exit;
  end;
  writeln(best_pos-val[best_pos]);
  first := true; // czy wypisywac spacjê?
  while (best_pos>=0) do
  begin
    bpp := prev[best_pos];
    if (bpp>=0) then 
      diff := (best_pos-val[best_pos])-(bpp-val[bpp])
    else
      diff := best_pos-val[best_pos];
    for x := bpp+1 to bpp+diff do { dla bpp=-1 tez jest ok }
    begin
      if (not first) then
        write(' ');
      write(1+x);
      first := false;
    end;
    best_pos := bpp;
  end;
  writeln;
end.

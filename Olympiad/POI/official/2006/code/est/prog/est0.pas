(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: EST (Estetyczny Tekst)                         *
 *   Plik:                est0.pas                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                        Zlozonosc: czasowa : O(n^2) pamieciowa: O(n^2) *
 *                                                                       *
 *************************************************************************)

CONST
INF = 1000000000;
VAR
tab: array[0..2100] of longint;
mniejsze,wieksze,wynik: array[0..2100,0..2100] of longint;


{ Zwraca sume slow z przedzialu z1, z2 (wlacznie) }
Function suma(z1,z2:longint):longint;
begin
  if (z1=0) then
    suma:= tab[z2]
  else
  suma := (tab[z2]-tab[z1-1]);
end;

{ szuka najmniejszej takiej liczby, aby suma(liczba,od-1)<=suma(od,dod) }
Function znajdz(od,dod:longint):longint;
VAR
pocz,kon,sr:longint;
wart:longint;
begin
  pocz := 0;
  kon := od;
  wart := suma(od,dod);
  sr := (pocz+kon) div 2;
  while (pocz<>kon) do
  begin
    sr := (pocz+kon) div 2;
    if (suma(sr,od-1)<=wart) then
      kon := sr
    else 
      pocz := sr+1;
  end;
  znajdz:=pocz;
end;

function min(z1,z2:longint):longint;
begin
  if (z1<z2) then
    min:=z1
  else   
    min:=z2;
end;

VAR
dod,q,od,i,n,m:longint;
mini:longint;
begin
  readln(m,n);
  for i:=0 to n-1 do
  begin
    read(tab[i]);
    tab[i] := tab[i]+1;
    if (i<>0) then tab[i]:=tab[i]+tab[i-1];
  end;
  m:=m+1;

  { Wyliczanie skrajnych wartosci }
  for dod:=0 to n-1 do
  begin
    mniejsze[0,dod] := INF;
    wieksze[0,dod] := INF;
    wynik[0,dod] := INF;
    if (suma(0,dod)<=m) then
    begin
      mniejsze[0,dod] := suma(0,dod);
      wieksze[0,dod] := -suma(0,dod);
      wynik[0,dod] := 0;
    end;
  end;

  for dod:=1 to n-1 do
  begin
    q := znajdz(1,dod);
    { tutaj czas dzialania = O(1) bo q = 0 lub q = 1}
    for od:=1 to dod do
    begin
      { niekiedy trzeba przesunac q } 
      while (suma(q,od-1)>suma(od,dod)) do  q:=q+1;

      wynik[od,dod] := INF;
      if (suma(od,dod)<=m) then
      begin
        if (q<>0) then wynik[od,dod] := min(wynik[od,dod],mniejsze[q-1,od-1]-suma(od,dod));
        if (q<>od) then wynik[od,dod] := min(wynik[od,dod],wieksze[q,od-1]+suma(od,dod));

      end;
    end;
    { wyliczanie pozostalych}
    for od:=1 to dod do
    begin
      mniejsze[od,dod] := min(INF,wynik[od,dod]+suma(od,dod));
      mniejsze[od,dod] := min(mniejsze[od,dod],mniejsze[od-1,dod]);
    end;
    for od:=dod downto 1 do
    begin
      wieksze[od,dod] := min(INF,wynik[od,dod]-suma(od,dod));
      if (od<>dod) then
        wieksze[od,dod] := min(wieksze[od,dod],wieksze[od+1,dod]);
    end;
  end;

  { wyliczanie wyniku}
  mini := INF;
  for i:=0 to n-1 do mini := min(mini,wynik[i][n-1]);

  writeln(mini);
end.

(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb9.cpp                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(n!*m!*n*m). Sprawdza wszystkie        *
 *             permutacje wierszy i kolumn.                              *
 *                                                                       *
 *************************************************************************)

program Tablice_zolw;

const CN=1001;
const CM=1000000;

var t, n, m, i, j, tnr, nr : Longint;
    tab : Array[1..2,1..CN,1..CN] of Longint;
    tmp : Array[-CM..CM] of Longint;
    perw, perk : Array[1..CN] of Longint;
    odp, f : Boolean;

function next_permutation(var t : Array of Longint; n : Longint) : Boolean;
var i, j, tmp : Longint;
begin
  i := n-1;
  while (i>0) and (t[i-1] >= t[i]) do
    dec(i);
  if i=0 then
    next_permutation := false
  else
  begin
    next_permutation := true;
    j := i;
    while (j<n) and (t[i-1]<t[j]) do 
      inc(j);
    tmp := t[i-1];
    t[i-1] := t[j-1];
    t[j-1] := tmp;
  end;
  j := n-1;
  while i<j do
  begin
    tmp := t[i];
    t[i] := t[j];
    t[j] := tmp;
    inc(i);
    dec(j);
  end;
end;

begin
{  for i:=1 to 4 do
    perw[i] := i;
  repeat
    for i:=1 to 4 do
      write(perw[i],' ');
    writeln;
  until not next_permutation(perw,4);}
  Readln(t);
  for i := -CM to CM do
    tmp[i] := 0;
  for tnr := 1 to t do
  begin
    Readln(n,m);
    odp := true;
    for nr := 1 to 2 do
      for i := 1 to n do
        for j := 1 to m do
        begin
          tab[nr,i,j] := 0;
          Read(tab[nr,i,j]);
          if nr=1 then
            tmp[tab[nr,i,j]] := tnr
          else
            if tmp[tab[nr,i,j]] <> tnr then
              odp := false;
        end;
    if not odp then
    begin
      Writeln('NIE');
      continue;
    end;
    for i := 1 to n do
      perw[i] := i;
    for j := 1 to m do
      perk[j] := j;
    odp := false;
    repeat
      repeat
        f := true;
        for i:=1 to n do
        begin
          for j:=1 to m do
            if tab[1,i,j]<>tab[2,perw[i],perk[j]] then
            begin
              f := false;
              break;
            end;
          if not f then
            break;
        end;
        odp := odp or f;
      until odp or (not next_permutation(perk,m));
    until odp or (not next_permutation(perw,n));
    if odp then
      Writeln('TAK')
    else
      Writeln('NIE');
  end;
end.

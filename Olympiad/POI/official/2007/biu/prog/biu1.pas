{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biu1.pas                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwi±zanie szukajace spojnych skladowych w grafie         *}
{*            dopelnionym, przy pomocy struktury Find & Union            *}
{*            o z³o¿ono¶ci O((n+m)log^* n)                               *}
{*                                                                       *}
{*************************************************************************}

Program Biura;
const MAXN = 100000;
      MAXM = 2000000;
type tablica=array [1..2*MAXM] of LongInt;
     tablicaN=array [1..MAXN] of LongInt;
var n,m,a,b,i,j,ile:LongInt;
    krawedzie,nast:tablica;                          { 2 * 4 * 4 MB }
    poczatki:tablicaN;                               { < 1MB }
    fu:tablicaN;                                     { < 1MB }
    spojne:tablicaN;
    liczniki:tablicaN;

procedure quickSort(var tab:tablicaN; l,r:LongInt);
var i,j,med,pom:LongInt;
begin
  i:=l; j:=r; med:=tab[(i+j) shr 1];
  repeat
    while tab[i] < med do Inc(i);
    while tab[j] > med do Dec(j);
    if i<=j then begin
      pom   := tab[i];
      tab[i]:=tab[j];
      tab[j]:=pom;
      Inc(i);
      Dec(j);
    end;
   until (i>=j);
  if i<r then quickSort(tab,i,r);
  if j>l then quickSort(tab,l,j);
end;

procedure dodajKrawedz(a,b:LongInt; var j:LongInt);
begin
    krawedzie[j]:=b;
    nast[j]:=poczatki[a];
    poczatki[a]:=j;
    Inc(j);
end;

function find(x:LongInt):LongInt;
begin
  if fu[x] < 0 
    then find:=x
    else begin
      fu[x]:=find(fu[x]);
      find:=fu[x];
    end;
end;

procedure union(a,b:LongInt);
var pom:LongInt;
begin
  a:=find(a);
  b:=find(b);
  if a<>b then begin
    if fu[a] > fu[b] then begin
      pom:=a; a:=b; b:=pom;
    end;
    fu[a]:=fu[a]+fu[b];
    fu[b]:=a;
  end;
end;

begin
  ReadLn(n,m);
  for i:=1 to n do begin
    spojne[i]:=i;
    fu[i] := -1;
  end;
  ile:=n;

  j:=1;
  for i:=1 to m do begin
    ReadLn(a,b);
    dodajKrawedz(a,b,j);
    dodajKrawedz(b,a,j);
  end;


  for i:=1 to n do begin

    for j:=1 to ile do 
      liczniki[spojne[j]] := 0;

    j:=poczatki[i];
    while j>0 do begin
      Inc(liczniki[find(krawedzie[j])]);
      j:=nast[j];
    end;

    for j:=1 to ile do
      if liczniki[spojne[j]] <> -fu[spojne[j]] then
        union(i,spojne[j]);

    j:=1;
    while j<=ile do begin
      if fu[spojne[j]] >= 0 then begin
        spojne[j]:=spojne[ile];
        Dec(ile);
      end
      else Inc(j);
    end;
  end;

  for i:=1 to ile do
    spojne[i] := -fu[spojne[i]];
  quickSort(spojne,1,ile);
  
  WriteLn(ile);
  for i:=1 to ile do
    Write(spojne[i],' ');
  WriteLn;
end.


{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    bius0.pas                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwi±zanie szukajace spojnych skladowych w grafie         *}
{*            dopelnionym, o pesymistycznej z³ozonosci O(n^2)            *}
{*                                                                       *}
{*************************************************************************}
Program Biura;
const MAXN = 100000;
      MAXM = 2000000;
type tablica=array [1..2*MAXM] of LongInt;

var n,m,a,b,i,j:LongInt;
    krawedzie,nast,poukladane:tablica;               {3 * 4 * 4 MB}
    poczatki:array[1..MAXN] of LongInt;              { < 1MB}
    konce:array[1..MAXN] of LongInt;                 { < 1MB}
    spojne:array[1..MAXN] of LongInt;


procedure quickSort(var tab:tablica; l,r:LongInt);
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

procedure poukladaj(var j:LongInt);
var i,pom:LongInt;
begin
  for i:=1 to n do begin
    pom:=poczatki[i];
    poczatki[i]:=j;
    while (pom > 0) do begin
      poukladane[j] := krawedzie[pom];
      pom := nast[pom];
      Inc(j);
    end;
    konce[i]:=j-1;
  end;
end;

procedure dodajKrawedz(a,b:LongInt; var j:LongInt);
begin
    krawedzie[j]:=b;
    nast[j]:=poczatki[a];
    poczatki[a]:=j;
    Inc(j);
end;

procedure wypisz(var tab: tablica);
var i,j:LongInt;
  begin
    for i:=1 to n do begin
      Write(i:2,': ');
      for j:=poczatki[i] to konce[i] do
        Write(tab[j]:2,' ');
      WriteLn;
    end;

  end;

procedure dfs(i,j:LongInt);
var k,l,p,x:LongInt;
begin
  spojne[i] := j;
  Inc(krawedzie[j]);
  k:=1;
  p := poczatki[i];
  if p <= konce[i]
    then l:=poukladane[p]-1
    else l:=n;

  repeat
    for x:=k to l do
      if spojne[x] = 0 then begin
      {Writeln(i:2,' -> ',x:2);}
        dfs(x,j);
      end;
    k:=l+2;
    Inc(p);
    if p <= konce[i]
      then l:=poukladane[p]-1
      else l:=n;
  until k>n;
end;


begin
  ReadLn(n,m);
  for i:=1 to n do begin
    poczatki[i]:=0;
    konce[i]:=0;
    spojne[i]:=0;
  end;

  j:=1;
  for i:=1 to m do begin
    ReadLn(a,b);
    dodajKrawedz(a,b,j);
    dodajKrawedz(b,a,j);
  end;

  j:=1;
  poukladaj(j);

  for i:=1 to n do
    if poczatki[i]<konce[i] then
      quickSort(poukladane,poczatki[i],konce[i]);

  j:=0;
  for i:=1 to n do begin
    if spojne[i] = 0 then begin
      Inc(j);
      krawedzie[j] := 0;
      dfs(i,j);
    end;
  end; 

  if j>1 then
    quickSort(krawedzie,1,j);

  WriteLn(j);
  for i:=1 to j do
    Write(krawedzie[i],' ');
  WriteLn;
end.

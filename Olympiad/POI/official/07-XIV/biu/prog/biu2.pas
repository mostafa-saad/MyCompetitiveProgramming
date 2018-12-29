{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biu2.pas                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwi±zanie szukajace spojnych skladowych w grafie         *}
{*            dopelnionym, przy pomocy obserwacji, ze jesli krawedzi w   *}
{*            grafie oryginalnym jest malo, to graf dopelniony zawiera   *}
{*            duza skladowa a nastepnie szukajace pozostalych skladowych *}
{*                                                                       *}
{*************************************************************************}
Program Biura;
const MAXN = 100000;
      MAXM = 2000000;
type tablica=array [1..2*MAXM] of LongInt;

var n,m,a,b,i,j:LongInt;
    krawedzie,nast,poukladane:tablica;               {3 * 4 * 4 MB}
    poczatki:array[1..MAXN] of LongInt;              { < 1MB}
    konce:array[1..MAXN] of LongInt;                  { < 1MB}
    spojne:array[1..MAXN] of LongInt;                { < 1MB}
    licznosci:array[1..MAXN] of LongInt;              { < 1MB}

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

function dfs(i,j:LongInt; force: Boolean):Boolean;
var k,l,p,x:LongInt;
    res:Boolean;
begin
  res:=false;
  spojne[i] := j;
  Inc(licznosci[j]);
  k:=1;
  p := poczatki[i];
  if p <= konce[i]
    then l:=poukladane[p]-1
    else l:=n;

  repeat
    for x:=k to l do
      if spojne[x] = 0 then
        res:= res or dfs(x,j,force)
      else if spojne[x] <> j then begin
        if force then
          dfs(x,j,force)
        else 
          res:=true;
      end;
    k:=l+2;
    Inc(p);
    if p <= konce[i]
      then l:=poukladane[p]-1
      else l:=n;
  until k>n;
  dfs:=res;
end;

function findk():LongInt;
var k:Int64;
  begin
    k:=n shr 1;
    while k*(n-k)>m do Dec(k);
    findk:=LongInt(k);
  end;

begin
  ReadLn(n,m);
  for i:=1 to n do begin
    poczatki[i]:=0;
    konce[i]:=0;
    spojne[i]:=0;
    licznosci[i]:=0;
  end;

  j:=1;
  for i:=1 to m do begin
    ReadLn(a,b);
    dodajKrawedz(a,b,j);
    dodajKrawedz(b,a,j);
  end;

  j:=1;
  poukladaj(j);

  j:=n-findk();
  if j > n shr 1 then
    for i:=1 to n do
      if konce[i]-poczatki[i]+1<j then begin
       spojne[i]:=1;
       Inc(licznosci[1]);
      end;
  
  if licznosci[1]>0 
    then j:=1
    else j:=0;

  for i:=1 to n do
    if (poczatki[i]<konce[i]) and (spojne[i] = 0)  then
      quickSort(poukladane,poczatki[i],konce[i]);

  for i:=1 to n do begin
    if spojne[i] = 0 then begin
      Inc(j);
      if dfs(i,j,false) then begin
        licznosci[j]:=0;
        Dec(j);
        dfs(i,1,true);
      end;
    end;
  end; 

  for i:=1 to j do
    krawedzie[i]:=licznosci[i];
  
  if j>1 then
    quickSort(krawedzie,1,j);

  WriteLn(j);
  for i:=1 to j do
    Write(krawedzie[i],' ');
  WriteLn;
end.


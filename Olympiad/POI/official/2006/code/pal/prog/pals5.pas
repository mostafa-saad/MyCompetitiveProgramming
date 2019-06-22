(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals5.pas                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywn polegajace na budowie  *
 *                        drzewa typu TRIE, do ktorego dodawane sa       *
 *                        palindromy w niemalejacym porzadku wzgledem    *
 *                        dlugosci, dla kazdego slowa tez za pomoca      *
 *                        algorytmy Manahera obliczane sa na poczatku    *
 *                        promienie palindromow, tak aby w miejscu gdzie *
 *                        napotkamy koniec innego krotszego palindromu   *
 *                        mozna bylo szybko odpowiedziec na pytanie czy  *
 *                        pozostaly fragment jest palindromem, zlozonosc *
 *                        O(n), gdzie n - suma dlugosci slow             *
 *                                                                       *
 *************************************************************************)

program Palindromy_s5;
const MAX=2000000;
const ALPHA=26;
type pWezel = ^Wezel;
     Wezel = record
              nast: array[0..ALPHA-1] of pWezel;
              czyKoniec: Boolean; {czy slowo sie konczy w tym miejscu}
             end;
     tablica = array[0..MAX] of LongInt;

var
    slowa,wczytywanie: array[0..MAX] of Char;
    poczatki,dlugosci,kolejnosc,pom,
    palNieparzyste,palParzyste:array[0..MAX] of LongInt;
    n,i,j, wynik,last: LongInt;
    root:PWezel;
    c:Char;

function palindrom(i,j:LongInt):Boolean;inline;
var dl:LongInt;
begin
  dl:=dlugosci[i];
  if Odd(dl-j) then
    palindrom:=palNieparzyste[j+((dl-j)shr 1)] >= (dl-j) shr 1
  else
    palindrom:=palParzyste[j+((dl-j) shr 1)] >= (dl-j) shr 1;
end;

function min(const a,b:LongInt):LongInt;inline;
begin
  if a>b then min:=b
  else min:=a;
end;

function maks(const a,b:LongInt):LongInt;inline;
begin
  if a<b then maks:=b
  else maks:=a;
end;

procedure posortuj;
var i,last,tmp:LongInt;
begin
  last:=0;
  for i:=0 to MAX-1 do pom[i]:=0;
  for i:=0 to n-1 do Inc(pom[dlugosci[i]]);
  for i:=0 to MAX-1 do begin
    tmp:=pom[i];
    pom[i]:=last;
    last:=last+tmp;
  end;
  for i:=0 to n-1 do begin
    kolejnosc[pom[dlugosci[i]]]:=i;
    Inc(pom[dlugosci[i]]);
  end;
end;

function stworz:PWezel;
var tmp:^WEZEL;
    i:LongInt;
begin
  tmp:= new(PWezel);
  for i:=0 to ALPHA-1 do tmp^.nast[i]:=nil;
  tmp^.czyKoniec:=false;
  stworz:=tmp;
end;

procedure Manacher(s,niep:LongInt; var r:tablica);
var n,i,j,k,x:LongInt;
begin
  n:=dlugosci[s]; i:=1; j:=0; x:=poczatki[s];
  for i:=0 to n-1 do r[n]:=0;
  i:=1;
  while i<n do begin
    while (i+j<=n) and (i-j>0) and (slowa[x+i-j-1]=slowa[x+i+j+niep]) do Inc(j);
    r[i]:=j;
    k:=1;
    while(r[i-k]<>r[i]-k) and ( k<=j) do begin
      r[i+k]:= min(r[i-k], r[i]-k);
      Inc(k);
    end;
    j:=maks(0,j-k);
    i:=k+i;
  end;
end;

procedure preprocess(k:LongInt);
var i,dl:LongInt;
begin
  dl:=dlugosci[k];
  for i:=0 to dl-1 do begin
    palNieparzyste[i]:=0;
    palParzyste[i]:=0;
  end;
  Manacher(k,0,palParzyste);
  Manacher(k,1,palNieparzyste);
end;

function dodaj(k:LongInt):LongInt;
var i,dl,akt,res:LongInt;
    wierzch:PWezel;
begin
  dl:=dlugosci[k];
  akt:=poczatki[k];
  wierzch:=root;
  res:=1;
  preprocess(k);
  for i:=akt to akt+dl-1 do begin
    if wierzch^.nast[byte(slowa[i])-byte('a')] = nil then
      wierzch^.nast[byte(slowa[i])-byte('a')]:= stworz();
    wierzch:= wierzch^.nast[byte(slowa[i])-byte('a')];
    if wierzch^.czyKoniec and palindrom(k,i-akt+1) then
        res:=res+2;
  end;
  wierzch^.czyKoniec:=true;
  dodaj:=res;
end;

begin
  root:=stworz;
  last:=0;
  ReadLn(n);
  for i:=0 to n-1 do begin
    poczatki[i]:=last;
    Read(dlugosci[i]);
    ReadLn(c,wczytywanie);
    for j:=0 to dlugosci[i] do
      slowa[last+j]:=wczytywanie[j];
    last:=last+dlugosci[i];
  end;
  posortuj();

  wynik:=0;
  for i:=0 to n-1 do begin
    wynik:=wynik+dodaj(kolejnosc[i]);
  end;

  WriteLn(wynik);
end.

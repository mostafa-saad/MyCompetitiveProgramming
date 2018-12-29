(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals9.pas                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywn polegajace na budowie  *
 *                        drzewa typu TRIE, do ktorego dodawane sa       *
 *                        palindromy w niemalejacym porzadku wzgledem    *
 *                        dlugosci, dla kazdego slowa tez za pomoca      *
 *                        funkcji prefiksowej z algorytmu KMP obliczane  *
 *                        sa wszystkie dlugosci sufiksow bedace takze    *
 *                        palindromami, zlozonosc                        *
 *                        O(n), gdzie n - suma dlugosci slow             *
 *                                                                       *
 *************************************************************************)

program Palindromy_s9;
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
    poczatki,dlugosci,kolejnosc,pom:tablica;
    palindromy: array[0..MAX] of Boolean;
    n,i,j, wynik,last: LongInt;
    root:PWezel;
    c:Char;

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

procedure preprocess(k:LongInt);
var i,q,dl,przes:LongInt;
begin
  {KMP prefix function part}
  pom[0]:=0; q:=0; dl:=dlugosci[k]; przes:=poczatki[k];
  for i:=1 to dl-1 do begin
    while (q>0) and (slowa[przes+i] <> slowa[przes+q]) do q:=pom[q-1];
    if slowa[przes+i] = slowa[przes+q] then Inc(q);
    pom[i]:=q;
  end;

  for i:=0 to dl-1 do palindromy[i]:=false;
  i:=pom[dl-1];
  palindromy[dl]:=true;
  palindromy[0]:=true;
  while i>0 do begin
    palindromy[i]:=true;
    i:=pom[i-1];
  end
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
    if wierzch^.czyKoniec and palindromy[dl+akt-1-i] then
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

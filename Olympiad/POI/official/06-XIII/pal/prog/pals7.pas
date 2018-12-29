(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals7.pas                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie optymalne polegajace na obliczaniu *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Nastepnie mozna posortowac te pierwiastki      *
 *                        pierwotne leksykograficznie i policzyc ile     *
 *                        jest tych samych, mozna tez jednak posortowac  *
 *                        je po dlugosci, a nastepnie dodawac je do      *
 *                        drzewa TRIE jednoczesnie je zliczajac zlozonos *
 *                        O(n), gdzie n - suma dlugosci slow             *
 *                        Jednak potrzebujace zbyt wiele pamieci         *
 *                                                                       *
 *************************************************************************)

program Palindromy_s7;
const MAX=2000000;
const ALPHA=26;
type pWezel = ^Wezel;
     Wezel = record
              nast: array[0..ALPHA-1] of pWezel;
              ileKoniec: LongInt; {ile slow sie konczy w tym miejscu}
             end;

var
    slowa,wczytywanie: array[0..MAX] of Char;
    poczatki,dlugosci,kolejnosc,pom,p:array[0..MAX] of LongInt;
    n,i,j, wynik,last: LongInt;
    root:PWezel;
    c:Char;

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

(*
 * funckja obliczajaca pierwiastek pierwotny danego slowa
 * wylicza tablice prefiksow, a nastepnie zgodnie z obserwacja
 * ze pierwiastek to n-p[n] jesli to dzieli n lub cale slowo
 *)
procedure pierwiastek(k:LongInt);
var i,q,dl,slowo:LongInt;
begin
  i:=1; q:=0; dl:=dlugosci[k]; slowo:=poczatki[k];
  p[0]:=0;
  while i<dl do begin
    while (q>0) and (slowa[slowo+i] <> slowa[slowo+q]) do q:=p[q-1];
    if (slowa[slowo+i] = slowa[slowo+q]) then Inc(q);
    p[i]:=q;
    Inc(i);
  end;
  if (dl mod (dl-p[dl-1]))=0 then
    dlugosci[k]:=dl-p[dl-1]
  else dlugosci[k]:=dl;
end;

function stworz:PWezel;
var tmp:^WEZEL;
    i:LongInt;
begin
  tmp:= new(PWezel);
  for i:=0 to ALPHA-1 do tmp^.nast[i]:=nil;
  stworz:=tmp;
end;

function dodaj(k:LongInt):LongInt;
var i,dl,akt:LongInt;
    wierzch:PWezel;
begin
  dl:=dlugosci[k];
  akt:=poczatki[k];
  wierzch:=root;
  for i:=akt to akt+dl-1 do begin
    if wierzch^.nast[byte(slowa[i])-byte('a')] = nil then
      wierzch^.nast[byte(slowa[i])-byte('a')]:= stworz();
    wierzch:= wierzch^.nast[byte(slowa[i])-byte('a')];
  end;
  Inc(wierzch^.ileKoniec);
  dodaj:=(wierzch^.ileKoniec shl 1)-1;
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
    pierwiastek(i);
  end;
  posortuj();

  wynik:=0;
  for i:=0 to n-1 do begin
    wynik:=wynik+dodaj(kolejnosc[i]);
  end;

  WriteLn(wynik);
end.

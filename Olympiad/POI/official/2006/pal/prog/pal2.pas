(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pal2.pas                                       *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie wzorcowe polegajace na obliczaniu  *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Nastepnie mozna posortowac te pierwiastki      *
 *                        pierwotne leksykograficznie, a nastepnie zlicz *
 *                        ile jest tych samych slow sortujac je          *
 *                        leksykograficznie zlozonosc O(n), gdzie        *
 *                        n - suma dlugosci slow                         *
 *                                                                       *
 *************************************************************************)

program Palindromy_2;
const MAX=2000000;
const ALPHA=26;
type
     tablica = array[0..MAX] of LongInt;
var
    slowa,wczytywanie: array[0..MAX] of Char;
    poczatki,dlugosci,p:array[0..MAX] of LongInt;
    kolejnosc:tablica;
    n,i,j, wynik,last: LongInt;
    c:Char;

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

(*
 * funkcja zwracajaca wartosc logiczna czy pierwiastek pierwotny
 * palindromu a jest mniejszy od pierwiastka pierwotnego palindromu b
 * w porzadku leksykograficznym
 *)
function porownaj(k,l:LongInt): LongInt ;
var dl,i,a,b:Longint;
  begin
    if dlugosci[k] < dlugosci[l] then  porownaj:=-1
    else if dlugosci[k] > dlugosci[l] then porownaj:= 1
    else begin
      dl:= dlugosci[k];
      a:=poczatki[k];
      b:=poczatki[l];
      i:=0;
      while (i<dl) and (slowa[a+i] = slowa[b+i]) do Inc(i);
      if i=dl then porownaj:=0
      else if slowa[a+i] < slowa[b+i] then porownaj:=-1
      else porownaj:=1;
    end
  end;


procedure sort(l,p:LongInt);
var pom,x,i,j:LongInt;
begin
  i:=l; j:=p;
  if l>=p then exit;
  x:=kolejnosc[(l+p) shr 1];
  repeat
    while porownaj(kolejnosc[i],x) = -1 do Inc(i);
    while porownaj(kolejnosc[j],x) = 1 do Dec(j);
    if i<=j then begin
      pom:= kolejnosc[i];
      kolejnosc[i]:= kolejnosc[j];
      kolejnosc[j]:= pom;
      Inc(i); Dec(j);
    end;
  until i>=j;
  sort(i,p);
  sort(l,j);
end;


(*
 * sortuje pierwiastki slow leksykograficznie
 *)
procedure posortuj;
  var i:LongInt;
begin
  for i:=0 to n-1 do kolejnosc[i]:=i;
  sort(0,n-1);
end;

function rowne(a,b:LongInt):Boolean;
var i,pa,pb:LongInt;

begin
  pa:=poczatki[a]; pb:=poczatki[b];
  if dlugosci[a] <> dlugosci[b] then rowne:=false
  else begin
    rowne:=true;
    for i:=0 to dlugosci[a]-1 do
      if slowa[pa+i] <> slowa[pb+i] then rowne:=false;
  end;
end;

begin
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

  last:=0;
  wynik:=n;
  for i:=1 to n-1 do
    if (rowne(kolejnosc[i-1],kolejnosc[i])) then begin
      Inc(last);
      wynik:=wynik+(last shl 1);
    end
    else last:=0;

  WriteLn(wynik);
end.

(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                sza.pas                                        *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Jêzyk: Pascal                                  *
 *                                                                       *
 *************************************************************************)
program sza;

const MAX=500000;

var s:array[1..MAX] of Char;
P, {tablica implementuj±ca funkcjê prefiksow±}
kand:array[1..MAX] of LongInt; {kandydaci na szablony}
ile_kand, {rozmiar tablicy kand}
len:LongInt; {d³ugo¶æ s³owa}
wyst:array[1..MAX] of Boolean; {tablica wyst±pieñ wzorca w s³owie, 
                                przydatna w KMP}
tmp:array[1..MAX] of LongInt;
ch:Char;

{Wg CLR "Wprowadzenie do algorytmów}
procedure prefiksosufiksy;
var m,q,k:LongInt;
begin
 m := len;
 P[1] := 0;
 k := 0;
 for q := 2 to m do
 begin
  while (k > 0) and (s[k + 1] <> s[q]) do
   k := P[k];
  if s[k + 1] = s[q] then
   Inc(k);
  P[q] := k
 end {for}
end; {prefiksosufiksy}

{Kandydaci na szablon to prefiksosufiksy naszego s³owa. Otrzymujemy
je poprzez iterowanie funkcji prefiksowej}
procedure licz_kandydatow;
var pref:LongInt;
begin
 ile_kand := 0;
 pref := len;
 while pref <> 0 do
 begin
  Inc(ile_kand);
  kand[ile_kand] := pref;
  pref := P[pref]
 end {while}
end; {licz_kandydatow} 

{Usuwanie z pewno¶ci± nieoptymalnych kandydatów na szablon}
procedure usun_zbednych;
var dlu,i:LongInt;
begin
 dlu := 0;
 for i := 1 to ile_kand - 1 do
  if 2 * kand[i + 1] < kand[i] then
  begin
   Inc(dlu);
   tmp[dlu] := kand[i]
  end; {if}
 Inc(dlu);
 tmp[dlu] := kand[ile_kand];

 ile_kand := dlu;
 for i := 1 to ile_kand do
  kand[i] := tmp[i]
end; {usun_zbednych}

{KMP, te¿ wed³ug CLR "Wprowadzenie do algorytmów"}
procedure kmp(m:LongInt);
var n,i,q:LongInt;
begin
 n := len;
 q := 0;
 for i := 1 to n do
  wyst[i] := false;
 for i := 1 to n do
 begin
  while (q > 0) and (s[q + 1] <> s[i]) do
   q := P[q];
  if s[q + 1] = s[i] then
   Inc(q);
  if q = m then
  begin
   wyst[i - m + 1] := true;
   q := P[q]
  end {if}
 end {for}
end; {kmp}   

{Sprawdzanie, czy kandydat na szablon - prefiks d³ugo¶ci x - jest
szablonem}
function szablon(x:LongInt):Boolean;
var i,ile:LongInt;
begin
 kmp(x);
 ile := 0;
 i := 0;
 repeat
  Inc(i);
  if (i <= len) and wyst[i] then
   ile := i + x - 1;
 until (i > len) or (i > ile);
 if i > len then
  szablon := true
 else
  szablon := false
end; {szablon}

{Znajdowanie najkrótszego szablonu}
function wynik:LongInt;
var i:LongInt;
begin
 i := ile_kand;
 while not szablon(kand[i]) do
  Dec(i);
 wynik := kand[i];
end; {wynik}

procedure odczyt;
begin
 len := 0;
 while not Eoln(input) do
 begin
  Read(ch);
  Inc(len);
  s[len] := ch;
 end {while}
end; {odczyt}

begin
 odczyt;
 prefiksosufiksy;
 licz_kandydatow;
 usun_zbednych;
 WriteLn(wynik)
end. {program}

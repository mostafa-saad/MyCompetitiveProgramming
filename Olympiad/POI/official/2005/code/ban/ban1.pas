(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban1.pas                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie wzorcowe do zadania BAN (Banknoty) *
 *                        Jêzyk: Pascal                                  *
 *                                                                       *
 *************************************************************************)

const MAX_N = 200;
const MAX_K = 20000;
const NIESKONCZONOSC = 1000000000;

{Element listy wska¼nikowej}
type pElement=^Element;
Element =
record
  w : LongInt; {warto¶æ}
  nast,pop : pElement; {wska¼niki do poprzedniego i kolejnego elementu listy}
end;

var
  n,k,i : LongInt;
  b,c   : array[1..MAX_N] of LongInt;
  R     : array[0..MAX_K] of LongInt; {R[x] to minimalna liczba banknotów, w
                  jakiej mo¿na wyp³aciæ kwotê x przy pomocy dotychczas
                  rozwa¿onych nomina³ów}
  M     : array[0..MAX_K] of LongInt; {Tablica pomocniczna zdefiniowana poprzez
                   M[i]=R[r + i*b[nr]] - i dla tablicy R przed uaktualnieniem}
  wyn   : array[0..MAX_K,1..MAX_N] of LongInt; {Tablica wskazuj±ca dla ka¿dej
                                 kwoty i dla
                                 ka¿dego banknotu, ile sztuk tego banknotu
                                 zosta³o u¿yte w optymalnym otrzymaniu kwoty}

{Odczyt danych}
procedure odczyt;
var i : LongInt;
begin
  ReadLn(n);
  for i := 1 to n do
    Read(b[i]);
  for i := 1 to n do
    Read(c[i]);
  Read(k);
end; {odczyt}

{Inicjalizacja tablic R i wyn}
procedure inicjuj;
var i,j : LongInt;
begin
  R[0] := 0;
  for i := 1 to k do
    R[i] := NIESKONCZONOSC;
  for i := 1 to k do
    for j := 1 to n do
      wyn[i][j] := 0;
end; {inicjuj}

{Aktualizuje tablicê R, analizuj±c kolejny nomina³ banknotów (o numerze nr)}
procedure aktualizuj(nr : LongInt);
var x,i : LongInt;
head,tail,tmp : ^Element;
begin
  for x := 0 to b[nr] - 1 do {r-kolejna reszta modulo nomina³ b[nr]}
  begin
    head := nil;
    tail := nil;
    i := 0;
    while x + i*b[nr] <= k do
    begin
      if R[x + i*b[nr]] = NIESKONCZONOSC then
        M[i] := NIESKONCZONOSC
      else
        M[i] := R[x + i*b[nr]] - i;
      while (tail <> nil) and (M[tail^.w] >= M[i]) do
      begin
        {usuniêcie ostatniego elementu z kolejki}
        tmp := tail^.pop;
        Dispose(tail);
        tail := tmp;
        if tail = nil then
          head := nil
        else
          tail^.nast := nil;          
      end; {while}
      
      {w³o¿enie liczby i na koniec kolejki}
      New(tmp);
      tmp^.w := i;
      tmp^.nast  := nil;
      tmp^.pop   := tail;
      if tail <> nil then
        tail^.nast := tmp;
      tail := tmp;
      if head = nil then
        head := tail;
      
      R[x + i*b[nr]] := M[head^.w] + i;
      wyn[x + i*b[nr],nr] := i - head^.w;
      if head^.w = i - c[nr] then
      begin
        {usuniêcie pierwszego elementu z kolejki}
        tmp := head^.nast;
        Dispose(head);
        head := tmp;
        if head = nil then
          tail := nil
        else
          head^.pop := nil;
      end; {if}
      Inc(i);
    end; {while}
  end; {for}
end; {aktualizuj}

procedure pisz(n,k : LongInt);
begin
  if n>1 then
    pisz(n - 1,k - wyn[k,n]*b[n]);
  if n = 1 then
    Write(wyn[k][n])
  else
    Write(' ',wyn[k][n]);
end; {pisz}

begin
  odczyt;
  inicjuj;
  for i := 1 to n do
    aktualizuj(i);
  WriteLn(R[k]);
  pisz(n,k);
  WriteLn;
end. {program}

(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     pers2.pas                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie o zlozonosci O(n^3lgm).                       *
 *                                                                       *
 *************************************************************************)

Program permutacja;

const MAX_N=300000;
      MAX_P=28001;

type para = record
    first,second:longint;
         end;
     tab  = array [0..10] of longint;


var n,m:longint;        {liczby z tresci zadania}
    T:array [0..MAX_N] of longint;    {permutacja z zadania}
    najw:longint;        {najwiekszy element w permutacji}
    ilosc:array [1..300001] of longint;    {drzewo licznikowe}
    il:longint;          {ilosc liczb pierwszych}
    nr:array [0..MAX_N] of longint;    {tablica z numerami kolejnych liczb pierwszych}
    rozklad:array [0..MAX_N] of longint;  {tablica umozliwiajaca szybki rozklad na czynniki pierwsze}
    pierw:array [0..MAX_P] of longint;    {ilosc liczb pierwszych w rozkladzie Si}
    L:array [0..MAX_P] of longint;    {kolejne liczby pierwsze}
    res:longint;        {wynik dzialania programu}
    i:longint;          {zmienna pomocnicza}



{fukcja wykonujaca szybkie potegowanie
 dostajac na wejsciu x,n,m zwraca x^n mod m}
function potega(x,n,m:longint):int64;
  var res,akt,mm:int64;
begin
  res:=1;akt:=int64(x);
  mm:=int64(m);
  while (n>0) do begin
    if ((n mod 2)=1) then begin
      res:=(res*akt) mod mm;
      dec(n);
    end;
    akt:=(akt*akt) mod mm;
    n:=n div 2;
  end;
  potega:=res;
end;


{sito eratostenesa umozliwiajace pozniej
 szybki rozklad kazdej liczby na czynniki pierwsze
 oraz numerujaca kolejne liczby pierwsze z zakresu [2..roz]}
procedure sito_eratostenesa(roz:longint);
  var Q:array [0..MAX_N] of boolean;
      i,j:longint;
begin
  il:=0;
  for i:=0 to roz do begin
    nr[i]:=-1;
    rozklad[i]:=-1;
    Q[i]:=true;
  end;

  for i:=2 to roz do
    if (Q[i]) then begin
      L[il]:=i;
      nr[i]:=il;
      inc(il);
      rozklad[i]:=i;
      j:=2*i;
      while (j<=roz) do begin
        Q[j]:=false;
        if (rozklad[j]=-1) then
          rozklad[j]:=i;
        inc(j,i);
      end;
    end;
end;


{trzy funkcje do obslugi reprezentacji liczb w postaci
 rozkladu na liczby pierwsze
 0) zerowanie rozk³adu
 1) obliczanie wartosci danej liczby modulo m
 2) mnozenie danej liczby przez longint
 3) dzielenie danej liczby przez longint    }
procedure zeruj;
  var i:longint;
begin
  for i:=0 to il-1 do
    pierw[i]:=0;
end;


function wartosc:longint;
  var res,mm:int64;
      i:longint;
begin
  res:=1;mm:=int64(m);
  for i:=0 to il-1 do
    res:=(res*(int64(potega(L[i],pierw[i],m)))) mod mm;
  wartosc:=longint(res);
end;


procedure pomnoz(x:longint);
begin
  while (x<>1) do begin
    inc(pierw[nr[rozklad[x]]]);
    x:=x div rozklad[x];
  end;
end;


procedure podziel(x:longint);
begin
  while (x<>1) do begin
    dec(pierw[nr[rozklad[x]]]);
    x:=x div rozklad[x];
  end;
end;


{funkcja obliczajaca wynik - po dokladny sposob dzialania
 odsylam do opracowania  - rozwiazanie wolniejsze    }
function oblicz_wynik:longint;
  var i,j,k,s:longint;
      res:int64;
begin
  res:=1;

  for s:=0 to n-2 do begin
    for i:=1 to T[s]-1 do
      if (ilosc[i]>0) then begin
        zeruj;
        for j:=2 to n-s-1 do
          pomnoz(j);
        for j:=1 to najw do
          for k:=2 to ilosc[j] do
            podziel(k);
        pomnoz(ilosc[i]);

        res:=(res+(int64(wartosc))) mod (int64(m));
      end;
    dec(ilosc[T[s]]);
  end;

  oblicz_wynik:=longint(res);
end;


begin
  readln(n,m);
  for i:=0 to n-1 do
    read(T[i]);

  najw:=0;
  for i:=0 to n-1 do
    if (T[i]>najw) then
      najw:=T[i];
  for i:=0 to n do
    inc(ilosc[T[i]]);
  sito_eratostenesa(n);

  res:=oblicz_wynik;
  writeln(res);
end.

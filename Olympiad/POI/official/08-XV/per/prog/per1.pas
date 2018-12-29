(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per1.pas                                                  *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie o zlozonosci O(z+n(lgz+lgm)+(lgm)^2).         *
 *                                                                       *
 *************************************************************************)

Program permutacja;

const MAX_N=300000;

type para = record
    first,second:longint;
         end;
     tab  = array [0..10] of longint;


var n,m:longint;        {liczby z tresci zadania}
    T:array [0..MAX_N] of longint;    {permutacja z zadania}
    najw:longint;        {najwiekszy element w permutacji}
    h:longint;          {wysokosc drzewa licznikowego}
    przes:longint;        {numer najbardziej lewewgo liscia}
    ilosc:array [1..1048601] of longint;  {drzewo licznikowe}
    pod,wyk,dziel:tab;        {m=pod[0]^wyk[0]*...,dziel[i]=pod[i]^wyk[i]}
    s:longint;          {ilosc roznych liczb pierwszych dzielacych m}
    res:longint;        {wynik dzialania programu}
    i:longint;          {zmienna pomocnicza}



{rozszerzony algorytm Euklidesa - dostajac na wejsciu liczby a i b
 zwraca trojke liczb takich ze a*x+b*y=NWD(x,y)         }
procedure NWD(a,b:longint; var x,y:int64; var d:longint);
  var x1,y1:int64;
      d1:longint;
begin
  if (b=0) then begin
    x:=1; y:=0;
    d:=a;
  end else begin
    NWD(b,a mod b,x1,y1,d1);
    x:=y1;
    y:=x1-y1*(int64(a div b));
    d:=d1;
  end;
end;


{funkcja obliczajaca odwrotnosc pewnej liczby s modulo t
 na wejsciu musi byc spelniony warunek NWD(s,t)=1        }
function odwrotnosc(s,t:longint):longint;
  var x,y:int64;
      w:longint;
begin
  NWD(s,t,x,y,w);
  w:=longint(x mod (int64(t)));
  odwrotnosc:=(w+t) mod t;
end;


{funkcja ktora buduje pelne statyczne drzewo licznikowe
 najw - najwiekszy element permutacji T
 h    - wysokosc drzewa licznikowego                    }
procedure buduj_drzewo;
  var i,pom:longint;
begin
  najw:=0;
  for i:=0 to n-1 do
    if (T[i]>najw) then
      najw:=T[i];

  {aby wygodnie korzystalo sie z drzewa
   potrzebujemy aby mialo ono canajmniej najw+1 lisci
   ktore kolejno odpowiadaja wartoscia 0,1,..,najw   }
  h:=0;pom:=1;
  while (pom<najw+1) do begin
    h:=h+1;
    pom:=2*pom;
  end;

  {teraz liscie drzewa maja numery w tablicy 2^h,..,2^(h+1)-1}
  for i:=0 to n-1 do
    inc(ilosc[pom+T[i]]);
  for i:=pom-1 downto 1 do
    ilosc[i]:=ilosc[2*i]+ilosc[2*i+1];
  przes:=pom;
end;


{funkcja modyfikujaca drzewo licznikowe
 wstaw(x,ile) zmienia ilosc elementow x o ile}
procedure wstaw(x,ile:longint);
  var i:longint;
begin
  i:=przes+x;
  ilosc[i]:=ilosc[i]+ile;
  i:=i div 2;
  while (i>0) do begin
    ilosc[i]:=ilosc[2*i]+ilosc[2*i+1];
    i:=i div 2;
  end;
end;


{funkcja zwracajaca ilosc elementow mniejszych od x}
function mniejsze(x:longint):longint;
  var i,res:longint;
begin
  i:=przes+x;
  res:=0;
  while (i>1) do begin
    if ((i mod 2)=1) then
      res:=res+ilosc[i-1];
    i:=i div 2;
  end;
  mniejsze:=res;
end;


{funkcja rozkladajaca m na czynniki pierwsze
 po wywolaniu tej funkcji mamy:
 m=pod[0]^wyk[0]*... = dziel[0]*dziel[1]*... }
procedure rozklad_m;
  var i,mm:longint;
      il,t:longint;
begin
  mm:=m;
  s:=0;i:=2;
  while (i*i<=m) do begin
    if ((mm mod i)=0) then begin
      il:=0;t:=1;
      while ((mm mod i)=0) do begin
        mm:=mm div i;
        inc(il);
        t:=t*i;
      end;
      pod[s]:=i;
      wyk[s]:=il;
      dziel[s]:=t;
      inc(s);
    end;
    inc(i);
  end;
  if (mm>1) then begin
    pod[s]:=mm;
    wyk[s]:=1;
    dziel[s]:=mm;
    inc(s);
  end;
end;


{fukcja wykonujaca szybkie potegowanie
 dostajac na wejsciu x,n,m zwraca x^n mod m}
function potega(x,n,m:longint):longint;
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
  potega:=longint(res);
end;


{trzy funkcje do obslugi naszej reprezentacji liczb
 gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
 1) funkcja zwracajaca wartosc modulo dziel[nr]
 2) funkcja mnozaca liczbe w naszej reprezentacji przez longint
 3) funkcja dzielaca liczbe w naszej reprezentacji przez longint }

function wartosc(x:para; nr:longint):longint;
  var p,q:int64;
begin
  if (x.second>=wyk[nr]) then
     wartosc:=0
  else begin
    p:=int64(potega(pod[nr],x.second,dziel[nr]));
    q:=int64(x.first);
    wartosc:=longint((p*q) mod (int64(dziel[nr])));
  end;
end;


function pomnoz(w:para; x,nr:longint):para;
  var p:longint;
begin
  p:=pod[nr];
  while ((x mod p)=0) do begin
    inc(w.second);
    x:=x div p;
  end;
  w.first:=longint(((int64(w.first))*(int64(x))) mod (int64(dziel[nr])));
  pomnoz:=w;
end;


function podziel(w:para; x,nr:longint):para;
  var p:longint;
begin
  p:=pod[nr];
  while ((x mod p)=0) do begin
    dec(w.second);
    x:=x div p;
  end;
  w.first:=longint(((int64(w.first))*(int64(odwrotnosc(x,dziel[nr])))) mod (int64(dziel[nr])));
  podziel:=w;
end;


{fukcja obliczajaca S0 i zwracajaca wynik w naszej reprezentacji
 gdzie liczba pierwsza dla tej reprezentacji jest pod[nr]
 oraz S0=(n-1)!/[l1!*...*lnajw!]                                 }
function oblicz_S0(nr:longint):para;
  var res:para;
      i,j:longint;
begin
  res.first:=1;res.second:=0;
  for i:=2 to n-1 do
    res:=pomnoz(res,i,nr);

  for i:=1 to najw do
    for j:=2 to ilosc[przes+i] do
      res:=podziel(res,j,nr);

  oblicz_S0:=res;
end;


{funkcja skladajaca wynik z chinskiego twierdzenia o resztach
 dane wejsciowe reprezentuja: m=dziel[0]*..*dziel[s-1]
 ponadto wynik = a[i] (modulo dziel[i]            }
function chinskie_twierdzenie(s:longint; a:tab):longint;
  var c,w:tab;
      i:longint;
      res:int64;
begin
  for i:=0 to s-1 do begin
    w[i]:=m div dziel[i];
    c[i]:=longint((int64(w[i]))*(int64(odwrotnosc(w[i],dziel[i]))));
  end;

  res:=0;
  for i:=0 to s-1 do
    res:=res+(int64((int64(a[i]))*(int64(c[i]))));
  res:=res mod (int64(m));
  chinskie_twierdzenie:=longint(res);
end;


{funkcja obliczajaca wynik - po dokladny sposob dzialania
 odsylam do opracowania            }
function oblicz_wynik:longint;
  var temp:array [0..10] of para;
      a:tab;
      ile,i,j:longint;
begin
  ile:=mniejsze(T[0]);
  for i:=0 to s-1 do begin
    temp[i]:=oblicz_S0(i);
    a[i]:=0;

    if (ile<>0) then begin
      a[i]:=wartosc(temp[i],i);
      a[i]:=longint(((int64(a[i]))*(int64(ile))) mod (int64(dziel[i])));
    end;
  end;

  for i:=1 to n-2 do begin
    for j:=0 to s-1 do begin
      temp[j]:=pomnoz(temp[j],ilosc[przes+T[i-1]],j);
      temp[j]:=podziel(temp[j],n-i,j);
    end;

    wstaw(T[i-1],-1);
    ile:=mniejsze(T[i]);
    if (ile=0) then
      continue;

    for j:=0 to s-1 do begin
      temp[j]:=pomnoz(temp[j],ile,j);
      a[j]:=(a[j]+wartosc(temp[j],j)) mod dziel[j];
      temp[j]:=podziel(temp[j],ile,j);
    end;
  end;

  oblicz_wynik:=(chinskie_twierdzenie(s,a)+1) mod m;
end;


begin
  readln(n,m);
  for i:=0 to n-1 do
    read(T[i]);

  buduj_drzewo;
  rozklad_m;

  res:=oblicz_wynik;
  writeln(res);
end.

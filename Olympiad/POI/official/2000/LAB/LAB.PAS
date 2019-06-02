{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: LABIRYNT STUDNI                                *}
{*   Plik:                LAB.PAS                                        *}
{*   Autor:               Krzysztof Sobusiak                             *}
{*************************************************************************}

program LabiryntStudni;

const MAXN = 6000;
      ID = 'lab';

type PElem = ^TElem; { listy liczb caˆkowitych }
     TElem = record
               l : Word;
               nast : PElem
             end;
     TKolejka = record { kolejki liczb caˆkowitych }
                  pocz,kon : PElem
                end;
     TListy = array [0..MAXN] of PElem; { tablica list }
     TKolejki = array [1..MAXN] of TKolejka; { tablica kolejek }
var V : array [1..MAXN] of record { komnaty }
                             kolor : Byte; { kolor }
                             numer : Word; { numeracja u¾ywana do sortowania }
                             Dol : array [1..3] of Word { korytarze }
                           end;
    Gora : ^TListy; { korytarze wstecz }
    Warstwy : ^TListy; { warstwy komnat }
    Kubly : ^TKolejki; { kubeˆki do sortowania leksykograficznego }
    n : Word;

procedure Wstaw(var L : PElem;
                i     : Word);
{ wstawia liczbe $i$ na pocz¥tek listy $L$ }
var P : PElem;
begin
  New(P);
  P^.l:=i;
  P^.nast:=L;
  L:=P
end;

procedure Przerzuc(var K : TKolejka;
                   var L : PElem);
{ przerzuca pierwszy element listy $L$ na koniec kolejki $K$ }
begin
  if K.kon=nil then
    K.pocz:=L
  else
    K.kon^.nast:=L;
  K.kon:=L;
  L:=L^.nast;
  K.kon^.nast:=nil
end;

procedure Doklej(var K : TKolejka;
                 var L : TKolejka);
{ dokleja kolejk© $L$ na koniec kolejki $K$ }
begin
  if K.pocz=nil then
    K.pocz:=L.pocz
  else
    K.kon^.nast:=L.pocz;
  K.kon:=L.kon;
  L.pocz:=nil; L.kon:=nil
end;

procedure WczytajDane(var F : Text);
{ wczytuje dane, tworz¥c korytarze w prz¢d i wstecz }
var i,j : Word;
    c : Char;
begin
  Readln(F,n);
  for i:=1 to n do
    Gora^[i]:=nil;
  for i:=1 to n-1 do
    with V[i] do begin
      Read(F,c);
      case c of
        'C' : kolor:=1;
        'Z' : kolor:=2;
        'N' : kolor:=3
      end;
      for j:=1 to 3 do begin
        Read(F,Dol[j]);
        Wstaw(Gora^[Dol[j]],i)
      end;
      Readln(F)
    end
end;

function WyznaczWarstwy : Word;
{ wyznacza warstwy komnat, zwraca liczb© warstw }
var i,gleb : Word;
    P,Q : PElem;
    T : array [0..MAXN] of Byte; { liczby nieodwiedzonych korytarzy }
                                 { dla ka¾dej z komnat }
begin
  for i:=0 to n do begin
    Warstwy^[i]:=nil;
    T[i]:=3
  end;
  Wstaw(Warstwy^[0],n);
  gleb:=0; { gˆ©boko˜† aktualnie przetwarzanej warstwy }
  while Warstwy^[gleb]<>nil do begin
    P:=Warstwy^[gleb];
    while P<>nil do begin { przejd« wszystkie komnaty warstwy }
      i:=P^.l;
      Q:=Gora^[i];
      while Q<>nil do begin { przejd« wstecz wszystkie korytarze
                              z danej komnaty }
        Dec(T[Q^.l]); { odwied« korytarz }
        if T[Q^.l]=0 then
          Wstaw(Warstwy^[gleb+1],Q^.l); { komnata do kt¢rej prowadzi }
                                        { nale¾y do nast©pnej warstwy }
        Q:=Q^.nast
      end;
      P:=P^.nast
    end;
    Inc(gleb)
  end;
  WyznaczWarstwy:=gleb-1
end;

function ScalKubly(maxnum : Word) : PElem;
{ scala kolejki z kubeˆk¢w o numerach [1..maxnum] }
var K : TKolejka;
    i : Word;
begin
  K.pocz:=nil; K.kon:=nil;
  for i:=1 to maxnum do
    if Kubly^[i].pocz<>nil then
      Doklej(K,Kubly^[i]);
  ScalKubly:=K.pocz
end;

function CzyZgodne(a,b : Word) : Boolean;
{ sprawdza, czy komnata $a$ odpowiada komnacie $b$ }
var j : Word;
begin
  CzyZgodne:=False;
  if V[a].kolor<>V[b].kolor { musz¥ mie† ten sam kolor }
    then Exit;
  for j:=1 to 3 do { korytarze musz¥ prowadzi† do tych samych komnat }
    if V[a].Dol[j]<>V[b].Dol[j]
      then Exit;
  CzyZgodne:=True
end;

procedure LikwidujKomnate(a,b : Word);
{ przekierunkowuje do komnaty $a$ korytarze prowadz¥ce do komnaty $b$ }
var P : PElem;
    j : Word;
begin
  P:=Gora^[b];
  while P<>nil do begin
    with V[P^.l] do
      for j:=1 to 3 do
        if Dol[j]=b then
          Dol[j]:=a;
    P:=P^.nast
  end
end;

function DolaczWarstwe(W : PElem) : Word;
{ przetwarza kolejn¥ warstw© komnat,
{ zwraca liczb© r¢¾nych komnat danej warstwy }
var num,ile,i,j,a,b : Word;
    P,Q : PElem;
begin
  num:=0;
  P:=W;
  while P<>nil do begin { ponumeruj wszystkie komnaty, do kt¢rych prowadz¥ }
                        { korytarze z komnat danej warstwy }
    for j:=1 to 3 do
      with V[V[P^.l].Dol[j]] do
        if numer=0 then begin
          Inc(num);
          numer:=num
        end;
    P:=P^.nast
  end;
  for j:=3 downto 1 do begin { sortuj leksykograficznie po numerach komnat
                               do kt¢rych prowadz¥ korytarze
                               z komnat danej warstwy }
    while W<>nil do
      Przerzuc(Kubly^[V[V[W^.l].Dol[j]].numer],W);
    W:=ScalKubly(num)
  end;
  while W<>nil do { sortuj jeszcze po kolorach }
    Przerzuc(Kubly^[V[W^.l].kolor],W);
  W:=ScalKubly(3);
  P:=W; Q:=P^.nast;
  ile:=1; { liczba r¢¾nych komnat warstwy }
  while Q<>nil do begin { przejd« posortowan¥ list© }
    a:=P^.l; b:=Q^.l; { komnaty zgodne le¾¥ obok siebie }
    if CzyZgodne(a,b) then
      LikwidujKomnate(a,b)
    else begin { komnata istotnie r¢¾na od dotychczasowych }
      Inc(ile);
      P:=Q;
    end;
    Q:=Q^.nast
  end;
  P:=W;
  while P<>nil do begin { likwiduj numeracj© }
    for j:=1 to 3 do
      V[V[P^.l].Dol[j]].numer:=0;
    P:=P^.nast
  end;
  DolaczWarstwe:=ile
end;

var F : Text;
    maxgleb,ile,i : Word;
    ilekublowpotrzeba: Word;
begin
  New(Gora); New(Warstwy); New(Kubly);
  Assign(F,ID+'.in');
  Reset(F);
  WczytajDane(F);
  Close(F);
  maxgleb:=WyznaczWarstwy;
  for i:=1 to n do
    V[i].numer:=0;
  if n > 3 then
    ilekublowpotrzeba := n
  else
    ilekublowpotrzeba := 3;
  for i:=1 to ilekublowpotrzeba do begin
    Kubly^[i].pocz:=nil;
    Kubly^[i].kon:=nil
  end;
  ile:=1;
  for i:=1 to maxgleb do { przetwarzaj kolejne warstwy
                           zaczynaj¥c od najgˆ©bszej }
    Inc(ile,DolaczWarstwe(Warstwy^[i]));
  Assign(F,ID+'.out');
  Rewrite(F);
  Writeln(F,ile);
  Close(F)
end.

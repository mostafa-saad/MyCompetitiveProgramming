{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: WIRUSY                                         *}
{*   Plik:                WIR.PAS                                        *}
{*   Autor:               PIOTR SANKOWSKI                                *}
{*************************************************************************}



{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q-,R-,S+,T-,V+,X+,Y+}
{$M 16384,0,655360}
const
  max=30000;

type
  tablicaIntPtr=^tablicaInt;
  tablicaInt=array[1..max+1]of integer;
  tablicaBoolPtr=^tablicaBool;
  tablicaBool=array[1..max]of boolean;
  tablicaBytePtr=^tablicaByte;
  tablicaByte=array[1..max]of byte;

var
  poczatki:tablicaIntPtr;
  sigma:array[0..1]of tablicaIntPtr;
  syn:array[0..1]of tablicaIntPtr;
  slowa:tablicaBytePtr;
  akceptujacy:tablicaBoolPtr;
  ileStanow:integer;
  ileSlow:integer;
  dlugoscWczytanych:integer;

type
  kolejka=object
    poczatek:integer;
    koniec:integer;
    elementy:tablicaIntPtr;
    constructor init;
    procedure wstaw(nr:integer);
    procedure wyjmij(var nr:integer);
    function pusta:boolean;
    destructor done;
  end;

  stos=object(kolejka)
    procedure wyjmij(var nr:integer);
  end;

constructor kolejka.init;
begin
  poczatek:=1;
  koniec:=1;
  new(elementy);
end;

destructor kolejka.done;
begin
  dispose(elementy);
end;

procedure kolejka.wstaw;
begin
  elementy^[koniec]:=nr;
  koniec:=koniec mod max + 1;
end;

procedure kolejka.wyjmij;
begin
  nr:=elementy^[poczatek];
  poczatek:=poczatek mod max + 1;
end;

procedure stos.wyjmij;
begin
  koniec:=(koniec+max-2)mod max+1;
  nr:=elementy^[koniec];
end;

function kolejka.pusta;
begin
  if poczatek = koniec then pusta:=true
                       else pusta:=false;
end;

procedure WczytajDane;
var
  i:integer;
  ch:char;
begin
  assign(Input,'wir.in');
  reset(Input);
  readln(ileSlow);
  dlugoscWczytanych:=0;

  for i:=1 to ileSlow do
  begin
    poczatki^[i]:=dlugoscWczytanych+1;
    while not eoln do
    begin
      inc(dlugoscWczytanych);
      read(ch);
      if ch='0' then slowa^[dlugoscWczytanych]:=0
                else slowa^[dlugoscWczytanych]:=1;
    end;
    readln;
  end;
  poczatki^[i+1]:=dlugoscWczytanych+1;
  close(Input);
end;

procedure KonstruujDrzewo;
var
  i,j,stan:integer;
begin
  ileStanow:=1;
  for i:=1 to ileSlow do
  begin
    stan:=1;
    for j:=poczatki^[i] to poczatki^[i+1]-1 do
    begin
      if syn[slowa^[j]]^[stan]=0 then
      begin
        inc(ileStanow);
        syn[slowa^[j]]^[stan]:=ileStanow;
      end;
      stan:=syn[slowa^[j]]^[stan];
    end;
    akceptujacy^[stan]:=true;
  end;
end;

procedure KonstruujAutomat;
var
  i,ii,stan,temp:integer;
  aktywneStany:kolejka;
begin
  aktywneStany.init;
  aktywneStany.wstaw(1);
  sigma[0]^[1]:=1;
  sigma[1]^[1]:=1;
  while not aktywneStany.pusta do
  begin
    aktywneStany.wyjmij(stan);
    for i:=0 to 1 do
      if syn[i]^[stan]<>0 then
      begin
        temp:=sigma[i]^[stan];
        sigma[i]^[stan]:=syn[i]^[stan];
        if akceptujacy^[temp] then akceptujacy^[syn[i]^[stan]]:=true;
        for ii:=0 to 1 do
        if syn[ii]^[temp]<>0 then sigma[ii]^[syn[i]^[stan]]:=syn[ii]^[temp]
                             else sigma[ii]^[syn[i]^[stan]]:=sigma[ii]^[temp];
        aktywneStany.wstaw(syn[i]^[stan]);
      end;
  end;
  aktywneStany.done;
end;

function szukajCyklu:boolean;
var
  odwiedzony:tablicaBoolPtr;
  synowie:tablicaIntPtr;
  stosStanow:stos;
  stan,i,syn:integer;
begin
  new(odwiedzony);
  new(synowie);
  fillchar(synowie^,sizeof(synowie^),0);
  fillchar(odwiedzony^,sizeof(odwiedzony^),0);
  stosStanow.init;
  stosStanow.wstaw(1);
  szukajCyklu:=false;
  while not stosStanow.pusta do
  begin
    stosStanow.wyjmij(stan);
    if synowie^[stan]>1 then odwiedzony^[stan]:=false
    else
    begin
      odwiedzony^[stan]:=true;
      stosStanow.wstaw(stan);
      syn:=synowie^[stan];
      inc(synowie^[stan]);
      if (not akceptujacy^[sigma[syn]^[stan]]) then
      begin
        if odwiedzony^[sigma[syn]^[stan]] then
        begin
          szukajCyklu:=true;
          break;
        end
        else stosStanow.wstaw(sigma[syn]^[stan]);
      end;
    end;
  end;
  stosStanow.done;
  dispose(odwiedzony);
end;

begin
  new(slowa);
  new(poczatki);

  WczytajDane;

  new(akceptujacy);
  new(syn[0]);
  new(syn[1]);
  fillchar(syn[0]^,sizeof(syn[0]^),0);
  fillchar(syn[1]^,sizeof(syn[1]^),0);
  fillchar(akceptujacy^,sizeof(akceptujacy^),0);

  KonstruujDrzewo;

  dispose(slowa);
  dispose(poczatki);

  new(sigma[0]);
  new(sigma[1]);
  fillchar(sigma[0]^,sizeof(sigma[0]^),0);
  fillchar(sigma[1]^,sizeof(sigma[1]^),0);

  KonstruujAutomat;
  dispose(syn[0]);
  dispose(syn[1]);
  assign(OutPut,'wir.out');
  rewrite(OutPut);
  if szukajCyklu then writeln('TAK')
                 else writeln('NIE');
  close(OutPut);
end.

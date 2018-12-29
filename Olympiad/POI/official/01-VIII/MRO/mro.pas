{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: MRÓWKI I BIEDRONKA                             *}
{*   Plik:                MRO.PAS                                        *}
{*   Autor:               TOMASZ WALEÑ                                   *}
{*************************************************************************}

{$M 65000,0,655360}
program mrowka;
const
   maxn = 5000;
   maxm = 1000;

   f_in  = 'mro.in';
   f_out = 'mro.out';
type
   plist = ^tlist;
   tlist = record
              v : integer;
              n : plist;
           end;
var
   f : text;
   n : integer; {liczba lisci i rozga³êzieñ w drzewie}
   m : integer; {liczba mrowek}
   l : integer; {liczba ladowan biedronki}

   d  : array[1..maxn] of plist; {drzewo jako lista sasiedztwa}
   dd : array[1..maxn] of integer; {to samo drzewo, jako tablica wskaznikow na
                                    przodka w drzewie (0 dla korzenia)}
   p : array[1..maxm] of integer; {pozycja mrówek}
   z : array[1..maxn] of integer; {zaznaczenie jakie wierzcholki w drzewie
                                   sa zajete przez mrowki (jesli>0) to
                                   jest podany numer mrowki}
   ile : array[1..maxm] of integer; {ile razy mrowka przegonika biedronke}
   biedronka : integer;

procedure DodajKrawedz(var lista : plist;v:integer);
var
   tmp : plist;
begin
   new(tmp);
   tmp^.v:=v;
   tmp^.n:=lista;
   lista:=tmp;
end;

procedure WczytajDrzewo;
var
   i   : integer;
   a,b : integer;
begin
   Assign(f,f_in);
   reset(f);
   readln(f,n);

   for i:=1 to n do d[i]:=nil;

   for i:=1 to n-1 do begin
      readln(f,a,b);
      DodajKrawedz(d[a],b);
      DodajKrawedz(d[b],a);
   end;
   readln(f,m);
   for i:=1 to m do Readln(f,p[i]);
end; { WczytajDrzewo }

procedure dfs(v : integer;poprz:integer);
var
   lista : plist;
begin
   dd[v]:=poprz;
   lista:=d[v];
   while (lista<>nil) do
   begin
      if (lista^.v<>poprz) then dfs(lista^.v,v);
      lista:=lista^.n;
   end;
end;

procedure PrzygotujDrzewo(korzen : integer);
begin
   dfs(korzen,0);
end; { PrzygotujDrzewo }


procedure SymulujPogon;
var
   mrowki    : array[1..maxm] of integer;
   pozycja   : array[1..maxm] of integer;
   drzewo    : array[1..maxn,1..2] of integer;
   droga     : array[1..maxm] of integer;
   spotkania : array[1..maxm] of integer;
   kolejnosc : array[1..maxm] of integer;

   i,j : integer;
   nr        : integer;
   p0,p1     : integer;
   tmp       : integer;

   procedure PoprawDroge(v : integer);
   var
      s : integer;
   begin
      kolejnosc[v]:=1;
      s:=spotkania[v];
      if (s>0) then begin
         if (kolejnosc[s]=0) then PoprawDroge(s);
         if (droga[s]<droga[v]) then droga[v]:=droga[s];
      end;
   end;

begin
   for i:=1 to m do mrowki[i]:=i;
   for i:=1 to m do droga[i]:=0;

   fillchar(drzewo,sizeof(drzewo),0);

   for i:=1 to m do drzewo[p[i],2]:=i;

   for i:=1 to m do pozycja[i]:=p[i];

   for i:=1 to m do spotkania[i]:=0;
   j:=m;

   while j>0 do begin
      for i:=1 to j do begin
         nr:=mrowki[i];
         p0:=pozycja[nr];
         p1:=dd[p0];

         if (drzewo[p1,2]=0) then begin
            inc(droga[nr]);
            drzewo[p1,1]:=droga[nr];
            drzewo[p1,2]:=nr;
            pozycja[nr]:=p1;
            {po dojsciu do biedronki mrowka staje w miejscu}
            if (p1=biedronka) then begin
              mrowki[i]:=0;
              inc(ile[nr]);
            end;
         end else begin
            spotkania[nr]:=drzewo[p1,2];
            if (drzewo[p1,1]<droga[nr]) then droga[nr]:=drzewo[p1,1];
            mrowki[i]:=0; {mrowka stop}
         end;
      end;

      {usuwanie z tablicy mrowki wpisow=0}
      tmp:=0;
      for i:=1 to j do if (mrowki[i]<>0) then begin
         inc(tmp);
         mrowki[tmp]:=mrowki[i];
      end;
      j:=tmp;
   end;

   {obliczanie kolejnosci}
   for i:=1 to m do kolejnosc[i]:=0;
   for i:=1 to m do if (kolejnosc[i]=0) then PoprawDroge(i);

   {i przesunac kazda mrowke o droga[i]}
   for i:=1 to m do begin
      p0:=p[i];
      z[p0]:=0;
      for j:=1 to droga[i] do p0:=dd[p0];
      z[p0]:=i;
      p[i]:=p0;
   end;
end;

procedure PoprawDrzewo(v : integer);
var
   tmp   : integer;
   poprz : integer;
begin
   poprz:=0;
   while (v<>0) do begin
      tmp:=dd[v];
      dd[v]:=poprz;
      poprz:=v;
      v:=tmp;
   end;
end;

procedure Rozwiazanie;
var
   i : integer;
   j : integer;
begin
{   Writeln('rozwiazanie');}

   fillchar(ile,sizeof(ile),0);
   fillchar(z,sizeof(z),0);
   for i:=1 to m do z[p[i]]:=i;

   readln(f,l);
   PrzygotujDrzewo(1);
   for i:=1 to l do begin
      readln(f,biedronka);
{      Writeln('biedronka=',biedronka);}

      if (z[biedronka]>0) then begin
         inc(ile[z[biedronka]]);
         continue;
      end;

      {trzeba przerobic drzewo tak by korzeniem byl wierzch. 'biedronka'}
{      Writeln('przygotowanie drzewa');      }
      j:=dd[biedronka];
      if (j<>0) then
         PoprawDrzewo(biedronka);

{      Writeln('symulacja');}

      SymulujPogon;

   end;
   close(f);
end; { Rozwiazanie }

procedure ZapiszWynik;
var
   i   : integer;
begin
{
   odp:=0;
   for i:=1 to m do if (ile[i]>odp) then odp:=ile[i];
}
   Assign(f,f_out);
   rewrite(f);
   for i:=1 to m do Writeln(f,p[i],' ',ile[i]);
   close(f);
end;

begin
   WczytajDrzewo;
   Rozwiazanie;
   ZapiszWynik;
end.

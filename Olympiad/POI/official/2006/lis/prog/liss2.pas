(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LIS (Listonosz)                                *
 *   Plik:                liss2.pas                                      *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Idea jest zablizona do liss1.cpp - trzyma      *
 *                        listy sciezek                                  *
 *                                                                       *
 *************************************************************************)

program LustracjaListonosza;

var kraw: array[0..200000,0..1] of longint; {posortowane krawedzie}
    i,j,n,m,l_sciezek,dl,a,b,popr_kraw,akt_kraw: longint;
    st_wch, st_wych: array[1..50000] of longint; {stopnie wychodzace i wchodzace wierzcholkow}
    start_kraw,gdzie_kraw: array[1..50001] of longint; {gdzie sie zaczynaja krawedzie wychodzace z kolejnych wierzcholkow w tablicy kraw}
                                                       {oraz gdzie aktualnie jestesmy przy szukaniu cyklu eulera}
    nast,popr: array[0..200000] of longint; {nastepna / poprzednia krawedz w sciezce w tablicy kraw}
    stos: array[0..200000] of longint; {stos krawedzi w cyklu eulera}
    stoscnt: longint;

{Porownanie krawedzi (a,b) i (c,d), do sortowania i do szukania}
function por_kraw(a,b,c,d: longint): longint;
begin
  if a < c then por_kraw := -1
  else if a > c then por_kraw := 1
  else if b < d then por_kraw := -1
  else if b > d then por_kraw := 1
  else por_kraw := 0;
end;

{Zamienia dwie krawedzie w kraw}
procedure zamien_kraw(i,j:longint);
var a,b:longint;
begin
  a := kraw[i,0]; b:= kraw[i,1];
  kraw[i,0] := kraw[j,0]; kraw[i,1] := kraw[j,1];
  kraw[j,0] := a; kraw[j,1] := b;
end;

{Qsort krawedzi}
procedure qsort(p,k:longint);
var a,b,c:longint;
begin
  if p + 1 < k then begin
    c := p + random(k-p);
    zamien_kraw(p,c);
    a := p + 1;
    b := k - 1;
    while a <= b do begin
      if por_kraw(kraw[a,0],kraw[a,1],kraw[p,0],kraw[p,1]) <= 0 then begin
          if por_kraw(kraw[b,0],kraw[b,1],kraw[p,0],kraw[p,1]) >= 0 then 
            dec(b);
          inc(a);
      end else begin
        if por_kraw(kraw[b,0],kraw[b,1],kraw[p,0],kraw[p,1]) >= 0 then
          dec(b)
        else begin
          zamien_kraw(a,b);
          inc(a);
          dec(b);
        end;
      end;
    end;
    zamien_kraw(p,b);
    qsort(p,b);
    qsort(b+1,k);
  end;
end;

{Szuka krawedzi w tablicy kraw}
function szukaj(p,k,a,b:longint):longint;
var wynik:longint;
begin
  wynik := por_kraw(a,b,kraw[(p+k) div 2,0],kraw[(p+k) div 2,1]);
  if wynik = 0 then 
    szukaj := (p+k) div 2
  else if p + 1 >= k then 
    szukaj := -1
  else if wynik < 0 then
    szukaj := szukaj(p,(p+k) div 2, a, b)
  else
    szukaj := szukaj(((p+k) div 2) + 1, k, a, b);
end;

{Dodaje krawedz na stos}
procedure nastos(i:longint);
begin
  stos[stoscnt] := i;
  inc(stoscnt);
end;

{Szuka cyklu Eulera rekurencyjnie}
procedure cykluj(wie:longint);
var i,j: longint;
begin
  while gdzie_kraw[wie] < start_kraw[wie+1] do begin
    i := gdzie_kraw[wie];
    inc(gdzie_kraw[wie]);
    if popr[i] = -1 then begin
      j := i;
      while nast[j] >= 0 do j := nast[j];
      cykluj(kraw[j,1]);
      while j >= 0 do begin
        nastos(j);
        j := popr[j];
      end;
    end;
  end;
end;

begin
  {Wczytujemy graf}
  readln(n,m);
  {Przy okazji inicjacja st_wych, st_wch, popr i nast}
  for i:=1 to n do begin
    st_wych[i] := 0;
    st_wch[i] := 0;
  end;
  for i:=0 to m-1 do begin
    readln(kraw[i,0],kraw[i,1]);
    inc(st_wch[kraw[i,1]]);
    inc(st_wych[kraw[i,0]]);
    nast[i] := -1;
    popr[i] := -1;
  end;
  {Sprawdzamy warunek stopien wchodzacy = stopien wychodzacy }
  for i:=1 to n do
    if st_wch[i] <> st_wych[i] then begin
      writeln('NIE');
      exit;
    end;
  {Sortujemy krawedzie}
  qsort(0,m);
  {Tworzymy tablice start_kraw}
  start_kraw[1] := 0;
  gdzie_kraw[1] := 0;
  j := 0;
  for i:=1 to n do begin
    while (j < m) and (kraw[j,0] = i) do 
      inc(j);
    start_kraw[i+1] := j;
    gdzie_kraw[i+1] := j;
  end;
  {Czytamy sciezki i uzupelniamy tablice nast i popr}
  readln(l_sciezek);
  while l_sciezek > 0 do begin
    dec(l_sciezek);
    read(dl);
    read(a);
    read(b);
    popr_kraw := szukaj(0,m,a,b);
    if popr_kraw = -1 then begin
      writeln('NIE');
      exit;
    end;
    a := b;
    for i := 3 to dl do begin
      read(b);
      akt_kraw := szukaj(0, m, a, b);
      if akt_kraw = -1 then begin
        writeln('NIE');
        exit;
      end;
      { Czy wlasnie nie rozdwoila sie sciezka? }
      if ((nast[popr_kraw] >= 0) and (nast[popr_kraw] <> akt_kraw)) or
         ((popr[akt_kraw] >= 0) and (popr[akt_kraw] <> popr_kraw)) then begin
         writeln('NIE');
         exit;
       end;
       nast[popr_kraw] := akt_kraw;
       popr[akt_kraw] := popr_kraw;
       popr_kraw := akt_kraw;
       a := b;
    end;
  end;
  {No i szukamy rekurencyjnie cyklu eulera, jesli nie ma wszystkich krawedzi (czyli jest cykl) to zle}
  stoscnt := 0;
  cykluj(1);
  if stoscnt <> m then begin
    writeln('NIE');
    exit;
  end;
  writeln('TAK');
  writeln(1);
  for i:=stoscnt-1 downto 0 do
    writeln(kraw[stos[i],1]);
end.

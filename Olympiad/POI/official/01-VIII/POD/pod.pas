{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: PODRÓ¯                                         *}
{*   Plik:                POD.PAS                                        *}
{*   Autor:               MARCIN STEFANIAK                               *}
{*************************************************************************}

{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+}
{$M 16384,0,655360}

program Podroze;

const HOUR  = 60;       {ile minut w godzinie}
      MAX_N = 1000;     {max. ile stacji}
      MAX_K = 2000;     {max. ile linii}
      MAX_S = MAX_N;    {max. ile przystankow na linii}
      MAX_P = 4000;     {max. w sumie przystankow}
      MAX_T = 240;      {max. czas przejazdu miedzy przystankami}

      MAX_TT = 24*HOUR; {maxymalny czas trwania podrozy}

type odjazd = record
                skad  : integer;
                dokad : integer;
                cz_p  : byte;       {czas_przejadu}
                go_o  : byte;       {jedna z godzin odjazdu}
                czest : byte;       {czestotliwosc kursowania}
              end;

    TRozklad = array[1 .. 2*MAX_P] of odjazd;
    PRozklad = ^TRozklad;

var l_linii: integer; {liczba linii komunikacyjnych}
    n:       integer; {liczba wszystkich stacji w sieci}

    stac_pocz, stac_kon  : integer; {pocz. i koncowe stacje przejazdu}
    godz_start, min_start: integer; {godzina i minuty startu}

    czest : integer;

    {numery stacji oraz czasy przejazdu - pomocnicze przy wczytywaniu}
    nr_stacji, czas_przej : array[1 .. MAX_S] of integer;

    rozklad,r2 : PRozklad;                      { tablica odjazdow }
    l_roz      : integer;                       { ile w rozkladzie }

    ix_roz     : array[0 .. MAX_N+1] of integer;  { indeks rozkladow }


procedure wstaw_odjazd(skad, dokad, cz_przejazdu, go_odjazdu, czest : integer);

begin
  inc(l_roz);
  rozklad^[l_roz].skad := skad;
  rozklad^[l_roz].dokad := dokad;
  rozklad^[l_roz].cz_p := cz_przejazdu;
  rozklad^[l_roz].go_o := go_odjazdu;
  rozklad^[l_roz].czest := czest;
end;

procedure sortuj_rozklad;

var i, j: integer;
begin

  fillchar(ix_roz, sizeof(ix_roz), 0);
  for i := 1 to l_roz do inc(ix_roz[rozklad^[i].skad]);
  for j := 1 to n+1 do inc(ix_roz[j], ix_roz[j-1]);
  New(r2);
  for i := 1 to l_roz do begin
    j := rozklad^[i].skad;
    r2^[ix_roz[j]] := rozklad^[i];
    dec(ix_roz[j]);
  end;

  { dispose(rozklad); }
  rozklad := r2;
end;

procedure Wczytaj;

var f: text;
    i, j, k, t: integer;

    nr_linii:      integer; {numer linii}
    liczba_stacji: integer; {liczba stacji w danej linii}
    czest:         integer; {czestotliwosc kursowania pociagow}

begin
(*  writeln;*)
  assign(f, 'pod.in'); reset(f);

  readln(f, n, l_linii, stac_pocz, stac_kon, godz_start, min_start);

  {inicjalizacja}

  New(rozklad);
  l_roz := 0;

  for i := 1 to l_linii do begin {wczytanie danych}
    nr_linii := i;
    readln(f, liczba_stacji, czest);

    for j := 1 to liczba_stacji do {czytanie numerow stacji}
      read(f, nr_stacji[j]);
    readln(f);

    for k := 1 to liczba_stacji - 1 do {czytanie czasow przejazdu}
      read(f, czas_przej[k]);
    readln(f);

    {wyznaczanie i wpisanie godz_odj}
    t := 0;
    for k := 1 to liczba_stacji-1 do begin {trasa w jedna strone}
      wstaw_odjazd(nr_stacji[k], nr_stacji[k + 1],
                   czas_przej[k], t, czest);
      t := (t + czas_przej[k]) mod 60;
    end;

    t := 0;
    for k := liczba_stacji downto 2 do begin {trasa w druga strone}
      wstaw_odjazd(nr_stacji[k], nr_stacji[k - 1],
                   czas_przej[k - 1], t, czest);
      {TW 2001.01.20 zmiana z czas_przej[k] na czas_przej[k-1]}
      t := (t + czas_przej[k-1]) mod 60;
    end;

  end;

  close(f);

end;


function czas_przejazdu(nr_odjazdu, godz_pocz: integer) : integer; {

  zwraca czas przejazdu polaczeniem rozklad^[nr_odjazdu],
  o godzinie poczatkowej godz_pocz
  (lacznie z ewentualnym czekaniem na stacji poczatkowej)
}
begin
  with rozklad^[nr_odjazdu] do begin
    czas_przejazdu := ((HOUR + go_o - godz_pocz) mod czest) + cz_p;
  end;
end;


procedure Solution(g, m: integer);
var f:text;
begin
  assign(f, 'pod.out');
  rewrite(f);
  writeln(f,g,' ',m);
  close(f);
end;

var D:     array[1 .. MAX_N] of integer; {czas w minutach od zrodla}
    ustal: array[1 .. MAX_N] of boolean; {= true oznacza, ze najkrotszy
                                        czas dla stacji zostal ustalony}
    Sk   :  array[1..MAX_N] of integer; {do wyznaczania sciezki}

procedure Dijkstra;

var    i, j, ii, jj, kk, t0, t, m: integer;

begin
  {inicjalizacja}
  for i := 1 to n do begin
    D[i] := maxint;
    ustal[i] := false;
  end;

  D[stac_pocz] := 0;        {czas dojazdu do zrodla = 0}

  for ii := 1 to n do begin {dla wszystkich wierzcholkow}

    t := maxint; m := 0; {szukanie minimum wsrod D[.]}
    for jj := 1 to n do
      if ustal[jj] = false then
        if D[jj] < t then begin
          t := D[jj];
          m := jj;
        end;

    if t > MAX_TT then begin
      { nie znaleziono minimum, albo juz przekroczylismy 24h podrozy }
      writeln('blad - koniec!'); { nie ma szukanej drogi miedzy startem a meta !!! }
      break;
    end;
(*    write('[',m,']');*)

    ustal[m] := true; {minimum w D[ind]}

    if m = stac_kon then begin
      t := godz_start * 60 + min_start + D[m];
(*      writeln('Zadanie rozwiazano!! ');
      writeln('start: ', godz_start:0, ' ', min_start:0,
              ' cel: ', (t div 60) mod 24, ' ', t mod 60,
              ' (pocz: ', stac_pocz:0, ' kon: ', stac_kon:0,')',
              ' ii =', ii);

      { wypisywanie sciezki }
      write('{');
      i := m; while i<>stac_pocz do begin
        write(i,'<-');
        i := Sk[i];
      end;
      writeln(i,'}');
*)
      Solution((t div 60) mod 24, t mod 60);
      break;
    end;

    t0 := (D[m] + min_start) mod HOUR; {chwila w ktorej docieramy do m }

    for kk := ix_roz[m]+1 to ix_roz[m+1] do
      with rozklad^[kk] do begin

        (*if skad <> m then writeln('error!');*)

        if not ustal[dokad] then begin

          { czas przyjazdu do nastepnej stacji polaczeniem kk }
          t := D[m] + integer((HOUR + go_o - t0) mod czest) + integer(cz_p);

          if t < D[dokad] then begin
            D[dokad] := t;
            Sk[dokad] := m;
          end;

        end; {if}
      end; {with rozklad^[kk]}

  end; {ii}

end;


begin {program glowny}

  Wczytaj;

  sortuj_rozklad;

  Dijkstra;

end.


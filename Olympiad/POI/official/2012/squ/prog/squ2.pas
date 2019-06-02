(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^3 log n)                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

program Squarki;

const
    MAXN = 300;
    LEAF = 65536;
    MAXV = 100000001;

var
    pary: array[0..MAXN*MAXN] of longint; //masy par kwarkow
    a: array[0..MAXN] of longint; //masy pojedynczych kwarkow
    wynik: array[0..MAXN, 0..MAXN] of longint; //tablica wynikow
    ilewynik: longint; //ilosc wynikow

    n, ilepar: longint; //ilosc kwarkow i par

    oczekiwane_wartosc: array[0..LEAF*2] of longint; //drzewo oczekiwanych mas
    oczekiwane_ilosc: array[0..LEAF*2] of longint; //drzewo oczekiwanych mas

    pomoc: array[0..MAXN*MAXN] of longint;

    i, j, l: longint; //petle
    znalezione: longint;
    ok: boolean;

function max(a, b: longint): longint;
begin
  if(a > b) then max := a
    else max := b;
end;

function min(a, b: longint): longint;
begin
  if(a < b) then min := a
    else min := b;
end;

procedure inicjalizuj();
var
    i: longint;
begin
  for i := 0 to (ilepar - 1) do begin
    oczekiwane_wartosc[LEAF + i] := pary[i];
    oczekiwane_ilosc[LEAF + i] := 0;
    end;
  for i := ilepar to (LEAF - 1) do begin
    oczekiwane_wartosc[LEAF + i] := MAXV;
    oczekiwane_ilosc[LEAF + i] := -2;
    end;
  for i := LEAF - 1 downto 1 do begin
    oczekiwane_wartosc[i] := max(oczekiwane_wartosc[i * 2], oczekiwane_wartosc[i * 2 + 1]);
    oczekiwane_ilosc[i] := 0;
    end;
end;

function znajdz(klucz: longint): longint;
var
  ind: longint;
begin
    ind := 1;
  while(ind < LEAF) do begin
    ind := ind * 2;
    if(oczekiwane_wartosc[ind] < klucz) then inc(ind);
    end;
  if(oczekiwane_wartosc[ind] <> klucz) then znajdz := -1
    else znajdz := ind;
end;

procedure zwieksz(klucz: longint);
var
    ind: longint;
begin
  ind := znajdz(klucz);
  if(ind > 0) then inc(oczekiwane_ilosc[ind])
end;

procedure zmniejsz(klucz: longint);
var
    ind: longint;
begin
  ind := znajdz(klucz);
  if(ind > 0) then dec(oczekiwane_ilosc[ind])
end;

function ile(klucz: longint): longint;
var
    ind: longint;
begin
  ind := znajdz(klucz);
  if(ind > 0) then ile := oczekiwane_ilosc[ind]
    else ile := ind;
end;

procedure polacz(start, srod, stop: longint);
var
    i, j: longint;
    akt: longint;
begin
  i := start;
    j := srod + 1;
    akt := i;
  while (i <= srod) or (j <= stop) do begin
    if(i <= srod) and (j <= stop) then begin
      if(pary[i] < pary[j]) then begin
        pomoc[akt] := pary[i];
        inc(i)
      end else begin
        pomoc[akt] := pary[j];
        inc(j);
      end
    end else begin
            if(i <= srod) then begin
          pomoc[akt] := pary[i];
          inc(i)
        end else begin
          pomoc[akt] := pary[j];
          inc(j)
            end;
        end;
    inc(akt);
    end;
  for i := start to stop do begin
        pary[i] := pomoc[i];
    end;
end;

procedure sortuj(start, stop: longint);//sortowanie przez scalanie
var
    ile: longint;
    srod: longint;
begin
  ile := stop - start + 1;
  if(ile >= 2) then begin
    srod := (start + stop) div 2;
    sortuj(start, srod);
    sortuj(srod + 1, stop);
    polacz(start, srod, stop);
    end;
end;
  
begin
    readln(n); //wczytujemy dane
    ilepar := (n * (n - 1)) div 2;
  for i := 0 to (ilepar - 1) do begin
    read(pary[i]); //wczytywanie par
    end;
    ilewynik := 0;
  sortuj(0, ilepar - 1);
  for i := 2 to (n - 1) do begin //iteracja po mozliwych masach a2+a3
    a[0] := pary[0] + pary[1] - pary[i]; //obliczanie a1
    if(a[0] mod 2 = 0) and (a[0] >= 0) and ((i <= 2) or (pary[i] <> pary[i - 1])) then begin
            a[0] := a[0] div 2;
            a[1] := pary[0] - a[0]; //a2
            a[2] := pary[1] - a[0]; //i a3
            //inicjalizacja oczekiwanych dodawanie do nich a1+a2, a1+a3 i a2+a3
            inicjalizuj();
            zwieksz(a[0] + a[1]);
            zwieksz(a[0] + a[2]);
            zwieksz(a[1] + a[2]);
            znalezione := 3;
            ok := True;
            for j := 0 to (ilepar - 1) do begin //przegladanie par
                if(ile(pary[j]) > 0) then begin
                    zmniejsz(pary[j]) //oczekiwana
                end else begin //nieoczekiwana, czyli masa nowego kwarka
                    if(znalezione >= n) then begin //za duzo kwarkow
                        ok := False
                    end else begin //dodanie nowego kwarka
                        a[znalezione] := pary[j] - a[0];
                        for l := 1 to (znalezione - 1) do zwieksz(a[l] + a[znalezione]);
                        inc(znalezione);
                    end;
                end;
            end;
            if(znalezione = n) and (ok) then begin //jesli poszlo ok
                for j := 1 to (n - 1) do begin
                    if (a[j] = a[j - 1]) then ok := False;
                end;
                if ok then begin
                    for j := 0 to (n - 1) do begin //dodajemy wynik do tablicy wynikow
                        wynik[ilewynik][j] := a[j];
                    end;
                    inc(ilewynik);
                end;
            end;
        end;
    end;
  writeln(ilewynik); //wypisanie wyniku
  for i := 0 to (ilewynik - 1) do begin
    for j := 0 to (n - 1) do begin
      write(wynik[i][j]);
            write(' ');
        end;
    writeln();
    end;
end.

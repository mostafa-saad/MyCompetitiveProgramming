{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw10.pas                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log z), czyli zachlanne pobieranie od   *}
{*            najwiekszego pojemnika, na wlasnych listach, z             *}
{*            zapamietywaniem gdzie wsadzilismy najwieksze odwazniki     *}
{*                                                                       *}
{*************************************************************************}
program odw5p;
var n, m, k:longint;
    wartosci, licznosc, przelicznik: array[0..31] of longint;

procedure wczytaj_odwazniki;
var wart, ile: array[0..31] of longint;
    i, logarytm, a, b: longint;
begin
    for i:=0 to 31 do begin
        ile[i] := 0;
        wart[i] := -1;
    end;
    for i:=0 to m-1 do begin
        read(a);
        b := a; logarytm := 0;
        if (b AND $ffff0000) <> 0 then begin
            b := b shr 16;
            logarytm := logarytm + 16;
        end;
        if (b AND $ff00) <> 0 then begin
            b := b shr 8;
            logarytm := logarytm + 8;
        end;
        if (b AND $f0) <> 0 then begin
            b := b shr 4;
            logarytm := logarytm + 4;
        end;
        if (b AND $c) <> 0 then begin
            b := b shr 2;
            logarytm := logarytm + 2;
        end;
        if (b AND $2) <> 0 then begin
            b := b shr 1;
            logarytm := logarytm + 1;
        end;
        wart[logarytm] := a;
        inc(ile[logarytm]);
    end;
    for i:=0 to 31 do if wart[i] >= 0 then begin
        wartosci[k] := wart[i];
        licznosc[k] := ile[i];
        inc(k);
    end;
    przelicznik[0] := wartosci[0];
    for i:=1 to k-1 do 
        przelicznik[i] := wartosci[i] div wartosci[i-1];
end;


var poj, gdzie, waga, pojemniki, lista, plista: array[0..99999] of longint;
    ostlisty, poczatki, licz: array[0..31] of longint;
    nk, wynik: longint;

function kubelek_pojemnika(najw, wlk:longint):longint;
var po, ko, c : longint;
begin
    po := 0; ko := najw;
    while po < ko do begin
        c := (po + ko + 1) div 2;
        if wlk < wartosci[c] then ko := c-1
        else po := c;
    end;
    kubelek_pojemnika := po;
end;

procedure probuj;
var i, j, ostatnia, nr, nnr, numer:longint;
begin
    for i:=0 to k-1 do licz[i] := licznosc[i];
    nk := k; wynik := 0;
    ostatnia := m-1;
    for i := 0 to nk-1 do begin
        poczatki[i] := -i-1;
        ostlisty[i] := -i-1;
    end;
    for i:=0 to n-1 do if pojemniki[i] > 0 then begin
         nr := kubelek_pojemnika(nk-1, pojemniki[i]);
         if poczatki[nr] < 0 then ostlisty[nr] := i
         else plista[poczatki[nr]] := i;
         lista[i] := poczatki[nr];
         plista[i] := -1-nr;
         poczatki[nr] := i;
         poj[i] := pojemniki[i];
    end;
    numer := m;
    for i := nk-1 downto 0 do begin
        while licz[i] > 0 do begin
            dec(licz[i]);
            dec(numer);
            waga[numer] := wartosci[i];
            if poczatki[i] < 0 then begin
                while (ostatnia > numer) and (gdzie[ostatnia] = -1) do dec(ostatnia);
                if ostatnia = numer then gdzie[numer] := -1
                else begin
                    gdzie[numer] := gdzie[ostatnia];
                    nr := gdzie[numer];
                    gdzie[ostatnia] := -1;
                    if poj[nr] <> 0 then begin
                        if lista[nr] >= 0 then plista[lista[nr]] := plista[nr]
                        else ostlisty[-lista[nr]-1] := plista[nr];
                        if plista[nr] >= 0 then lista[plista[nr]] := lista[nr]
                        else poczatki[-plista[nr]-1] := lista[nr];
                    end;
                    poj[nr] := poj[nr] + waga[ostatnia] - waga[numer];
                    if poj[nr] > 0 then begin
                        nnr := kubelek_pojemnika(i, poj[nr]);
                        if poczatki[nnr] = -1 then ostlisty[nnr] := nr
                        else plista[poczatki[nnr]] := nr;
                        lista[nr] := poczatki[nnr];
                        plista[nr] := -1-nnr;
                        poczatki[nnr] := nr;
                    end;
                end;
             end else begin
                 inc(wynik);
                 nr := poczatki[i];
                 gdzie[numer] := nr;
                 poczatki[i] := lista[nr];
                 if poczatki[i] >= 0 then plista[poczatki[i]] := -1-nr
                 else begin
                    poczatki[i] := -1-i;
                    ostlisty[i] := -1-i;
                 end;
                 poj[nr] := poj[nr] - wartosci[i];
                 if poj[nr] > 0 then begin
                    nnr := kubelek_pojemnika(i, poj[nr]);
                    if poczatki[nnr] = -1 then ostlisty[nnr] := nr
                    else plista[poczatki[nnr]] := nr;
                    lista[nr] := poczatki[nnr];
                    plista[nr] := -1-nnr;
                    poczatki[nnr] := nr;
                 end;
             end;
        end;
        if (i > 0) and (poczatki[i] >= 0) then begin
            if poczatki[i-1] < 0 then ostlisty[i-1] := ostlisty[i]
            else plista[poczatki[i-1]] := ostlisty[i];
            lista[ostlisty[i]] := poczatki[i-1];
            poczatki[i-1] := poczatki[i];
            plista[poczatki[i-1]] := -1-(i-1);
        end;
    end;
end;

var i:longint;
begin
    readln(n, m);
    for i := 0 to n-1 do read(pojemniki[i]);
    wczytaj_odwazniki;
    for i := 0 to n-1 do pojemniki[i] := pojemniki[i] div wartosci[0];
    for i := k-1 downto 0 do wartosci[i] := wartosci[i] div wartosci[0];
    probuj;
    writeln(wynik);
end.
